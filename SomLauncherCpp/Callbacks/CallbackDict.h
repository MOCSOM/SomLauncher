#ifndef CBD_H_     // equivalently, #if !defined HEADER_H_
#define CBD_H_

#include <qprogressbar.h>
#include <qcoreapplication.h>
#include <qlabel.h>

#include "../../../QObjects/SignalLabel.h"

#include <windows.h>
#include <tchar.h>

#include <iostream>
#include <memory>

#include <curl/curl.h>

#include "../../../Moc/Logger/MocIOStream.h"

#pragma comment(lib, "Urlmon.lib")

#define ProgressBarInConsole SomConsole::setloadbar

namespace SomConsole
{
	void setloadbar(unsigned curr_val, unsigned max_val, unsigned bar_width = 20);
}
namespace SomProgressBarr
{
	void set_prog_bar(unsigned curr_val, unsigned max_val,
		QProgressBar* progress_bar);
}

class CallbackNull : public IBindStatusCallback
{
public:
	CallbackNull() = default;
	~CallbackNull() = default;

public:
	void setQProgressBar(QProgressBar* progress_bar);
	void setQLabelProggress(SignalLabel* progress_label);
	void setCurl(CURL* curl);

	int progress_func(double TotalToDownload, double NowDownloaded,
		double TotalToUpload, double NowUploaded);

	void setProgress(size_t progress = -1, size_t progress_max = -1, size_t code = -1, const std::string& message = "");

	/// <summary>
	///
	/// </summary>
	/// <param name="ulProgress"></param>
	/// <param name="ulProgressMax"></param>
	/// <param name="ulStatusCode">- 6 для окончания загрузки</param>
	/// <param name="wszStatusText"></param>
	/// <returns></returns>
	STDMETHOD(OnProgress)(/* [in] */ ULONG ulProgress, /* [in] */ ULONG ulProgressMax, /* [in] */ ULONG ulStatusCode, /* [in] */ LPCWSTR wszStatusText)
	{
		return E_NOTIMPL;
	}

	// The rest  don't do anything...
	STDMETHOD(OnStartBinding)(/* [in] */ DWORD dwReserved,
		/* [in] */ IBinding __RPC_FAR* pib) {
		return E_NOTIMPL;
	}
	STDMETHOD(GetPriority)(/* [out] */ LONG __RPC_FAR* pnPriority) { return E_NOTIMPL; }
	STDMETHOD(OnLowResource)(/* [in] */ DWORD reserved) { return E_NOTIMPL; }
	STDMETHOD(OnStopBinding)(/* [in] */ HRESULT hresult,
		/* [unique][in] */ LPCWSTR szError) {
		return E_NOTIMPL;
	}
	STDMETHOD(GetBindInfo)(/* [out] */ DWORD __RPC_FAR* grfBINDF,
		/* [unique][out][in] */ BINDINFO __RPC_FAR* pbindinfo) {
		return E_NOTIMPL;
	}
	STDMETHOD(OnDataAvailable)(/* [in] */ DWORD grfBSCF,
		/* [in] */ DWORD dwSize, /* [in] */ FORMATETC __RPC_FAR* pformatetc,
		/* [in] */ STGMEDIUM __RPC_FAR* pstgmed) {
		return E_NOTIMPL;
	}
	STDMETHOD(OnObjectAvailable)(/* [in] */ REFIID riid,
		/* [iid_is][in] */ IUnknown __RPC_FAR* punk) {
		return E_NOTIMPL;
	}
	// IUnknown stuff
	STDMETHOD_(ULONG, AddRef)() { return 0; }
	STDMETHOD_(ULONG, Release)() { return 0; }
	STDMETHOD(QueryInterface)(/* [in] */ REFIID riid,
		/* [iid_is][out] */ void __RPC_FAR* __RPC_FAR* ppvObject) {
		return E_NOTIMPL;
	}
};

class CallbackDict : public CallbackNull
{
private:
	int m_percentLast = -1;
	QProgressBar* progress_bar = nullptr;
	SignalLabel* proggress_label = nullptr;
	CURL* curl = nullptr;

public:
	CallbackDict() = default;
	//CallbackDict(CallbackNull other) {}
	~CallbackDict() = default;

	void setQProgressBar(QProgressBar* progress_bar);
	void setQLabelProggress(SignalLabel* progress_label);
	void setCurl(CURL* curl);

	int progress_func(double TotalToDownload, double NowDownloaded,
		double TotalToUpload, double NowUploaded);

	void setProgress(size_t progress = -1, size_t progress_max = -1, size_t code = -1, const std::string& message = "");

	// This one is called by URLDownloadToFile
	STDMETHOD(OnProgress)(/* [in] */ ULONG ulProgress, /* [in] */ ULONG ulProgressMax, /* [in] */ ULONG ulStatusCode, /* [in] */ LPCWSTR wszStatusText) override;

	HRESULT setConsoleBar(ULONG& ulProgress, ULONG& ulProgressMax, ULONG& ulStatusCode, LPCWSTR& wszStatusText);

	// The rest  don't do anything...
	STDMETHOD(OnStartBinding)(/* [in] */ DWORD dwReserved,
		/* [in] */ IBinding __RPC_FAR* pib) {
		return E_NOTIMPL;
	}
	STDMETHOD(GetPriority)(/* [out] */ LONG __RPC_FAR* pnPriority) { return E_NOTIMPL; }
	STDMETHOD(OnLowResource)(/* [in] */ DWORD reserved) { return E_NOTIMPL; }
	STDMETHOD(OnStopBinding)(/* [in] */ HRESULT hresult,
		/* [unique][in] */ LPCWSTR szError) {
		return E_NOTIMPL;
	}
	STDMETHOD(GetBindInfo)(/* [out] */ DWORD __RPC_FAR* grfBINDF,
		/* [unique][out][in] */ BINDINFO __RPC_FAR* pbindinfo) {
		return E_NOTIMPL;
	}
	STDMETHOD(OnDataAvailable)(/* [in] */ DWORD grfBSCF,
		/* [in] */ DWORD dwSize, /* [in] */ FORMATETC __RPC_FAR* pformatetc,
		/* [in] */ STGMEDIUM __RPC_FAR* pstgmed) {
		return E_NOTIMPL;
	}
	STDMETHOD(OnObjectAvailable)(/* [in] */ REFIID riid,
		/* [iid_is][in] */ IUnknown __RPC_FAR* punk) {
		return E_NOTIMPL;
	}
	// IUnknown stuff
	STDMETHOD_(ULONG, AddRef)() { return 0; }
	STDMETHOD_(ULONG, Release)() { return 0; }
	STDMETHOD(QueryInterface)(/* [in] */ REFIID riid,
		/* [iid_is][out] */ void __RPC_FAR* __RPC_FAR* ppvObject) {
		return E_NOTIMPL;
	}
};

#endif // CBD_H_