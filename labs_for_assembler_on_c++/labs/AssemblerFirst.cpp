#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::string;

void main()
{
  setlocale(LC_ALL, "rus");
  string sFileName;
  BITMAPFILEHEADER bmpFileHeader;
  BITMAPINFOHEADER bmpInfoHeader;
  int Width, Height;
  RGBQUAD Palette[256];
  RGBTRIPLE* inBuf;
  SHORT* outBuf;
  HANDLE hInputFile, hOutFile;
  DWORD RW;

  hInputFile = CreateFile(L"HELLO.bmp", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
  if (hInputFile == INVALID_HANDLE_VALUE) return;
  hOutFile = CreateFile(L"output.bmp", GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL);

  // ��������� ����
  ReadFile(hInputFile, &bmpFileHeader, sizeof(bmpFileHeader), &RW, NULL);
  ReadFile(hInputFile, &bmpInfoHeader, sizeof(bmpInfoHeader), &RW, NULL);

  // ��������� ��������� �� ������ ������
  SetFilePointer(hInputFile, bmpFileHeader.bfOffBits, NULL, FILE_BEGIN);
  Width = bmpInfoHeader.biWidth;
  Height = bmpInfoHeader.biHeight;

  // ������� ������
  inBuf = new RGBTRIPLE[Width];
  outBuf = new SHORT[Width];

  cout << "���������� �����������: ";
  cout << Width << "x" << Height << endl;
  cout << "���������� ��� �� �������: " << bmpInfoHeader.biBitCount << endl;
  cout << "������ �����������: " << bmpFileHeader.bfSize << " ����" << endl;

  // �������� ���������
  bmpFileHeader.bfOffBits = sizeof(bmpFileHeader) + sizeof(bmpInfoHeader) + 1024;//���������� �� ��������
  bmpInfoHeader.biBitCount = 16;
  bmpFileHeader.bfSize = bmpFileHeader.bfOffBits + Width * Height * 2 + Height * 2 * Width % 4;//������

  // ������� ���������
  WriteFile(hOutFile, &bmpFileHeader, sizeof(bmpFileHeader), &RW, NULL);
  WriteFile(hOutFile, &bmpInfoHeader, sizeof(bmpInfoHeader), &RW, NULL);
  WriteFile(hOutFile, Palette, 256 * sizeof(RGBQUAD), &RW, NULL);

  //RRRRRRRRGGGGGGGGBBBBBBBB ��������� � 24 ���
  // 0RRRRRGGGGGBBBBB ��������� � 16 ���
  // F1 = 11111000
  // ������ ���������������
  for (int i = 0; i < Height; i++)
  {
    ReadFile(hInputFile, inBuf, sizeof(RGBTRIPLE) * Width, &RW, NULL);
    for (int j = 0; j < Width; j++)
    {
      outBuf[j] = (inBuf[j].rgbtBlue & 0xF1) / 8 + ((inBuf[j].rgbtGreen & 0xF1) / 8) * 32 + ((inBuf[j].rgbtRed & 0xF1) / 8) * 1024;
    }
    WriteFile(hOutFile, outBuf, sizeof(SHORT) * (Width), &RW, NULL);
  }

  // ����� ����� ��� ������������
  WriteFile(hOutFile, Palette, (2 * Width) % 4, &RW, NULL);
  SetFilePointer(hInputFile, Width % 4, NULL, FILE_CURRENT);

  delete[] inBuf;
  delete[] outBuf;
  CloseHandle(hInputFile);
  CloseHandle(hOutFile);
  system("pause");
}
