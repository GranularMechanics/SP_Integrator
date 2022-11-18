#ifndef FRAME_H
#define FRAME_H
#include <wx/wx.h>
#include <random>

class DrawingCanvas;
class ChartControl;

class Frame : public wxFrame
{
    wxToolBar* m_ToolBar{ nullptr };
    wxMenuBar* m_MenuBar{ nullptr };

    void OnNew(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnSaveAs(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnModel(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

public:
    Frame(const wxString &title, const wxPoint &pos, const wxSize &size);
    ~Frame();

    wxDECLARE_EVENT_TABLE();

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

enum
{
    ID_New,
    ID_Open,
    ID_Save,
    ID_Save_As,
    ID_Print,
    ID_View,
    ID_Loading,
    ID_2DPlots,
    ID_3DPlot,
    ID_Model,
    ID_Settings,
    ID_Controls,
    ID_Methods,
    ID_Tolerances,
    ID_Data,
    ID_Documentation,
    ID_Slider
};
#endif