#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include "playWordsUtils.h"
#include "router.h"
using namespace std;


// funções side
bool isMember_word(string word, vector<string> list) {

	for (unsigned i = 0; i < word.length(); i++) {
		word[i] = toupper(word[i]);
	}

	for (unsigned i = 0; i < list.size(); i++) {
		if (word == list[i])
			return true;
	}
	return false;
}

string scramble(string word) {
	string scramb = word;
	for (unsigned i = 0; i < scramb.length(); i++) {
		unsigned j = rand() % scramb.length();
		swap(scramb[i], scramb[j]);
	}
	return scramb;
}

bool char_pertence(char ch, string word) {
	for (unsigned i = 0; i < word.length(); i++) {
		if (ch == word[i]) {
			return true;
		}
	}
	return false;
}


//-------------------

// funções main
void func1(ifstream &file) {			// Verificar se palavra pertence ao dicionario
	vector<string> wordList;
	string temp;
	while (getline(file, temp)) {
		wordList.push_back(temp);
	}

	string word;
	cout << "Insira a palavra que quer pesquisar: ";
	pw::readString(word);
	word = pw::trim(word);
	word = pw::makeUpper(word);
	cout << '\n';

	if (isMember_word(word, wordList)) { cout << "A palavra " << word << " pertence ao dicionario.\n"; }
	else { cout << "A palavra " << word << " nao pertence ao dicionario.\n"; }
}

void func2(ifstream &file) {			// Adivinhar uma palavra baralhada
	vector<string> wordList;
	string temp;
	while (getline(file, temp)) {
		wordList.push_back(temp);
	}

	srand(time(NULL));
	int wordIndex = rand() % wordList.size();
	string word = wordList[wordIndex];
	string scrWord = scramble(word);
	string guessWord;
	cout << scrWord << "\n\n";
	for (int v = 3; v >= 0; v--) {
		if (v == 0) {
			cout << '\n' << "Perdeu! A resposta era " << word << "!\n";
			break;
		}
		pw::readString(guessWord);
		guessWord = pw::trim(guessWord);
		guessWord = pw::makeUpper(guessWord);
		if (word == guessWord) {
			cout << '\n' << "Acertou! Parabens!\n";
			break;
		}
	}
}

void func3(ifstream &file) {			// visualizar palavras com um set de letras
	vector<string> wordList;
	string temp;
	while (getline(file, temp)) {
		wordList.push_back(temp);
	}
	
	string letras_in;
	string letras_mid;
	string letras = string();
	cout << "Insira agora as letras que fazem parte do conjunto:\n";
	getline(cin, letras_in);
	size_t compin = letras_in.length();
	size_t comp = letras.length();

	for (char c : letras_in) {                        // remove espacos e qlqr simbolo e poe tudo em maiusculas
		if ((c > 64 && c < 91) || (c > 96 && c < 123)) {
			letras.push_back(toupper(c));
		}
	}

	cout << letras << '\n';                                  // mostra o set de letras

	cout << "\n\n" << "As palavras as quais pertencem todas as letras do conjunto sao:\n";
	bool pertence = false;
	for (unsigned i = 0; i < wordList.size(); i++) {
		pertence = true;
		for (unsigned j = 0; j < letras.length(); j++) {
			if (sizeof(wordList[i]) > letras.length()) {
				pertence = false;
				break;
			}
			if (!char_pertence(letras[j], wordList[i])) {
				pertence = false;
				break;
			}
		}
		if (pertence == true) {
			cout << wordList[i] << '\n';
		}
	}
}