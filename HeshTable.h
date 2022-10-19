#pragma once

using namespace std;

struct typeitem {
	int key = 0;
	int num = -1;
	bool isOpen = true; //��������
	bool isDeleted = false; //�� ���������
};

struct HeshTable {
	int length = 50;
	typeitem* T;
	void createHeshTable() {
		T = new typeitem[length];
	}
};

//���-�������1
int hesh1(int key, int length) {
	return key % length;
}

//���-�������2
int hesh2(int key, int length) {
	return (1 + key % (length - 2));
}

//������� ���������
int insertInHeshTable(int key, int num, HeshTable& t) {
	int index, i = 0;
	for (; i < t.length;) {
		index = (hesh1(key, t.length) + i * hesh2(key, t.length)) % t.length;
		if (t.T[index].isOpen == false) {
			i++;
		}
		else {
			t.T[index].key = key;
			t.T[index].num = num;
			t.T[index].isOpen = false;
			t.T[index].isDeleted = false;
			return 0;
		}
	}
	return 1;//������� ��������� ���������
}

void outTable(HeshTable& t) {
	for (int i = 0; i < t.length; i++) {
		cout << i << " " << t.T[i].key << " " << t.T[i].num << " " << t.T[i].isOpen << " " << t.T[i].isDeleted << endl;
	}
}

int search(HeshTable& t, int key) {
	int index, i = 0;
	do {
		index = (hesh1(key, t.length) + i * hesh2(key, t.length)) % t.length;
		if (t.T[index].isOpen == true) {
			i++;
		}
		if (t.T[index].key == key and t.T[index].isDeleted == true) {
			index = (hesh1(key, t.length) + i * hesh2(key, t.length)) % t.length;
		}
	} while ((i < t.length) and (t.T[index].key != key) and (t.T[index].isOpen == t.T[index].isDeleted));
	if (t.T[index].isOpen == true and t.T[index].isDeleted == false or i >= t.length) {
		return -1;
	}
	return index;
}

//��������
int isDeletedFromHeshTable(HeshTable& t, int key) {
	int i = search(t, key);;
	if (i == -1) {
		return 1;// ��� ������ � �������
	}
	t.T[i].isDeleted = true;
	t.T[i].isOpen = true;
	return 0;
}

void testHeshTable() {
	cout << "\n������������ ���������� ���-��������\n";
	HeshTable T;
	T.createHeshTable();
	insertInHeshTable(45, 0, T); //45
	insertInHeshTable(120, 0, T); //20
	insertInHeshTable(50, 0, T); //0
	insertInHeshTable(45, 0, T); //45 - 41 ��������
	insertInHeshTable(45, 0, T); // 45 - 37 ��������
	insertInHeshTable(45, 0, T); // 45 - 33 ��������
	cout << "���-�������: " << endl;
	outTable(T);
	typeitem r;
	int i = search(T, 120);
	cout << "����� ����� 120: ";
	if (i != -1) {
		r = T.T[i];
		cout << r.key << " " << endl;
	}
	i = isDeletedFromHeshTable(T, 50);
	cout << "�������� ����� 50: ";
	if (i == 0) {
		cout << "record is deleted" << endl;
	}
	else cout << "record is not found" << endl;

	i = isDeletedFromHeshTable(T, 2);
	cout << "�������� ����� 2: ";
	if (i == 0) {
		cout << "record is deleted" << endl;
	}
	else cout << "record is not found" << endl;

	i = isDeletedFromHeshTable(T, 45);
	cout << "�������� ����� 45: ";
	if (i == 0) {
		cout << "record is deleted" << endl;
	}
	else cout << "record is not found" << endl;
	i = search(T, 45);
	cout << "����� ����� 45: ";
	if (i != -1) {
		r = T.T[i];
		cout << "������ = " << i << " ����: " << r.key << endl;
	}
	i = search(T, 50);
	cout << "����� ����� 50: ";
	if (i != -1) {
		r = T.T[i];
		cout << r.key << " " << endl;
	}
	else cout << "record is not found" << endl;
	cout << "���-�������: " << endl;
	outTable(T);
}