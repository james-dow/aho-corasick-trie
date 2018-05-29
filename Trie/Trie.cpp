#include <iostream>
#include <cstring>
#include <string>
#include <set>
#include <algorithm>

#include "Trie.hpp"

Trie::Node::Node()
{
    parent = NULL;
    suffLink = NULL;
    up = NULL;
    charToParent = UNUSED_CHARACTER;
    isLeaf = false;
    memset(son, (char) NULL, sizeof son);
    memset(go, (char) NULL, sizeof go);
}

Trie::Node* Trie::getSuffLink(Trie::Node* v)
{
    if (v->suffLink == NULL) {
        if (v == this->root || v->parent == this->root) {
            v->suffLink = this->root;
        } else {
            v->suffLink = getGo(getSuffLink(v->parent), v->charToParent);
        }
    }
    return v->suffLink;
}

Trie::Node* Trie::getGo(Trie::Node* v, size_t c) 
{
    if (v->go[c] == NULL) {
        if (v->son[c] != NULL) {
            v->go[c] = v->son[c];
        } else if (v == this->root) {
            v->go[c] = this->root;
        } else {
            v->go[c] = getGo(getSuffLink(v), c);
        }
    }
    return v->go[c];
}

Trie::Node* Trie::getUp(Trie::Node* v)
{
    if (v->up == NULL) {
        Node *suffLink = getSuffLink(v);
        if (suffLink->isLeaf) {
            v->up = suffLink;
        } else if (suffLink == this->root) {
            v->up = this->root;
        } else {
            v->up = getUp(suffLink);
        }
    }
    
    return v->up;
}

void Trie::deleteNode(Trie::Node* v)
{
    for (int i = 0; i < ALPHABET_LIMIT; ++i) {
        if (v->son[i] != NULL) {
            deleteNode(v->son[i]);
        }
    }
    
    delete v;
}

inline size_t Trie::charInCharset(char c)
{
    return 128 + ((int) c);
}

Trie::Trie()
{
    this->root = new Trie::Node();
    this->nodeCount = 1;
}

Trie::~Trie()
{
    deleteNode(this->root);
}

void Trie::addPattern(const std::string &s, int n)
{
    Trie::Node* cur = this->root;
    for (int i = 0; i < s.length(); ++i) {
        size_t c = charInCharset(s[i]);
        if (cur->son[c] == NULL) {
            cur->son[c] = new Trie::Node();
            cur->son[c]->parent = cur;
            cur->son[c]->charToParent = c;
        }
        cur = cur->son[c];
    }
    cur->isLeaf = true;
    cur->patternNumbers.insert(n);
}

void Trie::processText(const std::string& t, std::set<int>& found)
{
    std::set<Trie::Node*> visitedUpLinks;
    found.clear();
    Trie::Node* cur = this->root;
    for (int i = 0; i < t.length(); ++i) {
        size_t c = 128 + ((int) t[i]);
        cur = getGo(cur, c);
        
        Trie::Node *collector = cur;
        do {
            if (visitedUpLinks.find(collector) != visitedUpLinks.end()) {
                break;
            }
            for (std::set<int>::iterator it = collector->patternNumbers.begin(); it != collector->patternNumbers.end(); ++it) {
                found.insert(*it);
            }
            visitedUpLinks.insert(collector);
            
            collector = getUp(collector);
        } while (collector != this->root);
    }
}

int Trie::getNodeCount()
{
    return this->nodeCount;
}
