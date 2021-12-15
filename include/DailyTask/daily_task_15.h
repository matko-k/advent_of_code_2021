#ifndef AOC2021_DAILY_TASK_15_H
#define AOC2021_DAILY_TASK_15_H

#include <DailyTask/DailyTask.h>

struct ChitonPoint
{
  int x;
  int y;
  int risk_level;

  ChitonPoint (int x, int y, int risk_level): x(x), y(y), risk_level(risk_level)
  {
  }
};

class DailyTask15 : DailyTask {
public:
  DailyTask15(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // AOC2021_DAILY_TASK_15_H
