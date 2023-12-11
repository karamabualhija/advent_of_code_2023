#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

const std::vector<std::pair<std::string, std::string>> StrToIntNumbers =
    {{"oneight", "18"}, {"twone", "21"}, {"threeight", "38"}, {"fiveight", "58"}, {"sevenine", "79"}, {"eightwo", "82"}, {"eighthree", "83"}, {"nineight", "93"}, {"one", "1"}, {"two", "2"}, {"three", "3"}, {"four", "4"}, {"five", "5"}, {"six", "6"}, {"seven", "7"}, {"eight", "8"}, {"nine", "9"}};

int getFirstNumber(std::string word)
{
  for (char c : word)
  {
    if (c >= '0' && c <= '9')
    {
      return c - '0';
    }
  }

  return 0;
}

int getLastNumber(std::string word)
{
  for (std::string::iterator it = word.end(); it > word.begin();)
  {
    --it;
    char c = *it;
    if (c >= '0' && c <= '9')
    {
      return c - '0';
    }
  }
  return 0;
}

int main()
{
  std::ifstream inputFile("advent_day1.txt");

  std::string line;

  size_t sum = 0;
  while (getline(inputFile, line))
  {
    for (auto stringPair : StrToIntNumbers)
    {
      line = std::regex_replace(line, std::regex(stringPair.first), stringPair.second);
    }

    int firstNum = getFirstNumber(line);
    int lastNum = getLastNumber(line);

    sum += firstNum * 10 + lastNum;
  }

  std::cout << "this is your Answer: " << sum << std::endl;

  return 0;
}