//
// Created by Lindsey on 3/3/2025.
//

#ifndef UTILS_H
#define UTILS_H

// upper and lower case sensitivity ASCII splits by 32
#define ALPHAN 26 + 32



// used for keywords table lookup
typedef struct TrieNode TrieNode;
struct TrieNode {
  char data;
  // hold letters from A to z
  TrieNode *children[ALPHAN];
  bool is_leaf;
};

// will create a node for combination of letter at a depth
TrieNode* create_trie_node(const char data);
void free_trie_node(TrieNode* node);
void insert(TrieNode* root, const char* word);
bool search(TrieNode* root, const char* word);



#endif //UTILS_H
