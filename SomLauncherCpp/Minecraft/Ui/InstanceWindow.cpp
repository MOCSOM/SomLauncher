#include "InstanceWindow.h"

InstanceWindow::InstanceWindow(InstancePtr proc, QWidget* parent)
	: QMainWindow(parent), m_instance(proc)
{
	setAttribute(Qt::WA_DeleteOnClose);

	//auto icon = APPLICATION->icons()->getIcon(m_instance->iconKey());
	QString windowTitle = tr("Console window for ") + m_instance->name();

	// Set window properties
	{
		//setWindowIcon(icon);
		setWindowTitle(windowTitle);
	}

	// Add page container
	{
		auto provider = std::make_shared<InstancePageProvider>(m_instance);
		m_container = new PageContainer(provider.get(), "console", this);
		m_container->setParentContainer(this);
		setCentralWidget(m_container);
		setContentsMargins(0, 0, 0, 0);
	}

	// Add custom buttons to the page container layout.
	{
		auto horizontalLayout = new QHBoxLayout();
		horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
		horizontalLayout->setContentsMargins(6, -1, 6, -1);

		auto btnHelp = new QPushButton();
		btnHelp->setText(tr("Help"));
		horizontalLayout->addWidget(btnHelp);
		connect(btnHelp, SIGNAL(clicked(bool)), m_container, SLOT(help()));

		auto spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		horizontalLayout->addSpacerItem(spacer);

		m_killButton = new QPushButton();
		horizontalLayout->addWidget(m_killButton);
		connect(m_killButton, SIGNAL(clicked(bool)), SLOT(on_btnKillMinecraft_clicked()));

		m_launchOfflineButton = new QPushButton();
		horizontalLayout->addWidget(m_launchOfflineButton);
		m_launchOfflineButton->setText(tr("Launch Offline"));
		updateLaunchButtons();
		connect(m_launchOfflineButton, SIGNAL(clicked(bool)), SLOT(on_btnLaunchMinecraftOffline_clicked()));

		m_closeButton = new QPushButton();
		m_closeButton->setText(tr("Close"));
		horizontalLayout->addWidget(m_closeButton);
		connect(m_closeButton, SIGNAL(clicked(bool)), SLOT(on_closeButton_clicked()));

		m_container->addButtons(horizontalLayout);
	}

	// restore window state
	{
		auto base64State = APPLICATION->settings()->get("ConsoleWindowState").toByteArray();
		restoreState(QByteArray::fromBase64(base64State));
		auto base64Geometry = APPLICATION->settings()->get("ConsoleWindowGeometry").toByteArray();
		restoreGeometry(QByteArray::fromBase64(base64Geometry));
	}

	// set up instance and launch process recognition
	{
		auto launchTask = m_instance->getLaunchTask();
		on_InstanceLaunchTask_changed(launchTask);
		connect(m_instance.get(), &BaseInstance::launchTaskChanged, this, &InstanceWindow::on_InstanceLaunchTask_changed);
		connect(m_instance.get(), &BaseInstance::runningStatusChanged, this, &InstanceWindow::on_RunningState_changed);
	}

	// set up instance destruction detection
	{
		connect(m_instance.get(), &BaseInstance::statusChanged, this, &InstanceWindow::on_instanceStatusChanged);
	}
	show();
}
