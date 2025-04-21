#include <iostream>
using namespace std;
// FPU - �������������� �����������, ������� �������� ��������� �����
//� ������� � �����
int main()
{
  float a = 1;
  float b = 3;
  float c = 5;
  float sum = 0;
  //1 - ����� ����� ������������ �����
  __asm
  {// stack: c b a => 8 a => 9
	finit // ������������� FPU ������� , ��� �������� � FPU (������� ����, ��������)
	fld a // �������� fld ���������� ��� �����
	fld b
	fld c
	fadd // ���������� ��� ����� �� ����� ����� � ������ ��������� � ����� ����
	fadd
	fstp sum // ���������� �������� �� ����� ����� � ������ � sum 
	//sum = (b + c) + a
  }
  cout << "1. sum = " << sum << endl;
  // 2 - ����� �������� �� �����
  //stack ������ => ���������� �� �����
  __asm
  {
	finit
	fstp sum
  }
  cout << "2. sum = " << sum << endl;
  //3 - �������� ����������
  int ctrl = 0x027B; // � ���� ����� ������� ���� ���������� , � ������ ������� �� ����
  // control - �������, � ������� 16 ��� - 0/1 
  // 0000 0001 0111 0100
  a = 5;
  b = 0;
  __asm
  {
	finit
	fldcw ctrl // ������� ctrl, ��� �� ��� ����������
	fld a
	fld b
	fdiv
	fstp sum
  }
  //cout << ctrl;
  cout << "3. sum = " << sum << endl;

  return 0;
}