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

  long DoWork1()
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

        m.printf(KVERBOSE, '.');

        auto [axis, howMuch] = RegExMatch2(d, R"(fold along (x|y)=(\d+))");

        if (axis == "x")
        {
          int hM = stoi(howMuch);
          int offset = 0;
          for (int i = hM; i <= m.max_x; ++i)
          {
            for (auto y : m.range_y())
            {
              char t = '.';
              m.at({ i, y }, &t);
              if (t == '#')
              {
                m[{hM - offset, y}] = t;
              }
              m[{i, y}] = '.';
            }
            offset++;
          }
          break;
        }
        if (axis == "y")
        {
          int hM = stoi(howMuch);
          int offset = 0;

          m[{4, 6}] = '@';
          for (auto x : m.range_x())
          {
            for (int i = hM; i <= m.max_y; ++i)
            {
                char t = '.';
                m.at({ x, i }, &t);
                if (t == '#')
                {
                  m[{x, hM - offset}] = '@';
                }
                m[{x, i}] = '/';
            }
            offset++;
          }
          break;
        }
      }
    }

    ret = m.for_each([](char b) { return b == '#'; });
    m.printf(KVERBOSE, '.', true);

    cout << mCurrentInput << " P1: " << ret << endl;
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
