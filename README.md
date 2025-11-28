# TextEngine

A high-performance C++ autocomplete and spell-checking system built with a Trie data structure and Levenshtein edit distance algorithm.

## Features

- **Autocomplete**: Get intelligent word suggestions based on prefix matching with frequency ranking
- **Spell Checking**: Identify misspelled words and receive correction suggestions using edit distance
- **Frequency Learning**: The system adapts to your usage patterns by tracking word frequencies
- **Dictionary Management**: Add new words and persist changes across sessions
- **Performance Optimized**: Fast lookups with optimized memory usage

## How It Works

### Trie Data Structure
The autocomplete system uses a Trie (prefix tree) for efficient prefix-based word retrieval. Each node stores:
- Child character mappings
- End-of-word markers
- Word frequency counts

### Levenshtein Edit Distance
The spell checker calculates the minimum number of operations (insertions, deletions, substitutions) needed to transform one word into another, helping suggest the closest matching words from the dictionary.

## Building the Project

### Prerequisites
- C++14 or higher
- A C++ compiler (g++, clang++, or MSVC)

### Compilation
```bash
g++ -std=c++14 -O2 main.cpp trie.cpp editdistance.cpp -o textengine
```

## Usage

### Running the Program
```bash
./textengine
```

### Dictionary Format
The program expects a `dictionary.txt` file in the same directory with the format:
```
word frequency
example 950
autocomplete 750
algorithm 980
```

### Interactive Menu

1. **Autocomplete**: Enter a prefix to get the top 5 word suggestions ranked by frequency
2. **Spell Checker**: Enter a word to verify spelling or receive correction suggestions
3. **Add New Word**: Add custom words to the dictionary
4. **Exit**: Save changes and exit the program

## Example Session

```
=== Autocomplete & Spell Checker ===
Loaded 94 words
Load time: 2 ms

========================================
1. Autocomplete
2. Spell Checker
3. Add New Word
4. Exit
========================================
Choice: 1

Enter prefix: alg

--- Results ---
Suggestions for 'alg':
  1. algorithm (freq: 980)

Select a suggestion (1-1) or 0 to skip: 1
Selected: algorithm (new freq: 981)
Time: 45 μs
```

## Technical Details

### Time Complexity
- **Insert**: O(m) where m is the word length
- **Search**: O(m) where m is the word length
- **Autocomplete**: O(p + n) where p is prefix length and n is number of matching words
- **Spell Check**: O(k × m × n) where k is max edit distance, m is word length, n is dictionary size

### Space Complexity
- **Trie Storage**: O(ALPHABET_SIZE × N × M) where N is number of words and M is average word length
- **Edit Distance**: O(min(m, n)) using space-optimized two-row approach

## Features in Detail

### Frequency-Based Ranking
Words are ranked by usage frequency, which increases each time a word is selected or verified. This creates a personalized autocomplete experience that adapts to your vocabulary.

### Edit Distance Threshold
The spell checker uses a maximum edit distance of 2 by default, finding words that require at most 2 character operations to match the input. This provides a good balance between suggestion quality and performance.

### Case Insensitivity
All operations are case-insensitive, converting input to lowercase for consistent matching.

## File Structure

```
textengine/
├── Trie.h              # Trie class definition
├── trie.cpp            # Trie implementation
├── editdistance.cpp    # Levenshtein distance algorithm
├── main.cpp            # Main program and UI
└── dictionary.txt      # Word dictionary with frequencies
```

## Contributing

Contributions are welcome! Feel free to submit issues or pull requests to improve TextEngine.

## Repository

GitHub: [codev-aryan/TextEngine](https://github.com/codev-aryan/TextEngine)

## License

This project is open source and available for educational and commercial use.
