#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
void func1(vector<string> wordList) {			// Verificar se palavra pertence ao dicionario
	string word;
	cout << "Insira a palavra que quer pesquisar: "; cin >> word;
	cout << '\n';

	if (isMember_word(word, wordList)) { cout << "A palavra " << word << " pertence ao dicionario.\n"; }
	else { cout << "A palavra " << word << " nao pertence ao dicionario.\n"; }
}

void func2(vector<string> wordList) {			// Adivinhar uma palavra baralhada
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
		cin >> guessWord;
		if (word == guessWord) {
			cout << '\n' << "Acertou! Parabens!\n";
			break;
		}
	}
}

void func3(vector<string> wordList) {			// visualizar palavras com um set de letras
	string letras_in;
	string letras_mid;
	string letras;
	cout << "Insira agora as letras que fazem parte do conjunto:\n";
	cin.ignore();
	getline(cin, letras_in);
	size_t compin = letras_in.length();
	size_t comp = letras.length();

	for (unsigned i = 0; i < compin; i++) {                        // remove espacos e qlqr simbolo e poe tudo em maiusculas
		if ((letras_in[i] > 64 && letras_in[i] < 91) || (letras_in[i] > 96 && letras_in[i] < 123)) {
			letras = letras + char(toupper(letras_in[i]));
		}
	}

	cout << letras << '\t';                                  // mostra o set de letras

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

//	cout << "\n\n" << "As palavras as quais pertencem todas as letras do conjunto sao:\n";
//	bool pertence = false;
//	for (unsigned i = 0; i < wordList.size(); i++) {
//		pertence = true;
//		for (unsigned j = 0; j < letras.length(); j++) {
//			if (!char_pertence(letras[j], wordList[i])) {
//				pertence = false;
//				break;
//			}
//		}
//		if (pertence == true) {
//			cout << wordList[i] << '\n';
//		}
//	}
//}


//-------------------


int interfStart() {
	int funcSelect = 0;

	cout << '\n';
	cout << "||''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''||" << '\n';
	cout << "||   Para verificar se uma palavra pertence ao dicionario, insira 1.                    ||" << '\n';
	cout << "||   --------------------------------------------------------------------------------   ||" << '\n';
	cout << "||   Para adivinhar uma palavra baralhada, insira 2.                                    ||" << '\n';
	cout << "||   --------------------------------------------------------------------------------   ||" << '\n';
	cout << "||   Para visualizar todas as palavras com um dado conjunto de letras, insira 3.        ||" << '\n';
	cout << "||   --------------------------------------------------------------------------------   ||" << '\n';
	cout << "||   Para construir uma palavra valida com um conjunto aleatório de letras, insira 4.   ||" << '\n';
	cout << "||   --------------------------------------------------------------------------------   ||" << '\n';
	cout << "||   Para ver todas as palavras correspondentes a uma string \"wildcard\", insira 5.      ||" << '\n';
	cout << "||......................................................................................||" << "\n \n";
	cin >> funcSelect; cout << '\n';

	return funcSelect;
}

int playwords()
{
	string open_fileName;
	vector<string> wordList;

	cout << "Open file name (xxxx.txt)? "; cin >> open_fileName;

	ifstream f(open_fileName);

	if (!f.is_open()) {
		cerr << "\nErro na leitura do ficheiro\n\n";
		system("pause");
		exit(1);
	}

	string s;

	while (getline(f, s)) {
		wordList.push_back(s);
	}

	int sel = interfStart();

	switch (sel) {
	case 1: func1(wordList); break;
	case 2: func2(wordList); break;
	case 3: func3(wordList); break;
	default: {
		cout << "Valor inserido invalido.\n \n";
		interfStart();
		break; }
	}

	system("pause");
	return 0;
}