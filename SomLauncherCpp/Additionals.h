#ifndef ADDITIONALS_H_
#define ADDITIONALS_H_

#include <initializer_list>
#include <cwchar>
#include <stdlib.h>     // for _countof
#include <errno.h>  // for return values
#include <cstring>

#include <list>
#include <string>

#include <filesystem>

#include <Windows.h>

#include <QFile>
#include <QTemporaryFile>
#include <QDataStream>
#include <QByteArray>
#include <QString>
#include <QList>
#include <QDir>

#include <iostream>


#define StrDogWA Additionals::String::strdogWA
#define StrDogW Additionals::String::strdogW
#define StrDogAW Additionals::String::strdogAW
#define StrDogA Additionals::String::strdogA
#define JoinW Additionals::Path::joinW
#define JoinA Additionals::Path::joinA

namespace Additionals 
{
	namespace file
	{
		class File : public QTemporaryFile
		{

		public:
			explicit File(QObject* parent = nullptr);

			File(const std::string& filename);
			File(const QString& filename);
			File(const Additionals::file::File& for_copy);
			~File() {};

			void Open();
			void Close();
		};
	}
	namespace ziparchives
	{
		class ZipArchive
		{
		private:
			QString file_name;

			QByteArray data;
			Additionals::file::File source_file;

			QDataStream data_stream;

			QList<Additionals::file::File> _entires;

		public:
			__declspec(property(get = _GetEntries)) QList<Additionals::file::File> entries;


		public:
			ZipArchive(const std::string& file_name);
			ZipArchive(const std::wstring& file_name);
			ZipArchive(const ZipArchive& for_copy);
			ZipArchive() = default;
			~ZipArchive();

			void ArchiveStream(const QString& sourceFilePath, QDataStream& data_stream);
			void ExtractFile(QDataStream& inStream, const QString& outputDir);
			void Open(const std::string& file_name);
			void Open(const std::wstring& file_name);
			void Close();

			static void ExtractFile(QFile& file_name, const std::string& outputDir);

			QList<Additionals::file::File> _GetEntries();

		};
	}

	namespace Convectors 
	{
		wchar_t* ConvertStringToWcharPtr(const std::string& str);
		std::string ConvertWcharPtrToString(const wchar_t* str);
		std::string ConvertWStringToString(const std::wstring& str);
		std::wstring ConvertWcharPtrToWstring(const wchar_t* str);
		std::unique_ptr<wchar_t[]> ConvertWstringToWcharPtr(const std::wstring& str);
	}

	namespace String 
	{
		/*wchar_t* strdogW(wchar_t* ref_str, wchar_t* str_to_add);
		wchar_t* strdogW(const wchar_t* ref_str, wchar_t* str_to_add);
		wchar_t* strdogW(wchar_t* ref_str, const wchar_t* str_to_add);*/
		wchar_t* strdogW(const wchar_t* ref_str, const wchar_t* str_to_add);

		wchar_t* strdogWA(const wchar_t* ref_str, const char* str_to_add);
		wchar_t* strdogAW(const char* ref_str, const wchar_t* str_to_add);
		wchar_t* strdogA(const char* ref_str, const char* str_to_add);

		wchar_t* strdogW(std::initializer_list<const wchar_t*> list);

		std::vector<std::string> split(const std::string& s, const char& seperator, const int& count = 0);
		std::vector<std::wstring> split(const std::wstring& s, const char& seperator, const int& count = 0);

		bool replace(std::string& str, const std::string& from, const std::string& to);
		bool replace(std::wstring& str, const std::wstring& from, const std::wstring& to);

		bool EndsWith(const std::string& str, const std::string& suffix);
		bool EndsWith(const std::wstring& str, const std::wstring& suffix);


		// trim from start (in place)
		static inline void ltrim(std::string& s);
		static inline void ltrim(std::string& s, const char& symbol);

		// trim from end (in place)
		static inline void rtrim(std::string& s);
		static inline void rtrim(std::string& s, const char& symbol);

		// trim from both ends (in place)
		static inline void trim(std::string& s);
		static inline void trim(std::string& s, const char& symbol);

		// trim from start (copying)
		static inline std::string ltrim_copy(std::string s);
		static inline std::string ltrim_copy(std::string s, const char& symbol);

		// trim from end (copying)
		static inline std::string rtrim_copy(std::string s);
		std::string rtrim_copy(std::string s, const char& symbol);

		// trim from both ends (copying)
		static inline std::string trim_copy(std::string s);
		static inline std::string trim_copy(std::string s, const char& symbol);
	}

	namespace Path 
	{
		wchar_t* joinW(std::initializer_list<const wchar_t*> list);
		wchar_t* joinA(std::initializer_list<const char*> list);
		std::vector<std::string> get_directories(const std::string& directory);
	}

	namespace TempFile 
	{
		wchar_t* get_tempdir();
		wchar_t* get_tempdir_SYSTEM();
		wchar_t* _get_default_tempdir();
	}
}


#endif // !ADDITIONALS_H_

