#include "pch.h"
#include "Trie.h"
#include <string>

using namespace std;

//Constructor
Trie::Trie() {
	//Create root trieNode
	root = new TrieNode;

	//Initialise all values in children array to NULL
	for (int i = 0; i < numberOfChar; i++) {
		root->children[i] = NULL;
	}

	root->endOfWord = false;
}

bool Trie::search(string target) {
	TrieNode* temp = root;

	for (int i = 0; i < target.length(); i++) {
		char currentCharacter = tolower(target[i]);

		if (temp->children[currentCharacter - 'a'] != NULL)
			temp = temp->children[currentCharacter - 'a'];

		else if ((temp->children[currentCharacter - 'a'] == NULL) && (temp->endOfWord) && (i == target.length() - 1))
			return true;

		else
			return false;
	}
}

//Insert a string into the trie
void Trie::insert(string target) {
	TrieNode* temp = root;

	for (int i = 0; i < target.length(); i++) {
		char currentCharacter = tolower(target[i]);				//Convert char to lowercase

		if (temp->children[currentCharacter - 'a'] == NULL) {	//Create new trieNode if it does not exist in trie
			TrieNode* newNode = new TrieNode();
			temp->children[currentCharacter - 'a'] = newNode;
		}

		temp = temp->children[currentCharacter - 'a'];			//Traverse to the next trie node
	}

	temp->endOfWord = true;										//Set endOfWord bool to true to indicate that the character completes the word
}

