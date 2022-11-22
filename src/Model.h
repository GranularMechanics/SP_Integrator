#ifndef MODEL_H
#define MODEL_H
#include <string>
#include <vector>

struct Parameter {
	std::string label{};
	double value{};
};

class Model {
	std::vector<Parameter> parameters{};
public:
	Model();
	std::vector<Parameter> getParameters() const;
	void set(const std::string& label, double value);
};

/*
    // graphics on the frame itself
    auto graphic1 = new wxListbook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);
    graphic1->SetInternalBorder(0);
    chart1 = new ChartControl(graphic1, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    chart1->Set("1st Chart", "Top Left", "Top Right", "Bottom Left", "Bottom Right");
    std::vector<double> v1;
    v1.push_back(0.34);
    v1.push_back(-0.17);
    v1.push_back(-0.98);
    v1.push_back(0.33);
    std::vector<double> v2;
    v2.push_back(0.34);
    v2.push_back(-0.17);
    v2.push_back(0.98);
    v2.push_back(0.33);
    std::vector<double> v3;
    v3.push_back(-0.34);
    v3.push_back(-0.17);
    v3.push_back(0.98);
    v3.push_back(0.33);
    std::vector<double> v4;
    v4.push_back(-0.34);
    v4.push_back(-0.17);
    v4.push_back(0.98);
    v4.push_back(-0.33);
    chart1->Set(v1, v2, v3, v4);
    graphic1->AddPage(chart1, "1st Chart");

    chart2 = new ChartControl(graphic1, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    chart2->Set("1st Chart", "Top Left", "Top Right", "Bottom Left", "Bottom Right");
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

    void ChartControl::Set(const wxString& title_, const wxString& lt, const wxString& rt, const wxString& lb, const wxString& rb) {
    title = title_;
    tlt = lt;
    trt = rt;
    tlb = lb;
    trb = rb;
}

void ChartControl::Set(
    std::vector<double> values_ltx,
    std::vector<double> values_lty,
    std::vector<double> values_rbx,
    std::vector<double> values_rby) {
    ltx = values_ltx;
    lty = values_lty;
    rbx = values_rbx;
    rby = values_rby;
}

void ChartControl::OnPaint(wxPaintEvent& evt)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();
    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if (gc && values.size() > 0)
    {
        wxFont titleFont = wxFont(wxNORMAL_FONT->GetPointSize() * 2.0,
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

        gc->DrawText(this->title, (chartArea.GetSize().GetWidth() - tw) / 2.0, (marginTop - th) / 2.0);

        wxFont subtitleFont = wxFont(wxNORMAL_FONT->GetPointSize(),
            wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM);

        gc->SetFont(subtitleFont, wxSystemSettings::GetAppearance().IsDark() ? *wxWHITE : *wxBLACK);

        auto halfWidth = static_cast<double>(GetSize().GetWidth()) / 2.0;
        auto halfHeight = static_cast<double>(GetSize().GetHeight()) / 2.0;

        wxRect2DDouble leftTopArea{ 0, th, halfWidth, halfHeight };
        DrawComponent(dc, gc, leftTopArea, tlt, ltx, lty);

        wxRect2DDouble rightTopArea{ halfWidth, th, halfWidth, halfHeight };
        DrawComponent(dc, gc, rightTopArea, trt, rbx, lty);

        wxRect2DDouble leftBottomArea{ 0, halfHeight, halfWidth, halfHeight };
        DrawComponent(dc, gc, leftBottomArea, tlb, rbx, rby);

        wxRect2DDouble rightBottomArea{ halfWidth, halfHeight, halfWidth, halfHeight };
        DrawComponent(dc, gc, rightBottomArea, trb, rbx, rby);

        delete gc;
    }
}

void ChartControl::DrawComponent(
    wxAutoBufferedPaintDC& dc, 
    wxGraphicsContext* gc, 
    wxRect2DDouble chartArea, 
    const wxString& chartTitle,
    std::vector<double> x, 
    std::vector<double> y) {

    double tw, th;
    gc->GetTextExtent(this->title, &tw, &th);
    const double titleTopBottomMinimumMargin = this->FromDIP(10);

    const double marginX = chartArea.GetSize().GetWidth() / 8.0;
    const double marginTop = std::max(chartArea.GetSize().GetHeight() / 8.0, titleTopBottomMinimumMargin * 2.0 + th);
    const double marginBottom = chartArea.GetSize().GetHeight() / 8.0;
    double labelsToChartAreaMargin = this->FromDIP(10);

    chartArea.Inset(marginX, marginTop, marginX, marginBottom);

    wxFont subtitleFont = wxFont(wxNORMAL_FONT->GetPointSize(),
        wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM);

    gc->SetFont(subtitleFont, wxSystemSettings::GetAppearance().IsDark() ? *wxWHITE : *wxBLACK);

    gc->DrawText(chartTitle, chartArea.GetPosition().m_x + (chartArea.GetSize().GetWidth() - tw) / 2.0, chartArea.GetPosition().m_y + (marginTop - th) / 2.0);

    wxAffineMatrix2D normalizedToChartArea{};
    normalizedToChartArea.Translate(chartArea.GetLeft(), chartArea.GetTop());
    normalizedToChartArea.Scale(chartArea.m_width, chartArea.m_height);

    double lowValue = *std::min_element(x.begin(), x.end());
    double highValue = *std::max_element(x.begin(), x.end());

    const auto& [segmentCount, rangeLow, rangeHigh] = calculateChartSegmentCountAndRange(lowValue, highValue);

    double yValueSpan = rangeHigh - rangeLow;
    lowValue = rangeLow;
    highValue = rangeHigh;

    double yLinesCount = segmentCount + 1;

    wxAffineMatrix2D normalizedToValue{};
    normalizedToValue.Translate(0, highValue);
    normalizedToValue.Scale(1, -1);
    normalizedToValue.Scale(static_cast<double>(values.size() - 1), yValueSpan);

    gc->SetPen(wxPen(wxColor(128, 128, 128)));
    gc->SetFont(*wxNORMAL_FONT, wxSystemSettings::GetAppearance().IsDark() ? *wxWHITE : *wxBLACK);

    for (int i = 0; i < yLinesCount; i++)
    {
        double normalizedLineY = static_cast<double>(i) / (yLinesCount - 1);

        auto lineStartPoint = normalizedToChartArea.TransformPoint({ 0, normalizedLineY });
        auto lineEndPoint = normalizedToChartArea.TransformPoint({ 1, normalizedLineY });

        wxPoint2DDouble linePoints[] = { lineStartPoint, lineEndPoint };
        gc->StrokeLines(2, linePoints);

        double valueAtLineY = normalizedToValue.TransformPoint({ 0, normalizedLineY }).m_y;

        auto text = wxString::Format("%.2f", valueAtLineY);
        text = wxControl::Ellipsize(text, dc, wxELLIPSIZE_MIDDLE, chartArea.GetLeft() - labelsToChartAreaMargin);

        double tw, th;
        gc->GetTextExtent(text, &tw, &th);
        gc->DrawText(text, chartArea.GetLeft() - labelsToChartAreaMargin - tw, lineStartPoint.m_y - th / 2.0);
    }

    wxPoint2DDouble leftHLinePoints[] = {
        normalizedToChartArea.TransformPoint({0, 0}),
        normalizedToChartArea.TransformPoint({0, 1}) };

    wxPoint2DDouble rightHLinePoints[] = {
        normalizedToChartArea.TransformPoint({1, 0}),
        normalizedToChartArea.TransformPoint({1, 1}) };

    gc->StrokeLines(2, leftHLinePoints);
    gc->StrokeLines(2, rightHLinePoints);

    wxPoint2DDouble* pointArray = new wxPoint2DDouble[x.size()];

    wxAffineMatrix2D valueToNormalized = normalizedToValue;
    valueToNormalized.Invert();
    wxAffineMatrix2D valueToChartArea = normalizedToChartArea;
    valueToChartArea.Concat(valueToNormalized);

    for (int i = 0; i < x.size(); i++)
    {
        pointArray[i] = valueToChartArea.TransformPoint({ static_cast<double>(i), x[i] });
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

class ChartControl : public wxWindow
{
public:
    ChartControl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size);

    std::vector<double> values;
    void Set(const wxString& title, const wxString& lt, const wxString& rt, const wxString& lb, const wxString& rb);
    void Set(std::vector<double> values_ltx,
        std::vector<double> values_lty,
        std::vector<double> values_rbx,
        std::vector<double> values_rby);

private:
    wxString title;
    wxString tlt, trt, tlb, trb;
    std::vector<double> ltx;
    std::vector<double> lty;
    std::vector<double> rbx;
    std::vector<double> rby;
    void DrawComponent(wxAutoBufferedPaintDC& dc, wxGraphicsContext* gc,
        wxRect2DDouble chartArea, const wxString& chartTitle,
        std::vector<double> x, std::vector<double> y);
    void OnPaint(wxPaintEvent &evt);
    std::tuple<int, double, double> calculateChartSegmentCountAndRange(double origLow, double origHigh);
};*/
#endif
