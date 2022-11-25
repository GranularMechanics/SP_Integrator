#include "Integrator.h"
#include <algorithm>

Integrator::Integrator() {
	defaultSettings.push_back(KeyValue{ "f_tolerance", 1.0e-5 });
    defaultSettings.push_back(KeyValue{ "e_tolerance", 1.0e-5 });
    defaultSettings.push_back(KeyValue{ "r_tolerance", 1.0e-5 });
    defaultSettings.push_back(KeyValue{ "d_tolerance", 1.0e-5 });
    defaultSettings.push_back(KeyValue{ "dt_next", 2.0 });
    defaultSettings.push_back(KeyValue{ "r_min", 0.01 });
    defaultSettings.push_back(KeyValue{ "dt_max", 1.0 });
    defaultInitialState.push_back(KeyValue{ "s_zz", 100.0 });
    defaultInitialState.push_back(KeyValue{ "s_zy", 0.0 });
    defaultInitialState.push_back(KeyValue{ "s_zx", 0.0 });
    defaultInitialState.push_back(KeyValue{ "s_yz", 0.0 });
    defaultInitialState.push_back(KeyValue{ "s_yy", 100.0 });
    defaultInitialState.push_back(KeyValue{ "s_yx", 0.0 });
    defaultInitialState.push_back(KeyValue{ "s_xz", 0.0 });
    defaultInitialState.push_back(KeyValue{ "s_xy", 0.0 });
    defaultInitialState.push_back(KeyValue{ "s_xx", 100.0 });
    defaultInitialState.push_back(KeyValue{ "v", 3.0 });
    defaultInitialState.push_back(KeyValue{ "a", 120.0 });
    defaultInitialState.push_back(KeyValue{ "q", 0.0 });
    defaultInitialState.push_back(KeyValue{ "p", 100.0 });
    defaultLoading.push_back(KeyValue{ "e_zz", 0.0434 });
    defaultLoading.push_back(KeyValue{ "e_zy", 0.0 });
    defaultLoading.push_back(KeyValue{ "e_zx", 0.0 });
    defaultLoading.push_back(KeyValue{ "e_yz", 0.0 });
    defaultLoading.push_back(KeyValue{ "e_yy", 0.0434 });
    defaultLoading.push_back(KeyValue{ "e_yx", 0.0 });
    defaultLoading.push_back(KeyValue{ "e_xz", 0.0 });
    defaultLoading.push_back(KeyValue{ "e_xy", 0.0 });
    defaultLoading.push_back(KeyValue{ "e_xx", 0.0434 });
    defaultLoading.push_back(KeyValue{ "e_q", 0.0 });
    defaultLoading.push_back(KeyValue{ "e_v", 0.1302 });
    settings = defaultSettings;
    initialState = defaultInitialState;
    loading = defaultLoading;
}

std::vector<KeyValue> Integrator::GetDefaultSettings() const {
	return defaultSettings;
}

std::vector<KeyValue> Integrator::GetDefaultInitialState() const {
    return defaultInitialState;
}

std::vector<KeyValue> Integrator::GetDefaultLoading() const {
    return defaultLoading;
}

std::vector<KeyValue> Integrator::GetSettings() const {
    return settings;
}

std::vector<KeyValue> Integrator::GetInitialState() const {
    return initialState;
}

std::vector<KeyValue> Integrator::GetLoading() const {
    return loading;
}

void Integrator::Set(const std::string& label, double value) {
	auto Iter = std::find_if(settings.begin(), settings.end(), [label](const KeyValue& p) {
		return label == p.label;
		});
	if (Iter != settings.end()) {
		Iter->value = value;
	}
}

void Integrator::SetSettings(const std::vector<KeyValue>& settings) {
    this->settings = settings;
}

void Integrator::SetInitialState(const std::vector<KeyValue>& initialState) {
    this->initialState = initialState;
}

void Integrator::SetLoading(const std::vector<KeyValue>& loading) {
    this->loading = loading;
}

std::vector<double> Integrator::Get(const std::string& label) const {
    typedef std::vector<double> wxVector;
    wxVector v;
    if (label == "p") {
        v.push_back(0.34);
        v.push_back(-0.17);
        v.push_back(-0.98);
        v.push_back(0.33);
    }
    else if (label == "q") {
        v.push_back(-0.98);
        v.push_back(0.34);
        v.push_back(-0.17);
        v.push_back(0.33);
    }
    else if (label == "eq") {
        v.push_back(0.34);
        v.push_back(0.33);
        v.push_back(-0.17);
        v.push_back(-0.98);
    }
    else if (label == "v") {
        v.push_back(0.34);
        v.push_back(-0.98);
        v.push_back(-0.17);
        v.push_back(0.23);
    }
    else {

    }
    return v;
}
