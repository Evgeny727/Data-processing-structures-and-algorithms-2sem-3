#pragma once
#include "BinFile.h"
#include "HeshTable.h"

void insertInTable(string namebf, HeshTable& t) {
	ifstream bf(namebf, ios::binary);
	student s;
	bf.read((char*)&s, sizeof(student));
	for (int i = 0; !bf.eof(); i++) {
		insertInHeshTable(s.numZachBook, i, t);
		bf.read((char*)&s, sizeof(student));
	}
	bf.close();
}

void deleteRecord(string namebf, HeshTable& t, int key) {
	int index = search(t, key);
	isDeletedFromHeshTable(t, key);
	deleteKeyBinFile(namebf, t.T[index].num);
	cout << "Результат удаления записи с ключом " << key << endl;
	cout << "Хеш-таблица\n";
	for (int i = index; i < t.length; i++) {
		if (t.T[i].isOpen == false) {
			t.T[i].num--;
		}
	}
	outTable(t);
	cout << endl;
	outBinFile(namebf);
}

void searchRecord(string namebf, HeshTable& t, int key) {
	int index = search(t, key);
	if (index != -1) {
		int num = t.T[index].num;
		student s = searchKeyBinFile(namebf, num);
		cout << "\nЗапись с ключом " << key << ":\n" << s;
	}
	else cout << "Запись не найдена!\n";
}