#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

// Function to split a string into words
std::vector<std::string> split(const std::string &text)
{
    std::vector<std::string> words;
    std::stringstream ss(text);
    std::string word;
    while (ss >> word)
    {
        words.push_back(word);
    }
    return words;
}

// Mapper function
std::vector<std::pair<std::string, int>> mapper(const std::string &document)
{
    std::vector<std::pair<std::string, int>> wordCounts;
    std::vector<std::string> words = split(document);
    for (const auto &word : words)
    {
        wordCounts.emplace_back(word, 1);
    }
    return wordCounts;
}

// Shuffle and sort phase
std::map<std::string, std::vector<int>> shuffleAndSort(const std::vector<std::pair<std::string, int>> &mappedData)
{
    std::map<std::string, std::vector<int>> groupedData;
    for (const auto &pair : mappedData)
    {
        groupedData[pair.first].push_back(pair.second);
    }
    return groupedData;
}

// Reducer function
std::map<std::string, int> reducer(const std::map<std::string, std::vector<int>> &groupedData)
{
    std::map<std::string, int> reducedData;
    for (const auto &pair : groupedData)
    {
        reducedData[pair.first] = std::accumulate(pair.second.begin(), pair.second.end(), 0);
    }
    return reducedData;
}

int main()
{
    // Input: List of documents
    std::vector<std::string> documents = {
        "hello world hello",
        "world of programming",
        "hello from the other side"};

    // Simulating MapReduce
    std::vector<std::pair<std::string, int>> mappedData;
    for (const auto &document : documents)
    {
        std::vector<std::pair<std::string, int>> partialMap = mapper(document);
        mappedData.insert(mappedData.end(), partialMap.begin(), partialMap.end());
    }

    std::map<std::string, std::vector<int>> groupedData = shuffleAndSort(mappedData);
    std::map<std::string, int> finalOutput = reducer(groupedData);

    // Print the final word counts
    std::cout << "Word Count Results:\n";
    for (const auto &pair : finalOutput)
    {
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    return 0;
}

