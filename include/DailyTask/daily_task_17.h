#ifndef AOC2021_DAILY_TASK_17_H
#define AOC2021_DAILY_TASK_17_H

#include <DailyTask/DailyTask.h>

struct ProbePoint
{
  int x;
  int y;
};

struct TargetArea
{
  int x1;
  int x2;
  int y1;
  int y2;

  bool isInTargetArea(ProbePoint point) const
  {
    return point.x >= x1 && point.x <= x2 && point.y <= y1 && point.y >= y2;
  }
};

class DailyTask17 : DailyTask {
public:
  DailyTask17(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // AOC2021_DAILY_TASK_17_H
