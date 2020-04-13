#include <windows.h>
#include <iomanip>
#include <iostream>
#include "timer.h"

Timer::Timer()
{
  QueryPerformanceFrequency(&frequency);
}

void Timer::start()
{
  QueryPerformanceCounter(&begin);
}

void Timer::stop()
{
  QueryPerformanceCounter(&end);
}

void Timer::show()
{
  const double frequencyMhz = frequency.QuadPart / 1024 / 1024;
  const double tick = end.QuadPart - begin.QuadPart;
  const double time = tick / double(this->frequency.QuadPart);
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(3);
  std::cout << "Clock Rate (MHz): " << frequencyMhz << std::endl;
  std::cout << std::setprecision(0);
  std::cout << "Clock Count (tick)：" << tick << std::endl;
  std::cout << std::setprecision(6);
  std::cout << "Time (second): " << time << std::endl;
  std::cout << std::endl;
}
