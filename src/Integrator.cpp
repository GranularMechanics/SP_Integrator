#include "Integrator.h"
#include <algorithm>

Integrator::Integrator() {
	settings.push_back(Settings{ "f_tolerance", 1.0e-5 });
	settings.push_back(Settings{ "e_tolerance", 1.0e-5 });
	settings.push_back(Settings{ "r_tolerance", 1.0e-5 });
	settings.push_back(Settings{ "d_tolerance", 1.0e-5 });
}

std::vector<Settings> Integrator::getSettings() const {
	return settings;
}

void Integrator::set(const std::string& label, double value) {
	auto Iter = std::find_if(settings.begin(), settings.end(), [label](const Settings& p) {
		return label == p.label;
		});
	if (Iter != settings.end()) {
		Iter->value = value;
	}
}