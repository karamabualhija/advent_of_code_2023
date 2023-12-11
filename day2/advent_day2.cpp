#include <iostream>
#include <fstream>
#include <cstddef>
#include <vector>

const size_t MAX_NUM_BLUE = 14;
const size_t MAX_NUM_GREEN = 13;
const size_t MAX_NUM_RED = 12;

void getAllRedOccurrences(std::string line, std::vector<size_t> &reds)
{
  std::size_t pos = line.find("red", 0);
  while (pos != std::string::npos)
  {
    std::size_t tempPos = pos - 2;
    while (isdigit(line[tempPos]))
    {
      --tempPos;
    }
    ++tempPos;
    std::string tempString = "";
    while (tempPos < pos - 1)
    {
      tempString += line[tempPos];
      ++tempPos;
    }
    reds.push_back(std::stoi(tempString));
    pos = line.find("red", pos + 1);
  }
}

void getAllBlueOccurrences(std::string line, std::vector<size_t> &blues)
{
  std::size_t pos = line.find("blue", 0);
  while (pos != std::string::npos)
  {
    std::size_t tempPos = pos - 2;
    while (isdigit(line[tempPos]))
    {
      --tempPos;
    }
    ++tempPos;
    std::string tempString = "";
    while (tempPos < pos - 1)
    {
      tempString += line[tempPos];
      ++tempPos;
    }
    blues.push_back(std::stoi(tempString));
    pos = line.find("blue", pos + 1);
  }
}

void getAllGreenOccurrences(std::string line, std::vector<size_t> &greens)
{
  std::size_t pos = line.find("green", 0);
  while (pos != std::string::npos)
  {
    std::size_t tempPos = pos - 2;
    while (isdigit(line[tempPos]))
    {
      --tempPos;
    }
    ++tempPos;
    std::string tempString = "";
    while (tempPos < pos - 1)
    {
      tempString += line[tempPos];
      ++tempPos;
    }
    greens.push_back(std::stoi(tempString));
    pos = line.find("green", pos + 1);
  }
}

std::size_t isLinePossible(std::string line)
{
  std::vector<std::size_t> redOccurrences;
  std::vector<std::size_t> blueOccurrences;
  std::vector<std::size_t> greenOccurrences;

  getAllRedOccurrences(line, redOccurrences);
  std::size_t maxRed = 0;
  for (auto num : redOccurrences)
  {
    if (num > maxRed)
    {
      maxRed = num;
    }
  }

  getAllBlueOccurrences(line, blueOccurrences);
  std::size_t maxBlue = 0;
  for (auto num : blueOccurrences)
  {

    if (num > maxBlue)
    {
      maxBlue = num;
    }
  }

  getAllGreenOccurrences(line, greenOccurrences);
  std::size_t maxGreen = 0;
  for (auto num : greenOccurrences)
  {
    if (num > maxGreen)
    {
      maxGreen = num;
    }
  }

  // std::cout << maxRed << " " << maxGreen << " " << maxBlue << std::endl;

  return maxBlue * maxGreen * maxRed;
}

int main()
{
  std::ifstream inputFile("advent_day2.txt");

  std::string line;
  std::size_t game = 1;

  size_t sum = 0;

  while (getline(inputFile, line))
  {
    // std::cout << line << std::endl;
    sum += isLinePossible(line);
    // break;
  }

  std::cout << "this is your Answer: " << sum << std::endl;

  return 0;
}