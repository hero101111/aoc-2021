#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day9 : public ISolutionDay
{
private:

  vector<string> mData;
  using DT = set<LL>;

public:

  Day9(){ }

  ~Day9() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "9";
  }

  long DoWork1()
  {
    LL ret = 0;
    DynamicMap<int> m;
    
    int crtLine = 0;
    for (auto d : mData)
    {
      int crtCol = 0;
      for (char c : d)
      {
        string strVal(1, c);
        int val = stoi(strVal);
        m[{crtCol, crtLine}] = val;
        crtCol += 1;
      }
      crtLine +=1;
    }
    //    auto [x1, y1, x2, y2] = RegExMatch4(d, R"((\d+),(\d+) -> (\d+),(\d+))");
    
      for (auto y : m.range_y())
    {
      for (auto x : m.range_x())
      {
        bool isLow = true;
        Point p{x, y};
        int crtVal = m[p];
        auto neigh = p.GetNeighbours();
        
       // vector<int> vals;
        
        for (auto n : neigh)
        {
          if (abs(n.x - x) + abs( n.y - y) > 1)
            continue;
          
          
          int nVal = 0;
          bool bb = m.at(n, &nVal);
          //vals.push_back(nVal);
          if (bb)
          {
            if (nVal <= crtVal)
              isLow = false;
          }
          else
            continue;
        }
        
        if (isLow)
          ret += crtVal + 1;
      }
    }
    cout <<ret << endl;
    return ret;
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
    mCurrentInput = "test";
    Part1();
    return true;
  }
};
