#include <DailyTask/daily_task_15.h>

void readInput(std::vector<std::vector<int>>& chiton_map)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_15_input.txt");
  std::string line;
  std::vector<int> chiton_row;

  while (std::getline(file, line))
  {
    chiton_row.clear();
    for (char ch : line)
    {
      chiton_row.push_back(ch - '0');
    }
    chiton_map.push_back(chiton_row);
  }
  file.close();
}

int getHCost(const ChitonPoint& current, const ChitonPoint& goal)
{
  return goal.x - current.x + goal.y - current.y;
}

void AStar(std::vector<std::vector<ChitonPoint>>& chiton_map, std::vector<ChitonPoint>& shortest_path)
{
  const int row_size = chiton_map[0].size();
  const int column_size = chiton_map.size();

  std::vector<ChitonPoint*> open_set;

  ChitonPoint start = chiton_map[0][0];
  ChitonPoint goal = chiton_map[chiton_map.size()-1][row_size - 1];
  open_set.push_back(&start);

  std::map<int, int> g_score;
  std::map<int, int> f_score;

  std::map<ChitonPoint*, ChitonPoint*> came_from;
  for (int i = 0; i < chiton_map.size(); i++)
  {
    for (int j = 0; j < chiton_map.size(); j++)
    {
      g_score[i*row_size + j] = std::numeric_limits<int>::max();
      f_score[i*row_size + j] = std::numeric_limits<int>::max();
    }
  }
  g_score[start.y *row_size + start.x] = 0;
  f_score[start.y *row_size + start.x] = getHCost(start, goal);

  while (!open_set.empty())
  {
    auto next_it = open_set.begin();
    ChitonPoint* next_point = *next_it;

    for (auto it = open_set.begin(); it != open_set.end(); it++)
    {
      ChitonPoint* current = *it;
      if (f_score[current->y * row_size + current->x] < f_score[next_point->y * row_size + next_point->x])
      {
        next_point = current;
        next_it = it;
      }
    }

    if (next_point->x == goal.x && next_point->y == goal.y)
    {
      shortest_path.push_back(*next_point);
      while (true)
      {
        next_point = came_from[next_point];
        shortest_path.push_back(*next_point);
        if (next_point->x == start.x && next_point->y == start.y)
        {
          break;
        }
      }
      break;
    }

    open_set.erase(next_it);

    std::vector<ChitonPoint*> neighbours;

    if (next_point->x < row_size - 1) neighbours.push_back(&chiton_map[next_point->y][next_point->x + 1]);
    if (next_point->x > 0) neighbours.push_back(&chiton_map[next_point->y][next_point->x - 1]);
    if (next_point->y > 0) neighbours.push_back(&chiton_map[next_point->y - 1][next_point->x]);
    if (next_point->y < column_size - 1) neighbours.push_back(&chiton_map[next_point->y + 1][next_point->x]);

    for (ChitonPoint* neighbour : neighbours)
    {
      int new_score = g_score[next_point->y * row_size + next_point->x] + neighbour->risk_level;
      if (new_score < g_score[neighbour->y * row_size + neighbour->x])
      {
        came_from[neighbour] = next_point;
        g_score[neighbour->y * row_size + neighbour->x] = new_score;
        f_score[neighbour->y * row_size + neighbour->x] = new_score + getHCost(*neighbour, goal);
        if (std::find(open_set.begin(), open_set.end(), neighbour) == open_set.end())
        {
          open_set.push_back(neighbour);
        }
      }
    }
  }

}

void DailyTask15::part1()
{
  std::vector<std::vector<int>> chiton_input;
  readInput(chiton_input);

  std::vector<std::vector<ChitonPoint>> chiton_map;
  std::vector<ChitonPoint> chiton_row;
  for (int i = 0; i < chiton_input.size(); i++)
  {
    chiton_row.clear();
    for (int j = 0; j < chiton_input[i].size(); j++)
    {
      ChitonPoint cp(j, i, chiton_input[i][j]);
      chiton_row.push_back(cp);
    }
    chiton_map.push_back(chiton_row);
  }
  std::vector<ChitonPoint> shortest_path;

  AStar(chiton_map, shortest_path);

  int cost = 0;
  for (const ChitonPoint& cp : shortest_path)
  {
    cost += cp.risk_level;
  }
  cost -= chiton_map[0][0].risk_level;
  std::cout<<"PART1: path cost: "<<cost<<std::endl;
}

void DailyTask15::part2()
{
  std::vector<std::vector<int>> chiton_input;
  readInput(chiton_input);
  int row_size = chiton_input[0].size();
  int column_size = chiton_input.size();

  std::vector<std::vector<ChitonPoint>> chiton_map;
  std::vector<ChitonPoint> chiton_row;
  for (int i = 0; i < column_size*5; i++)
  {
    chiton_row.clear();
    for (int j = 0; j < row_size*5; j++)
    {
      int new_risk_level = (chiton_input[i%row_size][j%row_size] + i/row_size + j/row_size);
      new_risk_level = new_risk_level > 9 ? new_risk_level - 9 : new_risk_level;
      ChitonPoint cp(j, i, new_risk_level);
      chiton_row.push_back(cp);
    }
    chiton_map.push_back(chiton_row);
  }
  std::vector<ChitonPoint> shortest_path;

  AStar(chiton_map, shortest_path);

  int cost = 0;
  for (const ChitonPoint& cp : shortest_path)
  {
    cost += cp.risk_level;
  }
  cost -= chiton_map[0][0].risk_level;
  std::cout<<"PART2: path cost: "<<cost<<std::endl;
}

int main() {

  DailyTask15 dt15("Day 15: Chiton");
  dt15.part1();
  dt15.part2();

  return 0;
}