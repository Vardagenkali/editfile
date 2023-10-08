#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>



using namespace std;

void Delete(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "������ �������� �����" << endl;
        return;
    }

    ofstream outFile("temp.txt");
    if (!outFile) {
        cout << "������ �������� ���������� �����" << endl;
        return;
    }

    string line, prevLine;

    while (getline(inFile, line)) {
        if (!prevLine.empty()) {
            outFile << prevLine << endl;
        }
        prevLine = line; 
    }

    inFile.close();
    outFile.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str()); 

    cout << "��������� ������ �������!" << endl;
}

void Search(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "������ �������� �����" << endl;
        return;
    }

    string longestLine;
    string line;

    while (getline(inFile, line)) {
        if (line.length() > longestLine.length()) {
            longestLine = line;
        }
    }

    inFile.close();

    if (!longestLine.empty()) {
        cout << "����� ������� ������: " << longestLine << endl;
    }
    else {
        cout << "���� ����." << endl;
    }
}

void Kolvo(const string& filename, const string& wordToCount) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "������ �������� �����" << endl;
        return;
    }

    int count = 0;
    string line;
    while (getline(inFile, line)) {
        size_t pos = 0;
        while ((pos = line.find(wordToCount, pos)) != string::npos) {
            count++;
            pos += wordToCount.length();
        }
    }

    inFile.close();

    cout << "����� '" << wordToCount << "' ����������� " << count << " ���(�)" << endl;
}

void Edit(const string& filename, const string& wordToReplace, const string& replace) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "������ �������� �����" << endl;
        return;
    }

    ofstream outFile("temp.txt");
    if (!outFile) {
        cout << "������ �������� ���������� �����" << endl;
        inFile.close();
        return;
    }

    string line;

    while (getline(inFile, line)) {
        size_t pos = 0;
        while ((pos = line.find(wordToReplace, pos)) != string::npos) {
            line.replace(pos, wordToReplace.length(), replace);
            pos += replace.length();
        }
        outFile << line << endl;
    }

    inFile.close();
    outFile.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    cout << "����� '" << wordToReplace << "' �������� �� '" << replace << "' � �����." << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    const string filename = "asd.txt";
    int vib;
    cout << "�������������� �����\n1)������� ��������� ������\n2)����� ����� ������� ������\n3)��������� ���-�� �������� �����\n4)�������� �������� �����\n��� �����: ";
    cin >> vib;
    cout << endl;
    if (vib < 1 || vib > 4) {
        cout << "������: ������������ �����" << endl;
        return 1;
    }

    if (vib == 1) {
        Delete(filename);
    }
    else if (vib == 2) {
        Search(filename);
    }
    else if (vib == 3) {
        string count;
        cout << "������� ����� ��� ��������: ";
        cin >> count;
        Kolvo(filename, count);
    }
    else if (vib == 4) {
        string wordToReplace, replace;
        cout << "������� �����, ������� ����� ��������: ";
        cin >> wordToReplace;
        cout << "������� �����, �� ������� ����� ��������: ";
        cin >> replace;
        Edit(filename, wordToReplace, replace);
    }

    return 0;
}