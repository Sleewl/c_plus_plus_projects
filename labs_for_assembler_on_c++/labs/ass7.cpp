#include <iostream>
using namespace std;
// FPU - математический сопроцессор, который помогает основному процу
//с числами с флоат
int main()
{
  float a = 1;
  float b = 3;
  float c = 5;
  float sum = 0;
  //1 - найти сумму вещественных чисел
  __asm
  {// stack: c b a => 8 a => 9
	finit // инициализация FPU говорим , что работаем с FPU (создает стек, регистры)
	fld a // командой fld закидываем три числа
	fld b
	fld c
	fadd // складывает два числа из верха стека и кладет результат в самый верх
	fadd
	fstp sum // извлечение значения из верха стека и кладет в sum 
	//sum = (b + c) + a
  }
  cout << "1. sum = " << sum << endl;
  // 2 - чтобы вывелось не число
  //stack пустой => достанется не число
  __asm
  {
	finit
	fstp sum
  }
  cout << "2. sum = " << sum << endl;
  //3 - получить исключение
  int ctrl = 0x027B; // в этом числе активен флаг прерывания , в случае деления на ноль
  // control - регистр, в котором 16 бит - 0/1 
  // 0000 0001 0111 0100
  a = 5;
  b = 0;
  __asm
  {
	finit
	fldcw ctrl // достаем ctrl, что мы его используем
	fld a
	fld b
	fdiv
	fstp sum
  }
  //cout << ctrl;
  cout << "3. sum = " << sum << endl;

  return 0;
}