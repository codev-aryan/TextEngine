#include "Trie.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>

// Forward declaration for edit distance function
int calculateEditDistance(const std::string& word1, const std::string& word2);

Trie::Trie() {
    root = std::make_shared<TrieNode>();
}

Trie::~Trie() {
    // Smart pointers handle cleanup
}

void Trie::insert(const std::string& word, int frequency) {
    if (word.empty()) return;
    
    std::shared_ptr<TrieNode> current = root;
    
    for (char c : word) {
        char lowerChar = std::tolower(c);
        
        if (current->children.find(lowerChar) == current->children.end()) {
            current->children[lowerChar] = std::make_shared<TrieNode>();
        }
        current = current->children[lowerChar];
    }
    
    current->isEndOfWord = true;
    current->frequency = frequency;
}

bool Trie::search(const std::string& word) const {
    if (word.empty()) return false;
    
    std::shared_ptr<TrieNode> current = root;
    
    for (char c : word) {
        char lowerChar = std::tolower(c);
        
        if (current->children.find(lowerChar) == current->children.end()) {
            return false;
        }
        current = current->children[lowerChar];
    }
    
    return current->isEndOfWord;
}

bool Trie::startsWith(const std::string& prefix) const {
    if (prefix.empty()) return true;
    
    std::shared_ptr<TrieNode> current = root;
    
    for (char c : prefix) {
        char lowerChar = std::tolower(c);
        
        if (current->children.find(lowerChar) == current->children.end()) {
            return false;
        }
        current = current->children[lowerChar];
    }
    
    return true;
}

void Trie::collectWords(std::shared_ptr<TrieNode> node, 
                       const std::string& prefix, 
                       std::vector<std::pair<std::string, int>>& results) const {
    if (!node) return;
    
    if (node->isEndOfWord) {
        results.push_back({prefix, node->frequency});
    }
    
    for (const auto& pair : node->children) {
        collectWords(pair.second, prefix + pair.first, results);
    }
}

std::vector<std::string> Trie::autocomplete(const std::string& prefix, int k) const {
    std::vector<std::string> suggestions;
    
    if (prefix.empty() || k <= 0) return suggestions;
    
    std::shared_ptr<TrieNode> current = root;
    std::string lowerPrefix;
    
    for (char c : prefix) {
        char lowerChar = std::tolower(c);
        lowerPrefix += lowerChar;
        
        if (current->children.find(lowerChar) == current->children.end()) {
            return suggestions;
        }
        current = current->children[lowerChar];
    }
    
    // Collect all words with this prefix
    std::vector<std::pair<std::string, int>> results;
    collectWords(current, lowerPrefix, results);
    
    // Sort by frequency
    std::sort(results.begin(), results.end(), 
              [](const auto& a, const auto& b) {
                  return a.second > b.second;
              });
    
    int count = std::min(k, static_cast<int>(results.size()));
    for (int i = 0; i < count; ++i) {
        suggestions.push_back(results[i].first);
    }
    
    return suggestions;
}

void Trie::getAllWords(std::shared_ptr<TrieNode> node,
                      const std::string& currentWord,
                      std::vector<std::string>& allWords) const {
    if (!node) return;
    
    if (node->isEndOfWord) {
        allWords.push_back(currentWord);
    }
    
    for (const auto& pair : node->children) {
        getAllWords(pair.second, currentWord + pair.first, allWords);
    }
}

std::vector<std::string> Trie::getSuggestions(const std::string& word, 
                                              int maxEditDistance) const {
    std::vector<std::string> suggestions;
    
    if (word.empty()) return suggestions;
    
    std::string lowerWord;
    for (char c : word) {
        lowerWord += std::tolower(c);
    }
    
    if (search(lowerWord)) {
        suggestions.push_back(lowerWord);
        return suggestions;
    }
    
    // Get all dictionary words
    std::vector<std::string> allWords;
    getAllWords(root, "", allWords);
    
    // Find words within edit distance threshold
    std::vector<std::pair<std::string, int>> candidatesWithDistance;
    
    for (const std::string& dictWord : allWords) {
        int distance = calculateEditDistance(lowerWord, dictWord);
        
        if (distance <= maxEditDistance) {
            candidatesWithDistance.push_back({dictWord, distance});
        }
    }
    
    // Sort by edit distance
    std::sort(candidatesWithDistance.begin(), candidatesWithDistance.end(),
              [](const auto& a, const auto& b) {
                  return a.second < b.second;
              });
    
    for (const auto& pair : candidatesWithDistance) {
        suggestions.push_back(pair.first);
    }
    
    return suggestions;
}

int Trie::getFrequency(const std::string& word) const {
    if (word.empty()) return 0;
    
    std::shared_ptr<TrieNode> current = root;
    
    for (char c : word) {
        char lowerChar = std::tolower(c);
        
        if (current->children.find(lowerChar) == current->children.end()) {
            return 0;
        }
        current = current->children[lowerChar];
    }
    
    return current->isEndOfWord ? current->frequency : 0;
}

void Trie::incrementFrequency(const std::string& word) {
    if (word.empty()) return;
    
    std::shared_ptr<TrieNode> current = root;
    std::string lowerWord;
    
    for (char c : word) {
        char lowerChar = std::tolower(c);
        lowerWord += lowerChar;
        
        if (current->children.find(lowerChar) == current->children.end()) {
            return; // Word doesn't exist
        }
        current = current->children[lowerChar];
    }
    
    if (current->isEndOfWord) {
        current->frequency++;
    }
}

void Trie::collectAllWordsWithFrequency(std::shared_ptr<TrieNode> node,
                                       const std::string& currentWord,
                                       std::vector<std::pair<std::string, int>>& words) const {
    if (!node) return;
    
    if (node->isEndOfWord) {
        words.push_back({currentWord, node->frequency});
    }
    
    for (const auto& pair : node->children) {
        collectAllWordsWithFrequency(pair.second, currentWord + pair.first, words);
    }
}

std::vector<std::pair<std::string, int>> Trie::getAllWordsWithFrequency() const {
    std::vector<std::pair<std::string, int>> words;
    collectAllWordsWithFrequency(root, "", words);
    
    // Sort alphabetically for consistent output
    std::sort(words.begin(), words.end(),
              [](const auto& a, const auto& b) {
                  return a.first < b.first;
              });
    
    return words;
}

bool Trie::saveDictionary(const std::string& filename) const {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "' for writing" << std::endl;
        return false;
    }
    
    std::vector<std::pair<std::string, int>> words = getAllWordsWithFrequency();
    
    for (const auto& pair : words) {
        file << pair.first << " " << pair.second << "\n";
    }
    
    file.close();
    return true;
}