#include <DailyTask/daily_task_20.h>

void readInput(std::string& algorithm, std::vector<std::string>& starting_image)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_20_input.txt");

  file >> algorithm;

  std::string line;

  while (file >> line)
  {
    starting_image.push_back(line);
  }

  file.close();
}

void initImage(const std::vector<std::string>& starting_image, std::map<long, bool>& image, const long row_size)
{
  for (int i = 0; i < row_size; i++)
  {
    for (int j = 0; j < row_size; j++)
    {
      image[i*row_size + j] = false;
    }
  }

  long zero_pos = (row_size/2 - starting_image.size()/2) * row_size + row_size/2 - starting_image.size()/2;

  for (int i = 0; i < starting_image.size(); i++)
  {
    for (int j = 0; j < starting_image[i].size(); j++)
    {
      image.at(zero_pos + i*row_size + j) = starting_image[i][j] == '#';
    }
  }
}

std::bitset<9> getWindowCode(const std::string& algorithm, const std::map<long, bool>& image, const long row_size, long position)
{
  std::string bits = "";
  for (int i = -1; i <= 1; i++)
  {
    long row = position + i * row_size;
    for (int j = -1; j <= 1; j++)
    {
      bits += image.at(row + j) ? "1" : "0";
    }
  }
  return std::bitset<9> (bits);
}

void enhanceImage(const std::string& algorithm, std::map<long, bool>& image, const long row_size, bool far_pixel)
{
  std::map<long, bool> enhanced_image = image;
  for (const auto [position, pixel] : image)
  {
    if (position/row_size == 0 || position/row_size >= row_size-1 || position % row_size == 0 || position % row_size >= row_size-1)
    {
      enhanced_image.at(position) = far_pixel;
    }
    else
    {
    enhanced_image.at(position) = algorithm.at(getWindowCode(algorithm, image, row_size, position).to_ulong()) == '#';
    }
  }

  image = enhanced_image;
}

void drawImage(const std::map<long, bool>& image, const long row_size)
{
  std::vector<std::vector<char>> out;
  out.resize(row_size+1);
  for (std::vector<char>& row : out)
  {
    row.resize(row_size+1);
  }

  for (const auto [position, pixel] : image)
  {
    out[position/row_size][position%row_size] = pixel ? '#' : '.';
  }

  for (const std::vector<char> row : out)
  {
    for (const char ch : row)
    {
      std::cout << ch;
    }
    std::cout << '\n';
  }

}

void DailyTask20::part1()
{
  int steps = 2;
  const int window = 3;
  std::string algorithm;
  std::vector<std::string> starting_image;
  readInput(algorithm, starting_image);

  std::map<long, bool> image;
  const long row_size = starting_image.size() + 2*steps*(window-1);
  initImage(starting_image, image, row_size);

  int i = steps;
  bool far_pixel = false;
  while (i > 0)
  {
    far_pixel = far_pixel ? algorithm.back() == '#' : algorithm.front() == '#';
    enhanceImage(algorithm, image, row_size, far_pixel);
    i--;
    //drawImage(image, row_size);
  }

  long count = 0;
  
  for (const auto [position, pixel] : image)
  {
    if (pixel) count++;
  }
  std::cout<<"PART1: light count: "<<count<<std::endl;
}

void DailyTask20::part2()
{
  int steps = 50;
  const int window = 3;
  std::string algorithm;
  std::vector<std::string> starting_image;
  readInput(algorithm, starting_image);

  std::map<long, bool> image;
  const long row_size = starting_image.size() + 2*steps*(window-1);
  initImage(starting_image, image, row_size);

  int i = steps;
  bool far_pixel = false;
  while (i > 0)
  {
    far_pixel = far_pixel ? algorithm.back() == '#' : algorithm.front() == '#';
    enhanceImage(algorithm, image, row_size, far_pixel);
    i--;
    //drawImage(image, row_size);
  }

  long count = 0;

  for (const auto [position, pixel] : image)
  {
    if (pixel) count++;
  }
  std::cout<<"PART1: light count: "<<count<<std::endl;
}

int main() {

  DailyTask20 dt20("Day 20: Trench Map");
  dt20.part1();
  dt20.part2();

  return 0;
}