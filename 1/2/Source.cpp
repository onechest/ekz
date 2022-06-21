#include <iostream>     //библиотеки
#include <string>
#include <fstream>
#include <Windows.h> 

using namespace std;

ifstream fileIn;
ofstream fileOut;
string lib;
const int alphabetR = 33;
const int alphabetENG = 26;
char squareR[alphabetR][alphabetR] = {};
char squareENG[alphabetENG][alphabetENG] = {};

string MakeLibR()
{
	//Заполняем библиотеку русскими символами
	for (int i = 192; i <= 255; i++) //upercace
	{
		lib += (char)i;
		//буква ё которой нет в данном диапазоне.
		if (i == 229)
		{
			lib += (char)184;
		}
		//буква Ё которой нет в данном диапазоне
		if (i == 197)
		{
			lib += (char)168;
		}
	}
	return lib;
}
string MakeLibENG()
{
	//Заполняем библиотеку английскими символами
	//Заглавные буквы
	for (int i = 65; i <= 90; i++)
	{
		lib += (char)i;
	}
	//маленькие буквы
	for (int i = 97; i <= 122; i++)
	{
		lib += (char)i;
	}
	return lib;
}

void SquareOfSymbolR(string lib)
{
	//Квадрат Виженера русскими символами
	for (int i = 0; i < 33; i++)
	{
		for (int j = 0; j < 33; j++)
		{
			squareR[i][j] = lib[(i + j) % 33 + lib.length() / 2];
		}
	}
}
void SquareOfSymbolENG(string lib)
{
	//Квадрат Виженера английскими символами
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			squareENG[i][j] = lib[(i + j) % 26 + lib.length() / 2];
		}
	}
}

string choiceLanguage(string& lang)
{
	//Меню выбора языка
	while (lang[0] != 49 && lang[0] != 50 || lang.length() > 1)
	{
		cout << "Языки:\n";
		cout << "Английский (1)\n";
		cout << "Русский (2)\n";
		cout << "Выберите действие: ";
		cin >> lang;
		if ((lang[0] != 49 && lang[0] != 50) || lang.length() > 1)
		{
			system("cls");
			cout << "ОШИБКА" << endl;
		}
	}
	cout << endl;
	system("cls");
	return lang;
}

string entryKey(string lang, string& key)
{
	//меню ввода ключа
	int a = 0;
	switch (lang[0])
	{
		//для русского языка
	case 50:
	{
		while (a != 1)
		{
			cout << "Введите ключ: ";
			cin >> key;
			for (int i = 0; i < key.length(); i++)
			{
				if ((key[i] >= -66 && key[i] <= 0) || key[i] == -72 || key[i] == -88)
				{
					a = 1;
				}
				else
				{
					cout << "ключ неверный." << endl;
					break;
				}
			}
		}
		break;
	}
	//для английского языка
	case 49:
	{
		while (a != 1)
		{
			cout << "Введите ключ: ";
			cin >> key;
			for (int i = 0; i < key.length(); i++)
			{
				if ((key[i] >= 65 && key[i] <= 90) || (key[i] >= 97 && key[i] <= 122))
				{
					a = 1;
				}
				else
				{
					cout << "ключ неверный." << endl;
					break;
				}
			}
		}
		break;
	}
	}
	system("cls");
	return key;
}

string readingFile(string lang, string key, string& Text)
{
	//Проверка на открытие файла
	fileIn.open("original.txt");
	if (fileIn.fail())
	{
		cout << "ERROR" << endl;
		return "FALSE";
	}
	//Считываем файл с исходного
	string str; //строка файла
	string choice = ""; //действие, которое будем выбирать (связано с использованием файлов)
	while (!fileIn.eof())
	{
		getline(fileIn, str); //принимаем строку
		for (int i = 0; i < str.length(); i++)
		{
			//если попадуться русские буквы в английском тексте, или английские буквы в русском тексте
			if (((lang == "2" && str[i] > 97 && str[i] < 122 || str[i] > 64 && str[i] < 91) || (lang == "1" && str[i] >= -66 && str[i] <= 0 || str[i] == -72 || str[i] == -88)) && choice != "1")
			{
				cout << "В файле, есть символы, которые не относяться к тем что вы выбрали\n";
				cout << "Вы уверены что хотите использовать файл? (1-да, 2-нет) ";
				cin >> choice;
				//проверка на правильность ввода
				while (choice.length() != 1 || choice != "2" && choice != "1")
				{
					cout << "Ошибка, введите правильное дейтсвие: ";
					cin >> choice;
				}
				//Если не хотим использовать файл, то заканчиваем код
				if (choice.length() == 1 && choice == "2")
				{
					return choice;
				}
				//Если хотим использовать файл, то игнорим
				break;
			}
		}
		Text += str;
		Text += "\n";
	}
	cout << endl;
	fileIn.close();
	system("cls");
	return Text;
}

void encryptText(string& Text, string& key, string lang)
{
	string encryptText;
	int keySymbol = 0; //символ кода, что бы на спецсимволах не работал, сделал отдельную переменную 

	for (int a = 0; a < Text.length(); a++) //символ текста
	{
		//Если код был написан с большой буквы
		if ((key[keySymbol % key.length()] < -33 && key[keySymbol % key.length()] != -88 && key[keySymbol % key.length()] != -72) || (key[keySymbol % key.length()] < 91 && key[keySymbol % key.length()] > 64))
		{
			key[keySymbol % key.length()] += 32;
		}
		//Для русского языка
		if (lang == "2")
		{
			//если попались спецсимволы
			if ((Text[a] >= 0 && Text[a] != -72 && Text[a] != -88))
			{
				encryptText += Text[a];
				continue;
			}
			//если попалась буква ё или Ё
			else if ((key[keySymbol % key.length()] == -72) || (key[keySymbol % key.length()] == -88))
			{
				key[keySymbol % key.length()] = -72;
			}
			//Ищем Индекс элемента ключа в библиотеке букв
			for (int i = 33; i < 66; i++) //строка(для ключей)
			{
				if (lib[i] == key[keySymbol % key.length()])
				{
					//Ищем индекс буквы в библиотеке букв
					for (int j = 0; j < 66; j++) //столбец(для текста)
					{
						if (lib[j] == Text[a])
						{
							//Если буква в тексте маленькая
							if (j >= 33)
							{
								encryptText += squareR[i - 33][j - 33];
							}
							//Если буква в тексте заглавная
							else
							{
								encryptText += squareR[i - 33][j];
							}
							break;
						}
					}
					keySymbol++; //переходим к следующему символу ключа
					break;
				}
			}
		}
		else
		{
			//принцип работы тот же, только символы - английские
			if ((Text[a] >= 0 && Text[a] < 65) || (Text[a] > 90 && Text[a] < 97) || (Text[a] < 0 && Text[a] >= -66 || Text[a] == -88 || Text[a] == -72))
			{
				encryptText += Text[a];
				continue;
			}
			for (int i = 26; i < 52; i++)
			{
				if (lib[i] == key[keySymbol % key.length()])
				{
					for (int j = 0; j < 52; j++) //столбец(для текста)
					{
						if (lib[j] == Text[a])
						{
							if (j >= 26)
							{
								encryptText += squareENG[i - 26][j - 26];
							}
							else
							{
								encryptText += squareENG[i - 26][j];
							}
							break;
						}
					}
					keySymbol++;
					break;
				}

			}
		}
	}
	//Переносим данный в файл
	fileOut.open("encrypted.txt");
	fileOut << encryptText;
	fileOut.close();
	Text = encryptText;

	//Если хотим сразу просмотреть в консоли содержимое
	string choice = "0";
	cout << "Файл успешно зашифрован, хотите просмотреть содержимое (1 - да, 2- нет): ";
	while (choice != "1" && choice != "2")
	{
		cin >> choice;
		if (choice == "1")
		{
			cout << Text;
		}
		else if (choice != "1" && choice != "2")
		{
			cout << "Введите правильное значение: ";
		}
	}
}
void decryptText(string& Text, string key, string lang)
{
	string decryptText;
	int numStr = 0;
	int keySymbol = 0;
	for (int a = 0; a < Text.length(); a++) //символ текста
	{
		//для русского языка
		if (lang == "2")
		{
			//если попались спецсимволы
			if ((Text[a] >= 0 && Text[a] != -72 && Text[a] != -88))
			{
				decryptText += Text[a];
				continue;
			}
			//если попалась буква ё
			else if ((key[keySymbol % key.length()] == -72) || (key[keySymbol % key.length()] == -88))
			{
				key[keySymbol % key.length()] = -72;
			}
			//ищем номер строки, зная символ кода
			for (int i = 33; i < lib.length(); i++) //номер строки
			{
				if (key[keySymbol % key.length()] == lib[i])
				{
					numStr = i;
					break;
				}
			}
			//ищем номер столбца, зная зашифрованую букву
			for (int j = 33; j < lib.length(); j++) //номер столбца
			{
				//Если буква в квадрате Виженера совпадает с буквой зашифрованого текста
				//то мы находим столбец под которой находиться буква, которая была в исходном тексте
				if (squareR[numStr - 33][j - 33] == Text[a])
				{
					decryptText += lib[j];
					break;
				}
			}
			keySymbol++;
		}
		//по такому же принципу и с английскими буквами
		else
		{
			if ((Text[a] >= 0 && Text[a] < 65) || (Text[a] > 90 && Text[a] < 97) || (Text[a] < 0 && Text[a] >= -66 || Text[a] == -88 || Text[a] == -72))
			{
				decryptText += Text[a];
				continue;
			}
			for (int i = 26; i < lib.length(); i++)
			{
				if (key[keySymbol % key.length()] == lib[i])
				{
					numStr = i;
					break;
				}
			}
			for (int j = 26; j < lib.length(); j++)
			{
				if (squareENG[numStr - 26][j - 26] == Text[a])
				{
					decryptText += lib[j];
					break;
				}
			}
			keySymbol++;
		}

	}
	//открываем текстовый файл в котором должен быть расшифрованый текст
	fileOut.open("deciphered.txt");
	//переносим туда значения
	fileOut << decryptText;
	//закрываем файл
	fileOut.close();

	//предлагаем пользователю просмотреть содержимое
	string choice = "0";
	cout << "Файл успешно расшифрован, хотите просмотреть содержимое (1 - да, 2- нет): ";
	while (choice != "1" && choice != "2")
	{
		cin >> choice;
		if (choice == "1")
		{
			cout << decryptText;
		}
		else if (choice != "1" && choice != "2")
		{
			cout << "Введите правильное значение: ";
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru"); //руссификатор

	string lang = "";
	string key = "";
	string Text = "";
	choiceLanguage(lang);
	//если английский язык
	if (lang == "1")
	{
		MakeLibENG();
		SquareOfSymbolENG(lib);
	}
	//ели русский язык
	else
	{
		MakeLibR();
		SquareOfSymbolR(lib);
	}

	entryKey(lang, key);
	//если решили не работать с файлом
	if (readingFile(lang, key, Text) == "2")
	{
		return 0;
	}

	//меню работы с файлом
	string choice = "0";
	while (choice != "1" && choice != "2" && choice != "3")
	{
		cout << "Что хотите сделать:\nШифровать (1)\nРасшифровать (2)\nВсе сразу (3)\nВыберите действие: ";
		cin >> choice;
		system("cls");
		if (choice == "1")
		{
			encryptText(Text, key, lang);
		}
		else if (choice == "2")
		{
			decryptText(Text, key, lang);
		}
		else if (choice == "3")
		{
			encryptText(Text, key, lang);
			decryptText(Text, key, lang);
		}
		else
		{
			cout << "Ошибка, введите правильное действие: " << endl;
		}
	}
	return 1;
}