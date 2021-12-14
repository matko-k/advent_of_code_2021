#include <DailyTask/daily_task_14.h>

void readInput(std::string& starting_polymer, std::unordered_map<std::string, char>& insertion_rules)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_14_input.txt");
  std::string line;
  std::string pair;
  std::string insertion;

  std::getline(file, starting_polymer);

  while (std::getline(file, line))
  {
    if (line.empty()) continue;

    pair = line.substr(0, line.find(" -> "));
    insertion = line.substr(line.find(" -> ") + 4, line.length());
    insertion_rules[pair] = insertion.at(0);
  }
  file.close();
}

void processPolymer(std::unordered_map<std::string, char>& insertion_rules, std::unordered_map<long long, char>& polymer, int steps)
{
  std::unordered_map<long long, char> new_polymer;
  long long insertions;
  std::string pair;
  while (steps > 0)
  {
    new_polymer.clear();
    new_polymer = polymer;
    insertions = 0;
    for (long long i = 0; i < polymer.size() - 1; i ++)
    {
      pair.clear();
      pair = std::string(1, polymer[i]) + polymer[i+1];
      new_polymer[insertions + i] = polymer[i];
      new_polymer[insertions + i + 1] = insertion_rules[pair];
      insertions++;
    }

    new_polymer[polymer.size() - 1 + insertions] = polymer[polymer.size() - 1];
    polymer = new_polymer;

    steps--;
  }
}

void initPolymer(const std::string starting_polymer, std::unordered_map<long long, char>& polymer)
{
  for (size_t i = 0; i < starting_polymer.length(); i++)
  {
    polymer[(long long)i] = starting_polymer.at(i);
  }
}

void DailyTask14::part1()
{
  int steps = 10;
  std::string starting_polymer;
  std::unordered_map<std::string, char> insertion_rules;

  readInput(starting_polymer, insertion_rules);

  std::unordered_map<long long, char> polymer;
  initPolymer(starting_polymer, polymer);

  processPolymer(insertion_rules, polymer, steps);

  std::map<char, long long> element_counter;

  for (auto it = polymer.begin(); it != polymer.end(); it++)
  {
    if (element_counter.find(it->second) == element_counter.end())
    {
      element_counter[it->second] = 1;
    }
    else
    {
      element_counter[it->second] += 1;
    }
  }

  long long max = 0;
  long long min = std::numeric_limits<long long>::max();

  for (auto it = element_counter.begin(); it != element_counter.end(); it++)
  {
    if (it->second > max) max = it->second;
    if (it->second < min) min = it->second;
  }

  std::cout<<"PART1: diff: "<< max-min <<std::endl;
}

void processPolymer2(std::unordered_map<std::string, char>& insertion_rules, std::unordered_map<std::string, long long>& polymer, int steps)
{
  std::unordered_map<std::string, long long> new_polymer;

  while (steps > 0)
  {
    new_polymer.clear();

    for (const std::pair<std::string, long long>& el_pair : polymer)
    {
      std::string new_pair_1 = el_pair.first.substr(0, 1) + insertion_rules[el_pair.first];
      std::string new_pair_2 = std::string(1, insertion_rules[el_pair.first]) + el_pair.first.substr(1);

      new_polymer[new_pair_1] += el_pair.second;
      new_polymer[new_pair_2] += el_pair.second;
    }

    polymer = new_polymer;

    steps--;
  }
}

void DailyTask14::part2()
{
  int steps = 40;
  std::string starting_polymer;
  std::unordered_map<std::string, char> insertion_rules;

  readInput(starting_polymer, insertion_rules);

  std::unordered_map<std::string, long long> polymer;

  for (size_t i = 0; i < starting_polymer.size() - 1; i++)
  {
    polymer[starting_polymer.substr(i, 2)] += 1;
  }

  processPolymer2(insertion_rules, polymer, steps);

  std::map<char, long long> element_counter;
  for (auto it = polymer.begin(); it != polymer.end(); it++)
  {
    element_counter[it->first.at(0)] += it->second;
  }
  element_counter[starting_polymer.at(starting_polymer.size()-1)] += 1;

  long long max = 0;
  long long min = std::numeric_limits<long long>::max();

  for (auto it = element_counter.begin(); it != element_counter.end(); it++)
  {
    max = std::max(max, it->second);
    min = std::min(min, it->second);
  }
  std::cout<<"PART2: diff: "<< max-min <<std::endl;
}

int main() {

  DailyTask14 dt14("Day 14: Extended Polymerization");
  dt14.part1();
  dt14.part2();

  return 0;
}