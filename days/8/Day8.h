#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day8 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day8(){ }

  ~Day8() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "8";
  }

  long DoWork1()
  {
    //    auto [x1, y1, x2, y2] = RegExMatch4(d, R"((\d+),(\d+) -> (\d+),(\d+))");
    unordered_map<char, unordered_set<char>> letters;
    letters['0'] = {'a', 'b', 'c', 'e', 'f', 'g'};
    letters['1'] = {'c', 'f'};
    letters['2'] = {'a', 'c', 'd', 'e', 'g'};
    letters['3'] = {'a', 'c', 'd', 'f', 'g'};
    letters['4'] = {'b', 'c', 'd', 'f'};
    letters['5'] = {'a', 'b', 'd', 'f', 'g'};
    letters['6'] = {'a', 'b', 'd', 'e', 'f', 'g'};
    letters['7'] = {'a', 'c', 'f'};
    letters['8'] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    letters['9'] = {'a', 'b', 'c', 'd', 'f', 'g'};
    
    LL ret = 0;
    for (auto d : mData)
    {
      auto data = tok(d, '|');
      auto randomData = data[0];
      auto outputValue = data[1];
      
      auto tokens = tok(randomData, ' ');
      auto outTokens = tok(outputValue, ' ');
      
      for (auto t : outTokens)
      {
        if (t.size() == 7) ret++; // 8
        if (t.size() == 3) ret++; // 7
        if (t.size() == 4) ret++; // 4
        
        // 1
        if (t.size() == 2) ret++;
//        for (auto )
      }
    }
    return ret;
  }

  long DoWork2()
  {

    return 0;
  }
  
  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork1());
  }

  string Part2() override
  {
    ReadData();

    return std::to_string(DoWork2());
  }

  bool Test() override
  {
    return true;
  }
};
