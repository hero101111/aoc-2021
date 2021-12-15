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
        m.insertAt(genMap2, { x * (genMap2.max_x + 1),  y * (genMap2.max_y + 1) });

        genMap2.transform([&](Point p, int v)
          {
            return (v + 1) % 10 == 0 ? 1 : (v + 1);
          });
      }

      genMap.transform([&](Point p, int v)
        {
          return (v + 1) % 10 == 0 ? 1 : (v + 1);
        });
    }

    for (auto x : m.range_x())
    {
      for (auto y : m.range_y())
      {
        Point p(x, y);

        int vAtP = 0;

        if (!m.at(p, &vAtP))
          continue;

        int v = 0;
        Point toRight = p.Right();
        Point toDown = p.Down();
        if (m.at(toRight, &v))
        {
          g.AddEdge(p, toRight, v);
          g.AddEdge(toRight, p, vAtP);
        }
        if (m.at(toDown, &v))
        {
          g.AddEdge(p, toDown, v);
          g.AddEdge(toDown, p, vAtP);
        }
      }
    }

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
