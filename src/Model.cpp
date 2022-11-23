#include "Model.h"
#include <algorithm>

Model::Model() {
	parameters.push_back(KeyValue{ "M", 0.9 });
	parameters.push_back(KeyValue{ "kappa", 0.05 });
	parameters.push_back(KeyValue{ "lambda", 0.25 });
	parameters.push_back(KeyValue{ "nu", 0.25 });
}

std::vector<KeyValue> Model::GetParameters() const {
	return parameters;
}

void Model::Set(const std::string& label, double value) {
	auto Iter = std::find_if(parameters.begin(), parameters.end(), [label](const KeyValue& p) {
		return label == p.label;
		});
	if (Iter != parameters.end()) {
		Iter->value = value;
	}
}