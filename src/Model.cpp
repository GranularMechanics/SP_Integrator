#include "Model.h"
#include <algorithm>

Model::Model() {
	parameters.push_back(Parameter{ "lambda", 0.25 });
	parameters.push_back(Parameter{ "kappa", 0.05 });
	parameters.push_back(Parameter{ "nu", 0.25 });
	parameters.push_back(Parameter{ "M", 0.9 });
}

std::vector<Parameter> Model::getParameters() const {
	return parameters;
}

void Model::set(const std::string& label, double value) {
	auto Iter = std::find_if(parameters.begin(), parameters.end(), [label](const Parameter& p) {
		return label == p.label;
		});
	if (Iter != parameters.end()) {
		Iter->value = value;
	}
}