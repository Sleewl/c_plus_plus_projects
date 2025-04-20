#include "avl_treeTP.h"

#define TEXT "1 1 1 2 2 3 3 3 4 5 6 7 9 9 9 9"

int Count_Words(const std::string& text) {
  std::istringstream iss(text);
  return std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>());
}

void Print_Text(const std::string& text) {
  std::cout << "�����:\n" << text << "\n";
  std::cout << "--------------------------------------\n���������� ����: " << Count_Words(text) << "\n--------------------------------------\n";
}

std::vector<std::string> Split_Text(const std::string& text) {
  std::vector<std::string> words;
  std::istringstream iss(text);
  std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(words));
  return words;
}

std::map<std::string, int> Make_Vocabulary(const std::string& text) {
  std::vector<std::string> words = Split_Text(text);
  std::map<std::string, int> vocabulary;
  for (const auto& word : words) {
    ++vocabulary[word];
  }
  return vocabulary;
}

void Print_Vocabulary(const std::map<std::string, int>& vocabulary) {
  for (const auto& pair : vocabulary) {
    std::cout << "���������� ���������� ����� \"" << pair.first << "\": " << pair.second << "\n";
  }
  std::cout << "--------------------------------------\n";
}

bool Find_Word(const std::map<std::string, int>& vocabulary, const std::string& word) {
  auto it = vocabulary.find(word);
  if (it != vocabulary.end()) {
    std::cout << "���������� ���������� ����� \"" << it->first << "\": " << it->second << "\n";
    return true;
  }
  else {
    std::cout << "����� \"" << word << "\" �� ������� � ������.\n";
    return false;
  }
}

void Find_Top3_Words(const std::map<std::string, int>& vocabulary) {
  std::vector<std::pair<std::string, int>> freq_words(vocabulary.begin(), vocabulary.end());
  std::partial_sort(freq_words.begin(), freq_words.begin() + 3, freq_words.end(), [](const auto& a, const auto& b) {
    return b.second < a.second;
    });
  std::cout << "��� ����� ������ �����:\n";
  for (int i = 0; i < 3 && i < freq_words.size(); ++i) {
    std::cout << freq_words[i].first << " (" << freq_words[i].second << ")\n";
  }
}

int main() {
  setlocale(LC_ALL, "");

  std::string text(TEXT);
  Print_Text(text);
  std::map<std::string, int> vocabulary = Make_Vocabulary(text);

  int choice;
  std::string word;

  do {
    std::cout << "\n�������� ��������:\n";
    std::cout << "1 - ���������� � ������� ������������� ����\n";
    std::cout << "2 - ���������� �������\n";
    std::cout << "3 - ����� ��������� ����� � �����\n";
    std::cout << "4 - ����� ��� ����� ������ �����\n";
    std::cout << "5 - �����\n";
    std::cout << "��� �����: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
      Print_Vocabulary(vocabulary);
      break;
    case 2:
      std::cout << "�������:\n";
      Print_Vocabulary(vocabulary);
      break;
    case 3:
      std::cout << "������� ����� ��� ������: ";
      std::cin >> word;
      Find_Word(vocabulary, word);
      break;
    case 4:
      Find_Top3_Words(vocabulary);
      break;
    case 5:
      std::cout << "����� �� ���������...\n";
      break;
    default:
      std::cout << "�������� �����, ���������� �����.\n";
      break;
    }
  } while (choice != 5);

  return 0;
}