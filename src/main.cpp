#include "SearchServer.cpp"
#include "ConverterJSON.cpp"
#include "InvertedIndex.cpp"

int main() {
    InvertedIndex invertedIndex;
    ConverterJSON converterJson;

    invertedIndex.updateDocumentBase(converterJson.getTextDocuments());

    SearchServer searchServer(invertedIndex);

    converterJson.putAnswers(searchServer.search(converterJson.getRequests()));

    return 0;
}
