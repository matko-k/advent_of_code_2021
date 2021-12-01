#ifndef AOC2021_DAILY_TASK_01_H
#define AOC2021_DAILY_TASK_01_H

#include <DailyTask/DailyTask.h>

class DailyTask01 : DailyTask {
public:
  DailyTask01(std::string task_name) : DailyTask(task_name){};

  virtual void calculate();
};

#endif // AOC2021_DAILY_TASK_01_H
