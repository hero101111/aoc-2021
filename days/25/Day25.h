#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day25 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day25(){ }

  ~Day25() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "25";
  }

  LL DoWork1()
  {
    LL ret = 0;
    DynamicMap<char> m;
    m.fromfile(GetInputPath());

    auto move = [&]() 
    {
      LL count = 0;

      auto m2 = m;
      m.for_eachYX([&](Point p, char c)
        {
          if (c == '>')
          {
            Point nextLocation = p.Right();
            if (nextLocation.x > m.max_x)
              nextLocation.x = m.min_x;

            if (m[nextLocation] == '.')
            {
              m2[nextLocation] = '>';
              m2[p] = '.';
              count += 1;
            }
          }
          return true;
        });
      m = m2;
      m2 = m;
      m.for_each([&](Point p, char c)
        {
          if (c == 'v')
          {
            Point nextLocation = p.Down();
            if (nextLocation.y > m.max_y)
              nextLocation.y = m.min_y;

            if (m[nextLocation] == '.')
            {
              m2[nextLocation] = 'v';
              m2[p] = '.';
              count += 1;
            }
          }
          return true;
        });
      m = m2;


      return count;
    };

    LL step = 0;

    //m.printf(KVERBOSE);
    while (true)
    {
      step += 1;
      auto changes = move();

     // m.printf(KVERBOSE, ' ', true);
      if (changes == 0)
        break;
    }
    ret = step;

    cout << "Day25 " << mCurrentInput << " P1: " << ret << endl;
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
  //  Part1();
    return true;
  }
};
