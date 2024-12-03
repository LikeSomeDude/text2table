#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {

	if (argc != 3) {
		cout << "Use: \n"
			 << "     text2table source destination. \n";
		return 1;
	}

	ifstream inFile(argv[1]);
	if (!inFile) {
		cout << "Can not open file " << argv[1] << "\n";
		return 2;
	}

	//1. Пройти по файлу и подсчитать ширины столбцов
	int lenwords[200] = { 0 };
	int wordlen = 0;
	int wordnum = 0;
	int ch;
	while ((ch = inFile.get()) != EOF) {
		if (ch == ' ' || ch == '\t') {
			if (wordlen != 0) {
				if (lenwords[wordnum] < wordlen) {
					lenwords[wordnum] = wordlen;
				}
				wordlen = 0;
				wordnum++;
			}

		}
		else if (ch == '\n') {
			if (lenwords[wordnum] < wordlen) {
				lenwords[wordnum] = wordlen;
			}
			wordlen = 0;
			wordnum = 0;
		}
		else {
			wordlen++;
		}
	}
	if (wordlen != 0) {
		if (lenwords[wordnum] < wordlen) {
			lenwords[wordnum] = wordlen;
		}
	}
	

//	for (int i = 0; i < 200; i++) {
//		cout << lenwords[i] << " ";
//	}
	inFile.clear();
	inFile.seekg(0);
	//2. Пройти по фалу и добавить пробелы к словам так, чтобы ширина слова с пробелами стала равна ширине столбца
	wordlen = 0;
	wordnum = 0;
	ofstream outFile(argv[2]);
	if (!outFile.is_open()) {
		cout << "Can not write to file: " << argv[2] << "\n";
		inFile.close();
		return 3;
	}
	int charcounter = 0;
	while ((ch = inFile.get()) != EOF) {
		if (ch == ' ' || ch == '\t') {
			if (wordlen != 0) {
				wordnum++;
				wordlen = 0;

			}

		}
		else if (ch == '\n') {
			outFile.put('\n');
			wordlen = 0; 
			wordnum = 0;
			charcounter = 0;
		}
		else {
			if (wordlen == 0 && wordnum > 0) {
				while (charcounter <= lenwords[wordnum-1]) {
					outFile.put(' ');
					charcounter++;
				}
				charcounter=0;
			}
			static_cast<char>(ch);
			outFile.put(ch);
			wordlen++;
			charcounter++;
		}
	}
	inFile.close();
	outFile.close();
	return 0;

	
	

}
