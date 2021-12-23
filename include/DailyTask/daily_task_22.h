#ifndef AOC2021_DAILY_TASK_22_H
#define AOC2021_DAILY_TASK_22_H

#include <DailyTask/DailyTask.h>

struct Command
{
  bool switch_on;

  std::pair<long, long> x_range;
  std::pair<long, long> y_range;
  std::pair<long, long> z_range;

  long XLow() const {return x_range.first;}
  long XUp() const {return x_range.second;}
  long YLow() const {return y_range.first;}
  long YUp() const {return y_range.second;}
  long ZLow() const {return z_range.first;}
  long ZUp() const {return z_range.second;}
};

class DailyTask22 : DailyTask {
public:
  DailyTask22(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // AOC2021_DAILY_TASK_22_H
