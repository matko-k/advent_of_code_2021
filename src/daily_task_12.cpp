#include <DailyTask/daily_task_12.h>

void readInput(std::unordered_map<std::string, Cave>& cave_map)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_12_input.txt");
  std::string line;

  while (std::getline(file, line))
  {
    std::string cave1 = line.substr(0, line.find('-'));
    std::string cave2 = line.substr(line.find('-') + 1, line.length());

    if (cave_map.find(cave1) == cave_map.end())
    {
      Cave new_cave(cave1);
      cave_map[cave1] = new_cave;
    }

    if (cave_map.find(cave2) == cave_map.end())
    {
      Cave new_cave(cave2);
      cave_map[cave2] = new_cave;
    }

    cave_map[cave1].connected_caves.push_back(&cave_map[cave2]);
    cave_map[cave2].connected_caves.push_back(&cave_map[cave1]);

  }

  file.close();
}

void explore_cave(std::unordered_map<std::string, Cave>& cave_map, Cave* current_cave, std::vector<std::vector<std::string>>& all_paths, std::vector<std::string>& current_path)
{
  current_cave->times_explored++;
  current_path.push_back(current_cave->cave_id);

  if (current_cave->isEnd())
  {
    all_paths.push_back(current_path);
    current_path.pop_back();
    return;
  }

  for (Cave* next_cave : current_cave->connected_caves)
  {
    if (next_cave->canBeExplored())
    {
      explore_cave(cave_map, next_cave, all_paths, current_path);
    }
  }
  current_path.pop_back();
  current_cave->times_explored = 0;
}

void explore_cave_advanced(std::unordered_map<std::string, Cave>& cave_map, Cave* current_cave, std::vector<std::vector<std::string>>& all_paths, std::vector<std::string>& current_path, bool& can_visit_explored_small_cave)
{
  current_cave->times_explored++;
  current_path.push_back(current_cave->cave_id);

  if (current_cave->isEnd())
  {
    all_paths.push_back(current_path);
    current_path.pop_back();
    return;
  }

  for (Cave* next_cave : current_cave->connected_caves)
  {
    bool advanced_condition = can_visit_explored_small_cave && next_cave->isSmall() && next_cave->times_explored == 1 && !next_cave->isStart() && !next_cave->isEnd();
    if (next_cave->canBeExplored() || advanced_condition)
    {
      if (advanced_condition)
      {
        can_visit_explored_small_cave = false;
      }
      explore_cave_advanced(cave_map, next_cave, all_paths, current_path, can_visit_explored_small_cave);
    }
  }
  if (current_cave->isSmall() && !current_cave->isStart() && current_cave->times_explored == 2)
  {
    can_visit_explored_small_cave = true;
    current_cave->times_explored = 1;
  }
  else
  {
    current_cave->times_explored = 0;
  }
  current_path.pop_back();
}

void DailyTask12::part1()
{
  std::unordered_map<std::string, Cave> cave_map;
  readInput(cave_map);
  std::vector<std::vector<std::string>> all_paths;
  std::vector<std::string> current_path;
  explore_cave(cave_map, &cave_map["start"], all_paths, current_path);

  std::cout<<"PART1: total paths: "<<all_paths.size()<<std::endl;
}

void DailyTask12::part2()
{
  std::unordered_map<std::string, Cave> cave_map;
  readInput(cave_map);
  std::vector<std::vector<std::string>> all_paths;
  std::vector<std::string> current_path;
  bool can_visit_small_cave_twice = true;
  explore_cave_advanced(cave_map, &cave_map["start"], all_paths, current_path, can_visit_small_cave_twice);

  std::cout<<"PART2: total paths: "<<all_paths.size()<<std::endl;
}

int main() {

  DailyTask12 dt12("Day 12: Passage Pathing");
  dt12.part1();
  dt12.part2();

  return 0;
}