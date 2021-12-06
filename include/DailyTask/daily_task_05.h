#ifndef AOC2021_DAILY_TASK_05_H
#define AOC2021_DAILY_TASK_05_H

#include <DailyTask/DailyTask.h>

struct Point
{
  int x;
  int y;

  Point(int x, int y): x(x), y(y)
  {}
};

struct Vent
{
  Point start;
  Point end;
  std::vector<Point> vent_line;

  Vent(const Point& start, const Point& end, bool use_diag): start(start), end(end)
  {
    if (start.x == end.x)
    {
      Point new_point(start.x, 0);
      int start_y = std::min(start.y, end.y);
      int end_y = std::max(start.y, end.y);
      for (int i = start_y; i <= end_y; i++)
      {
        new_point.y = i;
        vent_line.push_back(new_point);
      }
    }
    else if (start.y == end.y)
    {
      Point new_point(0, start.y);
      int start_x = std::min(start.x, end.x);
      int end_x = std::max(start.x, end.x);
      for (int i = start_x; i <= end_x; i++)
      {
        new_point.x = i;
        vent_line.push_back(new_point);
      }
    }
    else if (use_diag)
    {
      Point new_point (start.x, start.y);
      if (start.y > end.y)
      {
        if (start.x > end.x)
        {
          for (int i = 0; i < start.y - end.y + 1; i++) {
            vent_line.push_back(new_point);
            new_point.x--;
            new_point.y--;
          }
        }
        else
        {
          for (int i = 0; i < start.y - end.y + 1; i++) {
            vent_line.push_back(new_point);
            new_point.x++;
            new_point.y--;
          }
        }
      }
      else
      {
        if (start.x > end.x)
        {
          for (int i = 0; i < end.y - start.y + 1; i++) {
            vent_line.push_back(new_point);
            new_point.x--;
            new_point.y++;
          }
        }
        else
        {
          for (int i = 0; i < end.y - start.y + 1; i++) {
            vent_line.push_back(new_point);
            new_point.x++;
            new_point.y++;
          }
        }
      }
    }
  }
};

class DailyTask05 : DailyTask {
public:
  DailyTask05(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // AOC2021_DAILY_TASK_05_H
