#include <DailyTask/daily_task_07.h>

void readInput(std::vector<int>& crab_positions)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_07_input.txt");
  std::string line;
  std::getline(file, line);
  std::stringstream ss(line);
  std::string fish_num;
  while (std::getline(ss, fish_num, ','))
  {
    crab_positions.push_back(stoi(fish_num));
  }
  file.close();

}

void DailyTask07::part1()
{
  std::vector<int> crab_positions;
  readInput(crab_positions);
  int min_fuel = std::numeric_limits<int>::max();

  for (int crab_pos : crab_positions)
  {
    int current_fuel = 0;
    for (int crab_pos2 : crab_positions)
    {
      current_fuel += abs(crab_pos2 - crab_pos);
    }
    if (current_fuel < min_fuel) min_fuel = current_fuel;
  }

  std::cout<<"PART1: fuel cost: "<<min_fuel<<std::endl;
}

void DailyTask07::part2()
{
  std::vector<int> crab_positions;
  readInput(crab_positions);
  int min_fuel = std::numeric_limits<int>::max();
  int max_pos = 0;
  for (int crab_pos : crab_positions)
  {
    if (crab_pos > max_pos) max_pos = crab_pos;
  }

  for (int crab_pos = 0; crab_pos <= max_pos; crab_pos++)
  {
    int current_fuel = 0;
    for (int crab_pos2 : crab_positions)
    {
      int distance = abs(crab_pos2 - crab_pos);
      for (int i = 1; i <= distance; i++)
      {
        current_fuel += i;
      }
    }
    if (current_fuel < min_fuel) min_fuel = current_fuel;
  }

  std::cout<<"PART2: fuel cost: "<<min_fuel<<std::endl;
}

int main() {

  DailyTask07 dt07("Day 07: The Treachery of Whales");
  dt07.part1();
  dt07.part2();

  return 0;
}