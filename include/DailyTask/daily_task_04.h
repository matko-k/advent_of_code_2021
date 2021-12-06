#ifndef AOC2021_DAILY_TASK_04_H
#define AOC2021_DAILY_TASK_04_H

#include <DailyTask/DailyTask.h>

typedef std::pair<int, bool> BingoNum;

struct BingoRow
{
  std::vector<BingoNum> bingo_row;

  BingoRow(const std::vector<int> numbers)
  {
    bingo_row.reserve(numbers.size());
    for (int num : numbers)
    {
      bingo_row.push_back(std::make_pair(num, false));
    }
  }

  bool markNumber(int num)
  {
    for (BingoNum& bn : bingo_row)
    {
      if (bn.first == num && !bn.second)
      {
        bn.second = true;
        return true;
      }
    }
    return false;
  }

  bool isFullyMarked() const
  {
    for (const BingoNum& bn : bingo_row)
    {
      if (!bn.second) return false;
    }
    return true;
  }
};

struct BingoBoard
{
  std::vector<BingoRow> bingo_rows;
  bool hasWon = false;

  bool isWinning()
  {
    for (const BingoRow& br : bingo_rows)
    {
      if (br.isFullyMarked())
      {
        return true;
      }
    }
    return false;
  }
};

class DailyTask04 : DailyTask {
public:
  DailyTask04(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // AOC2021_DAILY_TASK_04_H
