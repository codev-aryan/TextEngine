<div align="center">

# 🚀 TextEngine

### *Lightning-fast autocomplete & spell-checking powered by advanced algorithms*

[![C++](https://img.shields.io/badge/C++-14+-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=for-the-badge)](http://makeapullrequest.com)

[Features](#-features) • [Quick Start](#-quick-start) • [Usage](#-usage) • [Technical Details](#-technical-details)

</div>

---

## ✨ Features

<table>
<tr>
<td width="50%">

### 🎯 Intelligent Autocomplete
Get smart word suggestions with prefix matching, ranked by usage frequency for a personalized experience.

</td>
<td width="50%">

### 🔍 Advanced Spell Checking
Powered by Levenshtein distance algorithm to find and suggest the closest matching words.

</td>
</tr>
<tr>
<td width="50%">

### 📊 Adaptive Learning
System learns from your usage patterns, automatically adjusting word frequencies over time.

</td>
<td width="50%">

### 💾 Persistent Storage
Add custom words and save your personalized dictionary across sessions.

</td>
</tr>
</table>

---

## 🚀 Quick Start

### Prerequisites
```bash
C++14 or higher
g++, clang++, or MSVC compiler
```

### Build & Run
```bash
# Clone the repository
git clone https://github.com/codev-aryan/TextEngine.git
cd TextEngine

# Compile
g++ -std=c++14 -O2 main.cpp trie.cpp editdistance.cpp -o textengine

# Run
./textengine
```

---

## 💡 Usage

### Interactive Demo

<details>
<summary><b>📝 Autocomplete Example</b></summary>

```
Choice: 1

Enter prefix: alg

--- Results ---
Suggestions for 'alg':
  1. algorithm (freq: 980) ⭐

Select a suggestion (1-1) or 0 to skip: 1
Selected: algorithm (new freq: 981)
Time: 45 μs ⚡
```

</details>

<details>
<summary><b>🔎 Spell Check Example</b></summary>

```
Choice: 2

Enter word: algoritm

✗ Not found

Did you mean:
  1. algorithm
  2. algorithmic
  3. algorithmically

Select a suggestion (1-3) or 0 to add 'algoritm' to dictionary: 1
Selected: algorithm (new freq: 982)
Time: 3 ms
```

</details>

### Dictionary Format
Create a `dictionary.txt` file with words and their frequencies:
```
algorithm 980
autocomplete 750
python 930
```

---

## 🏗️ Architecture

### 🌲 Trie Data Structure
Efficient prefix-based word retrieval using a tree structure where each node represents a character.

```
        root
       /  |  \
      a   b   c
     /    |    \
   l     o     a
  /      |      \
 g      o       t
```

### 📏 Levenshtein Edit Distance
Calculates minimum operations (insert/delete/substitute) to transform one word to another.

**Space Optimized**: Uses only 2 rows instead of full matrix - O(min(m,n)) space complexity!

---

## ⚡ Performance

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| **Insert** | O(m) | O(1) |
| **Search** | O(m) | O(1) |
| **Autocomplete** | O(p + n) | O(n) |
| **Spell Check** | O(k × m × n) | O(m) |

*where m = word length, n = matching words, p = prefix length, k = max edit distance*

---

## 📁 Project Structure

```
textengine/
│
├── 📄 Trie.h              # Trie class definition & interface
├── 📄 trie.cpp            # Core Trie implementation
├── 📄 editdistance.cpp    # Levenshtein distance algorithm
├── 📄 main.cpp            # Interactive CLI application
└── 📄 dictionary.txt      # Word frequency database
```

---

## 🎯 Key Highlights

> **🔥 Frequency-Based Ranking** - Words you use more often appear first in suggestions

> **🎨 Case Insensitive** - Automatic lowercase conversion for consistent matching

> **⚙️ Customizable** - Adjust edit distance threshold and autocomplete limits

> **💪 Memory Efficient** - Smart pointer usage and optimized algorithms

---

## 🤝 Contributing

Contributions, issues, and feature requests are welcome!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

---

## 📜 License

This project is open source and available under the MIT License.

---

<div align="center">

### Built with ❤️ by [codev-aryan](https://github.com/codev-aryan)

⭐ Star this repo if you find it helpful!

[Report Bug](https://github.com/codev-aryan/TextEngine/issues) • [Request Feature](https://github.com/codev-aryan/TextEngine/issues)

</div>
