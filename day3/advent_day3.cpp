#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstddef>

bool isSpecial(char val)
{
  bool isSpecial = true;

  if ((val >= '0' && val <= '9') || val == '.')
  {
    isSpecial = false;
  }
  return isSpecial;
}

bool isUpperLeftSpecial(std::vector<std::string> &data, std::size_t row, std::size_t col)
{
  if (row == 0 || col == 0)
  {
    return false;
  }
  return isSpecial(data[row - 1][col - 1]);
}

bool isUpperRightSpecial(std::vector<std::string> &data, std::size_t row, std::size_t col)
{
  if (row == 0 || col == data[row].length() - 1)
  {
    return false;
  }
  return isSpecial(data[row - 1][col + 1]);
}

bool isUpperCenterSpecial(std::vector<std::string> &data, std::size_t row, std::size_t col)
{
  if (row == 0)
  {
    return false;
  }
  return isSpecial(data[row - 1][col]);
}

bool isLeftSpecial(std::vector<std::string> &data, std::size_t row, std::size_t col)
{
  if (col == 0)
  {
    return false;
  }
  return isSpecial(data[row][col - 1]);
}

bool isRightSpecial(std::vector<std::string> &data, std::size_t row, std::size_t col)
{
  if (col == data[row].length() - 1)
  {
    return false;
  }
  return isSpecial(data[row][col + 1]);
}

bool isLowerLeftSpecial(std::vector<std::string> &data, std::size_t row, std::size_t col)
{
  if (row == data.size() - 1 || col == 0)
  {
    return false;
  }
  return isSpecial(data[row + 1][col - 1]);
}

bool isLowerRightSpecial(std::vector<std::string> &data, std::size_t row, std::size_t col)
{
  if (row == data.size() - 1 || col == data[row].length() - 1)
  {
    return false;
  }
  return isSpecial(data[row + 1][col + 1]);
}

bool isLowerCenterSpecial(std::vector<std::string> &data, std::size_t row, std::size_t col)
{
  if (row == data.size() - 1)
  {
    return false;
  }
  return isSpecial(data[row + 1][col]);
}

bool isPart(std::vector<std::string> &data, std::size_t row, std::size_t col)
{
  return isUpperLeftSpecial(data, row, col) || isUpperRightSpecial(data, row, col) || isUpperCenterSpecial(data, row, col) || isLeftSpecial(data, row, col) || isRightSpecial(data, row, col) || isLowerLeftSpecial(data, row, col) || isLowerRightSpecial(data, row, col) || isLowerCenterSpecial(data, row, col);
}

std::size_t parseNumber(std::string &currentStr, std::size_t position)
{
  std::size_t startPosition = position;
  while (startPosition > 0 && currentStr[startPosition - 1] >= '0' && currentStr[startPosition - 1] <= '9')
  {
    --startPosition;
  }

  std::size_t numOfDigits{};
  std::size_t parsedNum = std::stoi(currentStr.c_str() + startPosition, &numOfDigits);

  while (numOfDigits)
  {
    currentStr[startPosition] = '.';
    ++startPosition;
    --numOfDigits;
  }

  return parsedNum;
}

////////////////////////////PART 1///////////////////////////////////////

int main()
{
  std::ifstream input("advent_day3.txt");
  std::string line;
  std::vector<std::string> data;

  while (std::getline(input, line))
  {
    data.push_back(line);
  }

  std::size_t sum = 0;
  for (std::size_t i = 0; i < data.size(); ++i)
  {
    for (std::size_t j = 0; j < data[i].length(); ++j)
    {
      const char currentChar = data[i][j];
      if (isdigit(currentChar))
      {
        if (isPart(data, i, j))
        {
          sum += parseNumber(data[i], j);
        }
      }
    }
  }

  std::cout << "the answer is: " << sum << std::endl;
  return 0;
}

////////////////////////////////////PART 2

std::size_t getGearRatio(std::vector<std::string> &data, std::size_t row, std::size_t col)
{
  std::size_t maxRows = data.size();
  std::size_t maxCols = data[0].length();

  std::string oneLineBellow = data[row - 1];
  std::string oneLineAbove = data[row + 1];
  std::string thisLine = data[row];

  std::vector<std::size_t> ratios;
  if (row > 0 && col > 0 && isdigit(oneLineBellow[col - 1]))
  {
    ratios.push_back(parseNumber(oneLineBellow, col - 1));
  }

  if (row > 0 && isdigit(oneLineBellow[col]))
  {
    ratios.push_back(parseNumber(oneLineBellow, col));
  }

  if (row > 0 && col < maxCols - 1 && isdigit(oneLineBellow[col + 1]))
  {
    ratios.push_back(parseNumber(oneLineBellow, col + 1));
  }

  if (col > 0 && isdigit(thisLine[col - 1]))
  {
    ratios.push_back(parseNumber(thisLine, col - 1));
  }

  if (col < maxCols - 1 && isdigit(thisLine[col + 1]))
  {
    ratios.push_back(parseNumber(thisLine, col + 1));
  }

  if (row < maxRows - 1 && col > 0 && isdigit(oneLineAbove[col - 1]))
  {
    ratios.push_back(parseNumber(oneLineAbove, col - 1));
  }

  if (row < maxRows - 1 && isdigit(oneLineAbove[col]))
  {
    ratios.push_back(parseNumber(oneLineAbove, col));
  }

  if (row < maxRows - 1 && col < maxCols - 1 && isdigit(oneLineAbove[col + 1]))
  {
    ratios.push_back(parseNumber(oneLineAbove, col + 1));
  }

  if (ratios.size() > 1)
  {
    std::size_t mul = 1;
    for (auto x : ratios)
    {
      mul *= x;
    }

    return mul;
  }

  return 0;
}

// int main()
// {
//   std::ifstream input("advent_day3.txt");
//   std::string line;
//   std::vector<std::string> data;

//   while (std::getline(input, line))
//   {
//     data.push_back(line);
//   }

//   std::size_t sum = 0;
//   for (std::size_t i = 0; i < data.size(); ++i)
//   {
//     for (std::size_t j = 0; j < data[i].length(); ++j)
//     {
//       const char currentChar = data[i][j];
//       if (currentChar == '*')
//       {
//         sum += getGearRatio(data, i, j);
//       }
//     }
//   }

//   std::cout << "the answer is: " << sum << std::endl;
//   return 0;
// }