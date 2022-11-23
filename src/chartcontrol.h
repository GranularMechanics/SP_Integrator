#ifndef CHART_CONTROL_H
#define CHART_CONTROL_H

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <vector>
#include <string>

class ChartControl : public wxWindow
{
public:
    ChartControl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size);

    bool quad{ false };
    void Set(const wxString& title, const wxString& lt);
    void Set(const wxString& title, const wxString& lt, const wxString& rt, const wxString& lb, const wxString& rb);
    void Set(const std::vector<double>& values_ltx,
        const std::vector<double>& values_lty);
    void Set(const std::vector<double>& values_ltx,
        const std::vector<double>& values_lty,
        const std::vector<double>& values_rbx,
        const std::vector<double>& values_rby);

private:
    wxString title;
    wxString tlt, trt, tlb, trb;
    std::vector<double> ltx;
    std::vector<double> lty;
    std::vector<double> rbx;
    std::vector<double> rby;
    void DrawComponent(wxAutoBufferedPaintDC& dc, wxGraphicsContext* gc, wxRect2DDouble chartArea, const wxString& chartTitle,
        const std::vector<double>& x,
        const std::vector<double>& y,
        bool drawXLabels,
        bool drawYLabels);
    void OnPaint(wxPaintEvent &evt);
    std::tuple<int, double, double> calculateChartSegmentCountAndRange(double origLow, double origHigh);
};
#endif