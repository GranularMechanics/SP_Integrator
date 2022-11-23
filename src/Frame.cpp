#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/listbook.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>
#include "Frame.h"
#include "Model.h"
#include "Integrator.h"
#include "drawingcanvas.h"
#include "chartcontrol.h"

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
EVT_MENU(ID_New, Frame::OnNew)
EVT_MENU(ID_Open, Frame::OnOpen)
EVT_MENU(ID_Save, Frame::OnSave)
EVT_MENU(ID_Save_As, Frame::OnSaveAs)
EVT_MENU(ID_MCC, Frame::OnMCC)
wxEND_EVENT_TABLE()

Frame::Frame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{

    SetupMenuBar();
    m_ToolBar = this->CreateToolBar(wxTB_HORIZONTAL, wxID_ANY);
    CreateStatusBar();
    SetStatusText("Welcome to the Lassonde Integrator");

    Bind(wxEVT_MENU, &Frame::OnNew, this, ID_New);
    Bind(wxEVT_MENU, &Frame::OnOpen, this, ID_Open);
    Bind(wxEVT_MENU, &Frame::OnSave, this, ID_Save);
    Bind(wxEVT_MENU, &Frame::OnSaveAs, this, ID_Save_As);
    Bind(wxEVT_MENU, &Frame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &Frame::OnMCC, this, ID_MCC);
    Bind(wxEVT_MENU, &Frame::OnAbout, this, wxID_ABOUT);

    //-------------------------------------------------------------------------
    // Frame Design
    wxBoxSizer* sizerMstr = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizerRght = new wxBoxSizer(wxVERTICAL);
    wxPanel* rghtPanel = new wxPanel(this);
    wxPanel* rtopPanel = new wxPanel(rghtPanel);
    wxPanel* rmidPanel = new wxPanel(rghtPanel);
    wxPanel* rlowPanel = new wxPanel(rghtPanel);
    wxPanel* rbtmPanel = new wxPanel(rghtPanel);
    this->SetBackgroundColour(wxColor(200, 200, 200));
    rghtPanel->SetBackgroundColour(wxColor(200, 200, 200));
    rtopPanel->SetBackgroundColour(wxColor(120, 120,  50));
    rmidPanel->SetBackgroundColour(wxColor( 50, 120,  50));
    rlowPanel->SetBackgroundColour(wxColor(120,  50, 120));
    rbtmPanel->SetBackgroundColour(wxColor(120, 50, 120));

    // graphics on the frame's client area itself
    Integrator* integrator = new Integrator();
    auto book = new wxListbook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);
    book->SetInternalBorder(0);
    chart1 = new ChartControl(book, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    chart1->Set("p, q, v, eq", "q vs p", "q vs eq", "v vs p", "v vs eq");
    auto v1 = integrator->Get("p");
    auto v2 = integrator->Get("q");
    auto v3 = integrator->Get("eq");
    auto v4 = integrator->Get("v");
    chart1->Set(v1, v2, v3, v4);
    book->AddPage(chart1, "p, q, v, eq");
    chart2 = new ChartControl(book, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    chart2->Set("p, q", "q vs p");
    chart2->Set(v1, v2);
    book->AddPage(chart2, "q vs p");
    book->SetSelection(1);
    sizerMstr->Add(book, 1, wxEXPAND | wxALL, 3);

    // Model parameters
    Model* model = new Model();
    SetupListView(rtopPanel, "Parameter", model->GetParameters());
    sizerRght->Add(rtopPanel, 0, wxEXPAND | wxALL, 2);
    delete model;

    auto minChartSize = 2.0 * rtopPanel->GetBestSize();
    book->SetMinSize(minChartSize);

    // Settings
    SetupListView(rmidPanel, "Setting", integrator->GetSettings());
    sizerRght->Add(rmidPanel, 0, wxEXPAND | wxALL, 2);

    // Initial State
    SetupListView(rlowPanel, "Initial State", integrator->GetInitialState());
    sizerRght->Add(rlowPanel, 1, wxEXPAND | wxALL, 2);

    // Loading
    SetupListView(rbtmPanel, "Loading", integrator->GetLoading());
    sizerRght->Add(rbtmPanel, 1, wxEXPAND | wxALL, 2);

    delete integrator;

    rghtPanel->SetSizerAndFit(sizerRght);

    sizerMstr->Add(rghtPanel, 0, wxEXPAND | wxALL, 2);
    this->SetSizerAndFit(sizerMstr);
    sizerMstr->SetSizeHints(this);

    Centre();
    SetStatusText("Ready", 0);
}

void Frame::SetupMenuBar() {

    // add dropdown menu for File operations
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_New, "&New", "Open a new file");
    menuFile->Append(ID_Open, "&Open", "Open an existing file");
    menuFile->Append(ID_Save, "&Save", "Save to file");
    menuFile->Append(ID_Save_As, "&Save As", "Save to a new file");
    menuFile->AppendSeparator();
    menuFile->Append(ID_Print, "&Print", "Save to file");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    // add dropdown menu for View operations
    wxMenu* menuView = new wxMenu;
    menuView->Append(ID_Loading, "&Loading", "Select a Constitutive Model");
    menuView->Append(ID_2DPlots, "&2D Plots", "Select a Constitutive Model");
    menuView->Append(ID_3DPlot, "&3D Plot", "Select a Constitutive Model");

    // add dropdown menu for Model operations
    wxMenu* menuModel = new wxMenu;
    menuModel->Append(ID_MCC, "&MCC", "Modified Cam Clay");
    menuModel->Append(ID_MCC_H, "&MCC+H", "Modified Cam Clay with Hvorslev");
    menuModel->Append(ID_OCC, "&OCC", "Original Cam Clay");
    menuModel->Append(ID_OCC_H, "&OCC+H", "Original Cam Clay with Hvorslev");
    menuModel->Append(ID_M_C, "&Mohr-C", "Mohr-Coulomb");
    menuModel->Append(ID_M_C_C, "&Mohr-C+Cap", "Mohr-Coulomb with Cap");

    // add dropdown menu for Settings
    wxMenu* menuSettings = new wxMenu;
    menuSettings->Append(ID_Controls, "&Controls", "Integration Controls");
    menuSettings->Append(ID_Methods, "&Methods", "Integration Methods");
    menuSettings->Append(ID_Tolerances, "&Tolerances", "Integration Tolerances");

    // add dropdown menu for Data
    wxMenu* menuData = new wxMenu;
    menuData->Append(ID_Data, "&Data Files", "Integration Data");

    // add dropdown menu for Help operations
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(ID_Documentation, "&Documentation", "Online Documentation");
    menuHelp->Append(wxID_ABOUT);

    // create the menu bar
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuView, "&View");
    menuBar->Append(menuModel, "&Model");
    menuBar->Append(menuSettings, "&Settings");
    menuBar->Append(menuData, "&Data");
    menuBar->Append(menuHelp, "&Help");

    // add the menu bar
    SetMenuBar(menuBar);
}

void Frame::SetupListView(wxPanel* p, const wxString& label, const std::vector<KeyValue>& keyValue) {

    auto list = new wxListView(p);
    list->AppendColumn(label);
    list->AppendColumn("Value");
    list->SetColumnWidth(0, 100);
    list->SetColumnWidth(1, 100);
    auto index = list->GetItemCount();

    for (const auto& e : keyValue) {
        list->InsertItem(index, e.label);
        list->SetItem(index, 1, std::to_string(e.value));
    }
}

void Frame::SetupForm() {
    auto sizer = new wxBoxSizer(wxVERTICAL);
    auto centeringSizer = new wxBoxSizer(wxHORIZONTAL);
    auto panel = new wxPanel(this);
    auto panelSizer = new wxBoxSizer(wxVERTICAL);
    auto nameLabel = new wxStaticText(panel, wxID_ANY, "Setting");
    auto choice = wxChoice();
    auto userNameField = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(FromDIP(300), wxDefaultSize.y));
    std::vector<wxWindow*> formItems{ nameLabel, userNameField };

    for (auto item : formItems) {
        panelSizer->Add(item, 0, wxEXPAND | wxALL, FromDIP(3));
    }

    panel->SetSizerAndFit(panelSizer);
    centeringSizer->Add(panel, 1, wxALIGN_CENTER | wxALL, FromDIP(10));
    sizer->Add(centeringSizer, 1, wxEXPAND);
    SetSizerAndFit(sizer);
}

void Frame::OnNew(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

void Frame::OnOpen(wxCommandEvent& event)
{
}

void Frame::OnSave(wxCommandEvent& event)
{
}

void Frame::OnSaveAs(wxCommandEvent& event)
{
}

void Frame::OnExit(wxCommandEvent& event)
{
    Close(true);
    event.Skip();
}

void Frame::OnMCC(wxCommandEvent& event)
{
}

void Frame::OnMCC_H(wxCommandEvent& event)
{
}

void Frame::OnOCC(wxCommandEvent& event)
{
}

void Frame::OnOCC_H(wxCommandEvent& event)
{
}

void Frame::OnMohrC(wxCommandEvent& event)
{
}

void Frame::OnMohrCCap(wxCommandEvent& event)
{
}

void Frame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
        "About Hello World", wxOK | wxICON_INFORMATION);
}

Frame::~Frame()
{

}
