#include <DailyTask/daily_task_22.h>

void readInput(std::vector<Command>& commands)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_22_input.txt");
  std::string line;
  Command command;
  std::string cmd;

  while (std::getline(file, line))
  {
    std::stringstream ss(line);
    ss >> cmd;
    command.switch_on = cmd.compare("on") == 0;

    while (std::getline(ss, cmd, ','))
    {
      long limit_down = stol(cmd.substr(cmd.find("=") + 1, cmd.find("..")));
      long limit_up = stol(cmd.substr(cmd.find("..") + 2));

      if (cmd.find('x') < cmd.size())
      {
        command.x_range.first = limit_down;
        command.x_range.second = limit_up;
      }
      if (cmd.front() == 'y')
      {
        command.y_range.first = limit_down;
        command.y_range.second = limit_up;
      }
      if (cmd.front() == 'z')
      {
        command.z_range.first = limit_down;
        command.z_range.second = limit_up;
      }
    }

    commands.push_back(command);
  }

  file.close();
}

void checkForOverlap(std::vector<Command>& new_regions, const Command& old_region, const Command& new_region)
{
  if (old_region.XUp() < new_region.XLow() || old_region.YUp() < new_region.YLow() || old_region.ZUp() < new_region.ZLow())
  {
    new_regions.emplace_back(old_region);
  }
  else if (old_region.XLow() > new_region.XUp() || old_region.YLow() > new_region.YUp() || old_region.ZLow() > new_region.ZUp())
  {
    new_regions.emplace_back(old_region);
  }
  else
  {
    if (new_region.XLow() > old_region.XLow())
    {
      Command nr;
      nr.x_range = std::make_pair(old_region.XLow(), new_region.XLow() - 1);
      nr.y_range = std::make_pair(old_region.YLow(), old_region.YUp());
      nr.z_range = std::make_pair(old_region.ZLow(), old_region.ZUp());
      new_regions.push_back(nr);
    }
    if (new_region.XUp() < old_region.XUp())
    {
      Command nr;
      nr.x_range = std::make_pair(new_region.XUp() + 1, old_region.XUp());
      nr.y_range = std::make_pair(old_region.YLow(), old_region.YUp());
      nr.z_range = std::make_pair(old_region.ZLow(), old_region.ZUp());
      new_regions.push_back(nr);
    }

    long x_low = std::max(old_region.XLow(), new_region.XLow());
    long x_up = std::min(old_region.XUp(), new_region.XUp());
    if (new_region.YLow() > old_region.YLow())
    {
      Command nr;
      nr.x_range = std::make_pair(x_low, x_up);
      nr.y_range = std::make_pair(old_region.YLow(), new_region.YLow() - 1);
      nr.z_range = std::make_pair(old_region.ZLow(), old_region.ZUp());
      new_regions.push_back(nr);
    }
    if (new_region.YUp() < old_region.YUp())
    {
      Command nr;
      nr.x_range = std::make_pair(x_low, x_up);
      nr.y_range = std::make_pair(new_region.YUp() + 1, old_region.YUp());
      nr.z_range = std::make_pair(old_region.ZLow(), old_region.ZUp());
      new_regions.push_back(nr);
    }

    long y_low = std::max(old_region.YLow(), new_region.YLow());
    long y_up = std::min(old_region.YUp(), new_region.YUp());
    if (new_region.ZLow() > old_region.ZLow())
    {
      Command nr;
      nr.x_range = std::make_pair(x_low, x_up);
      nr.y_range = std::make_pair(y_low, y_up);
      nr.z_range = std::make_pair(old_region.ZLow(), new_region.ZLow() - 1);
      new_regions.push_back(nr);
    }
    if (new_region.ZUp() < old_region.ZUp())
    {
      Command nr;
      nr.x_range = std::make_pair(x_low, x_up);
      nr.y_range = std::make_pair(y_low, y_up);
      nr.z_range = std::make_pair(new_region.ZUp() + 1, old_region.ZUp());
      new_regions.push_back(nr);
    }
  }

}

void DailyTask22::part1()
{
  const long SIZE = 50;
  std::vector<Command> commands;
  readInput(commands);

  std::array<std::array<std::array<bool, 2*(SIZE)+1>, 2*(SIZE)+1>, 2*(SIZE)+1> cube_space = {};

  for (size_t i = 0; i < cube_space.size(); i++)
    for (size_t j = 0; j < cube_space[i].size(); j++)
      for (size_t k = 0; k < cube_space[i][j].size(); k++)
        cube_space[i][j][k] = false;

  for (const Command& cmd : commands)
  {
    int x_low = std::max(-SIZE, cmd.x_range.first);
    int x_up = std::min(SIZE, cmd.x_range.second);
    int y_low = std::max(-SIZE, cmd.y_range.first);
    int y_up = std::min(SIZE, cmd.y_range.second);
    int z_low = std::max(-SIZE, cmd.z_range.first);
    int z_up = std::min(SIZE, cmd.z_range.second);

    if (x_up < -SIZE || y_up < -SIZE || z_up < -SIZE || x_low > SIZE || y_low > SIZE || z_low > SIZE)
    {
      continue;
    }

    for (long i = x_low; i <= x_up; i++)
      for (long j = y_low; j <= y_up; j++)
        for (long k = z_low; k <= z_up; k++)
          cube_space[i+SIZE][j+SIZE][k+SIZE] = cmd.switch_on;
  }

  long long count = 0;

  for (size_t i = 0; i < cube_space.size(); i++)
    for (size_t j = 0; j < cube_space[i].size(); j++)
      for (size_t k = 0; k < cube_space[i][j].size(); k++)
        if (cube_space[i][j][k]) count++;

  std::cout<<"Part1: switched on: "<<count<<std::endl;
}

void DailyTask22::part2()
{
  std::vector<Command> commands;
  readInput(commands);

  std::vector<Command> all_regions;

  for (const Command& cmd : commands)
  {
    std::vector<Command> new_regions;

    for (const Command& region : all_regions)
    {
      checkForOverlap(new_regions, region, cmd);
    }
    if (cmd.switch_on)
      new_regions.push_back(cmd);

    all_regions = new_regions;
  }

  long long count = 0;

  for (const Command& region : all_regions)
  {
      count += (region.x_range.second - region.x_range.first + 1)
        * (region.y_range.second - region.y_range.first + 1)
        * (region.z_range.second - region.z_range.first + 1);
  }

  std::cout<<"Part2: switched on: "<<count<<std::endl;

}

int main() {

  DailyTask22 dt22("Day 22: Reactor Reboot");
  dt22.part1();
  dt22.part2();

  return 0;
}