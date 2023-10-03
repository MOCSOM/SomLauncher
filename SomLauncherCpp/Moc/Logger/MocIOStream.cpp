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
		std::cout.put(c);
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