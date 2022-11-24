#include "Model.h"
#include <algorithm>

Model::Model() {
	defaultLabel = "MCC";
	defaultParameters.push_back(KeyValue{ "M", 0.9 });
	defaultParameters.push_back(KeyValue{ "kappa", 0.05 });
	defaultParameters.push_back(KeyValue{ "lambda", 0.25 });
	defaultParameters.push_back(KeyValue{ "nu", 0.25 });
	label = defaultLabel;
	parameters = defaultParameters;
}

std::string Model::GetLabel() const {
	return label;
}

std::string Model::GetDefaultLabel() const {
	return defaultLabel;
}

std::vector<KeyValue> Model::GetParameters() const {
	return parameters;
}

std::vector<KeyValue> Model::GetDefaultParameters() const {
	return defaultParameters;
}

void Model::Set(const std::string& label) {
	this->label = label;
}

void Model::Set(const std::vector<KeyValue>& parameters) {
	this->parameters = parameters;
}

void Model::Set(const std::string& label, double value) {
	auto Iter = std::find_if(parameters.begin(), parameters.end(), [label](const KeyValue& p) {
		return label == p.label;
		});
	if (Iter != parameters.end()) {
		Iter->value = value;
	}
}