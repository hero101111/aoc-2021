#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day1 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day1(){ }

  ~Day1() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "1";
  }

  long DoWork1()
  {
    return 0;
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
