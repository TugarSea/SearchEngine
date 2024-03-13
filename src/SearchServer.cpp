#include "../include/SearchServer.h"
#include <algorithm>

void bubbleSort(std::vector<RelativeIndex> &relevance)
{
    int i, j;
    bool swapped;

    for (i = 0; i < relevance.size(); i++) {
        swapped = false;

        for (j = 0; j < relevance.size() - i; j++) {
            if (relevance[j].rank < relevance[j + 1].rank) {
                std::swap(relevance[j], relevance[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

void SearchServer::getUniqQueries(const std::vector<std::string> &queriesInput, std::vector<std::string> &uniqQueries) {
    for (const auto & i : queriesInput) {
        std::string uniqWords;
        std::string word;

        for (int j = 0; j < i.length(); ++j) {
            if(i[j] != ' ')
                word+= i[j];

            if (!word.empty() && uniqWords.find(word) == std::string::npos && (i[j] == ' ' || j + 1 == i.length())) {
                uniqWords += word + " ";
                uniqQueries.push_back(word);
                word = "";
            }
        }
    }
};

void SearchServer::setRelevance(std::vector<std::string> &uniqQueries, std::vector<RelativeIndex> &relevance) {
    float max_relevance = 0;
    for (int j = 0; j < _index.freqDictionary.size(); ++j) {


        RelativeIndex relativeIndex{};
        for (const auto & el : uniqQueries) {
            if (_index.freqDictionary.find(el) != _index.freqDictionary.end() && j < _index.freqDictionary.find(el)->second.size())
                relativeIndex.rank += _index.freqDictionary.find(el)->second[j].count;

        }
        relativeIndex.docId = j;
        relevance.push_back(relativeIndex);

        if (relativeIndex.rank > max_relevance)
            max_relevance = relativeIndex.rank;

        relativeIndex.rank = 0;


    }

    for (auto & i : relevance)
        i.rank /= max_relevance;
}

void SearchServer::setAnswer(std::vector<std::string> &uniqQueries, std::vector<std::vector<RelativeIndex>> &answer, std::vector<RelativeIndex> &relevance) {
    for (const auto & el : uniqQueries) {
        std::vector<RelativeIndex> preAnswer;
        int j = 0;
        preAnswer.clear();
        RelativeIndex relativeIndex{};

        while (_index.freqDictionary.find(el) != _index.freqDictionary.end() && j < _index.freqDictionary.find(el)->second.size()) {
            relativeIndex.docId = j;
            relativeIndex.rank = relevance[j].rank;
            preAnswer.push_back(relativeIndex);
            j++;

        }

        if (preAnswer.empty()) {
            relativeIndex.docId = 0;
            relativeIndex.rank = 0;
            preAnswer.push_back(relativeIndex);
        }
        answer.push_back(preAnswer);
    }
}

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queriesInput)
{
    std::vector<std::string> uniqQueries;
    std::vector<std::vector<RelativeIndex>> answer;
    std::vector<RelativeIndex> relevance;

    getUniqQueries(queriesInput, uniqQueries);
    setRelevance(uniqQueries, relevance);
    setAnswer(uniqQueries, answer, relevance);

    for (auto& el : answer) {
        bubbleSort(el);
    }

    return answer;
}






