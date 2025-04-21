#include <iostream>
#include <windows.h>
#include "fmod.hpp"
#include "fmod_errors.h"

#pragma comment(lib, "fmod_vc.lib") // Или fmodL_vc.lib / fmodstudio_vc.lib — в зависимости от версии

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

  // Создаём систему
  result = FMOD::System_Create(&system);
  ERRCHECK(result);

  // Инициализируем систему
  result = system->init(32, FMOD_INIT_NORMAL, 0);
  ERRCHECK(result);

  // Загружаем звук
  FMOD::Sound* sound = nullptr;
  result = system->createSound("iphone-11-pro.mp3", FMOD_DEFAULT, 0, &sound);
  ERRCHECK(result);

  // Проигрываем
  FMOD::Channel* channel = nullptr;
  // Вместо FMOD_CHANNEL_FREE — передаём nullptr в параметр ChannelGroup
  result = system->playSound(sound, nullptr, false, &channel);
  ERRCHECK(result);

  // Ждём, пока пользователь не нажмёт Enter
  std::cout << "Playing sound. Press Enter to quit.\n";
  std::cin.get();

  // Освобождаем ресурсы
  result = sound->release();
  ERRCHECK(result);
  result = system->close();
  ERRCHECK(result);
  result = system->release();
  ERRCHECK(result);

  return 0;
}
