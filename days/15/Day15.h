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
    Graph<Point> g(100*100*25);

    DynamicMap<int> smallMap;
    smallMap.fromfile(GetInputPath(), [](char c) { return c - '0'; });

    DynamicMap<int> m;
    DynamicMap<int> genMap = smallMap;
  
    for (int y : rangeint(0, 4))
    {
      DynamicMap<int> genMap2 = genMap;
      for (int x : rangeint(0, 4))
      {        
        genMap2.for_each([&](Point p, int v)
          {
            m[{p.x + x * (genMap2.max_x + 1), p.y + y * (genMap2.max_y + 1)}] = v;
            genMap2[p] = (v + 1) % 10 == 0 ? 1 : (v + 1);
            return true;
          });
      }

      genMap.for_each([&](Point p, int v)
        {
          genMap[p] = (v + 1) % 10 == 0 ? 1 : (v + 1);          

          return true;
        });
    }

    g.FromDynamicMap(m);

    auto walk = g.GetShortestPath(Point(m.min_x, m.min_y), Point(m.max_x, m.max_y));
    
    for (auto w : walk)
      ret += m[w];

    ret -= m[walk[0]];

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
    Part1();
    return true;
  }
};
