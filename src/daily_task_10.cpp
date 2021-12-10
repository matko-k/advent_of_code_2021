#include <DailyTask/daily_task_10.h>

void readInput(std::vector<std::string>& navigation_subsystem)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_10_input.txt");
  navigation_subsystem.clear();
  std::string line;

  while (std::getline(file, line))
  {
    navigation_subsystem.push_back(line);
  }

  file.close();
}

bool isOpenChar(char c)
{
  return c == '(' || c == '[' || c == '{' || c == '<';
}

char getPair(char c)
{
  if (c == '(') return ')';
  if (c == ')') return '(';
  if (c == '[') return ']';
  if (c == ']') return '[';
  if (c == '{') return '}';
  if (c == '}') return '{';
  if (c == '<') return '>';
  if (c == '>') return '<';

  return '\0';
}

void DailyTask10::part1()
{
  std::vector<std::string> navigation_subsystem;
  readInput(navigation_subsystem);

  std::vector<char> open_list;
  std::vector<char> corrupted_chars;
  for (const std::string& nav_line : navigation_subsystem)
  {
    for (char nav_char : nav_line)
    {
      if (!open_list.empty() && !isOpenChar(nav_char))
      {
        char last_open = open_list.back();
        if (last_open == getPair(nav_char))
        {
          open_list.pop_back();
        }
        else
        {
          corrupted_chars.push_back(nav_char);
          break;
        }
      }
      if (isOpenChar(nav_char))
      {
        open_list.push_back(nav_char);
      }

    }
  }

  long error_score = 0;

  for (char cc : corrupted_chars)
  {
    if (cc == ')') error_score += 3;
    if (cc == ']') error_score += 57;
    if (cc == '}') error_score += 1197;
    if (cc == '>') error_score += 25137;
  }

  std::cout<<"PART1 : error_score: "<<error_score<<std::endl;
}

void DailyTask10::part2()
{
  std::vector<std::string> navigation_subsystem;
  readInput(navigation_subsystem);

  std::vector<char> open_list;
  std::vector<std::vector<char>> line_completions;
  std::vector<char> added_chars;
  bool corrupted;

  for (const std::string& nav_line : navigation_subsystem)
  {
    corrupted = false;
    open_list.clear();
    added_chars.clear();
    for (char nav_char : nav_line)
    {
      if (!open_list.empty() && !isOpenChar(nav_char))
      {
        char last_open = open_list.back();
        if (last_open == getPair(nav_char))
        {
          open_list.pop_back();
        }
        else
        {
          corrupted = true;
          break;
        }
      }
      if (isOpenChar(nav_char))
      {
        open_list.push_back(nav_char);
      }

    }

    if (corrupted) continue;

    while(!open_list.empty())
    {
      char last_open = open_list.back();
      added_chars.push_back(getPair(last_open));
      open_list.pop_back();
    }
    line_completions.push_back(added_chars);
  }


  std::vector<long> line_scores;
  for (const std::vector<char>& line_completion : line_completions)
  {
    long line_score = 0;
    for (char c : line_completion)
    {
      line_score *= 5;
      if (c == ')') line_score += 1;
      if (c == ']') line_score += 2;
      if (c == '}') line_score += 3;
      if (c == '>') line_score += 4;
    }
    line_scores.push_back(line_score);
  }

  std::sort(line_scores.begin(), line_scores.end());

  std::cout<<"PART2 : middle_line_score: "<<line_scores[line_scores.size()/2]<<std::endl;
}

int main() {

  DailyTask10 dt10("Day 10: Syntax Scoring");
  dt10.part1();
  dt10.part2();

  return 0;
}