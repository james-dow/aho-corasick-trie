#pragma once
#include <iostream>
#include <string>
#include <set>
#include <algorithm>

const int ALPHABET_LIMIT = 256;
const int UNUSED_CHARACTER = 255;

/*
 * Implementation of Aho-Corasick Trie.
 * Constructed of the desired patterns, then it can process the text, finding all the samples included in the text.
 * Thread-safe. Memory usage O(nk), where n is the count of nodes and k is the size of the alphabet.
 * Interface:
 * - void addPattern(const string& s, int n)
 * - void processText(const string& t, set<int>& found)
 */
class Trie
{
private:
	
	/*
	 * Represents a trie node, which represents string, which consists of symbols from root to this node.
     * The suffix link is a node, which represents longest own suffix of the string represented by this node.
	 * The leaf is a node, in which at least one line from the set has ended.
     * The condensed suffix link is a node, which is the closest in path of transition by suffix links and a leaf node in same time.
	 */
	struct Node 
	{
		Node *son[ALPHABET_LIMIT];  // Arcs by each symbol.
		Node *go[ALPHABET_LIMIT];   // Calculated arcs.
		Node *parent;
		Node *suffLink;
		Node *up;                   // Condensed suffix link.
		size_t charToParent;        // Last symbol, with which current node was reached.
		bool isLeaf;                // Leaf flag.
		std::set<int> 
            patternNumbers;         // Set of patterns, which ended in current node.
		
		Node();
	};
	
	Node *root;
	int nodeCount;
    
	Node* getSuffLink(Node* v);
	Node* getGo(Node* v, size_t c);
	Node* getUp(Node* v);
	void deleteNode(Node* v);
	inline size_t charInCharset(char c);
	
public:
	Trie();
	~Trie();
	
	/*
	 * Adds pattern s into the trie with pattern number n.
	 */
	void addPattern(const std::string &s, int n);
	
	/*
	 * Process the text, resulting into found with found pattern numbers.
	 */
	void processText(const std::string& t, std::set<int>& found);
	
	int getNodeCount();
};

