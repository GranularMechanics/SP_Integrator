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
    wxBoxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizerLeft = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizerRght = new wxBoxSizer(wxVERTICAL);
    wxPanel* mainPanel = new wxPanel(this);
    wxPanel* leftPanel = new wxPanel(mainPanel);
    wxPanel* rghtPanel = new wxPanel(mainPanel);
    wxPanel* ltopPanel = new wxPanel(leftPanel);
    wxPanel* lbtmPanel = new wxPanel(leftPanel);
    wxPanel* rtopPanel = new wxPanel(rghtPanel);
    wxPanel* rbtmPanel = new wxPanel(rghtPanel);
    leftPanel->SetBackgroundColour(wxColor(200, 100, 100));
    rghtPanel->SetBackgroundColour(wxColor(100, 200, 100));
    ltopPanel->SetBackgroundColour(wxColor( 50, 120, 120));
    lbtmPanel->SetBackgroundColour(wxColor( 50, 120,  50));
    rtopPanel->SetBackgroundColour(wxColor(120, 120,  50));
    rbtmPanel->SetBackgroundColour(wxColor(120,  50, 120));

    // graphics on the frame itself
    auto graphic1 = new wxListbook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);
    graphic1->SetInternalBorder(0);
    chart1 = new ChartControl(graphic1, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    chart1->Set("1st Chart", "Top Left", "Top Right", "Bottom Left", "Bottom Right");
    chart1->values = { 0.34, -0.17, 0.98, 0.33 };
    wxVector<double> v1;
    v1.push_back(0.34);
    v1.push_back(-0.17);
    v1.push_back(-0.98);
    v1.push_back(0.33);
    wxVector<double> v2;
    v2.push_back(0.34);
    v2.push_back(-0.17);
    v2.push_back(0.98);
    v2.push_back(0.33);
    wxVector<double> v3;
    v3.push_back(-0.34);
    v3.push_back(-0.17);
    v3.push_back(0.98);
    v3.push_back(0.33);
    wxVector<double> v4;
    v4.push_back(-0.34);
    v4.push_back(-0.17);
    v4.push_back(0.98);
    v4.push_back(-0.33);
    chart1->Set(v1, v2, v3, v4);
    graphic1->AddPage(chart1, "1st Chart");
    chart2 = new ChartControl(graphic1, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    chart2->Set("2nd Chart", "Top Left", "Top Right", "Bottom Left", "Bottom Right");
    chart2->values = { -0.34, 0.17, 0.98, 0.33 };
    v1.clear();
    v1.push_back(-0.17);
    v1.push_back(0.34);
    v1.push_back(0.33);
    v1.push_back(-0.98);
    v2.clear();
    v2.push_back(0.34);
    v2.push_back(0.98);
    v2.push_back(-0.17);
    v2.push_back(0.33);
    v3.clear();
    v3.push_back(0.33);
    v3.push_back(-0.34);
    v3.push_back(-0.17);
    v3.push_back(0.98);
    v4.clear();
    v4.push_back(0.98);
    v4.push_back(-0.34);
    v4.push_back(-0.17);
    v4.push_back(-0.33);
    chart2->Set(v1, v2, v3, v4);
    graphic1->AddPage(chart2, "2nd Chart");
    graphic1->SetSelection(1);
    sizerMstr->Add(graphic1, 1, wxEXPAND | wxALL, 3);

    //auto graphic2 = new wxListbook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);
    //graphic2->SetInternalBorder(0);
    //chart3 = new ChartControl(graphic2, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    //chart3->title = "Important Chart 3";
    //chart3->values = { 0.34, -0.17, 0.98, 0.33 };
    //graphic2->AddPage(chart3, "3rd Chart");
    //chart4 = new ChartControl(graphic2, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    //chart4->title = "Less Important Chart";
    //chart4->values = { -0.34, 0.17, 0.98, 0.33 };
    //graphic2->AddPage(chart4, "4th Chart");
    //graphic2->SetSelection(1);
    //sizerMstr->Add(graphic2, 1, wxEXPAND | wxALL, 3);

    sizerMstr->Add(mainPanel, 1, wxEXPAND | wxALL, 1);

    sizerLeft->Add(ltopPanel, 1, wxEXPAND | wxALL, 2);
    sizerLeft->Add(lbtmPanel, 1, wxEXPAND | wxALL, 2);
    sizerRght->Add(rtopPanel, 1, wxEXPAND | wxALL, 2);
    sizerRght->Add(rbtmPanel, 1, wxEXPAND | wxALL, 2);
    sizerMain->Add(leftPanel, 1, wxALIGN_RIGHT | wxALL, 1);
    sizerMain->Add(rghtPanel, 1, wxALIGN_RIGHT | wxALL, 1);

    // Model parameters
    parameters = new wxListView(ltopPanel);
    parameters->AppendColumn("Label");
    parameters->AppendColumn("Value");
    parameters->SetColumnWidth(0, 100);
    parameters->SetColumnWidth(1, 100);
    auto index = parameters->GetItemCount();

    Model* model = new Model();
    for (const auto& e : model->getParameters()) {
        parameters->InsertItem(index, e.label);
        parameters->SetItem(index, 1, std::to_string(e.value));
    }
    delete model;

    // Settings
    settings = new wxListView(rtopPanel);
    settings->AppendColumn("Label");
    settings->AppendColumn("Value");
    settings->SetColumnWidth(0, 100);
    settings->SetColumnWidth(1, 100);
    index = settings->GetItemCount();

    Integrator* integrator = new Integrator();
    for (const auto& e : integrator->getSettings()) {
        settings->InsertItem(index, e.label);
        settings->SetItem(index, 1, std::to_string(e.value));
    }
    delete integrator;

    rghtPanel->SetSizerAndFit(sizerRght);
    leftPanel->SetSizerAndFit(sizerLeft);
    mainPanel->SetSizerAndFit(sizerMain);
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
