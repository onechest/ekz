#include "function.h"

ifstream fileIn;
ofstream fileOut;
string lib;

/// <summary>
/// В этой функциии создаеться библиотека символов
/// </summary>
/// <returns></returns>
string MakeLib()
{
	for (int i = 32; i <= 128; i++)
	{
		lib += (char)i;
	}
	for (int i = 192; i <= 255; i++)
	{
		lib += (char)i;
	}
	lib += (char)168;
	lib += (char)168;
	return lib;
}
/// <summary>
/// В этой функции пользователь вводит ключ
/// </summary>
/// <param name="key"> ключ, который вводит пользователь</param>
/// <returns></returns>
string entryKey(string& key)
{
	int a = 0;
	cout << "Введите ключ: ";
	cin >> key;
	system("cls");
	return key;
}
/// <summary>
/// Чтение текста из файла
/// </summary>
/// <param name="Text"> Текст из файла</param>
/// <returns></returns>
string readingFile(string& Text)
{
	string str;
	fileIn.open("original.txt");
	if (fileIn.fail())
	{
		cout << "ERROR" << endl;
		return "FALSE";
	}

	int kolStr = 0;
	while (!fileIn.eof())
	{
		getline(fileIn, str);
		Text += str;
		Text += "\n";

	}
	fileIn.close();

	system("cls");
	return Text;
}

/// <summary>
/// Шифрование текста
/// </summary>
/// <param name="Text"> - Текст оригинала</param>
/// <param name="key"> - Ключ шифрования</param>
void encryptText(string& Text, string key)
{
	string encryptText;
	int keySymbol = 0;
	for (int a = 0; a < Text.length(); a++) //символ текста
	{
		if (Text[a] == '\n')
		{
			continue;
		}
		int nymEncryptText = 0;
		if (keySymbol == key.length())
		{
			keySymbol = 0;
		}
		for (int i = 0; i < lib.length(); i++)
		{
			if (Text[a] == lib[i])
			{
				nymEncryptText += i;
				break;
			}
		}
		for (int i = 0; i < lib.length(); i++)
		{
			if (key[keySymbol] == lib[i])
			{
				nymEncryptText += i;
				break;
			}
		}
		encryptText += lib[nymEncryptText % lib.length()];
		keySymbol++;
	}

	//Переносим данный в файл
	Text = encryptText;
	fileOut.open("encrypted.txt");
	fileOut << Text;
	fileOut.close();

	//Если хотим сразу просмотреть в консоли содержимое
	string choice = "0";
	cout << "Файл успешно зашифрован, хотите просмотреть содержимое (1 - да, 2- нет): ";
	while (choice != "1" && choice != "2")
	{
		cin >> choice;
		if (choice == "1")
		{
			cout << Text << endl;
		}
		else if (choice != "1" && choice != "2")
		{
			cout << "Введите правильное значение: ";
		}
	}
}
/// <summary>
/// Дешифровка текста
/// </summary>
/// <param name="Text"> - зашифрованый текст</param>
/// <param name="key"> - ключ для дешифровки</param>
void decryptText(string& Text, string key)
{
	string decryptText;
	int numDecryptText = 0;
	int keySymbol = 0;
	for (int a = 0; a < Text.length(); a++) //символ текста
	{
		if (Text[a] == '\n')
		{
			continue;
		}
		if (keySymbol == key.length())
		{
			keySymbol = 0;
		}
		for (int i = 0; i < lib.length(); i++)
		{
			if (Text[a] == lib[i])
			{
				numDecryptText = i;
				break;
			}
		}
		for (int i = 0; i < lib.length(); i++)
		{
			if (key[keySymbol] == lib[i])
			{
				numDecryptText -= i;
				break;
			}
		}

		while (numDecryptText < 0)
		{
			numDecryptText += lib.length();
		}
		decryptText += lib[numDecryptText];
		keySymbol++;
	}

	fileOut.open("deciphered.txt");
	fileOut << decryptText;
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