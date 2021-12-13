#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day11 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day11(){ }

  ~Day11() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "11";
  }

  long DoWork1()
  {
    LL ret = 0;
    
    DynamicMap<int> m;
    m.fromfile(GetInputPath(), [](char c)
               {
      string s(1, c);
      return stoi(s);
    });
    
    int steps = 0;
    LL flashes = 0;
    m.printf(KVERBOSE, ' ', true);
    while (steps < 100)
    {
      auto m2 = m;
      m2.for_each([&](Point p, int v){m2[p] += 1; return true;});
      
      bool flashed = true;
      while (flashed)
      {
        flashed = false;
        m2.for_each([&](Point p, int v)
        {
          bool skip = false;
          if (v == 0 && m[p] != 0)
            skip = true;
          
          if (!skip && v > 9)
          {
            m2[p] = 0;
            flashed = true;
            flashes++;
            auto neighs = p.GetNeighbours();
            for (auto n : neighs)
            {
              if (m2[n] == 0 && m[n] != 0)
                continue;
              
              m2[n] += 1;
            }
            m2.printf(KVERBOSE, ' ', true);
            int k = 0; k++;
          }
          return true;
        });
        
        m2.printf(KVERBOSE, ' ', true);
        
        int i = 0; ++i;
      }
      m = m2;
      steps++;
    }
    ret = flashes;
    cout << mCurrentInput << " P1: " << ret << endl;
//    cout << mCurrentInput << " P2: " << ret << endl;
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
