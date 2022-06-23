#include "function.h"

void main()
{
    setlocale(LC_ALL, "Russian"); //руссификатор
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string text = "";
    cout << "¬ведите текст: ";
    getline(cin, text);

    Filters(text);

}