# Aho-Corasick trie

Implementation of Aho-Corasick Trie.
Constructed of the desired patterns, then it can process the text, finding all the samples included in the text.
Thread-safe. Memory usage O(nk), where n is the count of nodes and k is the size of the alphabet.
Interface:
- void addPattern(const string& s, int n)
- void processText(const string& t, set<int>& found)

Sample compilation:
```
g++ common.cpp ../Trie/Trie.cpp -o common
```