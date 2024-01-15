#ifndef DIALOGS_CUSTOMMESSAGEBOX_H_
#define DIALOGS_CUSTOMMESSAGEBOX_H_

#include <QMessageBox>

#include <memory>

namespace CustomMessageBox
{
    std::shared_ptr<QMessageBox> selectable(QWidget* parent, const QString& title, const QString& text,
        QMessageBox::Icon icon = QMessageBox::NoIcon,
        QMessageBox::StandardButtons buttons = QMessageBox::Ok,
        QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
}

#endif // !DIALOGS_CUSTOMMESSAGEBOX_H_
