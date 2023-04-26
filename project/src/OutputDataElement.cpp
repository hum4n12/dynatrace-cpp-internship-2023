#include "OutputDataElement.h"
#include <iostream>
#include <string>

using namespace internship;

OutputDataElement::OutputDataElement(){}

std::string OutputDataElement::getOsName() {
	return osName;
}

std::string OutputDataElement::getOsCycle() {
	return osCycle;
}

const unsigned int OutputDataElement::getSupportPeriodInDays() const {
	return supportPeriodInDays;
}

void OutputDataElement::setOsName(const std::string& osName) {
	this->osName = osName;
}

void OutputDataElement::setOsCycle(const std::string& osCycle) {
	this->osCycle = osCycle;
}

void OutputDataElement::setSupportPeriodInDays(unsigned int supportPeriodInDays) {
	this->supportPeriodInDays = supportPeriodInDays;
}

bool OutputDataElement::operator<(const OutputDataElement& other) const {
	return supportPeriodInDays > other.supportPeriodInDays;
}

std::ostream& internship::operator<<(std::ostream& stream, const OutputDataElement& obj)
{
	stream << obj.osName << ' ' << obj.osCycle << ' ' << obj.supportPeriodInDays;
	return stream;
}
