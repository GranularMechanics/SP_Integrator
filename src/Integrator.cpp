#include "Integrator.h"
#include <algorithm>

Integrator::Integrator() {
	settings.push_back(KeyValue{ "f_tolerance", 1.0e-5 });
    settings.push_back(KeyValue{ "e_tolerance", 1.0e-5 });
    settings.push_back(KeyValue{ "r_tolerance", 1.0e-5 });
    settings.push_back(KeyValue{ "d_tolerance", 1.0e-5 });
    settings.push_back(KeyValue{ "dt_next", 2.0 });
    settings.push_back(KeyValue{ "r_min", 0.01 });
    settings.push_back(KeyValue{ "dt_max", 1.0 });
    initialState.push_back(KeyValue{ "v", 3.0 });
    initialState.push_back(KeyValue{ "a", 120.0 });
    initialState.push_back(KeyValue{ "q", 0.0 });
    initialState.push_back(KeyValue{ "p", 100.0 });
    loading.push_back(KeyValue{ "eq", 0.0 });
    loading.push_back(KeyValue{ "ev", 0.130 });
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
        v.push_back(0.33);
    }
    else {

    }
    return v;
}
