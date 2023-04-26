#pragma once
#include <iostream>

namespace internship {

	class OutputDataElement {
	private:
		std::string osName;
		std::string osCycle;
		unsigned int supportPeriodInDays;
	public:
		OutputDataElement();
		OutputDataElement(const std::string& name, const std::string& cycle, long supportDays) : osName(name), osCycle(cycle), supportPeriodInDays(supportDays) {};
		std::string getOsName();
		std::string getOsCycle();
		const unsigned int getSupportPeriodInDays() const;
		void setOsName(const std::string& osName);
		void setOsCycle(const std::string& osCycle);
		void setSupportPeriodInDays(unsigned int supportPeriodInDays);
		bool operator<(const OutputDataElement& other) const;
		friend std::ostream& operator<<(std::ostream& stream, const OutputDataElement& obj);
	};
}