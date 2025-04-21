#include <iostream>
using namespace std;
// сложить два двойных слова через стек, через глобальные переменные, через регистры

void shift_stack(long long int a, long long int b, long long int& sum)
{
  //стек
  //...
  //bp = sp первые 8 байт bp указанные на начало стека
  //a 8байт
  //b 8байт
  //sum 8байт
  __asm
  {
	mov eax, [ebp + 8] //в eax (нижние 4 байта а)  eax - 32 бита
	mov ebx, [ebp + 16] // в eax (нижние 4 байта b) 
	add eax, ebx
	mov esi, [ebp + 24] // в esi кладем адрес по которому находится сумма (нижние 4 байта)
	mov[esi], eax // по адресу esi кладем нашу сумму, т.е а+б
	mov eax, [ebp + 12]
	mov ebx, [ebp + 20]
	adc eax, ebx // adc позволяет складывать, учитывая смещение
	mov[esi + 4], eax // к сумме добавляем + 4 т.к 4 байта мы уже записали
  }
}

void shift_reg()
{
  __asm
  {
	mov eax, [ebx]
	mov ecx, [edx]
	add eax, ecx
	mov[esi], eax // в сумму кладем 
	mov eax, [ebx + 4]
	mov ecx, [edx + 4]
	adc eax, ecx
	mov[esi + 4], eax
  }
}


long long int globA = 0;
long long int globB = 0;
long long int* globSum = 0;

void shift_global()
{
  __asm
  {
	lea ebx, globA // кладем адреса
	lea edx, globB
	mov esi, globSum // в esi значение globSum
	mov eax, [ebx]
	mov ecx, [edx]
	add eax, ecx
	mov[esi], eax // 
	mov eax, [ebx + 4]
	mov ecx, [edx + 4]
	adc eax, ecx
	mov[esi + 4], eax
  }
}


int main()
{
  setlocale(LC_ALL, "rus");
  long long int a = 0x0000000000000001;
  long long int b = 0x0000000000000002;
  long long int sum = 0;

  //передача через стек
  shift_stack(a, b, sum);
  cout << "Сумма через стек: " << sum << endl;
  sum = 0;

  //передача через регистры
  __asm
  {
	// кладем адреса
	lea ebx, a
	lea edx, b
	lea esi, sum
  }
  shift_reg();
  cout << "Сумма через регистры: " << sum << endl;
  sum = 0;

  //передача через глобальные переменные
  globA = a;
  globB = b;
  globSum = &sum;
  shift_global();
  cout << "Сумма через глобальные переменные: " << sum << endl;
  return 0;
}