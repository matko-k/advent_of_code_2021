#include <DailyTask/daily_task_05.h>

void readInput(std::vector<Vent>& vents, long& max_y, bool use_diag)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_05_input.txt");
  std::string line;
  max_y = 0;

  while (std::getline(file, line))
  {
    std::stringstream ss(line);
    std::string point1_data, point2_data;

    point1_data = line.substr(0, line.find(" -> "));
    point2_data = line.substr(line.find(" -> ") + 4, line.size());

    Point point1(std::stoi(point1_data.substr(0, point1_data.find(','))), std::stoi(point1_data.substr(point1_data.find(',') + 1, point1_data.size())));
    Point point2(std::stoi(point2_data.substr(0, point2_data.find(','))), std::stoi(point2_data.substr(point2_data.find(',') + 1, point2_data.size())));

    if (point1.y > max_y) max_y = point1.y;
    if (point2.y > max_y) max_y = point2.y;

    Vent vent(point1, point2, use_diag);
    vents.push_back(vent);
  }
  file.close();
}

void DailyTask05::part1()
{
  std::vector<Vent> vents;
  long max_y = 0;
  readInput(vents, max_y, false);

  std::map<long, int> vents_map;

  for (const Vent& vent : vents)
  {
    for (const Point& p : vent.vent_line)
    {
      vents_map[p.x * max_y + p.y]++;
    }
  }

  std::map<long, int>::iterator it;
  int count = 0;

  for (it = vents_map.begin(); it != vents_map.end(); it++)
  {
    if (it->second >= 2) count++;
  }

  std::cout<<"PART1: count: "<<count<<std::endl;

}

void DailyTask05::part2()
{
  std::vector<Vent> vents;
  long max_y = 0;
  readInput(vents, max_y, true);

  std::map<long, int> vents_map;

  for (const Vent& vent : vents)
  {
    for (const Point& p : vent.vent_line)
    {
      vents_map[p.x * max_y + p.y]++;
    }
  }

  std::map<long, int>::iterator it;
  int count = 0;

  for (it = vents_map.begin(); it != vents_map.end(); it++)
  {
    if (it->second >= 2) count++;
  }

  std::cout<<"PART2: count: "<<count<<std::endl;
}

int main() {

  DailyTask05 dt05("Day 05: Hydrothermal Venture");
  dt05.part1();
  dt05.part2();

  return 0;
}