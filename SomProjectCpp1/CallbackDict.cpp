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

    System::Console::Write(L"\r");
    System::Console::Write(L"  ");
    System::Console::Write((unsigned)(ratio * 100.0));
    System::Console::Write(L"% [");
    for (unsigned curr_val = 0; curr_val < bar_now; ++curr_val)
        System::Console::Write(L"=");
    for (unsigned curr_val = bar_now; curr_val < bar_width; ++curr_val)
        System::Console::Write(L" ");
    System::Console::Write(L"]");

    //System::Console::Clear();
}

void SomProgressBarr::set_prog_bar(unsigned curr_val, unsigned max_val)
{
    if ((curr_val != max_val) && (curr_val % (max_val / 100) != 0))
        return;

    double   ratio = curr_val / static_cast<double>(max_val);
    unsigned bar_now = static_cast<unsigned>(ratio * 20);

    for (unsigned curr_val = 0; curr_val < bar_now; ++curr_val) 
    {

    }
        
}

void CallbackNull::set_progress_bar_form()
{
}
