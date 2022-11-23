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
	std::vector<KeyValue> parameters{};
public:
	Model();
	std::vector<KeyValue> GetParameters() const;
	void Set(const std::string& label, double value);
};
#endif
