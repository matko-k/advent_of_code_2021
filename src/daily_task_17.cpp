#include <DailyTask/daily_task_17.h>

void readInput(TargetArea& target_area)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_17_input.txt");
  std::string line;
  file >> line;
  file >> line;
  file >> line;
  unsigned posx = line.find("x=") + 2;
  target_area.x1 = stoi(line.substr(posx, line.find("x=") - posx));
  target_area.x2 = stoi(line.substr(line.find("..") + 2,  line.length()));

  file >> line;
  unsigned posy = line.find("y=") + 2;
  target_area.y2 = stoi(line.substr(posy, line.find("y=") - posy));
  target_area.y1 = stoi(line.substr(line.find("..") + 2,  line.length()));

  file.close();
}

bool shouldReturn(const TargetArea& target_area, const ProbePoint current_point, const ProbePoint& current_velocity)
{
  if (current_point.x > target_area.x2) return true;
  if (current_velocity.x == 0 && current_point.x < target_area.x1) return true;
  if (current_point.y < target_area.y2 && current_velocity.y <= 0) return true;
  return false;
}

void stepProbePoint(ProbePoint& current_point, const ProbePoint& current_velocity)
{
  current_point.x += current_velocity.x;
  current_point.y += current_velocity.y;
}

void stepVelocity(ProbePoint& current_velocity)
{
  if (current_velocity.x != 0)
  {
    int abs_vel_x = abs(current_velocity.x);
    int sign = abs_vel_x/current_velocity.x;
    abs_vel_x -= 1;

    current_velocity.x = sign*abs_vel_x;
  }

  current_velocity.y -= 1;
}

void launchProbe(const TargetArea& target_area, ProbePoint& current_point, ProbePoint& current_velocity, int& highest_point, std::vector<int>& highest_points)
{
  if (shouldReturn(target_area, current_point, current_velocity)) return;

  stepProbePoint(current_point, current_velocity);

  highest_point = std::max(highest_point, current_point.y);

  if(target_area.isInTargetArea(current_point))
  {
    highest_points.push_back(highest_point);
    return;
  }

  stepVelocity(current_velocity);

  launchProbe(target_area, current_point, current_velocity, highest_point, highest_points);
}

void DailyTask17::part1()
{
  TargetArea target_area;
  readInput(target_area);

  ProbePoint current_velocity;
  std::vector<int> highest_points;

  for (int i = 1; i <= target_area.x2; i++)
  {
    for (int j = target_area.y2; j < 200; j++)
    {
      current_velocity.x = i;
      current_velocity.y = j;
      ProbePoint current_point;
      current_point.x = 0;
      current_point.y = 0;

      int highest_point = -std::numeric_limits<int>::max();
      launchProbe(target_area, current_point, current_velocity, highest_point, highest_points);
    }
  }

  std::sort(highest_points.begin(), highest_points.end());

  std::cout<<"PART 1: highest point: "<<highest_points.back()<<std::endl;
}

void DailyTask17::part2()
{
  TargetArea target_area;
  readInput(target_area);

  ProbePoint current_velocity;
  std::vector<int> highest_points;

  for (int i = 1; i <= target_area.x2; i++)
  {
    for (int j = target_area.y2; j < 200; j++)
    {
      current_velocity.x = i;
      current_velocity.y = j;
      ProbePoint current_point;
      current_point.x = 0;
      current_point.y = 0;

      int highest_point = -std::numeric_limits<int>::max();
      launchProbe(target_area, current_point, current_velocity, highest_point, highest_points);
    }
  }

  std::cout<<"PART 2: total: "<<highest_points.size()<<std::endl;
}

int main() {

  DailyTask17 dt17("Day 17: Trick Shot");
  dt17.part1();
  dt17.part2();

  return 0;
}