#ifndef MOCIOSTREAM_H_
#define MOCIOSTREAM_H_

#include <qplaintextedit.h>
#include <qsharedpointer.h>
#include <qlogging.h>

#include <iostream>
#include <string>
#include <streambuf>

#include <windows.h>
#include <cstring>

#include "../../../SomAdditionalsLib/Additionals.h"

void customHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

namespace moc
{
	class MocOStream : public std::ostream
	{
	private:
		class MocStreamBuf : public std::streambuf
		{
		private:
			QSharedPointer<QPlainTextEdit> plain_text_edit = nullptr;

		public:
			MocStreamBuf();

			void setQtPlainText(QSharedPointer<QPlainTextEdit> plain_text_edit);
			QSharedPointer<QPlainTextEdit> getQtPlainText();

		protected:
			virtual int_type overflow(int_type c);
		};

	public:
		MocOStream();
		MocOStream(QSharedPointer<QPlainTextEdit> plain_text_edit);
		void setQtPlainText(QSharedPointer<QPlainTextEdit> plain_text_edit);
		QSharedPointer<QPlainTextEdit> getQtPlainText();

	private:
		MocStreamBuf buffer;
	};

	class MocIStream : public std::istream
	{
	private:
		class MocStreamBuf : public std::streambuf
		{
		public:
			MocStreamBuf();

		protected:
			virtual int_type underflow();
		};

	public:
		MocIStream();

	private:
		MocStreamBuf buffer;
	};

	using SomLogger = MocOStream;
	//using SomLogger = QMessageLogger(static_cast<const char*>("C:\\Users\\alkor\\source\\repos\\SomLauncher\\SomLauncherCpp\\Moc\\Logger\\MocIOStream.h"), 67, static_cast<const char*>(__FUNCSIG__)).info();

	MocOStream& operator<<(MocOStream& out, LPCWSTR text);
}

#endif /*ARCHIVES_H_*/