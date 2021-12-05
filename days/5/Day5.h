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

  bool intersects(int x1, int y1, int x2, int y2)
  {

  }
  LL DoWork1()
  {

    LL ret = 0;

    DynamicMap<int> map;

    for (int i : rangeint(0, 10))
    {
      for (int j : rangeint(0, 10))
      {
        map[{i, j}] = 0;
      }
    }
    for (auto d : mData)
    {
      auto [x1s, y1s, x2s, y2s] = RegExMatch4(d, R"((\d+),(\d+) -> (\d+),(\d+))");
      int x1 = stoi(x1s);
      int y1 = stoi(y1s);
      int x2 = stoi(x2s);
      int y2 = stoi(y2s);

      if (y1 == y2)
      {
        //if (y1 == 4) { cout << "QQQQ " << x1 << " " << x2 << endl; }
        for (int x = min(x1, x2); x <= max(x1, x2); ++x)
        {
          int v = map[{x, y1}];
          map[{x, y1}] = 1 + v;
        }

      }
      else if (x1 == x2)
      {
        for (int y = min(y1, y2); y <= max(y1, y2); ++y)
        {
          int v = map[{x1, y}];
          map[{x1, y}] = 1 + v;
        }
      }
      else if (x1 > x2 && y1 > y2)
      {
        for (int x = x2,  y = y2; y <= y1; ++y, ++x)
        {
          map[{x, y}] += 1;
        }
      }
      else if (x1 < x2 && y1 > y2)
      {
        for (int x = x1,  y = y1; x <= x2; --y, ++x)
        {
          map[{x, y}] += 1;
        }
      }
      else if (x1 < x2 && y1 < y2)
      {
        for (int x = x1,  y = y1; y <= y2; ++y, ++x)
        {
          map[{x, y}] += 1;
        }
      }
      else if (x1 > x2 && y1 < y2)
      {
        for (int x = x2,  y = y2; x <= x1; --y, ++x)
        {
          map[{x, y}] += 1;
        }
      }


      //cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    }

    map.printf(KVERBOSE);
    ret = map.for_each([](int v) { return v > 1; });
    //cout << ret << endl;
    //system("PAUSE");
    //fprintf(KVERBOSE, "ffffff");
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
    //auto p1 = Part1();
    //p1;
    return true;
  }
};
