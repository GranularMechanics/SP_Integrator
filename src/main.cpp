#include "main.h"
#include "Frame.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    Frame *frame = new Frame("wxProject_1", wxPoint(640, 480), wxDefaultSize);
    frame->Show(true);
    return true;
}

