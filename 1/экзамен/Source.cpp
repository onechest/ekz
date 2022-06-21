#include <iostream>     //����������
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

ifstream fileIn1;
ofstream fileOut;

//��� ��������� �����
int readingFile(string& text)
{
    fileIn1.open("original.txt");

    if (fileIn1.fail())
    {
        cout << "ERROR" << endl;
        return 404;
    }
    while (!fileIn1.eof())
    {
        string str;
        getline(fileIn1, str);
        text += str;
        text += '\n';
    }
    fileIn1.close();
}

void filtrSymvols(string text, bool lat, bool kir, bool num, bool pun)
{
    string newText = "";
    for (int i = 0; i < text.length(); i++)
    {
        if (lat == true && (text[i] >= 65 && text[i] <= 90 || text[i] >= 97 && text[i] <= 122))
        {
            newText += " ";
        }
        else if (kir == true && (text[i] <= 0 && text[i] >= -66 || text[i] == -72 || text[i] == -88))
        {
            newText += " ";
        }
        else if (pun == true && (text[i] >= 33 && text[i] <= 47) || (text[i] >= 58 && text[i] <= 64) || (text[i] >= 91 && text[i] <= 96) || (text[i] >= 123 && text[i] <= 126))
        {
            newText += " ";
        }
        else if (num == true && (text[i] >= 48 && text[i] <= 57))
        {
            newText += " ";
        }
        else
        {
            newText += text[i];
        }
    }

    string choice = "";
    system("cls");
    cout << "���� ������� ������������ " << endl;
    cout << "������� ���������� ������� �� ����� (1 - ��) (2 - ���): ";
    while (choice != "1" && choice != "2")
    {
        cin >> choice;
        if (choice != "1" && choice != "2")
        {
            cout << "������������ ��������, ������� 1 ��� 2" << endl;
        }
    }
    if (choice == "1")
    {
        system("cls");
        cout << newText << endl;
    }

    fileOut.open("final.txt");
    fileOut << newText;
    fileOut.close();
    system("pause");
    cout << "����� ������� �������� � �����\n";
}

int Filters(string& text)
{
    string choice = "";
    bool lat = false;
    bool kir = false;
    bool num = false;
    bool pun = false;
    while (true)
    {
        system("cls");
        cout << "������� false - �������� true - ��������" << endl;
        cout << "������� ��������   (1) - ";
        if (lat == false)
            cout << "OFF" << endl;
        else
            cout << "ON" << endl;

        cout << "������� ��������   (2) - ";
        if (kir == false)
            cout << "OFF" << endl;
        else
            cout << "ON" << endl;

        cout << "������� ���������� (3) - ";
        if (pun == false)
            cout << "OFF" << endl;
        else
            cout << "ON" << endl;

        cout << "�����              (4) - ";
        if (num == false)
            cout << "OFF" << endl;
        else
            cout << "ON" << endl;

        cout << "������� 5, ��� �� ������ ������������ ������:\n";
        cout << "�������� �����, ��� �� �������� �������� �������: ";
        cin >> choice;

        if (choice == "1")
        {
            if (lat == false)
                lat = true;
            else
                lat = false;
        }
        else if (choice == "2")
        {
            if (kir == false)
                kir = true;
            else
                kir = false;
        }
        else if (choice == "3")
        {
            if (pun == false)
                pun = true;
            else
                pun = false;
        }
        else if (choice == "4")
        {
            if (num == false)
                num = true;
            else
                num = false;
        }
        else if (choice == "5")
        {
            filtrSymvols(text, lat, kir, num, pun);
            return 1;
        }
        else
        {
            cout << "������ �����!!!" << endl;
            system("pause");
        }
    }
}

void main()
{
    setlocale(LC_ALL, "Russian"); //������������
    string text = "";
    string choice = "";
    while (choice != "1" && choice != "2")
    {
        cout << "�������� ������ �����:\n";
        cout << "�� �����    (1)\n";
        cout << "������ ���� (2)\n";
        cout << "������� �����: ";
        cin >> choice;
        if (choice != "1" && choice != "2")
        {
            cout << "������ �����, ��������� �������";
        }
    }

    if (choice == "1")
    {
        readingFile(text);
    }
    else
    {
        cout << "������� �����: ";
        cin.ignore();
        getline(cin, text);
    }
    Filters(text);

}