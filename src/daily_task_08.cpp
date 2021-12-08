#include <DailyTask/daily_task_08.h>

void readInput(int& count1478, std::vector<std::vector<std::string>>& all_digits, std::vector<std::vector<std::string>>& all_outputs)
{
  count1478 = 0;
  std::ifstream file;
  file.open("../daily_inputs/daily_task_08_input.txt");
  std::string line;
  all_digits.clear();
  all_outputs.clear();

  while (std::getline(file, line))
  {
    std::stringstream ss_digits(line.substr(0, line.find('|') - 1));
    std::stringstream ss_output(line.substr(line.find('|') + 2));

    std::string digit;
    std::vector<std::string> digits;
    std::string output;
    std::vector<std::string> outputs;

    while (ss_digits >> digit)
    {
      std::sort(digit.begin(), digit.end());
      digits.push_back(digit);
    }
    all_digits.push_back(digits);

    while (ss_output >> output)
    {
      std::sort(output.begin(), output.end());
      if (output.length() == 2 || output.length() == 3 || output.length() == 4 || output.length() == 7)
      {
        count1478++;
      }
      outputs.push_back(output);
    }
    all_outputs.push_back(outputs);
  }

  file.close();
}

void readInput(int& count1478)
{
  std::vector<std::vector<std::string>> dummy_digits, dummy_outputs;
  readInput(count1478, dummy_digits, dummy_outputs);
}

// returns string with characters that string1 has and string2 doesn't have
std::string stringDiff(const std::string& string1, const std::string& string2)
{
  std::string string_diff = "";

  for (int i = 0; i < string1.length(); i++)
  {
    if (string2.find(string1.at(i)) == std::string::npos)
    {
      string_diff+=string1.at(i);
    }
  }

  return string_diff;
}

void DailyTask08::part1()
{
  int count1478;
  readInput(count1478);

  std::cout <<"PART1: count[1,4,7,8]: "<<count1478<<std::endl;
}

void DailyTask08::part2()
{
  std::vector<std::vector<std::string>> all_digits;
  std::vector<std::vector<std::string>> all_outputs;
  int count1478;
  readInput(count1478, all_digits, all_outputs);
  long out_sum = 0;
  std::vector<Display> displays;
  for (const std::vector<std::string>& digits : all_digits)
  {
    Display display;

    for (const std::string& digit : digits)
    {
      if (digit.length() == 2)
      {
        display.display_digits[digit] = 1;
        display.display_codes[1] = digit;
      }
      if (digit.length() == 3)
      {
        display.display_digits[digit] = 7;
        display.display_codes[7] = digit;
      }
      if (digit.length() == 4)
      {
        display.display_digits[digit] = 4;
        display.display_codes[4] = digit;
      }
      if (digit.length() == 5)
      {
        display.length_5_digits.push_back(digit);
      }
      if (digit.length() == 6)
      {
        display.length_6_digits.push_back(digit);
      }
      if (digit.length() == 7)
      {
        display.display_digits[digit] = 8;
        display.display_codes[8] = digit;
      }
    }
    std::string temp;

    //find number 3
    for (const std::string& dig : display.length_5_digits)
    {
      if (dig.find(display.display_codes[1].at(0)) != std::string::npos && dig.find(display.display_codes[1].at(1)) != std::string::npos)
      {
        display.display_digits[dig] = 3;
        display.display_codes[3] = dig;
        break;
      }
    }

    //find number 6
    for (const std::string& dig : display.length_6_digits)
    {
      temp = stringDiff(display.display_codes[7], dig);
      if (temp.length() > 0)
      {
        display.display_digits[dig] = 6;
        display.display_codes[6] = dig;
        break;
      }
    }

    //find number 0
    for (const std::string& dig : display.length_6_digits)
    {
      if (dig.compare(display.display_codes[6]) == 0) continue;
      temp = stringDiff(display.display_codes[3], dig);
      if (temp.length() > 0)
      {
        display.display_digits[dig] = 0;
        display.display_codes[0] = dig;
        break;
      }
    }

    //find number 9
    for (const std::string& dig : display.length_6_digits)
    {
      if (dig.compare(display.display_codes[0]) == 0) continue;
      if (dig.compare(display.display_codes[6]) == 0) continue;

      display.display_codes[9] = dig;
      display.display_digits[dig] = 9;
      break;
    }

    //find number 2
    int biggest_diff = 0;
    std::string digit_2;
    for (const std::string& dig : display.length_5_digits)
    {
      if (dig.compare(display.display_codes[3]) == 0) continue;
      temp = stringDiff(display.display_codes[6], dig);
      if (temp.length() > biggest_diff)
      {
        biggest_diff = temp.length();
        digit_2 = dig;
      }
    }
    display.display_codes[2] = digit_2;
    display.display_digits[digit_2] = 2;

    //find number 5
    for (const std::string& dig : display.length_5_digits)
    {
      if (dig.compare(display.display_codes[3]) == 0) continue;
      if (dig.compare(display.display_codes[2]) == 0) continue;

      display.display_codes[5] = dig;
      display.display_digits[dig] = 5;
      break;
    }

    displays.push_back(display);

  }

  for (size_t i = 0; i < displays.size(); i++)
  {
    std::string output_num = "";
    for (const std::string& output : all_outputs[i])
    {
      output_num += std::to_string(displays[i].display_digits[output]);
    }
    out_sum += stoi(output_num);
  }

  std::cout<<"PART2: sum: "<<out_sum<<std::endl;
}

int main() {

  DailyTask08 dt08("Day 08: Seven Segment Search");
  dt08.part1();
  dt08.part2();

  return 0;
}