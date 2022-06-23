#pragma once
#include <iostream>     //библиотеки
#include <string>
#include <fstream>
#include <Windows.h> 

using namespace std;

string MakeLib();
string entryKey(string& key);
string readingFile(string& Text);
void encryptText(string& Text, string key);
void decryptText(string& Text, string key);
