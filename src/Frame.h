#ifndef FRAME_H
#define FRAME_H
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/listbook.h>
#include <random>

class ChartControl;
struct KeyValue;
class Model;
class Integrator;

class Frame : public wxFrame
{
    // Project data
    Model* model{};
    Integrator* integrator{};
    wxString modelLabel{};
    wxString project{};
    std::vector<KeyValue> modelParameters;
    std::vector<KeyValue> integratorSettings;
    std::vector<KeyValue> integratorInitialState;
    std::vector<KeyValue> integratorLoading;
    bool notSaved{ false };

    // Frame Components
    wxToolBar* m_ToolBar{ nullptr };
    wxMenuBar* m_MenuBar{ nullptr };
    ChartControl* chart1{ nullptr };
    ChartControl* chart2{ nullptr };
    wxPanel* rtopPanel{ nullptr };
    wxPanel* rmidPanel{ nullptr };
    wxPanel* rlowPanel{ nullptr };
    wxPanel* rbtmPanel{ nullptr };
    wxPanel* rghtPanel{ nullptr };
    wxBoxSizer* sizerRght;
    int rectCount = 0;
    std::mt19937 randomGen;

    // callbacks
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

    // Frame constructor functions
    void SetupMenuBar();
    void SetupListView(wxPanel* p, const wxString& label, const std::vector<KeyValue>& keyValue);
    void SetupForm();
    void LoadDefaults();
    void FillRightPanels();
    KeyValue trim(const std::string& line, size_t pos);
public:
    Frame(const wxString &title, const wxPoint &pos, const wxSize &size);
    ~Frame();
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