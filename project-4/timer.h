#pragma once

#include <windows.h>

class Timer
{
private:
  LARGE_INTEGER frequency;
  LARGE_INTEGER begin;
  LARGE_INTEGER end;

public:
  Timer();
  void start();
  void stop();
  void show();
};
