#ifndef UPDATER_UPDATECONTROLLER_H_
#define UPDATER_UPDATECONTROLLER_H_

#include <QString>
#include <QList>
#include <QFile>
#include <QMessageBox>
#include <QApplication>
#include <QProcess>
#include <QDir>
#include <QSysInfo>
#include <QWidget>
#include <QLatin1String>

#include <thread>
#include <chrono>
#include <filesystem>

//#include <GoUpdate.h>
#include <LocalPeer.h>

// from <sys/stat.h>
#ifndef S_IRUSR
#define __S_IREAD 0400         /* Read by owner.  */
#define __S_IWRITE 0200        /* Write by owner.  */
#define __S_IEXEC 0100         /* Execute by owner.  */
#define S_IRUSR __S_IREAD      /* Read by owner.  */
#define S_IWUSR __S_IWRITE     /* Write by owner.  */
#define S_IXUSR __S_IEXEC      /* Execute by owner.  */

#define S_IRGRP (S_IRUSR >> 3) /* Read by group.  */
#define S_IWGRP (S_IWUSR >> 3) /* Write by group.  */
#define S_IXGRP (S_IXUSR >> 3) /* Execute by group.  */

#define S_IROTH (S_IRGRP >> 3) /* Read by others.  */
#define S_IWOTH (S_IWGRP >> 3) /* Write by others.  */
#define S_IXOTH (S_IXGRP >> 3) /* Execute by others.  */
#endif

#define LAUNCHER_NAME QString("SomLauncherCpp")

namespace GoUpdate
{

    struct Operation
    {
        static Operation CopyOp(QString from, QString to, int fmode = 0644)
        {
            return Operation{ OP_REPLACE, from, to, fmode };
        }
        static Operation DeleteOp(QString file)
        {
            return Operation{ OP_DELETE, QString(), file, 0644 };
        }

        // FIXME: for some types, some of the other fields are irrelevant!
        bool operator==(const Operation& u2) const
        {
            return type == u2.type &&
                source == u2.source &&
                destination == u2.destination &&
                destinationMode == u2.destinationMode;
        }

        //! Specifies the type of operation that this is.
        enum Type
        {
            OP_REPLACE,
            OP_DELETE,
        } type;

        //! The source file, if any
        QString source;

        //! The destination file.
        QString destination;

        //! The mode to change the destination file to.
        int destinationMode;
    };
    typedef QList<Operation> OperationList;
}

class UpdateController
{
public:
    UpdateController(QWidget* parent, const QString& root, const QString updateFilesDir, GoUpdate::OperationList operations);
    void installUpdates();

private:
    void fail();
    bool rollback();

private:
    QString m_root;
    QString m_updateFilesDir;
    GoUpdate::OperationList m_operations;
    QWidget* m_parent;

    struct BackupEntry
    {
        // path where we got the new file from
        QString update;
        // path of what is being actually updated
        QString original;
        // path where the backup of the updated file was placed
        QString backup;
    };
    QList <BackupEntry> m_replace_backups;
    QList <BackupEntry> m_delete_backups;
    enum Failure
    {
        Replace,
        Delete,
        Start,
        Nothing
    } m_failedOperationType = Nothing;
    QString m_failedFile;
};

#endif // !UPDATER_UPDATECONTROLLER_H_