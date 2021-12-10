#include <DailyTask/daily_task_09.h>

void readInput(std::vector<std::vector<int>>& floor_map)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_09_input.txt");
  floor_map.clear();
  std::string line;
  std::vector<int> floor_row;
  while (std::getline(file, line))
  {
    floor_row.clear();
    for (const char& height : line)
    {
      floor_row.push_back(int(height - '0'));
    }
    floor_map.push_back(floor_row);
  }

  file.close();
}

bool isLocalLowPoint(const std::vector<std::vector<int>>& floor_map, size_t x, size_t y)
{
  size_t width = floor_map[0].size();
  size_t height = floor_map.size();
  int local_point = floor_map[y][x];

  //check right
  if (x < width-1 && floor_map[y][x+1] <= local_point)
    return false;

  //check left
  if (x > 0 && floor_map[y][x-1] <= local_point)
    return false;

  //check up
  if (y > 0 && floor_map[y-1][x] <= local_point)
    return false;

  //check down
  if (y < height-1 && floor_map[y+1][x] <= local_point)
    return false;

  return true;
}

void expandLowPoint(const std::vector<std::vector<int>>& floor_map, std::map<int, bool>& floor_map_exploration, std::vector<int>& basin, size_t x, size_t y)
{
  int current_point = floor_map[y][x];
  if (current_point == 9)
    return;

  size_t width = floor_map[0].size();
  size_t height = floor_map.size();
  int next_x;
  int next_y;

  //add current point
  basin.push_back(current_point);
  floor_map_exploration[y*width + x] = true;

  //check right point
  next_x = x + 1;
  next_y = y;
  if (next_x < width && !floor_map_exploration[next_y*width + next_x])
  {
    expandLowPoint(floor_map, floor_map_exploration, basin, next_x, next_y);
  }

  //check left point
  next_x = x - 1;
  next_y = y;
  if (next_x >= 0 && !floor_map_exploration[next_y*width + next_x])
  {
    expandLowPoint(floor_map, floor_map_exploration, basin, next_x, next_y);
  }

  //check up point
  next_x = x;
  next_y = y - 1;
  if (next_y >= 0 && !floor_map_exploration[next_y*width + next_x])
  {
    expandLowPoint(floor_map, floor_map_exploration, basin, next_x, next_y);
  }

  //check down point
  next_x = x;
  next_y = y + 1;
  if (next_y < height && !floor_map_exploration[next_y*width + next_x])
  {
    expandLowPoint(floor_map, floor_map_exploration, basin, next_x, next_y);
  }

  return;
}

void DailyTask09::part1()
{
  std::vector<std::vector<int>> floor_map;
  readInput(floor_map);
  std::vector<int> low_points;

  for (size_t i = 0; i < floor_map.size(); i++)
  {
    for (size_t j = 0; j < floor_map[i].size(); j++)
    {
      if (isLocalLowPoint(floor_map, j, i))
      {
        low_points.push_back(floor_map[i][j]);
      }
    }
  }

  int risk_sum = 0;
  for(int i : low_points)
  {
    risk_sum += i + 1;
  }

  std::cout<<"PART 1: risk sum: "<<risk_sum<<std::endl;
}

void DailyTask09::part2()
{
  std::vector<std::vector<int>> floor_map;
  readInput(floor_map);
  std::vector<int> basin;
  std::vector<std::vector<int>> basins;

  std::map<int, bool> floor_map_exploration;
  for (size_t i = 0; i < floor_map.size(); i++)
  {
    for (size_t j = 0; j < floor_map[i].size(); j++)
    {
      floor_map_exploration[i*floor_map[i].size() + j] = false;
    }
  }

  for (size_t i = 0; i < floor_map.size(); i++)
  {
    for (size_t j = 0; j < floor_map[i].size(); j++)
    {
      if (isLocalLowPoint(floor_map, j, i))
      {
        if (!floor_map_exploration[j*floor_map[i].size() + i])
        {
          expandLowPoint(floor_map, floor_map_exploration, basin, j, i);
          basins.push_back(basin);
        }
      }
      basin.clear();
    }
  }

  std::vector<int> basins_sizes;
  for (const std::vector<int>& basin : basins)
  {
    basins_sizes.push_back(basin.size());
  }

  std::sort(basins_sizes.begin(), basins_sizes.end(), std::greater());

  long largest_basins_multiplied = basins_sizes[0]*basins_sizes[1]*basins_sizes[2];

  std::cout<<"PART2: "<<largest_basins_multiplied<<std::endl;

}

int main() {

  DailyTask09 dt09("Day 09: Smoke Basin");
  dt09.part1();
  dt09.part2();

  return 0;
}