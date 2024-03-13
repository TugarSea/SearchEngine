#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H

#include <vector>
#include <string>
#include <exception>
#include <cassert>
#include <fstream>
#include "../nlohmann_json/json.hpp"
#include "SearchServer.h"

class ConverterJSON {
    class InvalidData: public std::exception
    {
        const char* what() const noexcept override {
            return "Incorrect JSON format";
        }
    };
    void isCorrect(std::ifstream &file, nlohmann::json::value_type &jsonData);
public:
    ConverterJSON() = default;

    std::vector<std::string> getTextDocuments();

    int getResponsesLimit();

    std::vector<std::string> getRequests();

    void putAnswers(std::vector<std::vector<RelativeIndex>>answers);
};


#endif //SEARCH_ENGINE_CONVERTERJSON_H
