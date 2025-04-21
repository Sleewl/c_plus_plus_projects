#include <iostream>
using namespace std;
// ������� ��� ������� ����� ����� ����, ����� ���������� ����������, ����� ��������

void shift_stack(long long int a, long long int b, long long int& sum)
{
  //����
  //...
  //bp = sp ������ 8 ���� bp ��������� �� ������ �����
  //a 8����
  //b 8����
  //sum 8����
  __asm
  {
	mov eax, [ebp + 8] //� eax (������ 4 ����� �)  eax - 32 ����
	mov ebx, [ebp + 16] // � eax (������ 4 ����� b) 
	add eax, ebx
	mov esi, [ebp + 24] // � esi ������ ����� �� �������� ��������� ����� (������ 4 �����)
	mov[esi], eax // �� ������ esi ������ ���� �����, �.� �+�
	mov eax, [ebp + 12]
	mov ebx, [ebp + 20]
	adc eax, ebx // adc ��������� ����������, �������� ��������
	mov[esi + 4], eax // � ����� ��������� + 4 �.� 4 ����� �� ��� ��������
  }
}

void shift_reg()
{
  __asm
  {
	mov eax, [ebx]
	mov ecx, [edx]
	add eax, ecx
	mov[esi], eax // � ����� ������ 
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
	lea ebx, globA // ������ ������
	lea edx, globB
	mov esi, globSum // � esi �������� globSum
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

  //�������� ����� ����
  shift_stack(a, b, sum);
  cout << "����� ����� ����: " << sum << endl;
  sum = 0;

  //�������� ����� ��������
  __asm
  {
	// ������ ������
	lea ebx, a
	lea edx, b
	lea esi, sum
  }
  shift_reg();
  cout << "����� ����� ��������: " << sum << endl;
  sum = 0;

  //�������� ����� ���������� ����������
  globA = a;
  globB = b;
  globSum = &sum;
  shift_global();
  cout << "����� ����� ���������� ����������: " << sum << endl;
  return 0;
}