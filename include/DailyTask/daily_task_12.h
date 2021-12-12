#ifndef AOC2021_DAILY_TASK_12_H
#define AOC2021_DAILY_TASK_12_H

#include <DailyTask/DailyTask.h>

struct Cave
{
  std::string cave_id;
  int times_explored;
  std::vector<Cave*> connected_caves;

  Cave(std::string cave_id): cave_id(cave_id)
  {
    times_explored = 0;
  };

  Cave(): Cave("dummy")
  {};

  bool isStart()
  {
    return cave_id.compare("start") == 0;
  }

  bool isEnd()
  {
    return cave_id.compare("end") == 0;
  }

  bool isSmall()
  {
    return std::islower(cave_id.at(0));
  }

  bool isBig()
  {
    return std::isupper(cave_id.at(0));
  }

  bool canBeExplored()
  {
    return isEnd() || !isStart() && isBig() || !isStart() && isSmall() && times_explored == 0;
  }

};

class DailyTask12 : DailyTask {
public:
  DailyTask12(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // AOC2021_DAILY_TASK_12_H
