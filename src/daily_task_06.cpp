#include <DailyTask/daily_task_06.h>

void readInput(std::unordered_map<int, long>& fish_school, long& total_fish)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_06_input.txt");
  std::string line;
  std::getline(file, line);
  std::stringstream ss(line);
  std::string fish_num;
  total_fish = 0;
  while (std::getline(ss, fish_num, ','))
  {
    fish_school[stoi(fish_num)]++;
    total_fish++;
  }

  file.close();
}

void calculate(int days)
{
  std::unordered_map<int, long> fish_school;
  long fish_count;
  readInput(fish_school, fish_count);
  while (days > 0)
  {
    std::unordered_map<int, long> fish_updated;

    for (int i = 7; i >= 0; i--)
    {
      fish_updated[i] = fish_school[i+1];
    }
    fish_updated[6] += fish_school[0];
    fish_count += fish_school[0];
    fish_updated[8] = fish_school[0];

    fish_school = fish_updated;

    days--;
  }

  std::cout<<"total fish: "<<fish_count<<std::endl;
}

void DailyTask06::part1()
{
  calculate(80);
}

void DailyTask06::part2()
{
  calculate(256);
}

int main() {

  DailyTask06 dt06("Day 06: Lanternfish");
  dt06.part1();
  dt06.part2();

  return 0;
}