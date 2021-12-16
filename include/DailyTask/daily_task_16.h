#ifndef AOC2021_DAILY_TASK_16_H
#define AOC2021_DAILY_TASK_16_H

#include <DailyTask/DailyTask.h>

struct Packet
{
  int version;
  int type_id;

  long value;
  int operator_id;
  int length;
  std::vector<Packet> subpackets;
};


std::string getBinFromHex(char c)
{
  switch (c)
  {
    case '0':
      return "0000";

    case '1':
      return "0001";

    case '2':
      return "0010";

    case '3':
      return "0011";

    case '4':
      return "0100";

    case '5':
      return "0101";

    case '6':
      return "0110";

    case '7':
      return "0111";

    case '8':
      return "1000";

    case '9':
      return "1001";

    case 'A':
    case 'a':
      return "1010";

    case 'B':
    case 'b':
      return "1011";

    case 'C':
    case 'c':
      return "1100";

    case 'D':
    case 'd':
      return "1101";

    case 'E':
    case 'e':
      return "1110";

    case 'F':
    case 'f':
      return "1111";

  }
}

class DailyTask16 : DailyTask {
public:
  DailyTask16(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // AOC2021_DAILY_TASK_16_H
