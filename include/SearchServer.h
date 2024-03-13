#ifndef SEARCH_ENGINE_SEARCHSERVER_H
#define SEARCH_ENGINE_SEARCHSERVER_H

#include <vector>
#include "InvertedIndex.h"

struct RelativeIndex{
    size_t docId;
    float rank;
    bool operator == (const RelativeIndex& other) const {
        return (docId == other.docId && rank == other.rank);
    }
};

class SearchServer {
    void getUniqQueries(const std::vector<std::string> &queriesInput, std::vector<std::string> &uniqQueries);
    void setRelevance(std::vector<std::string> &uniqQueries, std::vector<RelativeIndex> &relevance);
    void setAnswer(std::vector<std::string> &uniqQueries, std::vector<std::vector<RelativeIndex>> &answer, std::vector<RelativeIndex> &relevance);
public:
    InvertedIndex _index;
    SearchServer(InvertedIndex& idx){
        _index = idx;
    };

    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queriesInput);

};


#endif //SEARCH_ENGINE_SEARCHSERVER_H
