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

  chrono::steady_clock timer1; // ïóñòîé öèêë
  auto start = timer1.now();
  for (int i = 0; i < number; ++i);
  auto end = timer1.now();

  cout << "Âðåìÿ âûïîëíåíèÿ ïóñòîãî öèêëà â ìñ : " << duration_cast<milliseconds>(end - start).count() << endl;

  chrono::steady_clock timer2; // íåïîñðåäñòâåííàÿ àäðåñàöèÿ
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
  cout << "Âðåìÿ âûïîëíåíèÿ c èñïîëüçîâàíèåì íåïîñðåñòâåííîé àäðåñàöèè â ìñ : " << duration_cast<milliseconds>(end - start).count() << endl;


  chrono::steady_clock timer3; // ðåãèñòðîâàÿ àäðåñàöèÿ
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

  cout << "Âðåìÿ âûïîëíåíèÿ c èñïîëüçîâàíèåì ðåãèñòðîâîé àäðåñàöèè â ìñ : " << duration_cast<milliseconds>(end - start).count() << endl;

  chrono::steady_clock timer4; // êîñâåííî-ðåãèñòðîâàÿ àäðåñàöèÿ
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

  cout << "Âðåìÿ âûïîëíåíèÿ c èñïîëüçîâàíèåì êîñâåííî-ðåãèñòðîâîé àäðåñàöèè â ìñ : " << duration_cast<milliseconds>(end - start).count() << endl;

  int arr[4][5] = { 1, 1, 1, 1, 1,
					2, 2, 2, 2, 2,//
					3, 3, 3, 3, 3,
					4, 4, 4, 4, 4 };
  int k = 0;
  cout << "Èñõîäíûé ìàññèâ: " << endl;
  outArray(arr[0], 4, 5);

  __asm {
	cld
	mov ebx, 2
	lea edi, [arr + 20]//çíà÷åíèå ýëåìåíòà íà ÷åòíîé ñòðî÷êå

	loop1:
	mov eax, k
	  mov ecx, 5 // ò.ê 5 ñòðîê â ìàññèâå
	  rep stosd // êëàäåò çíà÷åíèå èç eax â edi
	  add edi, 20
	  dec ebx
	  cmp ebx, 0
	  jne loop1
  }
  cout << "Ìàññèâ ïîñëå èçìåíåíèÿ ÷åòíûõ ñòðîê : " << endl;
  outArray(arr[0], 4, 5);
  return 0;
}
