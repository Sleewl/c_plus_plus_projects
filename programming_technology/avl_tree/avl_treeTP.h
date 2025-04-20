#ifndef AVL_TREETP_H
#define AVL_TREETP_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <algorithm>
#include <iterator>

// Функции для работы с текстом и частотой слов
int Count_Words(const std::string& text);
void Print_Text(const std::string& text);
std::vector<std::string> Split_Text(const std::string& text);

// Функции для работы с деревом слов
std::map<std::string, int> Make_Vocabulary(const std::string& text);
void Print_Vocabulary(const std::map<std::string, int>& vocabulary);
bool Find_Word(const std::map<std::string, int>& vocabulary, const std::string& word);
void Find_Top3_Words(const std::map<std::string, int>& vocabulary);

#endif // AVL_TREETP_H