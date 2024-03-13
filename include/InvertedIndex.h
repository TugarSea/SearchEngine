#include <cstddef>
#include <vector>
#include <iostream>
#include <map>
#include <unordered_set>
#include <thread>
#include <mutex>

#ifndef SEARCH_ENGINE_INVERTEDINDEX_H
#define SEARCH_ENGINE_INVERTEDINDEX_H

struct Entry {
    size_t docId, count;

    bool operator ==(const Entry& other) const {
        return (docId == other.docId &&
                count == other.count);
    }
};


class InvertedIndex {
    std::vector<std::string> docs;
    void separateDocs();
    void counting(std::vector<Entry> &vecEntry,const std::string& word, int j);

public:
    mutable std::mutex countingAccess;
    InvertedIndex() = default;
    void updateDocumentBase(const std::vector<std::string>& inputDocs);
    std::vector<Entry> getWordCount(const std::string& word);

    std::map<std::string, std::vector<Entry>> freqDictionary;

    InvertedIndex(InvertedIndex  &x) {
        std::lock_guard<std::mutex> lk2(x.countingAccess);
        x.freqDictionary = freqDictionary;
    }

    InvertedIndex& operator =( InvertedIndex  &x) {
        std::lock(this->countingAccess, x.countingAccess);
        std::lock_guard<std::mutex> lk1(this->countingAccess, std::adopt_lock);
        std::lock_guard<std::mutex> lk2(x.countingAccess, std::adopt_lock);
        this->freqDictionary = x.freqDictionary;
        return *this;
    }
};


#endif //SEARCH_ENGINE_INVERTEDINDEX_H
