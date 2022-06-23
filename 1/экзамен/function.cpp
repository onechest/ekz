#include "function.h"

ofstream fileOut;

/// <summary>
/// Фильтруем символы относительно выбраных настроек
/// </summary>
/// <param name="text"> - текст для фильтрации</param>
/// <param name="lat"> - будут ли фильтроваться символы латиницы</param>
/// <param name="kir"> - будут ли фильтроваться символы латиницы</param>
/// <param name="num"> - будут ли фильтроваться цифры</param>
/// <param name="pun"> - будут ли фильтроваться пунктуационые символы</param>
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
    cout << "========================================================\n";
    cout << "Файл успешно зафильтрован                              |" << endl;
    cout << "Желаете содержимое вывести на экран (1 - да) (2 - нет) |" << endl;
    cout << "========================================================\n";
    while (choice != "1" && choice != "2")
    {
        cout << "Введите значение: ";
        cin >> choice;
        if (choice != "1" && choice != "2")
        {
            cout << "Неккоректное значение, введите 1 или 2" << endl;
        }
    }
    if (choice == "1")
    {
        system("cls");
        cout << newText << endl;
        system("pause");
    }

    choice = "";
    while (choice != "1" && choice != "2")
    {
        system("cls");
        cout << "=====================================" << endl;
        cout << "Желаете содержимое сохранить в файле|\n";
        cout << "ДА  (1)                             |\n";
        cout << "НЕТ (2)                             |\n";
        cout << "=====================================" << endl;
        cout << "Введите значение: ";
        cin >> choice;
        if (choice != "1" && choice != "2")
        {
            cout << "Неккоректное значение, введите 1 или 2" << endl;
            system("pause");
        }
    }

    if (choice == "1")
    {
        fileOut.open("final.txt");
        fileOut << newText;
        fileOut.close();
        cout << "Текст успешно сохранен в файле\n";
    }
    cout << "Программа завершила свою работу\n";
}

/// <summary>
/// Меню фильтрации текста
/// Здесь пользователь будет выставлять настройки для фильтрации
/// </summary>
/// <param name="text">  Текст, который ввел пользователь</param>
/// <returns></returns>
int Filters(string text)
{
    string choice = "";
    bool lat = false;
    bool kir = false;
    bool num = false;
    bool pun = false;
    while (true)
    {
        system("cls");
        cout << "=================================================" << endl;
        cout << "ФИЛЬТРЫ false - оключено true - включено        |" << endl;
        cout << "Символы латиницы   (1) - ";
        if (lat == false)
            cout << "OFF" << "                    |" << endl;
        else
            cout << "ON" << "                     |" << endl;
        cout << "Символы кирилицы   (2) - ";
        if (kir == false)
            cout << "OFF" << "                    |" << endl;
        else
            cout << "ON" << "                     |" << endl;
        cout << "Символы пунктуации (3) - ";
        if (pun == false)
            cout << "OFF" << "                    |" << endl;
        else
            cout << "ON" << "                     |" << endl;
        cout << "Цифры              (4) - ";
        if (num == false)
            cout << "OFF" << "                    |" << endl;
        else
            cout << "ON" << "                     |" << endl;
        cout << "Нажмите 5, что бы начать фильтрование текста:   |\n";
        cout << "=================================================" << endl;
        cout << "Выберите число, что бы изменить значение фильтра: ";
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
            cout << "Ошибка ввода!!!" << endl;
            system("pause");
        }
    }
}