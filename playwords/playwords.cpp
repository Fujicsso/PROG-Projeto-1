#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std		


unsigned n_letters = 4;


// funções auxiliares
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

bool isMember_char(char ch, string word) {
	for (unsigned i = 0; i < word.length(); i++) {
		if (ch == word[i]) {
			return true;
		}
	}
	return false;
}

bool wildcardMatch(const char *str, const char *strWild) {
	while (*strWild) {
		if (*strWild == '?') {
			if (!*str)
				return false;

			++str;
			++strWild;
		}
		else if (*strWild == '*') {
			if (wildcardMatch(str, strWild + 1))
				return true;

			if (*str && wildcardMatch(str + 1, strWild))
				return true;

			return false;
		}
		else {
			if (toupper(*str++) != toupper(*strWild++))
				return false;
		}
	}
	return (!*str && !*strWild);
}
//-------------------

// funções principais
void func1(vector<string> wordList) {			// verificar se palavra pertence
	string word;
	cout << "Insira a palavra que pretende pesquisar: "; cin >> word;
	cout << '\n';

	if (isMember_word(word, wordList)) { cout << "A palavra " << word << " pertence ao dicionario.\n"; }
	else { cout << "A palavra " << word << " nao pertence ao dicionario.\n"; }
}

void func2(vector<string> wordList) {			// adivinhar palavra baralhada
	int wordIndex = rand() % wordList.size();
	string word = wordList[wordIndex];
	string scrWord = scramble(word);
	string guessWord;
	cout << scrWord << "\n\n";
	for (int v = 3; v >= 0; v--) {
		if (v == 0) {
			cout << '\n' << "Pena, perdeu! A resposta era " << word << "!\n";
			break;
		}
		cin >> guessWord;
		if (word == guessWord) {
			cout << '\n' << "Correto! Acertou!\n";
			break;
		}
	}
}

void func3(vector<string> wordList) {			// visualizar palavras com um set de letras
	char setLetters[n_letters];

	cout << "Insira agora as " << n_letters << " letras que fazem parte do conjunto:\n";

	for (unsigned i = 0; i < n_letters; i++) {						// preenche o set de letras
		char letter;
		cin >> letter;
		setLetters[i] = toupper(letter);
	}

	for (unsigned i = 0; i < n_letters; i++) {						// mostra o set de letras
		cout << setLetters[i] << '\t';
	}

	cout << "\n\n" << "As palavras as quais pertencem todas as letras do conjunto sao:\n";

	for (unsigned i = 0; i < wordList.size(); i++) {				// percorre as palavras do dicionário
		for (unsigned j = 0; j < n_letters; j++) {					// verifica se TODAS as letras do set pertencem à palavra a ser analisada
			if (!isMember_char(setLetters[j], wordList[i])) {
				break;
			}
		}
		cout << wordList[i] << '\n';
	}
}

void func4(vector<string> wordList) {			// construir palavra com um set aleatório de letras
	char setLetters[n_letters];
	string guessWord;

	for (unsigned i = 0; i < n_letters; i++) {						// preenche o set de letras
		char letter;
		letter = char(rand() % 26 + 65);							// o resultado da expressao devolverá um número entre 65 e 90 (intervalo dos códigos ASCII de A a Z)
		setLetters[i] = toupper(letter);
		cout << setLetters[i] << '\t';								// mostra o set de letras, um a um
	}

	cout << "\n\n" << "Indique uma palavra do dicionario com as letras mostradas acima: "; cin >> guessWord;

	bool valid = false;
	for (unsigned i = 0; i < wordList.size(); i++) {
		if (wordList[i] == guessWord) {
			valid = true;
			for (unsigned j = 0; j < n_letters; j++) {
				if (!isMember_char(setLetters[j], guessWord))
					valid = false;
					break;
			}
			break;
		}
	}

	if (valid)
		cout << '\n' << "Correto, acertou! A palavra " << guessWord << " pertence ao dicionario e contem todas as letras!\n";
	else
		cout << '\n' << "Ah, azar.. Falhou, algo nao bateu certo!\n";
}

void func5(vector<string> wordList) {			// inserir wildcard para procurar todas as palavras correspondentes
	string wildcard;
	cout << "Insira a string com wildcards: "; cin >> wildcard;
	const char *strWild = wildcard.c_str();
	
	cout << "\n\n" << "As palavras do dicionario que correspondem sao:\n";
	for (unsigned i = 0; i < wordList.size(); i++) {
		const char *str = wordList[i].c_str();
		if (wildcardMatch(str, strWild)) {
			cout << wordList[i] << '\n';
		}
	}
	cout << '\n';
}
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

int main()
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
	case 4: func4(wordList); break;
	case 5: func5(wordList); break;
	default: {
		cout << "Valor inserido invalido.\n \n";
		interfStart();
		break; }
	}

	system("pause");
	return 0;
}