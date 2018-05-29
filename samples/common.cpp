#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "../Trie/Trie.hpp"

using namespace std;

int main() 
{
    Trie trie;
    set<int> found;
    char* patternsChar[] = {
        "Lorem",
        "lorem",
        "five centuries",
        "since the 1500s, when an unknown printer",
        "containing the Lorem"
    };
    vector<string> patterns(patternsChar, patternsChar + sizeof(patternsChar) / sizeof(patternsChar[0]));
    string text = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";
    
    for (size_t i = 0; i < patterns.size(); ++i) {
        trie.addPattern(patterns[i], i);
    }
    
    trie.processText(text, found);
    
    for (set<int>::iterator it = found.begin(); it != found.end(); it++) {
        cout << "Found pattern (" << *it + 1 << "): " << patterns[*it] << "." << endl;
    }
    
    return 0;
}