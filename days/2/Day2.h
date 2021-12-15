#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day2 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day2(){ }

  ~Day2() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "2";
  }

  LL DoWork1()
  {
    int horiz = 0;
    int depth = 0;
    
    for (auto l : mData)
    {
      auto tokens = tok(l);
      int value = stoi(tokens[1]);
      if (tokens[0] == "forward")
      {
        horiz+=value;
      }
      if (tokens[0] == "down")
      {
        depth+=value;
      }
      
      if (tokens[0] == "up")
      {
        depth-=value;
      }
    }
    return horiz * depth;
  }

  LL DoWork2()
  {
    int horiz = 0;
    int depth = 0;
    int aim = 0;
    
    for (auto l : mData)
    {
      auto tokens = tok(l);
      int value = stoi(tokens[1]);
      if (tokens[0] == "forward")
      {
        horiz+=value;
        depth += aim * value;
      }
      if (tokens[0] == "down")
      {
        aim+=value;
      }
      
      if (tokens[0] == "up")
      {
        aim-=value;
      }
    }
    return horiz * depth;
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
    mCurrentInput = "test";
    assert(Part1() == "150");
    assert(Part2() == "900");
    return true;
  }
};
