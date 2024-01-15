#include "CustomMessageBox.h"

std::shared_ptr<QMessageBox> CustomMessageBox::selectable(QWidget* parent, const QString& title, const QString& text, QMessageBox::Icon icon, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
{
    std::shared_ptr<QMessageBox> messageBox = std::make_shared<QMessageBox>(parent);
    messageBox->setWindowTitle(title);
    messageBox->setText(text);
    messageBox->setStandardButtons(buttons);
    messageBox->setDefaultButton(defaultButton);
    messageBox->setTextInteractionFlags(Qt::TextSelectableByMouse);
    messageBox->setIcon(icon);
    messageBox->setTextInteractionFlags(Qt::TextBrowserInteraction);

    return messageBox;
}
