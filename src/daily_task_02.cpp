#include <DailyTask/daily_task_02.h>

void DailyTask02::part1()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_02_input.txt");

  std::vector<command> commands;
  command cmd;
  std::string command_type;
  int command_value;

  while (file >> command_type >> command_value)
  {
    cmd = std::make_pair(command_type.front() ,command_value);
    commands.push_back(cmd);
  }
  file.close();

  int distance = 0;
  int depth = 0;

  for (const command& cmd : commands)
  {
    if (cmd.first == 'f')
    {
      distance += cmd.second;
    }
    else if (cmd.first == 'd')
    {
      depth += cmd.second;
    }
    else if (cmd.first == 'u')
    {
      depth -= cmd.second;
    }
    else
    {
      std::cout<<"WTF?!?\n";
    }
  }

  std::cout<<"PART1: final distance: "<<distance<<", final depth: "<<depth<<", solution: "<<distance*depth<<std::endl;
}

void DailyTask02::part2()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_02_input.txt");

  std::vector<command> commands;
  command cmd;
  std::string command_type;
  int command_value;

  while (file >> command_type >> command_value)
  {
    cmd = std::make_pair(command_type.front() ,command_value);
    commands.push_back(cmd);
  }
  file.close();

  int distance = 0;
  int depth = 0;
  int aim = 0;

  for (const command& cmd : commands)
  {
    if (cmd.first == 'f')
    {
      distance += cmd.second;
      depth += cmd.second * aim;
    }
    else if (cmd.first == 'd')
    {
      aim += cmd.second;
    }
    else if (cmd.first == 'u')
    {
      aim -= cmd.second;
    }
    else
    {
      std::cout<<"WTF?!?\n";
    }
  }

  std::cout<<"PART2: final distance: "<<distance<<", final depth: "<<depth<<", solution: "<<distance*depth<<std::endl;
}

int main() {

  DailyTask02 dt2("Day 2: Dive!");
  dt2.part1();
  dt2.part2();

  return 0;
}