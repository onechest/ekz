#include <iostream>     //����������
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

ifstream fileIn;
ofstream fileOut;

void main()
{   
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian"); //������������
    
    string str = "          ";
    fileOut.open("text.txt");
    fileOut << str;
    fileOut.close();
    cout << "������" << endl;
}