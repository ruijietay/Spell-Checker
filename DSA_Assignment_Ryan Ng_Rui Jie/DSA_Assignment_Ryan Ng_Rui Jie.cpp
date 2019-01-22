#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Trie.h"

#pragma comment(linker, "/STACK:256000000")
#pragma comment(linker, "/HEAP:256000000")

using namespace std;

int option;
string temp;
bool specialchars = false;

void Menu();
void readDictionary();
void option1();
void option2();
//void option6();

Trie dictionary;

int main()
{
	readDictionary(); //Initialization

	while (true) { 	//Menu

		string temp;

		//Open destination file
		ofstream destinationfile;

		Menu();

		switch (option) {
		case 1:
			option1();
			break;
		case 2:
			option2();
			break;
		case 3:
			//Prompt user for new word to input
			cout << "Enter the new word: ";
			cin >> temp;

			for (int i = 0; i < temp.length(); i++) {
				if (!isalpha(temp[i])) {
					specialchars = true;
					break;
				}
			}

			if (!specialchars) {
				//Insert new word to trie dictionary
				dictionary.insert(temp);
				cout << "\"" << temp << "\"" << " has been successfully added" << endl;
			}

			else {
				cout << "Invalid character(s). Please try again" << endl;
				specialchars = false;
			}

			break;
		case 4:
			destinationfile.open("../Resource Files/Text Files/testoutput.txt", ios::out);
			dictionary.printAllWords(&destinationfile);
			destinationfile.close();
			break;
		case 5:
			cout << "Enter prefix: ";
			cin >> temp;
			dictionary.printAllWords(dictionary.getNode(temp), temp);
			break;
		//case 6:
		//	option6();
		//	break;
		case 100:

			break;
		case 0:
			cout << "Bye!" << endl;
			return 0;
		}
	}
}

void Menu() {
	cout << endl << "---------------- Spell Checker -------------------" << endl;
	cout << "[1] Spell Check a Word" << endl;
	cout << "[2] Spell Check a File" << endl;
	cout << "[3] Add a New Word to the Dictionary" << endl;
	cout << "[4] Save the Dictionary (With New Words Added)" << endl;
	cout << "[5] Display All Words in the Dictionary that Starts with a Certain Letter" << endl;
	//cout << "[6] Remove a word from the dictionary" << endl;
	cout << "[100] Option for testing" << endl;
	cout << "[0] Exit " << endl;
	cout << "----------------------------------------------" << endl;
	cout << "Enter your option : ";

	cin >> option;

	cout << endl;
}

void readDictionary() {
	ifstream readDictionary;
	string tempWord;

	readDictionary.open("../Resource Files/Dictionary Files/dictionary10KR.txt", ios::in);

	while (readDictionary.good()) {
		readDictionary >> tempWord;
		dictionary.insert(tempWord);
	}

	readDictionary.close();
}

void option1() {
	string searchstring;
	string autocorrect;
	string wrongwords[50];
	int count = 0;

	cout << "Enter a keyword to search: ";
	cin >> searchstring;

	if (dictionary.search(searchstring))
		cout << searchstring << " is present in the dictionary." << endl;

	else {
		cout << searchstring << " is not present in the dictionary." << endl;

		autocorrect = searchstring;

		for (int i = 0; i < autocorrect.length(); i++) { //Insertion error (extra char added)
			autocorrect.erase(i, 1);
			if (dictionary.search(autocorrect)) {
				cout << "Insertion error. Did you mean: " << autocorrect << endl;
			}

			else
				autocorrect = searchstring; //reset autocorrect to delete second char
		}

		for (int i = 0; i < autocorrect.length() - 1; i++) { //Transposition error (two adjancent char swapped)
			swap(autocorrect[i], autocorrect[i + 1]);
			if (dictionary.search(autocorrect)) {
				cout << "Transposition error. Did you mean: " << autocorrect << endl;
			}

			else
				autocorrect = searchstring; //reset autocorrect to delete second word
		}
	}
}

void option2() {
	ifstream readTextFile;
	string temp;
	bool flag = false;
	string autocorrect;
	string wrongwords[50];
	int count = 0;

	readTextFile.open("../Resource Files/Text Files/Option2Errors.txt", ios::in);

	while (readTextFile.good()) {

		readTextFile >> temp;

		if (!dictionary.search(temp)) {

			if (flag) {
				cout << "List of words not in dictionary:" << endl;
				flag = true;
			}

			autocorrect = temp;

			for (int i = 0; i < autocorrect.length(); i++) { //Insertion error (extra char added)
				autocorrect.erase(i, 1);
				if (dictionary.search(autocorrect)) {
					wrongwords[count] = "\"" + temp + "\" (Insertion error) " + "[Did you mean: " + autocorrect + "]";
					count++;
				}

				else
					autocorrect = temp; //reset autocorrect to delete second char
			}

			for (int i = 0; i < autocorrect.length() - 1; i++) { //Transposition error (two adjancent char swapped)
				swap(autocorrect[i], autocorrect[i + 1]);
				if (dictionary.search(autocorrect)) {
					wrongwords[count] = "\"" + temp + "\" (Transposition error) " + "[Did you mean: " + autocorrect + "]";
					count++;
				}

				else
					autocorrect = temp; //reset autocorrect to delete second word
			}
		}
	}

	for (int i = 0; i < count; i++) {
		cout << i + 1 << ". " << wrongwords[i] << endl;
	}

	if (count == 0)
		cout << "All words in this text file are found in the dictionary." << endl;

	readTextFile.close();
}

//void option6() {
//	string temp;
//
//	cout << "Enter a keyword to remove: ";
//	cin >> temp;
//
//	if (dictionary.search(temp)) {
//		dictionary.remove(temp);
//		cout << "Successfull" << endl;
//	}
//	else {
//		cout << "Does not exist" << endl;
//	}
//}
