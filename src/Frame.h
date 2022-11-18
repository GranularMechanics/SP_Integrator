#ifndef FRAME_H
#define FRAME_H
#include <wx/wx.h>
#include <random>

class DrawingCanvas;
class ChartControl;

class Frame : public wxFrame
{
public:
    Frame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void OnAddButtonClick(wxCommandEvent &event);
    void OnRemoveButtonClick(wxCommandEvent &event);

    void OnRectAdded(wxCommandEvent &event);
    void OnRectRemoved(wxCommandEvent &event);

    wxPanel *createButtonPanel(wxWindow *parent);

    DrawingCanvas *canvas;
    ChartControl *chart;

    int rectCount = 0;
    std::mt19937 randomGen;
};
#endif