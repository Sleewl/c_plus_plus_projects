#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

std::chrono::milliseconds;

void outArray(int* a, int nRow, int nColumn)
{
  for (int i = 0; i < nRow; ++i)
  {
	for (int j = 0; j < nColumn; ++j)
	{
	  cout << *(a + nColumn * i + j) << " ";
	}
	cout << endl;
  }
}

int main()
{
  setlocale(LC_ALL, "rus");

  const long int number = 10E+9;

  chrono::steady_clock timer1; // ������ ����
  auto start = timer1.now();
  for (int i = 0; i < number; ++i);
  auto end = timer1.now();

  cout << "����� ���������� ������� ����� � �� : " << duration_cast<milliseconds>(end - start).count() << endl;

  chrono::steady_clock timer2; // ���������������� ���������
  start = timer2.now();
  for (long long i = 0; i < number; ++i) {
	__asm {
	  add eax, 10;
	  add edx, 10;
	  add eax, 10;
	  add edx, 10;
	  add eax, 10;
	  add edx, 10;
	  add eax, 10;
	  add edx, 10;
	  add eax, 10;
	  add edx, 10;
	  add eax, 10;
	  add edx, 10;
	  add eax, 10;
	  add edx, 10;
	  add eax, 10;
	  add edx, 10;
	}
  }
  end = timer2.now();
  cout << "����� ���������� c �������������� ��������������� ��������� � �� : " << duration_cast<milliseconds>(end - start).count() << endl;


  chrono::steady_clock timer3; // ����������� ���������
  start = timer3.now();
  for (int i = 0; i < number; ++i) {
	__asm {
	  add eax, ebx;
	  add eax, ebx;
	  add eax, ebx;
	  add eax, ebx;
	  add eax, ebx;
	  add eax, ebx;
	  add eax, ebx;
	  add eax, ebx;
	  add eax, ebx;
	  add eax, ebx;
	  add eax, ebx;
	  add eax, ebx;
	  add eax, ebx;
	  add eax, ebx;
	  add eax, ebx;
	  add eax, ebx;
	}
  }
  end = timer3.now();

  cout << "����� ���������� c �������������� ����������� ��������� � �� : " << duration_cast<milliseconds>(end - start).count() << endl;

  chrono::steady_clock timer4; // ��������-����������� ���������
  start = timer4.now();
  for (int i = 0; i < number; ++i) {
	__asm {
	  add eax, [ebx]
	  add eax, [ebx]
	  add eax, [ebx]
	  add eax, [ebx]
	  add eax, [ebx]
	  add eax, [ebx]
	  add eax, [ebx]
	  add eax, [ebx]
	  add eax, [ebx]
	  add eax, [ebx]
	  add eax, [ebx]
	  add eax, [ebx]
	  add eax, [ebx]
	  add eax, [ebx]
	  add eax, [ebx]
	}
  }
  end = timer4.now();

  cout << "����� ���������� c �������������� ��������-����������� ��������� � �� : " << duration_cast<milliseconds>(end - start).count() << endl;

  int arr[4][5] = { 1, 1, 1, 1, 1,
					2, 2, 2, 2, 2,//
					3, 3, 3, 3, 3,
					4, 4, 4, 4, 4 };
  int k = 0;
  cout << "�������� ������: " << endl;
  outArray(arr[0], 4, 5);

  __asm {
	cld
	mov ebx, 2
	lea edi, [arr + 20]//�������� �������� �� ������ �������

	loop1:
	mov eax, k
	  mov ecx, 5 // �.� 5 ����� � �������
	  rep stosd // ������ �������� �� eax � edi
	  add edi, 20
	  dec ebx
	  cmp ebx, 0
	  jne loop1
  }
  cout << "������ ����� ��������� ������ ����� : " << endl;
  outArray(arr[0], 4, 5);
  return 0;
}