#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day5 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day5(){ }

  ~Day5() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "5";
  }

  LL DoWork(bool isPartOne)
  {
    DynamicMap<int> map; 
    for (auto d : mData)
    {
      auto [x1, y1, x2, y2] = RegExMatch4(d, R"((\d+),(\d+) -> (\d+),(\d+))");
      for (auto w : Point(x1, y1).GetTo(Point(x2, y2), isPartOne))
      {
        map[w] += 1;
      }
    }

    return map.for_each([](int v) { return v > 1; });
  }
  
  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork(true));
  }

  string Part2() override
  {
    ReadData();

    return std::to_string(DoWork(false));
  }

  bool Test() override
  {
    mCurrentInput = "test";
    //auto p1 = Part1();
    //p1;
    return true;
  }
};
