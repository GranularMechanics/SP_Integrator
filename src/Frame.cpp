#include <wx/wx.h>
#include <wx/listbook.h>
#include "Frame.h"
#include "drawingcanvas.h"
#include "chartcontrol.h"

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
EVT_MENU(ID_New, Frame::OnNew)
EVT_MENU(ID_Open, Frame::OnOpen)
EVT_MENU(ID_Save, Frame::OnSave)
EVT_MENU(ID_Save_As, Frame::OnSaveAs)
EVT_MENU(ID_Model, Frame::OnModel)
wxEND_EVENT_TABLE()

Frame::Frame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    // add a menu bar
    wxMenuBar* menuBar = new wxMenuBar;
    SetMenuBar(menuBar);

    // add menu for File operations
    wxMenu* menuFile = new wxMenu;
    menuBar->Append(menuFile, "&File");
    menuFile->Append(ID_New, "&New", "Open a new file");
    menuFile->Append(ID_Open, "&Open", "Open an existing file");
    menuFile->Append(ID_Save, "&Save", "Save to file");
    menuFile->Append(ID_Save_As, "&Save As", "Save to a new file");
    menuFile->AppendSeparator();
    menuFile->Append(ID_Print, "&Print", "Save to file");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    // add menu for View operations
    wxMenu* menuView = new wxMenu;
    menuBar->Append(menuView, "&View");
    menuView->Append(ID_Loading, "&Loading", "Select a Constitutive Model");
    menuView->Append(ID_2DPlots, "&2D Plots", "Select a Constitutive Model");
    menuView->Append(ID_3DPlot, "&3D Plot", "Select a Constitutive Model");

    // add menu for Model operations
    wxMenu* menuModel = new wxMenu;
    menuBar->Append(menuModel, "&Model");
    menuModel->Append(ID_Model, "&Model", "Select a Constitutive Model");

    // add menu for Settings
    wxMenu* menuSettings = new wxMenu;
    menuBar->Append(menuSettings, "&Settings");
    menuSettings->Append(ID_Controls, "&Controls", "Integration Controls");
    menuSettings->Append(ID_Methods, "&Methods", "Integration Methods");
    menuSettings->Append(ID_Tolerances, "&Tolerances", "Integration Tolerances");

    // add menu for Data
    wxMenu* menuData = new wxMenu;
    menuBar->Append(menuData, "&Data");
    menuData->Append(ID_Data, "&Data Files", "Integration Data");

    // add menu for Help operations
    wxMenu* menuHelp = new wxMenu;
    menuBar->Append(menuHelp, "&Help");
    menuHelp->Append(ID_Documentation, "&Documentation", "Online Documentation");
    menuHelp->Append(wxID_ABOUT);

    // add a toolbar
    m_ToolBar = this->CreateToolBar(wxTB_HORIZONTAL, wxID_ANY);
    // add the Status Bar
    CreateStatusBar();
    SetStatusText("Welcome to the Lassonde Integrator");

    Bind(wxEVT_MENU, &Frame::OnNew, this, ID_New);
    Bind(wxEVT_MENU, &Frame::OnOpen, this, ID_Open);
    Bind(wxEVT_MENU, &Frame::OnSave, this, ID_Save);
    Bind(wxEVT_MENU, &Frame::OnSaveAs, this, ID_Save_As);
    Bind(wxEVT_MENU, &Frame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &Frame::OnModel, this, ID_Model);
    Bind(wxEVT_MENU, &Frame::OnAbout, this, wxID_ABOUT);

    auto tabs = new wxListbook(this, wxID_ANY, wxDefaultPosition, this->FromDIP(wxSize(640, 480)), wxNB_TOP);
    tabs->SetInternalBorder(0);

    wxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(tabs, 1, wxEXPAND);

    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    wxPanel *drawingPaneWithButtons = new wxPanel(tabs);
    auto buttonPanel = createButtonPanel(drawingPaneWithButtons);
    canvas = new DrawingCanvas(drawingPaneWithButtons, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    canvas->Bind(CANVAS_RECT_ADDED, &Frame::OnRectAdded, this);
    canvas->Bind(CANVAS_RECT_REMOVED, &Frame::OnRectRemoved, this);

    rectCount = canvas->getObjectCount();

    sizer->Add(buttonPanel, 0, wxEXPAND | wxALL, 0);
    sizer->Add(canvas, 1, wxEXPAND | wxALL, 0);

    drawingPaneWithButtons->SetSizerAndFit(sizer);

    tabs->AddPage(drawingPaneWithButtons, "Rectangles");

    chart = new ChartControl(tabs, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    chart->title = "Important Chart";
    chart->values = {0.34, -0.17, 0.98, 0.33};

    tabs->AddPage(chart, "Chart");
    tabs->SetSelection(1);

    this->SetSizerAndFit(mainSizer);

    SetStatusText("Ready", 0);
}

void Frame::OnAddButtonClick(wxCommandEvent &event)
{
    std::uniform_int_distribution sizeDistrib(this->FromDIP(50), this->FromDIP(100));
    std::uniform_int_distribution xDistrib(0, canvas->GetSize().GetWidth());
    std::uniform_int_distribution yDistrib(0, canvas->GetSize().GetHeight());
    std::uniform_real_distribution angleDistrib(0.0, M_PI * 2.0);

    std::uniform_int_distribution colorDistrib(0, 0xFFFFFF);

    rectCount++;
    canvas->addRect(sizeDistrib(randomGen), sizeDistrib(randomGen), xDistrib(randomGen), yDistrib(randomGen),
                    angleDistrib(randomGen), wxColour(colorDistrib(randomGen)), "Rect #" + std::to_string(rectCount));
}

void Frame::OnRemoveButtonClick(wxCommandEvent &event)
{
    canvas->removeTopRect();
}

void Frame::OnRectAdded(wxCommandEvent &event)
{
    SetStatusText("Rect named " + event.GetString() + " added!", 0);
}

void Frame::OnRectRemoved(wxCommandEvent &event)
{
    SetStatusText("Rect named " + event.GetString() + " REMOVED!", 0);
}

wxPanel *Frame::createButtonPanel(wxWindow *parent)
{
    wxPanel *panel = new wxPanel(parent);
    wxButton *addRectButton = new wxButton(panel, wxID_ANY, "Add Rect");
    wxButton *removeLastButton = new wxButton(panel, wxID_ANY, "Remove Top");

    wxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(addRectButton, 0, wxEXPAND | wxALL, 3);
    sizer->Add(removeLastButton, 0, wxEXPAND | wxALL, 3);

    panel->SetSizer(sizer);

    addRectButton->Bind(wxEVT_BUTTON, &Frame::OnAddButtonClick, this);
    removeLastButton->Bind(wxEVT_BUTTON, &Frame::OnRemoveButtonClick, this);

    return panel;
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
    //ModelFrame* model = new ModelFrame(this, "Model");
    //model->Show();
    //event.Skip();
}

void Frame::OnSaveAs(wxCommandEvent& event)
{
    //Pane* pane = new Pane(this);
}

void Frame::OnExit(wxCommandEvent& event)
{
    Close(true);
    event.Skip();
}

void Frame::OnModel(wxCommandEvent& event)
{
    //ModelFrame* model = new ModelFrame(this, "Model");
    //model->Show();
}

void Frame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
        "About Hello World", wxOK | wxICON_INFORMATION);
}

Frame::~Frame()
{

}
