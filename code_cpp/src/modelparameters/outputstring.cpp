#include "modelparameters.ih"

/*
 * Output the model parameters using stdout.
 */

std::string ModelParameters::outputString() const
{
	std::string outputLine;
	std::ostringstream oss;

	// Assign all values
	oss << nbORs << ' ' << cf << ' ' << cv << ' ' << meanDuration << ' ' << stdDuration << ' ' << eps1 << ' ' << eps2 << ' ' << nbScenarios << ' ' << seed;

	outputLine = oss.str();

	return outputLine;
}