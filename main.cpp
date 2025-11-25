#include "Trie.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

bool loadDictionary(const std::string& filename, Trie& trie) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
        return false;
    }
    
    std::string line;
    int wordCount = 0;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::istringstream iss(line);
        std::string word;
        int frequency;
        
        if (iss >> word >> frequency) {
            trie.insert(word, frequency);
            wordCount++;
        }
    }
    
    file.close();
    std::cout << "Loaded " << wordCount << " words" << std::endl;
    
    return wordCount > 0;
}

void handleAutocomplete(const Trie& trie) {
    std::string prefix;
    std::cout << "\nEnter prefix: ";
    std::cin >> prefix;
    
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::string> suggestions = trie.autocomplete(prefix, 5);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "\n--- Results ---" << std::endl;
    
    if (suggestions.empty()) {
        std::cout << "No suggestions found" << std::endl;
    } else {
        std::cout << "Suggestions for '" << prefix << "':" << std::endl;
        for (size_t i = 0; i < suggestions.size(); ++i) {
            std::cout << "  " << (i + 1) << ". " << suggestions[i] 
                     << " (freq: " << trie.getFrequency(suggestions[i]) << ")" << std::endl;
        }
    }
    
    std::cout << "Time: " << duration.count() << " μs" << std::endl;
}

void handleSpellCheck(const Trie& trie) {
    std::string word;
    std::cout << "\nEnter word: ";
    std::cin >> word;
    
    auto start = std::chrono::high_resolution_clock::now();
    bool exists = trie.search(word);
    
    if (exists) {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "\n✓ Correct spelling!" << std::endl;
        std::cout << "Frequency: " << trie.getFrequency(word) << std::endl;
        std::cout << "Time: " << duration.count() << " μs" << std::endl;
    } else {
        std::vector<std::string> suggestions = trie.getSuggestions(word, 2);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        std::cout << "\n✗ Not found" << std::endl;
        
        if (suggestions.empty()) {
            std::cout << "No suggestions" << std::endl;
        } else {
            std::cout << "Did you mean:" << std::endl;
            int count = std::min(10, static_cast<int>(suggestions.size()));
            for (int i = 0; i < count; ++i) {
                std::cout << "  " << (i + 1) << ". " << suggestions[i] << std::endl;
            }
        }
        
        std::cout << "Time: " << duration.count() << " ms" << std::endl;
    }
}

int main() {
    std::cout << "=== Autocomplete & Spell Checker ===" << std::endl;
    
    Trie trie;
    
    auto startLoad = std::chrono::high_resolution_clock::now();
    if (!loadDictionary("dictionary.txt", trie)) {
        std::cerr << "Failed to load dictionary" << std::endl;
        return 1;
    }
    auto endLoad = std::chrono::high_resolution_clock::now();
    auto loadTime = std::chrono::duration_cast<std::chrono::milliseconds>(endLoad - startLoad);
    std::cout << "Load time: " << loadTime.count() << " ms\n" << std::endl;
    
    bool running = true;
    
    while (running) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "1. Autocomplete" << std::endl;
        std::cout << "2. Spell Checker" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Choice: ";
        
        int choice;
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        
        switch (choice) {
            case 1:
                handleAutocomplete(trie);
                break;
            case 2:
                handleSpellCheck(trie);
                break;
            case 3:
                std::cout << "Goodbye!" << std::endl;
                running = false;
                break;
            default:
                std::cout << "Invalid choice" << std::endl;
        }
    }
    
    return 0;
}