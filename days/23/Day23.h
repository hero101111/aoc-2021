#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day23 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day23(){ }

  ~Day23() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "23";
  }

  LL DoWork1()
  {

    return 0;
  }

  LL DoWork2()
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
