#ifndef CBD_H_     // equivalently, #if !defined HEADER_H_
#define CBD_H_

#include <windows.h>
#include <tchar.h>

#include <iostream>

//#include "MainForm.h"

#pragma comment(lib, "Urlmon.lib")

#define ProgressBarInConsole SomConsole::setloadbar

namespace SomConsole
{
    void setloadbar(unsigned curr_val, unsigned max_val, unsigned bar_width = 20);
}
namespace SomProgressBarr {
    void set_prog_bar(unsigned curr_val, unsigned max_val);
}

class CallbackNull : public IBindStatusCallback
{
public:
    CallbackNull() {}
    //CallbackNull(CallbackDict other) {}
    ~CallbackNull() {}

    void set_progress_bar_form();

    // This one is called by URLDownloadToFile
    virtual __declspec(nothrow) HRESULT __stdcall OnProgress(/* [in] */ ULONG ulProgress, /* [in] */ ULONG ulProgressMax, /* [in] */ ULONG ulStatusCode, /* [in] */ LPCWSTR wszStatusText)
    {
        return S_OK;
    }

    // The rest  don't do anything...
    STDMETHOD(OnStartBinding)(/* [in] */ DWORD dwReserved,
        /* [in] */ IBinding __RPC_FAR* pib) {
        return E_NOTIMPL;
    }
    STDMETHOD(GetPriority)(/* [out] */ LONG __RPC_FAR* pnPriority) {
        return E_NOTIMPL;
    }
    STDMETHOD(OnLowResource)(/* [in] */ DWORD reserved) {
        return E_NOTIMPL;
    }
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
    STDMETHOD_(ULONG, AddRef)() {
        return 0;
    }
    STDMETHOD_(ULONG, Release)() {
        return 0;
    }
    STDMETHOD(QueryInterface)(/* [in] */ REFIID riid,
        /* [iid_is][out] */ void __RPC_FAR* __RPC_FAR* ppvObject) {
        return E_NOTIMPL;
    }
};

class CallbackDict : public CallbackNull
{
private:
    int m_percentLast = 0;

public:
    CallbackDict() {}
    CallbackDict(CallbackNull other) {}
	~CallbackDict() {}

    // This one is called by URLDownloadToFile
    STDMETHOD(OnProgress)(/* [in] */ ULONG ulProgress, /* [in] */ ULONG ulProgressMax, /* [in] */ ULONG ulStatusCode, /* [in] */ LPCWSTR wszStatusText) override
    {
        if (ulProgress == NULL && ulProgressMax == NULL && ulStatusCode == NULL)
        {
            //System::Console::WriteLine(System::String(wszStatusText).ToString());

            std::cout << wszStatusText;
        }

        switch (ulStatusCode)
        {
            case BINDSTATUS_FINDINGRESOURCE:
                //System::Console::WriteLine("Finding resource...");
                std::cout << "Finding resource..." << '\n';
                break;
            case BINDSTATUS_CONNECTING:
                //System::Console::WriteLine("Connecting...");
                std::cout << "Connecting..." << '\n';
                break;
            case BINDSTATUS_SENDINGREQUEST:
                //System::Console::WriteLine("Sending request...");
                break;
            case BINDSTATUS_MIMETYPEAVAILABLE:
                //System::Console::WriteLine("Mime type available");
                break;
            case BINDSTATUS_CACHEFILENAMEAVAILABLE:
                //System::Console::WriteLine("Cache filename available");
                break;
            case BINDSTATUS_BEGINDOWNLOADDATA:
                //System::Console::WriteLine("Begin download");
                std::cout << "Begin download" << '\n';
                break;
            case BINDSTATUS_DOWNLOADINGDATA:
            case BINDSTATUS_ENDDOWNLOADDATA:
            {
                int percent = (int)(100.0 * static_cast<double>(ulProgress)
                    / static_cast<double>(ulProgressMax));
                if (m_percentLast < percent)
                {
                    ProgressBarInConsole(percent, 100);
                    m_percentLast = percent;
                }
                if (ulStatusCode == BINDSTATUS_ENDDOWNLOADDATA)
                {
                    /*System::Console::WriteLine();
                    System::Console::WriteLine("End download");
                    System::Console::WriteLine(System::String(wszStatusText).ToString());*/

                    std::cout << '\n' << "End download" << '\n' << wszStatusText;
                }
            }
            break;

            default:
            {
                /*System::Console::Write("Status code : ");
                System::Console::WriteLine(static_cast<long int>(ulStatusCode));*/

                std::cout << "Status code : " << ulStatusCode << '\n';
            }
        }
        
        // The download can be cancelled by returning E_ABORT here
        // of from any other of the methods.
        return S_OK;
    }


    // The rest  don't do anything...
    STDMETHOD(OnStartBinding)(/* [in] */ DWORD dwReserved,
        /* [in] */ IBinding __RPC_FAR* pib) { return E_NOTIMPL; }
    STDMETHOD(GetPriority)(/* [out] */ LONG __RPC_FAR* pnPriority){ return E_NOTIMPL; }
    STDMETHOD(OnLowResource)(/* [in] */ DWORD reserved){ return E_NOTIMPL; }
    STDMETHOD(OnStopBinding)(/* [in] */ HRESULT hresult,
        /* [unique][in] */ LPCWSTR szError) { return E_NOTIMPL; }
    STDMETHOD(GetBindInfo)(/* [out] */ DWORD __RPC_FAR* grfBINDF,
        /* [unique][out][in] */ BINDINFO __RPC_FAR* pbindinfo) { return E_NOTIMPL; }
    STDMETHOD(OnDataAvailable)(/* [in] */ DWORD grfBSCF,
        /* [in] */ DWORD dwSize, /* [in] */ FORMATETC __RPC_FAR* pformatetc,
        /* [in] */ STGMEDIUM __RPC_FAR* pstgmed) { return E_NOTIMPL; }
    STDMETHOD(OnObjectAvailable)(/* [in] */ REFIID riid,
        /* [iid_is][in] */ IUnknown __RPC_FAR* punk) { return E_NOTIMPL; }
    // IUnknown stuff
    STDMETHOD_(ULONG, AddRef)() { return 0; }
    STDMETHOD_(ULONG, Release)() { return 0; }
    STDMETHOD(QueryInterface)(/* [in] */ REFIID riid,
        /* [iid_is][out] */ void __RPC_FAR* __RPC_FAR* ppvObject) { return E_NOTIMPL; }



};


#endif // CBD_H_