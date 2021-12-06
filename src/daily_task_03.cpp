#include <DailyTask/daily_task_03.h>

void DailyTask03::part1()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_03_input.txt");

  const size_t line_size = 12;
  std::vector<std::bitset<line_size>> diagnostic_data;
  std::bitset<line_size> line;

  while (file >> line)
  {
    diagnostic_data.push_back(line);
  }
  file.close();

  std::bitset<line_size> gamma_rate = std::bitset<line_size>(0);
  std::bitset<line_size> epsilon_rate = std::bitset<line_size>(0);

  for (size_t i = 0; i < line_size; i++)
  {
    int ones_count = 0;
    for (size_t j = 0; j < diagnostic_data.size(); j++)
    {
      if (diagnostic_data[j][i])
      {
        ones_count++;
      }
    }
    if (ones_count > diagnostic_data.size()/2)
    {
      gamma_rate |= std::bitset<line_size>(pow(2, i));
    }
    else
    {
      epsilon_rate |= std::bitset<line_size>(pow(2, i));
    }
  }

  std::cout<<"PART1: gamma_rate: "<<gamma_rate.to_ulong()<<", epsilon rate: "<<epsilon_rate.to_ulong()<<", power consumption: "<<gamma_rate.to_ulong() * epsilon_rate.to_ulong()<<std::endl;

}

void DailyTask03::part2()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_03_input.txt");

  const size_t line_size = 12;
  std::vector<std::bitset<line_size>> diagnostic_data;
  std::bitset<line_size> line;

  while (file >> line)
  {
    diagnostic_data.push_back(line);
  }
  file.close();

  std::bitset<line_size> oxygen;
  std::bitset<line_size> co2;

  std::vector<std::bitset<line_size>> oxygen_data = diagnostic_data;

  for (size_t i = 0; i < line_size; i++)
  {
    int ones_count = 0;
    for (size_t j = 0; j < oxygen_data.size(); j++)
    {
      if (oxygen_data[j][line_size - 1 - i])
      {
        ones_count++;
      }
    }

    bool keep_ones = ones_count >= (oxygen_data.size()+1)/2;
    std::vector<std::bitset<line_size>> oxygen_data_new;

    for (size_t j = 0; j < oxygen_data.size(); j++)
    {
      if (oxygen_data[j][line_size - 1 - i] == keep_ones)
      {
        oxygen_data_new.push_back(oxygen_data[j]);
      }
    }

    oxygen_data = oxygen_data_new;

    if (oxygen_data.size() == 1)
    {
      oxygen = oxygen_data.front();
      break;
    }
  }

  // co2
  std::vector<std::bitset<line_size>> co2_data = diagnostic_data;

  for (size_t i = 0; i < line_size; i++)
  {
    int ones_count = 0;
    for (size_t j = 0; j < co2_data.size(); j++)
    {
      if (co2_data[j][line_size - 1 - i])
      {
        ones_count++;
      }
    }

    bool keep_ones = ones_count < (co2_data.size()+1)/2;
    std::vector<std::bitset<line_size>> co2_data_new;

    for (size_t j = 0; j < co2_data.size(); j++)
    {
      if (co2_data[j][line_size - 1 - i] == keep_ones)
      {
        co2_data_new.push_back(co2_data[j]);
      }
    }

    co2_data = co2_data_new;

    if (co2_data.size() == 1)
    {
      co2 = co2_data.front();
      break;
    }
  }

  std::cout<<"PART2: oxygen: "<<oxygen.to_ulong()<<", co2: "<<co2.to_ulong()<<", life support: "<<oxygen.to_ulong() * co2.to_ulong()<<std::endl;



}

int main() {

  DailyTask03 dt03("Day 03: Binary Diagnostic");
  dt03.part1();
  dt03.part2();

  return 0;
}