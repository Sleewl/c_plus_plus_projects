#include <iostream>
#include <windows.h>
#include "fmod.hpp"
#include "fmod_errors.h"

#pragma comment(lib, "fmod_vc.lib") // ��� fmodL_vc.lib / fmodstudio_vc.lib � � ����������� �� ������

void ERRCHECK(FMOD_RESULT result)
{
  if (result != FMOD_OK)
  {
    std::cerr << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
    exit(-1);
  }
}

int main()
{
  FMOD::System* system = nullptr;
  FMOD_RESULT result;

  // ������ �������
  result = FMOD::System_Create(&system);
  ERRCHECK(result);

  // �������������� �������
  result = system->init(32, FMOD_INIT_NORMAL, 0);
  ERRCHECK(result);

  // ��������� ����
  FMOD::Sound* sound = nullptr;
  result = system->createSound("iphone-11-pro.mp3", FMOD_DEFAULT, 0, &sound);
  ERRCHECK(result);

  // �����������
  FMOD::Channel* channel = nullptr;
  // ������ FMOD_CHANNEL_FREE � ������� nullptr � �������� ChannelGroup
  result = system->playSound(sound, nullptr, false, &channel);
  ERRCHECK(result);

  // ���, ���� ������������ �� ����� Enter
  std::cout << "Playing sound. Press Enter to quit.\n";
  std::cin.get();

  // ����������� �������
  result = sound->release();
  ERRCHECK(result);
  result = system->close();
  ERRCHECK(result);
  result = system->release();
  ERRCHECK(result);

  return 0;
}
