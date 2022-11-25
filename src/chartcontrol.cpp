#include "ChartControl.h"
#include <wx/settings.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

// wxFULL_REPAINT_ON_RESIZE needed for Windows
ChartControl::ChartControl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size) : 
    wxWindow(parent, id, pos, size, wxFULL_REPAINT_ON_RESIZE)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT); // needed for windows

    this->Bind(wxEVT_PAINT, &ChartControl::OnPaint, this);
}

void ChartControl::Set(const wxString& title_, const wxString& lt, const wxString& rt, const wxString& lb, const wxString& rb) {
    title = title_;
    tlt = lt;
    trt = rt;
    tlb = lb;
    trb = rb;
}

void ChartControl::Set(const wxString& title_, const wxString& lt) {
    title = title_;
    tlt = lt;
}

void ChartControl::Set(
    const std::vector<double>& values_ltx,
    const std::vector<double>& values_lty,
    const std::vector<double>& values_rbx,
    const std::vector<double>& values_rby) {
    ltx = values_ltx;
    lty = values_lty;
    rbx = values_rbx;
    rby = values_rby;
    quad = true;
}

void ChartControl::Set(
    const std::vector<double>& values_ltx,
    const std::vector<double>& values_lty) {
    ltx = values_ltx;
    lty = values_lty;
    quad = false;
}

void ChartControl::OnPaint(wxPaintEvent& evt)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();
    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if (gc)
    {
        wxFont titleFont = wxFont(wxNORMAL_FONT->GetPointSize() * 1.5,
            wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

        gc->SetFont(titleFont, wxSystemSettings::GetAppearance().IsDark() ? *wxWHITE : *wxBLACK);

        double tw, th;
        gc->GetTextExtent(this->title, &tw, &th);
        const double titleTopBottomMinimumMargin = this->FromDIP(10);
        wxRect2DDouble chartArea{ 0.0,0.0,static_cast<double>(GetSize().GetWidth()), static_cast<double>(GetSize().GetHeight()) };
        const double marginX = chartArea.GetSize().GetWidth() / 8.0;
        const double marginTop = std::max(chartArea.GetSize().GetHeight() / 8.0, titleTopBottomMinimumMargin * 2.0 + th);
        const double marginBottom = chartArea.GetSize().GetHeight() / 8.0;
        chartArea.Inset(marginX, marginTop, marginX, marginBottom);

        gc->DrawText(this->title, marginX + (chartArea.GetSize().GetWidth() - tw) / 2.0, titleTopBottomMinimumMargin);

        wxFont subtitleFont = wxFont(wxNORMAL_FONT->GetPointSize(),
            wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM);

        gc->SetFont(subtitleFont, wxSystemSettings::GetAppearance().IsDark() ? *wxWHITE : *wxBLACK);

        if (quad) {
            auto halfWidth = static_cast<double>(GetSize().GetWidth()) / 2.0;
            auto halfHeight = static_cast<double>(GetSize().GetHeight()) / 2.0;

            wxRect2DDouble leftTopArea{ marginX / 2.0, th, halfWidth, halfHeight };
            DrawComponent(dc, gc, leftTopArea, tlt, ltx, lty, false, true);

            wxRect2DDouble rightTopArea{ halfWidth, th, halfWidth, halfHeight };
            DrawComponent(dc, gc, rightTopArea, trt, rbx, lty, false, false);

            wxRect2DDouble leftBottomArea{ marginX / 2.0, halfHeight, halfWidth, halfHeight };
            DrawComponent(dc, gc, leftBottomArea, tlb, ltx, rby, true, true);

            wxRect2DDouble rightBottomArea{ halfWidth, halfHeight, halfWidth, halfHeight };
            DrawComponent(dc, gc, rightBottomArea, trb, rbx, rby, true, false);
        }
        else {
            auto Width = static_cast<double>(GetSize().GetWidth());
            auto Height = static_cast<double>(GetSize().GetHeight());

            wxRect2DDouble leftTopArea{ 0.0, th, Width, Height };
            DrawComponent(dc, gc, leftTopArea, tlt, ltx, lty, true, true);
        }

        delete gc;
    }
}

void ChartControl::DrawComponent(
    wxAutoBufferedPaintDC& dc, 
    wxGraphicsContext* gc, 
    wxRect2DDouble chartArea, 
    const wxString& chartTitle,
    const std::vector<double>& x,
    const std::vector<double>& y,
    bool drawXLabels,
    bool drawYLabels
) {

    auto values = y;
    double tw, th;
    gc->GetTextExtent(this->title, &tw, &th);
    const double titleTopBottomMinimumMargin = this->FromDIP(10);

    const double marginX = chartArea.GetSize().GetWidth() / 8.0;
    const double marginTop = std::max(chartArea.GetSize().GetHeight() / 8.0, titleTopBottomMinimumMargin * 2.0 + th);
    const double marginBottom = chartArea.GetSize().GetHeight() / 8.0;
    double labelsToChartAreaMargin = this->FromDIP(10);

    chartArea.Inset(marginX, marginTop, marginX, marginBottom);

    wxFont subtitleFont = wxFont(wxNORMAL_FONT->GetPointSize(),
        wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    gc->SetFont(subtitleFont, wxSystemSettings::GetAppearance().IsDark() ? *wxWHITE : *wxBLACK);

    gc->DrawText(chartTitle, chartArea.GetPosition().m_x + (chartArea.GetSize().GetWidth() - tw) / 2.0, chartArea.GetPosition().m_y - (marginTop) / 2.0 );

    wxAffineMatrix2D normalizedToChartArea{};
    normalizedToChartArea.Translate(chartArea.GetLeft(), chartArea.GetTop());
    normalizedToChartArea.Scale(chartArea.m_width, chartArea.m_height);

    // vertical axis
    double lowValueY = *std::min_element(values.begin(), values.end());
    double highValueY = *std::max_element(values.begin(), values.end());

    const auto& [segmentCount, rangeLow, rangeHigh] = calculateChartSegmentCountAndRange(lowValueY, highValueY);

    double yValueSpan = rangeHigh - rangeLow;
    lowValueY = rangeLow;
    highValueY = rangeHigh;

    double yLinesCount = segmentCount + 1;

    wxAffineMatrix2D normalizedToValueY{};
    normalizedToValueY.Translate(0, highValueY);
    normalizedToValueY.Scale(1, -1);
    normalizedToValueY.Scale(static_cast<double>(values.size() - 1), yValueSpan);

    gc->SetPen(wxPen(wxColor(128, 128, 128)));
    gc->SetFont(*wxNORMAL_FONT, wxSystemSettings::GetAppearance().IsDark() ? *wxWHITE : *wxBLACK);

    for (int i = 0; i < yLinesCount; i++)
    {
        double normalizedLineY = static_cast<double>(i) / (yLinesCount - 1);

        auto lineStartPoint = normalizedToChartArea.TransformPoint({ 0, normalizedLineY });
        auto lineEndPoint = normalizedToChartArea.TransformPoint({ 1, normalizedLineY });

        wxPoint2DDouble linePoints[] = { lineStartPoint, lineEndPoint };
        gc->StrokeLines(2, linePoints);

        if (drawYLabels) {
            double valueAtLineY = normalizedToValueY.TransformPoint({ 0, normalizedLineY }).m_y;

            auto text = wxString::Format("%.2f", valueAtLineY);
            text = wxControl::Ellipsize(text, dc, wxELLIPSIZE_MIDDLE, chartArea.GetLeft() - labelsToChartAreaMargin);

            double tw, th;
            gc->GetTextExtent(text, &tw, &th);
            gc->DrawText(text, chartArea.GetLeft() - labelsToChartAreaMargin - tw, lineStartPoint.m_y - th / 2.0);
        }
    }

    // horizontal axis 
    values = x;
    auto lowValueX = *std::min_element(values.begin(), values.end());
    auto highValueX = *std::max_element(values.begin(), values.end());

    const auto& [xsegmentCount, xrangeLow, xrangeHigh] = calculateChartSegmentCountAndRange(lowValueX, highValueX);

    double xValueSpan = xrangeHigh - xrangeLow;
    lowValueX = xrangeLow;
    highValueX = xrangeHigh;

    double xLinesCount = xsegmentCount + 1;

    wxAffineMatrix2D normalizedToValueX;
    normalizedToValueX.Translate(lowValueX, 0);
    normalizedToValueX.Scale(1, -1);
    normalizedToValueX.Scale(xValueSpan, static_cast<double>(values.size() - 1));

    gc->SetPen(wxPen(wxColor(128, 128, 128)));
    gc->SetFont(*wxNORMAL_FONT, wxSystemSettings::GetAppearance().IsDark() ? *wxWHITE : *wxBLACK);

    for (int i = 0; i < xLinesCount; i++)
    {
        double normalizedLineX = static_cast<double>(i) / (xLinesCount - 1);

        auto lineStartPoint = normalizedToChartArea.TransformPoint({ normalizedLineX, 0 });
        auto lineEndPoint = normalizedToChartArea.TransformPoint({ normalizedLineX, 1 });

        wxPoint2DDouble linePoints[] = { lineStartPoint, lineEndPoint };
        gc->StrokeLines(2, linePoints);

        if (drawXLabels) {
            double valueAtLineX = normalizedToValueX.TransformPoint({ normalizedLineX, 0 }).m_x;

            auto text = wxString::Format("%.2f", valueAtLineX);
            text = wxControl::Ellipsize(text, dc, wxELLIPSIZE_MIDDLE, chartArea.GetLeft() - labelsToChartAreaMargin);

            double tw, th;
            gc->GetTextExtent(text, &tw, &th);
            gc->DrawText(text, lineStartPoint.m_x - tw / 2.0, chartArea.GetLeftBottom().m_y + th / 2.0);
        }
    }

    wxPoint2DDouble leftHLinePoints[] = {
        normalizedToChartArea.TransformPoint({0, 0}),
        normalizedToChartArea.TransformPoint({0, 1}) };

    wxPoint2DDouble rightHLinePoints[] = {
        normalizedToChartArea.TransformPoint({1, 0}),
        normalizedToChartArea.TransformPoint({1, 1}) };

    gc->StrokeLines(2, leftHLinePoints);
    gc->StrokeLines(2, rightHLinePoints);

    // line plot
    wxPoint2DDouble* pointArray = new wxPoint2DDouble[values.size()];

    wxAffineMatrix2D valueToNormalized;
    valueToNormalized.Translate(lowValueX, highValueY);
    valueToNormalized.Scale(xValueSpan, -yValueSpan);
    valueToNormalized.Invert();
    wxAffineMatrix2D valueToChartArea = normalizedToChartArea;
    valueToChartArea.Concat(valueToNormalized);

    for (int i = 0; i < values.size(); i++)
    {
        pointArray[i] = valueToChartArea.TransformPoint({ x[i], y[i]});
    }

    gc->SetPen(wxPen(wxSystemSettings::GetAppearance().IsDark() ? *wxCYAN : *wxBLUE, 3));
    gc->StrokeLines(values.size(), pointArray);

    delete[] pointArray;
}

std::tuple<int, double, double> ChartControl::calculateChartSegmentCountAndRange(double origLow, double origHigh)
{
    constexpr double rangeMults[] = {0.2, 0.25, 0.5, 1.0, 2.0, 2.5, 5.0};
    constexpr int maxSegments = 6;

    double magnitude = std::floor(std::log10(origHigh - origLow));

    for (auto r : rangeMults)
    {
        double stepSize = r * std::pow(10.0, magnitude);
        double low = std::floor(origLow / stepSize) * stepSize;
        double high = std::ceil(origHigh / stepSize) * stepSize;

        int segments = round((high - low) / stepSize);

        if (segments <= maxSegments)
        {
            return std::make_tuple(segments, low, high);
        }
    }

    // return some defaults in case rangeMults and maxSegments are mismatched
    return std::make_tuple(10, origLow, origHigh);
}