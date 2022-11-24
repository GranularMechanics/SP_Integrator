#ifndef MODEL_H
#define MODEL_H
#include <string>
#include <vector>

#ifndef KEY_VALUE
#define KEY_VALUE
struct KeyValue {
	std::string label{};
	double value{};
};
#endif

class Model {
	std::string defaultLabel{};
	std::vector<KeyValue> defaultParameters{};
	std::string label;
	std::vector<KeyValue> parameters{};
public:
	Model();
	std::string GetLabel() const;
	std::string GetDefaultLabel() const;
	std::vector<KeyValue> GetParameters() const;
	std::vector<KeyValue> GetDefaultParameters() const;
	void Set(const std::string& label);
	void Set(const std::vector<KeyValue>& parameters);
	void Set(const std::string& label, double value);
};
#endif
