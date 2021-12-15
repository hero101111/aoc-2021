#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day13 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day13(){ }

  ~Day13() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "13";
  }

  LL DoWork1()
  {
    LL ret = 0;

    DynamicMap<char> m;

    bool beginFold = false;
    for (auto d : mData)
    {
      if (d == "")
      {
        beginFold = true;
        continue;
      }

      if (!beginFold)
      {
        auto tokens = stoll(tok(d, ','));
        m[{tokens[0], tokens[1]}] = '#';
      }
      else
      {
        auto [axis, howMuch] = RegExMatch2(d, R"(fold along (x|y)=(\d+))");

        if (axis == "x")
        {
          LL hM = stoll(howMuch);
          
          for (LL i = hM; i <= m.max_x; ++i)
          {
            for (auto y : m.range_y())
            {
              char t = '.';
              m.at({ i, y }, &t);
              if (t == '#')
              {
                m[{2 * hM - i, y}] = t;
              }
              m[{i, y}] = '.';
            }
          }
        }
        if (axis == "y")
        {
          LL hM = stoll(howMuch);

          for (auto x : m.range_x())
          {
            for (LL i = hM; i <= m.max_y; ++i)
            {
                char t = '.';
                m.at({ x, i }, &t);
                if (t == '#')
                {
                  m[{x, 2 * hM - i}] = t;
                }
                m[{x, i}] = '.';
            }
          }
        }
        
        DynamicMap<char> m2;
        m.for_each([&](Point p, char c)
        {
          if (c == '#')
            m2[p] = c;
          return true;
        });
        m = m2;
      }
    }

    ret = m.for_each([](char b) { return b == '#'; });
    m.printf(KVERBOSE, '.', true);

    cout << mCurrentInput << " P1: " << ret << endl;
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
   // Part1();
    return true;
  }

};
