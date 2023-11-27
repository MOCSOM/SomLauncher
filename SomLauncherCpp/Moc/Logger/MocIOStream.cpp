#include "MocIOStream.h"

int moc::MocIStream::MocStreamBuf::underflow()
{
	// Здесь можно реализовать чтение данных из своего источника
	// Например, из файла или другого источника данных
	// В этом примере используется стандартный поток ввода
	return std::cin.get();
}

moc::MocOStream::MocStreamBuf::MocStreamBuf()
{
	// Установка буфера по умолчанию
	setp(0, 0);
}

void moc::MocOStream::MocStreamBuf::setQtPlainText(QSharedPointer<QPlainTextEdit> plain_text_edit)
{
	this->plain_text_edit = plain_text_edit;
}

QSharedPointer<QPlainTextEdit> moc::MocOStream::MocStreamBuf::getQtPlainText()
{
	return this->plain_text_edit;
}

moc::MocIStream::MocStreamBuf::MocStreamBuf()
{
	// Установка буфера по умолчанию
	setg(0, 0, 0);
}

int moc::MocOStream::MocStreamBuf::overflow(int_type c)
{
	// Здесь можно реализовать вывод символа в свой вывод
	// Например, можно записать его в файл или передать другому месту
	// В этом примере просто выводим символ в стандартный поток вывода
	if (this->plain_text_edit != nullptr && c != EOF)
	{
		std::string char_input(1, static_cast<char>(c));
		this->plain_text_edit->setPlainText(char_input.c_str());
	}
	else if (c != EOF)
	{
		qInstallMessageHandler(customHandler);
		qInfo() << static_cast<char>(c);
		//std::cout.put(c);
	}
	return c;
}

moc::MocIStream::MocIStream()
	: std::istream(&buffer) {}

moc::MocOStream::MocOStream()
	: std::ostream(&buffer) {}

moc::MocOStream::MocOStream(QSharedPointer<QPlainTextEdit> plain_text_edit)
	: std::ostream(&buffer)
{
	moc::MocOStream::setQtPlainText(plain_text_edit);
}

void moc::MocOStream::setQtPlainText(QSharedPointer<QPlainTextEdit> plain_text_edit)
{
	this->buffer.setQtPlainText(plain_text_edit);
}

QSharedPointer<QPlainTextEdit> moc::MocOStream::getQtPlainText()
{
	return this->buffer.getQtPlainText();
}

moc::MocOStream& moc::operator<<(MocOStream& out, LPCWSTR text)
{
	std::string wstr_to_convert = Additionals::Convectors::ConvertLPCWSTRToString(text);
	out << wstr_to_convert;
	return out;
}

QDebug& moc::operator<<(QDebug& out, const LPCWSTR text)
{
	std::string wstr_to_convert = Additionals::Convectors::ConvertLPCWSTRToString(text);
	out << wstr_to_convert;
	return out;
}

void customHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
	QByteArray localMsg = msg.toLocal8Bit();
	const char* file = context.file ? context.file : "";
	const char* function = context.function ? context.function : "";

	QFile outFile("somlogs\\last_log.txt");
	outFile.open(QIODevice::WriteOnly | QIODevice::Append);

	QTextStream textStream(&outFile);

	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);

	switch (type)
	{
	case QtDebugMsg:
		std::fstream(stdout) << "[Debug]: " << localMsg.constData();
		textStream << "[" << now->tm_sec << ":" << now->tm_min << ":" << now->tm_hour << "]"
			<< " " << "[" << function << "\\" << "DEBUG]: " << localMsg.constData();
		break;
	case QtInfoMsg:
		std::fstream(stdout) << "[Info]: " << localMsg.constData();
		textStream << "[" << now->tm_sec << ":" << now->tm_min << ":" << now->tm_hour << "]"
			<< " " << "[" << function << "\\" << "INFO]: " << localMsg.constData();
		break;
	case QtWarningMsg:
		std::fstream(stdout) << "[Warning]: " << localMsg.constData() << std::endl;
		textStream << "[" << now->tm_sec << ":" << now->tm_min << ":" << now->tm_hour << "]"
			<< " " << "[" << function << "\\" << "WARNING]: " << localMsg.constData() << std::endl;
		break;
	case QtCriticalMsg:
		std::fstream(stdout) << "[Critical]: " << localMsg.constData() << std::endl;
		textStream << "[" << now->tm_sec << ":" << now->tm_min << ":" << now->tm_hour << "]"
			<< " " << "[" << function << "\\" << "CRITICAL]: " << localMsg.constData() << std::endl;
		break;
	case QtFatalMsg:
		std::fstream(stdout) << "[Fatal]: " << localMsg.constData() << std::endl;
		textStream << "[" << now->tm_sec << ":" << now->tm_min << ":" << now->tm_hour << "]"
			<< " " << "[" << function << "\\" << "FATAL]: " << localMsg.constData() << std::endl;
		break;
	}

	outFile.close();
}

QTextStream& std::endl(QTextStream& ostr)
{
	ostr << '\n';
	ostr.flush();
	return ostr;
}