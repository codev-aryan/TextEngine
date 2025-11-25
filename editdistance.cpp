#include <string>
#include <vector>
#include <algorithm>

// Calculate Levenshtein edit distance between two words
int calculateEditDistance(const std::string& word1, const std::string& word2) {
    int m = word1.length();
    int n = word2.length();
    
    // Swap to ensure word2 is shorter for space optimization
    if (m < n) {
        return calculateEditDistance(word2, word1);
    }
    
    if (n == 0) return m;
    
    // Use two rows instead of full matrix to save space
    std::vector<int> prev(n + 1);
    std::vector<int> curr(n + 1);
    
    // Initialize first row
    for (int j = 0; j <= n; ++j) {
        prev[j] = j;
    }
    
    // Fill the table row by row
    for (int i = 1; i <= m; ++i) {
        curr[0] = i;
        
        for (int j = 1; j <= n; ++j) {
            if (word1[i - 1] == word2[j - 1]) {
                curr[j] = prev[j - 1];
            } else {
                // Take minimum of: delete, insert, or substitute
                curr[j] = 1 + std::min({
                    prev[j],      // delete
                    curr[j - 1],  // insert
                    prev[j - 1]   // substitute
                });
            }
        }
        
        std::swap(prev, curr);
    }
    
    return prev[n];
}