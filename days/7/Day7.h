#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day7 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day7(){ }

  ~Day7() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "7";
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
