#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day22 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day22(){ }

  ~Day22() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "22";
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
