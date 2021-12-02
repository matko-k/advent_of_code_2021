#include <DailyTask/daily_task_01.h>

void DailyTask01::part1()
{
    std::ifstream file;
    file.open("../daily_inputs/daily_task_01_input.txt");

    std::vector<int> depths;
    int depth;

    while (file >> depth)
    {
        depths.push_back(depth);
    }
    file.close();

    int increases_count = 0;

    int last_depth = depths.front();

    for (size_t i = 1; i < depths.size(); i++) //skip first
    {
        if (depths[i] > last_depth)
        {
            increases_count++;
        }
        last_depth = depths[i];
    }

    std::cout<<"PART1: Depth increases count: "<< increases_count<<std::endl;
}

void DailyTask01::part2()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_01_input.txt");

  std::vector<int> depths;
  int depth;

  while (file >> depth)
  {
    depths.push_back(depth);
  }
  file.close();

  int increases_count = 0;
  int last_sum = depths[0] + depths[1] + depths[2];

  for (size_t i = 1; i < depths.size()-2; i++)
  {
    int current_sum = depths[i] + depths[i+1] + depths[i+2];
    if (current_sum > last_sum)
    {
      increases_count++;
    }
    last_sum = current_sum;
  }

  std::cout<<"PART2: Depth increases count: "<< increases_count<<std::endl;
}

int main() {

  DailyTask01 dt1("Day 1: Sonar Sweep");
  dt1.part1();
  dt1.part2();

  return 0;
}