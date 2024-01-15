#include "JavaChecker.h"

JavaChecker::JavaChecker(QObject* parent)
	: QObject(parent)
{
}

void JavaChecker::performCheck()
{
    QString checkerJar = std::filesystem::path(APPLICATION->getJarsPath(), std::filesystem::path("JavaCheck.jar")).u8string().c_str();

    QStringList args;

    this->process.reset(std::make_shared<QProcess>().get());
    if (this->m_args.size())
    {
        auto extraArgs = Commandline::splitArgs(this->m_args);
        args.append(extraArgs);
    }
    if (this->m_minMem != 0)
    {
        args << QString("-Xms%1m").arg(this->m_minMem);
    }
    if (this->m_maxMem != 0)
    {
        args << QString("-Xmx%1m").arg(this->m_maxMem);
    }
    if (this->m_permGen != 64)
    {
        args << QString("-XX:PermSize=%1m").arg(this->m_permGen);
    }

    args.append({ "-jar", checkerJar });
    this->process->setArguments(args);
    this->process->setProgram(this->m_path);
    this->process->setProcessChannelMode(QProcess::SeparateChannels);
    this->process->setProcessEnvironment(CleanEnviroment());
    qDebug() << "Running java checker: " + m_path + args.join(" ");;

    connect(this->process.get(), SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(finished(int, QProcess::ExitStatus)));
    connect(this->process.get(), SIGNAL(error(QProcess::ProcessError)), this, SLOT(error(QProcess::ProcessError)));
    connect(this->process.get(), SIGNAL(QProcess::readyReadStandardOutput()), this, SLOT(stdoutReady()));
    connect(this->process.get(), SIGNAL(QProcess::readyReadStandardError()), this, SLOT(stderrReady()));
    connect(&this->killTimer, SIGNAL(timeout()), SLOT(timeout()));
    this->killTimer.setSingleShot(true);
    this->killTimer.start(15000);
    this->process->start();
}

void JavaChecker::timeout()
{
    // NO MERCY. NO ABUSE.
    if (this->process)
    {
        qDebug() << "Java checker has been killed by timeout.";
        this->process->kill();
    }
}

void JavaChecker::finished(int exitcode, QProcess::ExitStatus status)
{
    this->killTimer.stop();
    QProcessPtr _process = this->process;
    this->process.reset();

    JavaCheckResult result;
    {
        result.path = m_path;
        result.id = m_id;
    }
    result.errorLog = this->m_stderr;
    result.outLog = this->m_stdout;
    qDebug() << "STDOUT" << this->m_stdout;
    qWarning() << "STDERR" << this->m_stderr;
    qDebug() << "Java checker finished with status " << status << " exit code " << exitcode;

    if (status == QProcess::CrashExit || exitcode == 1)
    {
        result.validity = JavaCheckResult::Validity::Errored;
        emit checkFinished(result);
        return;
    }

    bool success = true;

    QMap<QString, QString> results;
    QStringList lines = m_stdout.split("\n", Qt::SkipEmptyParts);
    for (QString line : lines)
    {
        line = line.trimmed();
        // NOTE: workaround for GH-4125, where garbage is getting printed into stdout on bedrock linux
        if (line.contains("/bedrock/strata")) 
        {
            continue;
        }

        auto parts = line.split('=', Qt::SkipEmptyParts);
        if (parts.size() != 2 || parts[0].isEmpty() || parts[1].isEmpty())
        {
            continue;
        }
        else
        {
            results.insert(parts[0], parts[1]);
        }
    }

    if (!results.contains("os.arch") || !results.contains("java.version") || !results.contains("java.vendor") || !success)
    {
        result.validity = JavaCheckResult::Validity::ReturnedInvalidData;
        emit checkFinished(result);
        return;
    }

    auto& os_arch = results["os.arch"];
    auto& java_version = results["java.version"];
    auto& java_vendor = results["java.vendor"];
    bool is_64 = os_arch == "x86_64" || os_arch == "amd64";


    result.validity = JavaCheckResult::Validity::Valid;
    result.is_64bit = is_64;
    result.mojangPlatform = is_64 ? "64" : "32";
    result.realPlatform = os_arch;
    result.javaVersion = java_version;
    result.javaVendor = java_vendor;
    qDebug() << "Java checker succeeded.";
    emit checkFinished(result);
}

void JavaChecker::error(QProcess::ProcessError err)
{
    if (err == QProcess::FailedToStart)
    {
        qDebug() << "Java checker has failed to start.";
        qDebug() << "Process environment:";
        qDebug() << this->process->environment();
        qDebug() << "Native environment:";
        qDebug() << QProcessEnvironment::systemEnvironment().toStringList();
        this->killTimer.stop();
        JavaCheckResult result;
        {
            result.path = this->m_path;
            result.id = this->m_id;
        }

        emit checkFinished(result);
        return;
    }
}

void JavaChecker::stdoutReady()
{
    QByteArray data = this->process->readAllStandardOutput();
    QString added = QString::fromLocal8Bit(data);
    added.remove('\r');
    this->m_stdout += added;
}

void JavaChecker::stderrReady()
{
    QByteArray data = this->process->readAllStandardError();
    QString added = QString::fromLocal8Bit(data);
    added.remove('\r');
    this->m_stderr += added;
}