#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day15 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day15(){ }

  ~Day15() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "15";
  }

  LL DoWork1()
  {
    LL ret = 0;
    cout << "Day15 " << mCurrentInput << " P1: " << ret << endl;
    return ret;
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
    mCurrentInput = "test";
    //Part1();
    return true;
  }
};
