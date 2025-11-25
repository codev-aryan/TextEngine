#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

// TrieNode structure
struct TrieNode {
    std::unordered_map<char, std::shared_ptr<TrieNode>> children;
    bool isEndOfWord;
    int frequency;
    
    TrieNode() : isEndOfWord(false), frequency(0) {}
};

// Trie class for autocomplete and prefix operations
class Trie {
private:
    std::shared_ptr<TrieNode> root;
    
    // Helper function for DFS traversal
    void collectWords(std::shared_ptr<TrieNode> node, 
                     const std::string& prefix, 
                     std::vector<std::pair<std::string, int>>& results) const;
    
    void getAllWords(std::shared_ptr<TrieNode> node,
                    const std::string& currentWord,
                    std::vector<std::string>& allWords) const;

public:
    Trie();
    ~Trie();
    
    void insert(const std::string& word, int frequency);
    bool search(const std::string& word) const;
    bool startsWith(const std::string& prefix) const;
    
    std::vector<std::string> autocomplete(const std::string& prefix, int k = 5) const;
    std::vector<std::string> getSuggestions(const std::string& word, int maxEditDistance = 2) const;
    
    int getFrequency(const std::string& word) const;
};

#endif // TRIE_H