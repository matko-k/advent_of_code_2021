#ifndef AOC2021_DAILY_TASK_08_H
#define AOC2021_DAILY_TASK_08_H

#include <DailyTask/DailyTask.h>

struct Display
{
  std::map<std::string, int> display_digits;
  std::map<int, std::string> display_codes;
  std::vector<std::string> length_5_digits;
  std::vector<std::string> length_6_digits;
};

class DailyTask08 : DailyTask {
public:
  DailyTask08(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // AOC2021_DAILY_TASK_08_H
