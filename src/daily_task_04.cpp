#include <DailyTask/daily_task_04.h>

void readInput(std::vector<int>& bingo_numbers, std::vector<BingoBoard>& bingo_boards)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_04_input.txt");
  std::string line;
  bool read_bingo_nums = true;
  BingoBoard bingo_board;
  while (std::getline(file, line))
  {
    if (line.empty() && !read_bingo_nums)
    {
      BingoBoard board_rows = bingo_board;
      if (board_rows.bingo_rows.empty())
      {
        continue;
      }
      for (int i = 0; i < board_rows.bingo_rows[0].bingo_row.size(); i++)
      {
        std::vector<int> bingo_row;
        for (const BingoRow& br : board_rows.bingo_rows)
        {
          bingo_row.push_back(br.bingo_row[i].first);
        }
        bingo_board.bingo_rows.push_back(bingo_row);
      }
      bingo_boards.push_back(bingo_board);
      bingo_board.bingo_rows.clear();
      continue;
    }

    std::stringstream ss(line);
    std::string number;

    if (read_bingo_nums)
    {
      while (std::getline(ss, number, ','))
      {
        bingo_numbers.push_back(std::stoi(number));
      }
      read_bingo_nums = false;
    }
    else
    {
      std::vector<int> bingo_row;
      while (ss >> number)
      {
        bingo_row.push_back(std::stoi(number));
      }
      BingoRow br(bingo_row);
      bingo_board.bingo_rows.push_back(bingo_row);
    }
  }

  BingoBoard board_rows = bingo_board;
  for (int i = 0; i < board_rows.bingo_rows[0].bingo_row.size(); i++)
  {
    std::vector<int> bingo_row;
    for (const BingoRow& br : board_rows.bingo_rows)
    {
      bingo_row.push_back(br.bingo_row[i].first);
    }
    bingo_board.bingo_rows.push_back(bingo_row);
  }
  bingo_boards.push_back(bingo_board);

  file.close();
}

void DailyTask04::part1()
{
  std::vector<BingoBoard> bingo_boards;
  std::vector<int> bingo_numbers;
  readInput(bingo_numbers, bingo_boards);

  long score = 0;

  for (int bingo_number : bingo_numbers)
  {
    if (score > 0) break;
    for (BingoBoard& bingo_board : bingo_boards)
    {
      for (BingoRow& bingo_row : bingo_board.bingo_rows)
      {
        bingo_row.markNumber(bingo_number);
      }
      if (bingo_board.isWinning())
      {
        int sum = 0;
        for (const BingoRow& bingo_row : bingo_board.bingo_rows)
        {
          for (const BingoNum& bn : bingo_row.bingo_row)
          {
            if (!bn.second)
            {
              sum += bn.first;
            }
          }
        }
        score = 0.5 * sum * bingo_number;
        break;
      }
    }
  }

  std::cout<<"PART1: result: "<< score <<std::endl;
}

void DailyTask04::part2()
{
  std::vector<BingoBoard> bingo_boards;
  std::vector<int> bingo_numbers;
  readInput(bingo_numbers, bingo_boards);

  long score = 0;
  int wins_counter = bingo_boards.size();

  for (int bingo_number : bingo_numbers)
  {
    if (score > 0) break;
    for (BingoBoard& bingo_board : bingo_boards) {
      if (bingo_board.hasWon) continue;
      for (BingoRow &bingo_row: bingo_board.bingo_rows) {
        bingo_row.markNumber(bingo_number);
      }
      if (bingo_board.isWinning()) {
        bingo_board.hasWon = true;
        wins_counter--;
        if (wins_counter == 0)
        {
          int sum = 0;
          for (const BingoRow &bingo_row: bingo_board.bingo_rows) {
            for (const BingoNum &bn: bingo_row.bingo_row) {
              if (!bn.second) {
                sum += bn.first;
              }
            }
          }
          score = 0.5 * sum * bingo_number;
          break;
        }
    }
    }
  }

  std::cout<<"PART2: result: "<< score <<std::endl;
}

int main() {

  DailyTask04 dt04("Day 04: Giant Squid");
  dt04.part1();
  dt04.part2();

  return 0;
}