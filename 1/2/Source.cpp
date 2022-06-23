#include "function.h" 

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru"); //руссификатор

	int nymEncryptText = 0;
	string key = "";
	string Text = "";

	MakeLib();
	readingFile(Text);
	entryKey(key);

	string choice = "0";
	while (choice != "1" && choice != "2" && choice != "3")
	{
		cout << "|===================|\n";
		cout << "|Что хотите сделать:|\n|Шифровать       (1)|\n|Расшифровать    (2)|\n|Все сразу       (3)|\n" << "|===================|\n" << "Выберите действие: ";
		cin >> choice;
		system("cls");
		if (choice == "1")
		{
			encryptText(Text, key);
		}
		else if (choice == "2")
		{
			decryptText(Text, key);
		}
		else if (choice == "3")
		{
			encryptText(Text, key);
			decryptText(Text, key);
		}
		else
		{
			cout << "Ошибка, введите правильное действие: " << endl;
		}
	}
	return 1;
}