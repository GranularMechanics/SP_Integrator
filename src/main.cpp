#include <wx/wx.h>
#include "Frame.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    Frame *frame = new Frame("wx_projects", wxPoint(640, 480), wxDefaultSize);
    frame->Show(true);
    return true;
}

