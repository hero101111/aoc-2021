#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day6 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day6(){ }

  ~Day6() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "6";
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
