#include <DailyTask/daily_task_11.h>

void readInput(std::map<int, int>& octopuses, size_t& octo_group_width, size_t& octo_group_height)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_11_input.txt");
  std::string line;
  std::vector<std::vector<int>> octo_input;
  std::vector<int> octo_line;

  while (std::getline(file, line))
  {
    octo_line.clear();
    for (char octopus : line)
    {
      octo_line.push_back((int)octopus - '0');
    }
    octo_input.push_back(octo_line);
  }

  for (size_t i = 0; i < octo_input.size(); i++)
  {
    for (size_t j = 0; j < octo_input[i].size(); j++)
    {
      octopuses[i*octo_input[i].size() + j] = octo_input[i][j];
    }
  }

  octo_group_width = octo_input[0].size();
  octo_group_height = octo_input.size();
  file.close();
}

void printStep(std::map<int, int>& octopuses, int step, int width)
{
  std::cout<<std::endl<<"Step: "<<step<<std::endl;
  for (std::map<int, int>::iterator it = octopuses.begin(); it != octopuses.end(); it++)
  {
    std::cout<<it->second;
    if ((it->first + 1) % width == 0)
      std::cout<<std::endl;
  }
}

void resetFlashed(std::map<int, int>& octopuses)
{
  for (std::map<int, int>::iterator it = octopuses.begin(); it != octopuses.end(); it++)
  {
    if (it->second > 9)
      it->second = 0;
  }
}

void increaseEnergyByOne(std::map<int, int>& octopuses)
{
  for (std::map<int, int>::iterator it = octopuses.begin(); it != octopuses.end(); it++)
  {
    it->second += 1;
  }
}

bool canEnergizeRight(std::map<int, int>& octopuses, int octo_coordinate, int octo_line_width, int octo_line_height)
{
  return (octo_coordinate % octo_line_width + 1) < octo_line_width && octopuses[octo_coordinate + 1] < 11;
}

bool canEnergizeLeft(std::map<int, int>& octopuses, int octo_coordinate, int octo_line_width, int octo_line_height)
{
  return (octo_coordinate % octo_line_width - 1) >= 0 && octopuses[octo_coordinate - 1] < 11;
}

bool canEnergizeUp(std::map<int, int>& octopuses, int octo_coordinate, int octo_line_width, int octo_line_height)
{
  return (octo_coordinate - octo_line_width) >= 0 && octopuses[octo_coordinate - octo_line_width] < 11;
}

bool canEnergizeDown(std::map<int, int>& octopuses, int octo_coordinate, int octo_line_width, int octo_line_height)
{
  return (octo_coordinate + octo_line_width)/octo_line_width < octo_line_height && octopuses[octo_coordinate + octo_line_width] < 11;
}

bool canEnergizeRightUp(std::map<int, int>& octopuses, int octo_coordinate, int octo_line_width, int octo_line_height)
{
  return (octo_coordinate % octo_line_width + 1) < octo_line_width
  && (octo_coordinate - octo_line_width) >= 0
  && octopuses[octo_coordinate - octo_line_width + 1] < 11;
}

bool canEnergizeRightDown(std::map<int, int>& octopuses, int octo_coordinate, int octo_line_width, int octo_line_height)
{
  return (octo_coordinate % octo_line_width + 1) < octo_line_width
         && (octo_coordinate + octo_line_width)/octo_line_width < octo_line_height
         && octopuses[octo_coordinate + octo_line_width + 1] < 11;
}

bool canEnergizeLeftUp(std::map<int, int>& octopuses, int octo_coordinate, int octo_line_width, int octo_line_height)
{
  return (octo_coordinate % octo_line_width - 1) >= 0
         && (octo_coordinate - octo_line_width) >= 0
         && octopuses[octo_coordinate - octo_line_width - 1] < 11;
}

bool canEnergizeLeftDown(std::map<int, int>& octopuses, int octo_coordinate, int octo_line_width, int octo_line_height)
{
  return (octo_coordinate % octo_line_width - 1) >= 0
         && (octo_coordinate + octo_line_width)/octo_line_width < octo_line_height
         && octopuses[octo_coordinate + octo_line_width - 1] < 11;
}

void flashSingle(std::map<int, int>& octopuses, int octo_coordinate, size_t octo_line_width, size_t octo_line_height, long& flashes)
{
  octopuses[octo_coordinate] += 1;
  flashes++;

  //check right
  if (canEnergizeRight(octopuses, octo_coordinate, octo_line_width, octo_line_height))
  {
    octopuses[octo_coordinate + 1] += 1;
    if (octopuses[octo_coordinate + 1] > 9)
      flashSingle(octopuses, octo_coordinate + 1, octo_line_width, octo_line_height, flashes);
  }

  //check right up
  if (canEnergizeRightUp(octopuses, octo_coordinate, octo_line_width, octo_line_height))
  {
    octopuses[octo_coordinate - octo_line_width + 1] += 1;
    if (octopuses[octo_coordinate - octo_line_width + 1] > 9)
      flashSingle(octopuses, octo_coordinate - octo_line_width + 1, octo_line_width, octo_line_height, flashes);
  }

  //check right down
  if (canEnergizeRightDown(octopuses, octo_coordinate, octo_line_width, octo_line_height))
  {
    octopuses[octo_coordinate + octo_line_width + 1] += 1;
    if (octopuses[octo_coordinate + octo_line_width + 1] > 9)
      flashSingle(octopuses, octo_coordinate + octo_line_width + 1, octo_line_width, octo_line_height, flashes);
  }

  //check left
  if (canEnergizeLeft(octopuses, octo_coordinate, octo_line_width, octo_line_height))
  {
    octopuses[octo_coordinate - 1] += 1;
    if (octopuses[octo_coordinate - 1] > 9)
      flashSingle(octopuses, octo_coordinate - 1, octo_line_width, octo_line_height, flashes);
  }

  //check left up
  if (canEnergizeLeftUp(octopuses, octo_coordinate, octo_line_width, octo_line_height))
  {
    octopuses[octo_coordinate - octo_line_width - 1] += 1;
    if (octopuses[octo_coordinate - octo_line_width - 1] > 9)
      flashSingle(octopuses, octo_coordinate - octo_line_width - 1, octo_line_width, octo_line_height, flashes);
  }

  //check left down
  if (canEnergizeLeftDown(octopuses, octo_coordinate, octo_line_width, octo_line_height))
  {
    octopuses[octo_coordinate + octo_line_width - 1] += 1;
    if (octopuses[octo_coordinate + octo_line_width - 1] > 9)
      flashSingle(octopuses, octo_coordinate + octo_line_width - 1, octo_line_width, octo_line_height, flashes);
  }

  //check up
  if (canEnergizeUp(octopuses, octo_coordinate, octo_line_width, octo_line_height))
  {
    octopuses[octo_coordinate - octo_line_width] += 1;
    if (octopuses[octo_coordinate - octo_line_width] > 9)
      flashSingle(octopuses, octo_coordinate - octo_line_width, octo_line_width, octo_line_height, flashes);
  }

  //check down
  if (canEnergizeDown(octopuses, octo_coordinate, octo_line_width, octo_line_height))
  {
    octopuses[octo_coordinate + octo_line_width] += 1;
    if (octopuses[octo_coordinate + octo_line_width] > 9)
      flashSingle(octopuses, octo_coordinate + octo_line_width, octo_line_width, octo_line_height, flashes);
  }
}

void flashThem(std::map<int, int>& octopuses, long& flashes, size_t octo_line_width, size_t octo_line_height)
{
  for (std::map<int, int>::iterator it = octopuses.begin(); it != octopuses.end(); it++)
  {
    if (it->second == 10)
    {
      flashSingle(octopuses, it->first, octo_line_width, octo_line_height, flashes);
    }
  }
}

void flashOctopuses(std::map<int, int>& octopuses, long& flashes, size_t octo_line_width, size_t octo_line_height, long& steps)
{
  flashes = 0;
  resetFlashed(octopuses);

  if (steps > 0)
  {
    while (steps > 0) {
      printStep(octopuses, steps, octo_line_width);
      increaseEnergyByOne(octopuses);
      flashThem(octopuses, flashes, octo_line_width, octo_line_height);
      resetFlashed(octopuses);
      steps--;
    }
  }
  else
  {
    steps = 0;
    while (true)
    {
      steps++;
      flashes = 0;
      printStep(octopuses, steps, octo_line_width);
      increaseEnergyByOne(octopuses);
      flashThem(octopuses, flashes, octo_line_width, octo_line_height);
      if (flashes == octo_line_height*octo_line_width)
      {
        break;
      }
      resetFlashed(octopuses);
    }
  }

}

void DailyTask11::part1()
{
  std::map<int, int> octopuses;
  size_t octo_group_width;
  size_t octo_group_height;
  readInput(octopuses, octo_group_width, octo_group_height);

  long steps = 100;
  long flashes;
  flashOctopuses(octopuses, flashes, octo_group_width, octo_group_height, steps);

  std::cout<<"PART1: total flashes after "<<steps<<" steps: "<<flashes<<std::endl;
}

void DailyTask11::part2()
{
  std::map<int, int> octopuses;
  size_t octo_group_width;
  size_t octo_group_height;
  readInput(octopuses, octo_group_width, octo_group_height);

  long steps = -1;
  long flashes;
  flashOctopuses(octopuses, flashes, octo_group_width, octo_group_height, steps);

  std::cout<<"PART2: sync after "<<steps<<" steps"<<std::endl;
}

int main() {

  DailyTask11 dt11("Day 11: Dumbo Octopus");
  dt11.part1();
  dt11.part2();

  return 0;
}