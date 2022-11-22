#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <vector>
#include <string>

class ChartControl : public wxWindow
{
public:
    ChartControl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size);

    std::vector<double> values;
    void Set(const wxString& title, const wxString& lt, const wxString& rt, const wxString& lb, const wxString& rb);
    void Set(const wxVector<double>& values_ltx,
        const wxVector<double>& values_lty,
        const wxVector<double>& values_rbx,
        const wxVector<double>& values_rby);

private:
    wxString title;
    wxString tlt, trt, tlb, trb;
    wxVector<double> ltx;
    wxVector<double> lty;
    wxVector<double> rbx;
    wxVector<double> rby;
    void DrawComponent(wxAutoBufferedPaintDC& dc, wxGraphicsContext* gc, wxRect2DDouble chartArea, const wxString& chartTitle,
        const wxVector<double>& x, 
        const wxVector<double>& y,
        bool drawYLabels);
    void OnPaint(wxPaintEvent &evt);
    std::tuple<int, double, double> calculateChartSegmentCountAndRange(double origLow, double origHigh);
};