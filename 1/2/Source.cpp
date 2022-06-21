#include <iostream>     //����������
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
	//��������� ���������� �������� ���������
	for (int i = 192; i <= 255; i++) //upercace
	{
		lib += (char)i;
		//����� � ������� ��� � ������ ���������.
		if (i == 229)
		{
			lib += (char)184;
		}
		//����� � ������� ��� � ������ ���������
		if (i == 197)
		{
			lib += (char)168;
		}
	}
	return lib;
}
string MakeLibENG()
{
	//��������� ���������� ����������� ���������
	//��������� �����
	for (int i = 65; i <= 90; i++)
	{
		lib += (char)i;
	}
	//��������� �����
	for (int i = 97; i <= 122; i++)
	{
		lib += (char)i;
	}
	return lib;
}

void SquareOfSymbolR(string lib)
{
	//������� �������� �������� ���������
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
	//������� �������� ����������� ���������
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
	//���� ������ �����
	while (lang[0] != 49 && lang[0] != 50 || lang.length() > 1)
	{
		cout << "�����:\n";
		cout << "���������� (1)\n";
		cout << "������� (2)\n";
		cout << "�������� ��������: ";
		cin >> lang;
		if ((lang[0] != 49 && lang[0] != 50) || lang.length() > 1)
		{
			system("cls");
			cout << "������" << endl;
		}
	}
	cout << endl;
	system("cls");
	return lang;
}

string entryKey(string lang, string& key)
{
	//���� ����� �����
	int a = 0;
	switch (lang[0])
	{
		//��� �������� �����
	case 50:
	{
		while (a != 1)
		{
			cout << "������� ����: ";
			cin >> key;
			for (int i = 0; i < key.length(); i++)
			{
				if ((key[i] >= -66 && key[i] <= 0) || key[i] == -72 || key[i] == -88)
				{
					a = 1;
				}
				else
				{
					cout << "���� ��������." << endl;
					break;
				}
			}
		}
		break;
	}
	//��� ����������� �����
	case 49:
	{
		while (a != 1)
		{
			cout << "������� ����: ";
			cin >> key;
			for (int i = 0; i < key.length(); i++)
			{
				if ((key[i] >= 65 && key[i] <= 90) || (key[i] >= 97 && key[i] <= 122))
				{
					a = 1;
				}
				else
				{
					cout << "���� ��������." << endl;
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
	//�������� �� �������� �����
	fileIn.open("original.txt");
	if (fileIn.fail())
	{
		cout << "ERROR" << endl;
		return "FALSE";
	}
	//��������� ���� � ���������
	string str; //������ �����
	string choice = ""; //��������, ������� ����� �������� (������� � �������������� ������)
	while (!fileIn.eof())
	{
		getline(fileIn, str); //��������� ������
		for (int i = 0; i < str.length(); i++)
		{
			//���� ���������� ������� ����� � ���������� ������, ��� ���������� ����� � ������� ������
			if (((lang == "2" && str[i] > 97 && str[i] < 122 || str[i] > 64 && str[i] < 91) || (lang == "1" && str[i] >= -66 && str[i] <= 0 || str[i] == -72 || str[i] == -88)) && choice != "1")
			{
				cout << "� �����, ���� �������, ������� �� ���������� � ��� ��� �� �������\n";
				cout << "�� ������� ��� ������ ������������ ����? (1-��, 2-���) ";
				cin >> choice;
				//�������� �� ������������ �����
				while (choice.length() != 1 || choice != "2" && choice != "1")
				{
					cout << "������, ������� ���������� ��������: ";
					cin >> choice;
				}
				//���� �� ����� ������������ ����, �� ����������� ���
				if (choice.length() == 1 && choice == "2")
				{
					return choice;
				}
				//���� ����� ������������ ����, �� �������
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
	int keySymbol = 0; //������ ����, ��� �� �� ������������ �� �������, ������ ��������� ���������� 

	for (int a = 0; a < Text.length(); a++) //������ ������
	{
		//���� ��� ��� ������� � ������� �����
		if ((key[keySymbol % key.length()] < -33 && key[keySymbol % key.length()] != -88 && key[keySymbol % key.length()] != -72) || (key[keySymbol % key.length()] < 91 && key[keySymbol % key.length()] > 64))
		{
			key[keySymbol % key.length()] += 32;
		}
		//��� �������� �����
		if (lang == "2")
		{
			//���� �������� �����������
			if ((Text[a] >= 0 && Text[a] != -72 && Text[a] != -88))
			{
				encryptText += Text[a];
				continue;
			}
			//���� �������� ����� � ��� �
			else if ((key[keySymbol % key.length()] == -72) || (key[keySymbol % key.length()] == -88))
			{
				key[keySymbol % key.length()] = -72;
			}
			//���� ������ �������� ����� � ���������� ����
			for (int i = 33; i < 66; i++) //������(��� ������)
			{
				if (lib[i] == key[keySymbol % key.length()])
				{
					//���� ������ ����� � ���������� ����
					for (int j = 0; j < 66; j++) //�������(��� ������)
					{
						if (lib[j] == Text[a])
						{
							//���� ����� � ������ ���������
							if (j >= 33)
							{
								encryptText += squareR[i - 33][j - 33];
							}
							//���� ����� � ������ ���������
							else
							{
								encryptText += squareR[i - 33][j];
							}
							break;
						}
					}
					keySymbol++; //��������� � ���������� ������� �����
					break;
				}
			}
		}
		else
		{
			//������� ������ ��� ��, ������ ������� - ����������
			if ((Text[a] >= 0 && Text[a] < 65) || (Text[a] > 90 && Text[a] < 97) || (Text[a] < 0 && Text[a] >= -66 || Text[a] == -88 || Text[a] == -72))
			{
				encryptText += Text[a];
				continue;
			}
			for (int i = 26; i < 52; i++)
			{
				if (lib[i] == key[keySymbol % key.length()])
				{
					for (int j = 0; j < 52; j++) //�������(��� ������)
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
	//��������� ������ � ����
	fileOut.open("encrypted.txt");
	fileOut << encryptText;
	fileOut.close();
	Text = encryptText;

	//���� ����� ����� ����������� � ������� ����������
	string choice = "0";
	cout << "���� ������� ����������, ������ ����������� ���������� (1 - ��, 2- ���): ";
	while (choice != "1" && choice != "2")
	{
		cin >> choice;
		if (choice == "1")
		{
			cout << Text;
		}
		else if (choice != "1" && choice != "2")
		{
			cout << "������� ���������� ��������: ";
		}
	}
}
void decryptText(string& Text, string key, string lang)
{
	string decryptText;
	int numStr = 0;
	int keySymbol = 0;
	for (int a = 0; a < Text.length(); a++) //������ ������
	{
		//��� �������� �����
		if (lang == "2")
		{
			//���� �������� �����������
			if ((Text[a] >= 0 && Text[a] != -72 && Text[a] != -88))
			{
				decryptText += Text[a];
				continue;
			}
			//���� �������� ����� �
			else if ((key[keySymbol % key.length()] == -72) || (key[keySymbol % key.length()] == -88))
			{
				key[keySymbol % key.length()] = -72;
			}
			//���� ����� ������, ���� ������ ����
			for (int i = 33; i < lib.length(); i++) //����� ������
			{
				if (key[keySymbol % key.length()] == lib[i])
				{
					numStr = i;
					break;
				}
			}
			//���� ����� �������, ���� ������������ �����
			for (int j = 33; j < lib.length(); j++) //����� �������
			{
				//���� ����� � �������� �������� ��������� � ������ ������������� ������
				//�� �� ������� ������� ��� ������� ���������� �����, ������� ���� � �������� ������
				if (squareR[numStr - 33][j - 33] == Text[a])
				{
					decryptText += lib[j];
					break;
				}
			}
			keySymbol++;
		}
		//�� ������ �� �������� � � ����������� �������
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
	//��������� ��������� ���� � ������� ������ ���� ������������� �����
	fileOut.open("deciphered.txt");
	//��������� ���� ��������
	fileOut << decryptText;
	//��������� ����
	fileOut.close();

	//���������� ������������ ����������� ����������
	string choice = "0";
	cout << "���� ������� �����������, ������ ����������� ���������� (1 - ��, 2- ���): ";
	while (choice != "1" && choice != "2")
	{
		cin >> choice;
		if (choice == "1")
		{
			cout << decryptText;
		}
		else if (choice != "1" && choice != "2")
		{
			cout << "������� ���������� ��������: ";
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru"); //������������

	string lang = "";
	string key = "";
	string Text = "";
	choiceLanguage(lang);
	//���� ���������� ����
	if (lang == "1")
	{
		MakeLibENG();
		SquareOfSymbolENG(lib);
	}
	//��� ������� ����
	else
	{
		MakeLibR();
		SquareOfSymbolR(lib);
	}

	entryKey(lang, key);
	//���� ������ �� �������� � ������
	if (readingFile(lang, key, Text) == "2")
	{
		return 0;
	}

	//���� ������ � ������
	string choice = "0";
	while (choice != "1" && choice != "2" && choice != "3")
	{
		cout << "��� ������ �������:\n��������� (1)\n������������ (2)\n��� ����� (3)\n�������� ��������: ";
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
			cout << "������, ������� ���������� ��������: " << endl;
		}
	}
	return 1;
}