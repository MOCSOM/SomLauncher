#include "CallbackDict.h"

// Adapted from:
// Creating a progress bar in C/C++ (or any other console app.)
// http://www.rosshemsley.co.uk/2011/02/creating-a-progress-bar-in-c-or-any-other-console-app/
void SomConsole::setloadbar(unsigned curr_val, unsigned max_val, unsigned bar_width)
{
	if ((curr_val != max_val) && (curr_val % (max_val / 100) != 0))
		return;

	double   ratio = curr_val / (double)max_val;
	unsigned bar_now = (unsigned)(ratio * bar_width);

	std::cout << "\r" /*<< std::setw(3)*/ << (unsigned)(ratio * 100.0) << "% [";
	for (unsigned curr_val = 0; curr_val < bar_now; ++curr_val)
		std::cout << "=";
	for (unsigned curr_val = bar_now; curr_val < bar_width; ++curr_val)
		std::cout << " ";
	std::cout << "]" << std::flush;
}

void SomProgressBarr::set_prog_bar(unsigned curr_val, unsigned max_val,
	std::shared_ptr<QProgressBar> progress_bar)
{
	if ((curr_val != max_val) && (curr_val % (max_val / 100) != 0))
	{
		return;
	}

	progress_bar->setMinimum(0);
	progress_bar->setMaximum(max_val);
	progress_bar->setValue(curr_val);

	/*double   ratio = curr_val / static_cast<double>(max_val);
	unsigned bar_now = static_cast<unsigned>(ratio * 20);

	for (unsigned curr_val = 0; curr_val < bar_now; ++curr_val)
	{
		progress_bar->setValue(curr_val);
	}*/
}

inline void CallbackDict::setLogger(moc::SomLogger logger)
{
	this->Logger.setQtPlainText(logger.getQtPlainText());
}

inline void CallbackDict::setQProgressBar(std::shared_ptr<QProgressBar> progress_bar)
{
	this->progress_bar = progress_bar;
}

STDMETHODIMP_(HRESULT __stdcall) CallbackDict::OnProgress(ULONG ulProgress, ULONG ulProgressMax,
	ULONG ulStatusCode, LPCWSTR wszStatusText)
{
	setConsoleBar(ulProgress, ulProgressMax, ulStatusCode, wszStatusText);

	switch (ulStatusCode)
	{
	case BINDSTATUS_FINDINGRESOURCE:
		//Logger << "Finding resource..." << std::endl;
		break;
	case BINDSTATUS_CONNECTING:
		//Logger << "Connecting..." << std::endl;
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
		//Logger << "Begin download" << std::endl;
		break;
	case BINDSTATUS_DOWNLOADINGDATA:
	case BINDSTATUS_ENDDOWNLOADDATA:
	{
		int percent = static_cast<int>(100.0 * static_cast<double>(ulProgress)
			/ static_cast<double>(ulProgressMax));
		if (m_percentLast < percent)
		{
			ProgressBarInConsole(percent, 100);
			m_percentLast = percent;
		}
		if (ulStatusCode == BINDSTATUS_ENDDOWNLOADDATA)
		{
			Logger << " End download ";
			Logger << wszStatusText << std::endl;
			m_percentLast = -1;
		}
	}
	break;

	default:
	{
		//Logger << "Status code : " << ulStatusCode << std::endl << std::endl;
	}
	}

	// The download can be cancelled by returning E_ABORT here
	// of from any other of the methods.
	return S_OK;
}

HRESULT CallbackDict::setConsoleBar(ULONG& ulProgress, ULONG& ulProgressMax, ULONG& ulStatusCode, LPCWSTR& wszStatusText)
{
	if (ulProgress == NULL && ulProgressMax == NULL && ulStatusCode == NULL)
	{
		if (wszStatusText != NULL)
		{
			Logger << wszStatusText << std::endl;
		}
		else
		{
			Logger << wszStatusText << std::endl;
		}
		return S_OK;
	}

	if (ulProgress == NULL || ulStatusCode == NULL && wszStatusText == NULL)
	{
		int percent = (int)(100.0 * static_cast<double>(ulProgress)
			/ static_cast<double>(ulProgressMax));
		if (m_percentLast < percent)
		{
			ProgressBarInConsole(percent, 100);
			m_percentLast = percent;
		}
		return S_OK;
	}

	if (ulProgressMax == NULL || ulStatusCode == NULL && wszStatusText == NULL)
	{
		int percent = (int)(100.0 * static_cast<double>(ulProgress)
			/ static_cast<double>(ulProgressMax));
		if (m_percentLast < percent)
		{
			ProgressBarInConsole(percent, 100);
			m_percentLast = percent;
		}
		return S_OK;
	}
	return S_OK;
}