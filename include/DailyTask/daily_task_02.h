#ifndef AOC2021_DAILY_TASK_02_H
#define AOC2021_DAILY_TASK_02_H

#include <DailyTask/DailyTask.h>

typedef std::pair<char, int> command;

class DailyTask02 : DailyTask {
public:
  DailyTask02(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // AOC2021_DAILY_TASK_02_H
