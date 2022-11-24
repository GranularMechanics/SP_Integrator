#ifndef INTEGRATOR_H
#define INTEGRATOR_H
#include <string>
#include <vector>

#ifndef KEY_VALUE
#define KEY_VALUE
struct KeyValue {
	std::string label{};
	double value{};
};
#endif
struct QuadFrame {
	std::vector<double> v1;
	std::vector<double> v2;
	std::vector<double> v3;
	std::vector<double> v4;
};

class Integrator {
	std::vector<KeyValue> defaultSettings{};
	std::vector<KeyValue> defaultInitialState{};
	std::vector<KeyValue> defaultLoading{};
	std::vector<KeyValue> settings{};
	std::vector<KeyValue> initialState{};
	std::vector<KeyValue> loading{};
public:
	Integrator();
	std::vector<KeyValue> GetDefaultSettings() const;
	std::vector<KeyValue> GetDefaultInitialState() const;
	std::vector<KeyValue> GetDefaultLoading() const;
	std::vector<KeyValue> GetSettings() const;
	std::vector<KeyValue> GetInitialState() const;
	std::vector<KeyValue> GetLoading() const;
	void Set(const std::string& label, double value);
	void SetSettings(const std::vector<KeyValue>& settings);
	void SetInitialState(const std::vector<KeyValue>& initialState);
	void SetLoading(const std::vector<KeyValue>& loading);
	std::vector<double> Get(const std::string& label) const;
};
#endif
