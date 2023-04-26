#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

#include <date/date.h>
#include <nlohmann/json.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "internship.h"
#include "OutputDataElement.h"

using json = nlohmann::json;
using namespace date;

namespace internship {

    const std::string OS_KEY = "os";
    const std::string PRODUCT_VERSIONS_KEY = "versions";
    const std::string NAME_KEY = "name";
    const std::string CYCLE_KEY = "cycle";
    const std::string RELEASE_DATE_KEY = "releaseDate";
    const std::string EOL_KEY = "eol";

    long countSupportPeriodInDays(std::string date1, std::string date2) {
        using namespace boost;

        try {
            gregorian::date dateFormat1(gregorian::from_string(date1));
            gregorian::date dateFormat2(gregorian::from_string(date2));
            gregorian::date_period datePeriod(dateFormat1, dateFormat2);
            return abs(datePeriod.length().days()) + 1;
        }
        catch (...) {
            throw std::runtime_error("Date parsing error");
        }
    }

    void collectVersions(const json& product, std::vector<OutputDataElement>& filteredProducts) {
        for (const json& version : product[PRODUCT_VERSIONS_KEY]) {
            OutputDataElement element;
            try {
                element.setOsName(product[NAME_KEY]);
                element.setOsCycle(version[CYCLE_KEY]);
                element.setSupportPeriodInDays(countSupportPeriodInDays(version[RELEASE_DATE_KEY], version[EOL_KEY]));
                filteredProducts.push_back(element);
            }
            catch (const std::exception& exc) {
                std::cerr << exc.what() << std::endl;
                continue;
            }
        }

    }

    std::vector<OutputDataElement> parse(const std::string& jsonFileName, int elementsCount) {
        std::vector<OutputDataElement> filteredProducts;
        
        if (elementsCount <= 0) {
            return filteredProducts;
        }

        std::ifstream f(jsonFileName);
        json data = json::parse(f);

        for (const auto& [id, product] : data.items()) {
            if (product[OS_KEY]) {
                collectVersions(product, filteredProducts);
            }
        }
        std::sort(filteredProducts.begin(), filteredProducts.end());

        if (elementsCount > filteredProducts.size()) {
            elementsCount = filteredProducts.size();
        }

        std::vector<OutputDataElement> result;
        std::copy(filteredProducts.begin(), filteredProducts.begin() + elementsCount, std::back_inserter(result));

        return result;
    }

    // do not remove this function
    void solution(const std::string& jsonFileName, int elementsCount) {
        std::vector<OutputDataElement> products = parse(jsonFileName, elementsCount);

        for (int i = 0; i < products.size(); i++) {
            OutputDataElement j = products[i];
            std::cout << j << std::endl;
        }
    }
}