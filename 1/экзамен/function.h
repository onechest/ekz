#pragma once
#include <iostream>     //библиотеки
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

int readingFile(string& text);
void filtrSymvols(string text, bool lat, bool kir, bool num, bool pun);
int Filters(string text);
