#ifndef FRAME_H
#define FRAME_H
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/listbook.h>
#include <random>

class ChartControl;

class Frame : public wxFrame
{
    wxToolBar* m_ToolBar{ nullptr };
    wxMenuBar* m_MenuBar{ nullptr };
    wxListView* parameters;
    wxListView* settings;
    wxPanel* modelPanel{};
    wxPanel* right_top;
    wxPanel* left;

    void OnNew(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnSaveAs(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnMCC(wxCommandEvent& event);
    void OnMCC_H(wxCommandEvent& event);
    void OnOCC(wxCommandEvent& event);
    void OnOCC_H(wxCommandEvent& event);
    void OnMohrC(wxCommandEvent& event);
    void OnMohrCCap(wxCommandEvent& event);
    //void OnData(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

public:
    Frame(const wxString &title, const wxPoint &pos, const wxSize &size);
    ~Frame();

    wxDECLARE_EVENT_TABLE();

private:
    ChartControl *chart1;
    ChartControl* chart2;
    ChartControl* chart3;
    ChartControl* chart4;

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
    ID_MCC,
    ID_MCC_H,
    ID_OCC,
    ID_OCC_H,
    ID_M_C,
    ID_M_C_C,
    ID_Settings,
    ID_Controls,
    ID_Methods,
    ID_Tolerances,
    ID_Data,
    ID_Documentation,
    ID_Slider
};
#endif