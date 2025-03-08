//
// Created by Lindsey on 3/3/2025.
//
#include "../include/utils.h"
#include <stdlib.h>


// create tree node, set children to null
TrieNode* create_trie_node(const char data) {
  // allocate space for children nodes
	// memory leak ??? see insert when assigning chidlren of index to that letter
	const auto node = (TrieNode*)calloc(1, sizeof(TrieNode));
	if (!node) {
		// allocation failed
		return nullptr;
	}
  // set children data to null
	for (int i = 0; i < ALPHAN; i++) {
		node->children[i] = nullptr;
	};
	node->is_leaf = false;
	node->data = data;

	return node;
};

// free memory recursively for entire trie
void free_trie_node(TrieNode* node) {
  // recursively free children if contain
  for (int i = 0; i < ALPHAN; i++) {
    if (node->children[i] != NULL) {
      free_trie_node(node->children[i]);
    }
  }
  free(node);
};




void insert(TrieNode* root, const char* word) {
	TrieNode* current = root;
	// iterate over each char in word
	for (int i = 0; word[i] != '\0'; i++) {
		// is child of current null
		const int index = word[i] - 'A';
		if (current->children[index] == nullptr) {
			//create node
			TrieNode* new_node = create_trie_node(word[i]);
			if (new_node == NULL) {
				return;
			}
			current->children[index] = new_node;
		}
		// current points to next
		current = current->children[index];
	};
	//finally, end of word = leaf node
	current->is_leaf = true;
};

static bool is_alphabet(const char c) {
	//
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool search(const TrieNode* root, const char* word) {
	const TrieNode* current = root;
	// until word ends
	for (int i = 0; word[i] != '\0'; i++) {
		if (!is_alphabet(word[i])) {
			return false;
		}
		const int index = word[i] - 'A';
		// word has not been added
		if (current->children[index] == NULL) {
			return false;
		};
		// descend trie
		current = current->children[index];
	};
	// if current is not null AND is_leaf -> end of word
	if (current != nullptr && current->is_leaf) {
		return true;
	}
	return false;
};


