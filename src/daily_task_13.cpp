#include <DailyTask/daily_task_13.h>

void readInput(std::vector<std::vector<bool>>& paper, std::vector<FoldingInstruction>& folding_instructions)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_13_input.txt");
  std::string line;
  std::vector<Point> points;
  Point point;
  int max_x = 0;
  int max_y = 0;
  bool reading_points = true;
  FoldingInstruction folding_instruction;

  while (std::getline(file, line))
  {
    if (line.empty())
    {
      reading_points = false;
      continue;
    }

    if (reading_points)
    {
      std::string test = line.substr(line.find(',') - 1, line.find(','));
      int x = stoi(line.substr(0, line.find(',')));
      int y = stoi(line.substr(line.find(',') + 1, line.length()));

      max_x = std::max(x, max_x);
      max_y = std::max(y, max_y);
      point.x = x;
      point.y = y;
      points.push_back(point);
    }
    else
    {
      folding_instruction.is_x = line.substr(line.find('=') - 1, line.find('=')).at(0) == 'x';
      folding_instruction.line_num = stoi(line.substr(line.find('=') + 1, line.length()));
      folding_instructions.push_back(folding_instruction);
    }
  }
  paper.clear();
  paper.resize(max_y+1);

  for (size_t i = 0; i < paper.size(); i++)
  {
    paper[i].resize(max_x+1);
  }

  for (const Point& p : points)
  {
    paper[p.y][p.x] = true;
  }

  file.close();
}

void foldPaperByRow(std::vector<std::vector<bool>>& paper, int folding_row)
{
  bool good_fold = folding_row >= paper.size() / 2;
  std::vector<std::vector<bool>> folded_paper;

  if (good_fold)
  {
    int folded_paper_size = folding_row;
    folded_paper.resize(folded_paper_size);

    for (size_t i = 0; i < folded_paper.size(); i++)
    {
      folded_paper[i].resize(paper[0].size());
    }

    int folded_part_size = paper.size() - folding_row - 1;
    int limit = folding_row - folded_part_size;

    for (size_t i = 0; i < folded_paper.size(); i++)
    {
      for (size_t j = 0; j < folded_paper[i].size(); j++)
      {
        if (i < limit)
        {
          folded_paper[i][j] = paper[i][j];
        }
        else
        {
          folded_paper[i][j] = paper[i][j] || paper[paper.size() - 1 - i + limit][j];
        }
      }
    }
  }
  else
  {
    int folded_paper_size = paper.size() - folding_row - 1;
    folded_paper.resize(folded_paper_size);

    for (size_t i = 0; i < folded_paper.size(); i++)
    {
      folded_paper[i].resize(paper[0].size());
    }

    int folded_part_size = folding_row;
    int limit = folding_row + folded_part_size + 1;

    for (size_t i = 0; i < folded_paper.size(); i++)
    {
      for (size_t j = 0; j < folded_paper[i].size(); j++)
      {
        if (i < limit)
        {
          folded_paper[i][j] = paper[folding_row + i + 1][j] || paper[folding_row - i - 1][j];
        }
        else
        {
          folded_paper[i][j] = paper[folding_row + i + 1][j];
        }
      }
    }
  }

  paper = folded_paper;
}

void foldPaperByColumn(std::vector<std::vector<bool>>& paper, int folding_column)
{
  bool good_fold = folding_column >= paper[0].size() / 2;
  std::vector<std::vector<bool>> folded_paper;

  if (good_fold)
  {
    int folded_paper_size = folding_column;
    folded_paper.resize(paper.size());

    for (size_t i = 0; i < paper.size(); i++)
    {
      folded_paper[i].resize(folded_paper_size);
    }

    int folded_part_size = paper[0].size() - folding_column - 1;
    int limit = folding_column - folded_part_size;

    for (size_t i = 0; i < folded_paper.size(); i++)
    {
      for (size_t j = 0; j < folded_paper[i].size(); j++)
      {
        if (j < limit)
        {
          folded_paper[i][j] = paper[i][j];
        }
        else
        {
          folded_paper[i][j] = paper[i][j] || paper[i][paper[0].size() - 1 - j + limit];
        }
      }
    }
  }
  else
  {
    int folded_paper_size = paper.size() - folding_column - 1;
    folded_paper.resize(paper.size());

    for (size_t i = 0; i < paper.size(); i++)
    {
      folded_paper[i].resize(folded_paper_size);
    }

    int folded_part_size = folding_column;
    int limit = folding_column + folded_part_size + 1;

    for (size_t i = 0; i < folded_paper.size(); i++)
    {
      for (size_t j = 0; j < folded_paper[i].size(); j++)
      {
        if (j < limit)
        {
          folded_paper[i][j] = paper[i][folding_column + j + 1] || paper[i][folding_column - j - 1];
        }
        else
        {
          folded_paper[i][j] = paper[i][folding_column + j + 1];
        }
      }
    }
  }

  paper = folded_paper;
}

void DailyTask13::part1()
{
  std::vector<std::vector<bool>> paper;
  std::vector<FoldingInstruction> folding_instructions;
  readInput(paper, folding_instructions);

  FoldingInstruction first_folding = folding_instructions.front();

  if (first_folding.is_x)
  {
    foldPaperByColumn(paper, first_folding.line_num);
  }
  else
  {
    foldPaperByRow(paper, first_folding.line_num);
  }

  int count = 0;

  for (const std::vector<bool>& pr : paper)
  {
    for (bool point : pr)
    {
      if (point)
        count++;
    }
  }
  std::cout<<"PART1: point count: "<<count<<std::endl;
}

void DailyTask13::part2()
{
  std::vector<std::vector<bool>> paper;
  std::vector<FoldingInstruction> folding_instructions;
  readInput(paper, folding_instructions);

  for (const FoldingInstruction& fi : folding_instructions)
  {
    if (fi.is_x)
    {
      foldPaperByColumn(paper, fi.line_num);
    }
    else
    {
      foldPaperByRow(paper, fi.line_num);
    }
  }

  for (size_t i = 0; i < paper.size(); i++)
  {
    for (size_t j = 0; j < paper[i].size(); j++)
    {
      if (paper[i][j]) std::cout<<'#';
      else std::cout<<'.';
    }
    std::cout<<std::endl;
  }
}

int main() {

  DailyTask13 dt13("Day 13: Transparent Origami");
  dt13.part1();
  dt13.part2();

  return 0;
}