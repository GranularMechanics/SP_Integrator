#include "Frame.h"
#include <wx/wx.h>
#include <wx/listbook.h>
#include "drawingcanvas.h"
#include "chartcontrol.h"

Frame::Frame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
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

    CreateStatusBar(1);
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