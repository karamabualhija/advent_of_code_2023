#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <array>

#define PART_TWO

void buildGameWinningNum(std::string &str, std::unordered_map<std::size_t, std::size_t> &winningNumbers)
{
  std::size_t startPos = 0;

  while (startPos < str.length())
  {
    std::size_t numOfDigits{};
    std::size_t winnerNum = std::stoi(str.c_str() + startPos, &numOfDigits);
    winningNumbers[winnerNum] = winnerNum;
    startPos += numOfDigits + 1;
  }
}

std::size_t numOfMatches(std::string &str, std::unordered_map<std::size_t, std::size_t> &winningNumbers)
{
  std::size_t startPos = 0;
  std::size_t matches = 0;

  while (startPos < str.length())
  {
    std::size_t numOfDigits{};
    std::size_t chosenNumber = std::stoi(str.c_str() + startPos, &numOfDigits);

    if (winningNumbers[chosenNumber] == chosenNumber)
    {
      ++matches;
    }
    startPos += numOfDigits + 1;
  }

  return matches;
}

std::size_t getGamePoint(std::string &game)
{
  std::size_t startingPos = game.find(':');
  std::size_t winningEndPos = game.find('|', startingPos);

  std::string winningStr = game.substr(startingPos + 2, winningEndPos - startingPos - 2);

  std::unordered_map<std::size_t, std::size_t> winningMap;
  buildGameWinningNum(winningStr, winningMap);

  std::string chosenNumbers = game.substr(winningEndPos + 2);
  std::size_t matches = numOfMatches(chosenNumbers, winningMap);

#ifndef PART_TWO
  if (matches == 0)
  {
    return 0;
  }

  return 1 << (matches - 1);
#else
  return matches;
#endif
}

int main()
{
  std::ifstream input("advent_day4.txt");
  std::string line;

#ifdef PART_TWO
  std::unordered_map<std::size_t, std::size_t> gamePoints;
#endif

  std::size_t sum = 0;
  std::size_t game = 0;
  while (std::getline(input, line))
  {
#ifdef PART_TWO
    gamePoints[game + 1] = getGamePoint(line);
    ++game;
#else
    sum += getGamePoint(line);
#endif
  }

#ifdef PART_TWO
  std::array<std::size_t, 190> cards; // should have used dynamic array

  for (auto &x : cards)
  {
    x = 1;
  }

  for (std::size_t j = 0; j < game; ++j)
  {
    for (std::size_t i = 0; i < gamePoints[j + 1]; ++i)
    {
      cards[j + i + 1] += cards[j];
    }
  }

  sum = 0;
  for (std::size_t j = 0; j < game; ++j) // can be done with std::accumulate
  {
    sum += cards[j];
  }
#endif
  std::cout << "Your Answer is: " << sum << std::endl;

  return 0;
}