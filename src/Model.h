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
#endif
