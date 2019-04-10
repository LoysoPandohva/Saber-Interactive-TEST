#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <ctime>
using namespace std;
#pragma warning(disable:4996)

void Print(int x) {
	if (x) {
		Print(x >> 1);
		cout << (x & 1);
	}
}
void First() {
	int x;
	cout << "Enter a signed integer: ";
	cin >> x;
	cout << "Binary representation : ";
	if (x > 0) cout << 0;
	else {
		x = -x;
		cout << 1;
	}
	Print(x);
	cout << endl;
}

void RemoveDups(char *pStr) {
	for (int i = 0; i < 256; i++) {
		if (pStr[i] == '\0') break;
		if (pStr[i] == pStr[i + 1]) {
			for (int j = i; j < 256; j++) {
				pStr[j] = pStr[j + 1];
				if (pStr[j] == '\0') break;
			}
			i--;
		}
	}
}
void Second() {
	char str[256];
	cout << "Enter string: ";
	cin.ignore();
	cin.getline(str, 256, '\n');
	RemoveDups(str);
	cout << str;
	cout << endl;
}

struct ListNode {
	ListNode *	prev;
	ListNode *	next;
	ListNode *	rand; // указатель на произвольный элемент данного списка либо NULL
	string		data;
	int			randNumber; //
};
class List {
public:
	// ищу ссылку на рандомный элемент списка
	ListNode * RandomPointer(int randNumber) {
		if (randNumber == -1) return NULL;
		ListNode* node = this->head;
		for (int i = 0; i < randNumber; i++) {
			node = node->next;
		}
		return node;
	}

	// функция создает список
	void CreateList(string* str, int* r) {
		this->head = new ListNode;
		this->head->prev = NULL;
		this->head->next = NULL;
		this->head->rand = NULL;
		this->head->data = str[0];
		this->head->randNumber = r[0];
		ListNode* node = this->head;
		ListNode* n;
		for (int i = 1; i < this->count; i++) {
			n = node;
			node->next = new ListNode;
			node = node->next;
			node->prev = n;
			node->next = NULL;
			node->rand = NULL;
			node->data = str[i];
			node->randNumber = r[i];
		}
		this->tail = node;

		node = this->head;
		while (node != NULL) {
			node->rand = RandomPointer(node->randNumber);
			node = node->next;
		}
	}

	// инициализирую данные узлов списка и создаю его
	List(int count) {
		this->count = count;
		string str[] = { "I","WANT","WORK","IN","SABER_INTERACTIVE" };
		int *r = new int[count];
		for (int i = 0; i < this->count; i++) {
			r[i] = (rand() % (count + 1)) - 1;
		}
		CreateList(str, r);
	}

	void PresentList() {
		ListNode* node = this->head;
		int i = 1;
		while (node != NULL) {
			cout << "Node №" << i << " by the address '0x" << node;
			cout << "' keeps field '" << node->data;
			if (node->randNumber == -1) cout << "' and refers to NULL." << endl;
			else {
				cout << "' and refers to node №" << node->randNumber + 1;
				cout << " by the address '0x" << node->rand << "'." << endl;
			}
			node = node->next;
			i++;
		}
	}

	// сохранение в файл (файл открыт с помощью fopen(path, "wb"))
	void Serialize(FILE * file) {
		fprintf(file, "%d ", this->count);
		ListNode* node = this->head;
		while (node != NULL) {
			fprintf(file, "%s %d ", node->data.c_str(), node->randNumber);
			node = node->next;
		}
	}

	// загрузка из файла (файл открыт с помощью fopen(path, "rb"))
	void Deserialize(FILE * file) {
		int _count;
		fscanf(file, "%d ", &_count);
		this->count = _count;
		char ch[20];
		string *str = new string[this->count];
		int *r = new int[this->count];
		for (int i = 0; i < this->count; i++) {
			fscanf(file, "%s %d ", ch, &r[i]);
			str[i] = string(ch);
		}
		CreateList(str, r);		
	} 
private:
	ListNode *	head;
	ListNode *  tail;
	int			count;
};
void Third() {
	system("cls");
	FILE *file;
	List l(5);
	char path[] = "file.txt";
	cout << "List already created" << endl;
	int num, stop = 1;
	while (stop == 1) {
		l.PresentList();
		cout << endl << "Your opportunities:" << endl;
		cout << "1. Serialize" << endl;
		cout << "2. Deserialize" << endl;
		cout << "0. Back" << endl;
		cout << "Select: ";
		cin >> num;
		switch (num) {
		case 1:
			fopen_s(&file, path, "wb");
			l.Serialize(file);
			fclose(file);
			break;
		case 2:
			fopen_s(&file, path, "rb");
			l.Deserialize(file);
			fclose(file);
			break;
		case 0:
			stop = 0;
		}
		if (stop != 0) {
			system("pause >> NULL");
			system("cls");
		}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	int num, stop = 1;
	while (stop == 1) {
		cout << "Select task number: ";
		cin >> num;
		switch (num) {
		case 1:
			First();
			break;
		case 2:
			Second();
			break;
		case 3:
			Third();
			break;
		case 0:
			stop = 0;
		}
		system("pause >> NULL");
		system("cls");
	}
}