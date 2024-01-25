#ifndef UI_INSTANCEWINDOW_H_
#define UI_INSTANCEWINDOW_H_

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QPushButton>
#include <QScrollBar>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <qlayoutitem.h>
#include <QCloseEvent>

#include "../LaunchController.h"
#include "../Launch/LaunchTask.h"

#include "Pages/BasePageContainer.h"

#include "../QObjectPtr.h"

#include "../Application.h"

#include "Dialogs/CustomMessageBox.h"
#include "Dialogs/ProgressDialog.h"
#include "Widgets/PageContainer.h"

#include "InstancePageProvider.h"

//#include "Icons/IconList.h"

class InstanceWindow : public QMainWindow, public BasePageContainer
{
	Q_OBJECT

private:
	shared_qobject_ptr<LaunchTask> m_proc;
	InstancePtr m_instance;
	bool m_doNotSave = false;
	PageContainer* m_container = nullptr;
	QPushButton* m_closeButton = nullptr;
	QPushButton* m_killButton = nullptr;
	QPushButton* m_launchOfflineButton = nullptr;

public:
	explicit InstanceWindow(InstancePtr proc, QWidget* parent = 0);
	virtual ~InstanceWindow();

	bool selectPage(QString pageId) override;
	void refreshContainer() override;

	QString instanceId();

	// save all settings and changes (prepare for launch)
	bool saveAll();

	// request closing the window (from a page)
	bool requestClose() override;

signals:
	void isClosing();

private slots:
	void on_closeButton_clicked();
	void on_btnKillMinecraft_clicked();
	void on_btnLaunchMinecraftOffline_clicked();

	void on_InstanceLaunchTask_changed(shared_qobject_ptr<LaunchTask> proc);
	void on_RunningState_changed(bool running);
	void on_instanceStatusChanged(BaseInstance::Status, BaseInstance::Status newStatus);

protected:
	void closeEvent(QCloseEvent*) override;

private:
	void updateLaunchButtons();
};

#endif // !UI_INSTANCEWINDOW_H_