#include "function.h"

void main()
{
    setlocale(LC_ALL, "Russian"); //������������
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string text = "";
    cout << "������� �����: ";
    getline(cin, text);

    Filters(text);

}