#ifndef INTEGRATOR_H
#define INTEGRATOR_H
#include <string>
#include <vector>

struct Settings {
	std::string label{};
	double value{};
};

class Integrator {
	std::vector<Settings> settings{};
public:
	Integrator();
	std::vector<Settings> getSettings() const;
	void set(const std::string& label, double value);
};
#endif
