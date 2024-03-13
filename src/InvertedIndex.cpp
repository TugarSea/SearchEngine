#include "../include/InvertedIndex.h"

void InvertedIndex::updateDocumentBase(const std::vector<std::string>& inputDocs)
{
    if (!docs.empty())
        docs.clear();
    for (const auto & el : inputDocs) {
        docs.push_back(el);
    }
    separateDocs();
};

void InvertedIndex::separateDocs()
{
    std::unordered_set<std::string> uniqWords;
    std::string word;

    for(auto & doc : docs) {
        for (int j = 0; j < doc.length(); ++j) {
            if (doc[j] != ' ')
                word += doc[j];
            else if (uniqWords.count(word) == 0) {
                getWordCount(word);
                uniqWords.insert(word);
                word.clear();
            }
            else word.clear();
        }

    }
};

void InvertedIndex::counting(std::vector<Entry> &vecEntry, const std::string& word, int j) {
    j--;
    if (j < docs.size()) {
        size_t count{};
        Entry entry{};

        for (size_t i {}; i <= docs[j].length() - word.length();) {
            size_t position = docs[j].find(word, i);
            if (position == std::string::npos) break;
            ++count;
            i = position + 1;
        }

        entry.docId = j;
        entry.count = count;

        if (count != 0) {
            countingAccess.lock();
            vecEntry.push_back(entry);
            countingAccess.unlock();
        }
    }
}

std::vector<Entry> InvertedIndex::getWordCount(const std::string& word) {
    std::vector<Entry> vecEntry;
    std::vector<std::thread> threadWordCount;

    for (int j = 0; j <= docs.size(); ++j) {
        std::thread thread([&]() {counting(vecEntry, word, j);});
        threadWordCount.push_back(std::move(thread));
    }

    for (auto &el : threadWordCount) {
        if(el.joinable())
            el.join();
    }

    freqDictionary.insert({word, vecEntry});

    return vecEntry;
}



