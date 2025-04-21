#include <iostream>
#include <chrono>

using namespace std::chrono;
using std::chrono::milliseconds;

int main()
{
  //первый пункт
  int a = 1;
  int* pA = &a;
  int nums[] = { 1, 2, 3, 4, 5, 6 };
  __asm
  {
    mov eax, 5
    mov ebx, 3
    add eax, ebx // регистровая

    mov ebx, pA
    add eax, [ebx] // косвенно-регистровая

    lea esi, [nums + 4]
    add eax, [esi] // индексная

    lea ebx, [nums]
    mov esi, 8
    add eax, [ebx + esi] // базово-индексная

    add eax, [ebx + esi + 4] // базово-индексная со смещением
  }

  // второй пункт
  const long int iter = 10e+10;
  steady_clock timer1; // замеры для пустого цикла
  auto start1 = timer1.now();
  for (int i = 0; i < iter; i++);
  auto end1 = timer1.now();
  std::cout << "Empty cycle: " << duration_cast<milliseconds>(end1 - start1).count() << " ms" << std::endl;

  steady_clock timer2; // замеры для регистровой адресации
  auto start2 = timer2.now();
  for (int i = 0; i < iter; i++)
  {
    _asm
    {
      add eax, ebx
      add eax, ebx
      add eax, ebx
      add eax, ebx
      add eax, ebx
      add eax, ebx
      add eax, ebx
      add eax, ebx
      add eax, ebx
      add eax, ebx
    }
  }
  auto end2 = timer2.now();
  std::cout << "Reg addressing cycle: " << duration_cast<milliseconds>(end2 - start2).count() << " ms" << std::endl;

  steady_clock timer3; // замеры для косвенно-регистровой адресации
  auto start3 = timer3.now();
  for (int i = 0; i < iter; i++)
  {
    _asm
    {
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
  auto end3 = timer3.now();
  std::cout << "Indirect-Reg addressing cycle: " << duration_cast<milliseconds>(end3 - start3).count() << " ms" << std::endl;

  steady_clock timer4; // замеры для непосредственной адресации
  auto start4 = timer4.now();
  for (int i = 0; i < iter; i++)
  {
    _asm
    {
      add eax, 10
      add eax, 10
      add eax, 10
      add eax, 10
      add eax, 10
      add eax, 10
      add eax, 10
      add eax, 10
      add eax, 10
      add eax, 10
    }
  }
  auto end4 = timer4.now();
  std::cout << "Forward addressing cycle: " << duration_cast<milliseconds>(end4 - start4).count() << " ms" << std::endl;

  //третий пункт
  int arr[4][4] = { 1, 2, 3, 4,
                    5, 6, 7, 8,
                   9, 10, 11, 12,
                  13, 14, 15, 16 };
  int num = 0;
  __asm
  {
    cld
    mov ebx, 2
    lea edi, [arr + 16]

    met:
    mov eax, num
      mov ecx, 4
      rep stosd
      add edi, 16
      dec ebx
      cmp ebx, 0
      jnz met
  }
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      std::cout << arr[i][j] << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}