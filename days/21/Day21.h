#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day21 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day21()= default;

  ~Day21() override = default;

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  auto GetDay() -> string override
  {
    return "21";
  }

  auto DoWork1() -> LL
  {
    LL ret = 0;

    vector<int> players = { 6, 3 }; // real data

    //vector<int> players = { 4, 8 }; // test data
   
    map<int, int> scores;

    int dice = 1;
    int dieCount = 0;
    auto throwDice = [&]()
    {
      dieCount++;
      int ret = dice;
      dice += 1;
      if (dice == 101)
        dice = 1;
      return ret;
    };

    bool won = false;
    while (true)
    {
      for (int playerIndex : rangeint(0, players.size() -1 ))
      {
        int dice1 = throwDice();
        int dice2 = throwDice();
        int dice3 = throwDice();
        int val = dice1 + dice2 + dice3;
        int& p = players[playerIndex];
        p = (p + val);
        if (p > 10)
          p %= 10;
        scores[playerIndex] += p;

        if (scores[playerIndex] >= 1000)
        {
          won = true;
          ret = scores[playerIndex == 0 ? 1 : 0] * dieCount;
          break;
        }
      }
      if (won)
        break;
    }

    cout << "Day20 " << mCurrentInput << " P1: " << ret << endl;
    return ret;
  }

  auto DoWork2() -> LL
  {
    map<int, LL> universesWonCount;
    universesWonCount[0] = 0;
    universesWonCount[1] = 0;
    
    struct Universe
    {
      unordered_map<int, pair<int, LL>> playerPosAndScore;
      int playerTurn{ 0 };
    };
    function<void(Universe , LL)> throwDice;

    unordered_map<int, int> diceThrowProbabilityCloud;
    for (int i : rangeint(1, 3))
    {
      for (int j : rangeint(1, 3))
      {
        for (int k : rangeint(1, 3))
          diceThrowProbabilityCloud[i + j + k]++;
      }
    }
    throwDice = [&](Universe universe, LL pastUniversesMultiplier)
    {
        for (auto probableDiceThrow : diceThrowProbabilityCloud)
        {
          int newPos = universe.playerPosAndScore[universe.playerTurn].first + probableDiceThrow.first;
          if (newPos > 10)
            newPos %= 10;
          LL newScore = universe.playerPosAndScore[universe.playerTurn].second + newPos;
          if (newScore >= 21)
            universesWonCount[universe.playerTurn] += pastUniversesMultiplier * probableDiceThrow.second;
          else
          {
            auto newUniverse = universe;
            newUniverse.playerPosAndScore[universe.playerTurn].first = newPos;
            newUniverse.playerPosAndScore[universe.playerTurn].second = newScore;
            newUniverse.playerTurn = universe.playerTurn == 0 ? 1 : 0;
            throwDice(newUniverse, pastUniversesMultiplier * probableDiceThrow.second);
          }
        }
    };

    Universe firstUniverse;
    firstUniverse.playerPosAndScore[0] = make_pair(6, 0);  // real data
    firstUniverse.playerPosAndScore[1] = make_pair(3, 0);
    firstUniverse.playerTurn = 0;
    throwDice(firstUniverse, 1);

    return max(universesWonCount[0], universesWonCount[1]);
  }
  
  auto Part1() -> string override
  {
    ReadData();

    return std::to_string(DoWork1());
  }

  auto Part2() -> string override
  {
    ReadData();

    return std::to_string(DoWork2());
  }

  auto Test() -> bool override
  {
    return true;
  }
};
