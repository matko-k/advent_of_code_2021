#ifndef AOC2021_DAILY_TASK_13_H
#define AOC2021_DAILY_TASK_13_H

#include <DailyTask/DailyTask.h>

struct Point
{
  int x;
  int y;
};

struct FoldingInstruction
{
  bool is_x;
  int line_num;
};

class DailyTask13 : DailyTask {
public:
  DailyTask13(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // AOC2021_DAILY_TASK_13_H
