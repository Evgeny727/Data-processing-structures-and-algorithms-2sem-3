#pragma once

using namespace std;

struct student {
    int numZachBook;
    int numGroup;
    char FIO[100];
};

// создание бинарного фала из текстового
int CreateBinFile(string nametf, string namebf) {
    ifstream tf(nametf);
    if (tf) {
        fstream bf(namebf, ios::out | ios::binary);
        student s;
        while (!tf.eof()) {
            tf >> s.numZachBook;
            tf.get();//прочитать до пробела(вместе с пробелом)
            tf >> s.numGroup;
            tf.get();//прочитать до пробела(вместе с пробелом)
            tf.getline(s.FIO, 100, '\n');
            bf.write((char*)&s, sizeof(student));
        }
        tf.close();
        bf.close();
        return 0;
    }
    return 1;
}

//вывод бинарного файла на монитор
void outBinFile(string namebf) {
    fstream bf(namebf, ios::in | ios::binary);
    cout << "Содержание бинарного файла: \n";
    student s;
    bf.read((char*)&s, sizeof(student));
    while (!bf.eof()) {
        cout << s.numZachBook << " " << s.numGroup << " " << s.FIO << endl;
        bf.read((char*)&s, sizeof(student));
    }
    bf.close();
}

//функция ищет запись с номером и при успешном поиске возвращает запись
student searchKeyBinFile(string namebf, int key) {
    ifstream bf;
    bf.open(namebf, ios::binary);
    student s;
    bf.read((char*)&s, sizeof(student));
    int i = 0;
    while (!bf.eof()) {
        if (i == key) {
            bf.close();
            return s;
        }
        i++;
        bf.read((char*)&s, sizeof(student));
    }
    bf.close();
   return s;
}

//добавление записи
void insertInBinFile(string namebf, student s) {
    ifstream bf(namebf, ios::binary);
    bf.seekg(0, ios::end);
    int size = bf.tellg();
    size = size / sizeof(student);
    student* Students_1 = new student[size];
    bf.seekg(0, ios::beg);
    bf.read((char*)Students_1, sizeof(student) * size);
    bf.close();
    ofstream obf(namebf, ios::binary);
    for (int i = 0; i < size; i++)
    {
            obf.write((char*)&Students_1[i], sizeof(student));
    }
    obf.write((char*)&s, sizeof(student));
    obf.close();
}

//удаление записи с заданным номером
void deleteKeyBinFile(string namebf, int key) {
    ifstream bf(namebf, ios::binary);
    bf.seekg(0, ios::end);
    int size = bf.tellg();
    size = size / sizeof(student);
    student* Students_1 = new student[size];
    bf.seekg(0, ios::beg);
    bf.read((char*)Students_1, sizeof(student) * size);
    bf.close();
    ofstream obf(namebf, ios::binary);
    for (int i = 0; i < size; i++)
    {
        if (i != key)
            obf.write((char*)&Students_1[i], sizeof(student));
    }
    obf.close();
}

ostream& operator<< (ostream &out, const student s) {
    out << s.numZachBook << " " << s.numGroup << " " << s.FIO;
    return out;
}

void testBinTask() {
    cout << "Тестирование управления бинарным файлом\n";
    if (CreateBinFile("programTextFile.txt", "Data.dat")) {
        cout << "Error";
    }
    outBinFile("Data.dat");
    student s = searchKeyBinFile("Data.dat", 1);
    cout << "Поиск записи под порядковым номером 1\n";
    cout << "Запись под номером 1:  " << s;
    cout << "\nУдаление записи под порядковым номером 1\n";
    deleteKeyBinFile("Data.dat", 1);
    outBinFile("Data.dat");
    s = searchKeyBinFile("Data.dat", 1);
    cout << "Поиск записи под порядковым номером 1\n";
    cout << "Запись под номером 1:  " << s;
    s.numZachBook = 22020;
    s.numGroup = 7;
    cout << "\nВведите ФИО для новой записи\n";
    cin >> s.FIO;
    insertInBinFile("Data.dat", s);
    outBinFile("Data.dat");
}