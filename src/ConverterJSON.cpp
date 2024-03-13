#include "../include/ConverterJSON.h"

void ConverterJSON::isCorrect(std::ifstream &file, nlohmann::json::value_type &jsonData) {
    assert(file.is_open());
    try {
        file >> jsonData;
    }
    catch (const std::exception & x) {
        std::cerr << "Caught exception: ";
        throw InvalidData();
    }
}

std::vector<std::string> ConverterJSON::getTextDocuments() {
    std::vector<std::string> configData;
    nlohmann::json::value_type jsonData;
    std::ifstream file;

    file.open("config.json", std::ifstream::binary);
    isCorrect(file, jsonData);
    configData = jsonData["files"];

    for (auto & i : configData) {
        std::ifstream tempFile;
        std::string text;

        tempFile.open(i, std::ifstream::in);
        assert(tempFile.is_open());

        while (!tempFile.eof()) { // std::getline(tempFile, partText)
            std::string partText;
            tempFile >> partText;
            text += partText + " ";
        }
        i = text;
        tempFile.close();
    }

    file.close();
    return configData;
}

int ConverterJSON::getResponsesLimit() {
    nlohmann::json::value_type jsonData;
    std::ifstream file;

    file.open("config.json", std::ifstream::binary);
    isCorrect(file, jsonData);

    return jsonData["config"]["max_responses"];
}

std::vector<std::string> ConverterJSON::getRequests() {
    std::vector<std::string> requestData;
    nlohmann::json::value_type jsonData;
    std::ifstream file;

    file.open("requests.json", std::ifstream::binary);
    isCorrect(file, jsonData);
    requestData = jsonData["requests"];

    file.close();
    return requestData;
}

void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>> answers) {
    std::ofstream file("answers.json");
    if (file)
        file.clear();

    nlohmann::json answersJson, requestsJson, request, resultJson, relevance, docid;
    int i = 0, j = 0;

    while(i < answers.size()) {
        if (answers[i][j].rank != 0) {
            request["result"] = "true";
            while (j < answers[i].size()) {
                docid["rank"] = answers[i][j].rank;
                docid["docid"] = answers[i][j].docId;
                std::string docidNum =  std::to_string(answers[i][j].docId + 1);
                relevance[docidNum] = docid;
                j++;
            }
        }
        else request["result"] = "false";

        request["relevance"] = relevance;
        j = 0;
        i++;
        docid.clear();
        relevance.clear();
        std::string id = std::to_string(i);
        if (i < 10) id = "00" + id;
        else if (i < 100) id = "0" + id;
        std::string requestNum = "request" + id;
        requestsJson[requestNum] = request;
    }

    answersJson["answers"] = requestsJson;

    file << answersJson;
    file.close();
}


