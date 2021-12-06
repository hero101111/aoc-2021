#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day6 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day6(){ }

  ~Day6() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "6";
  }

  long DoWork1()
  {
    LL ret = 0;
    vector<LL> lanterns = stoll(tok(mData[0], ','));
    int day = 0;

    while (day < 256)
    {
      auto lant = lanterns;
      for (int i = 0; i < lant.size(); ++i)
      {
        if (lant[i] > 0)
        {
          lant[i] -= 1;
          lanterns[i] = lant[i];
        }
        else
        {
          lant[i] = 6;
          lanterns[i] = lant[i];
          lanterns.push_back(8);
        }
      }
     //  printvec(lanterns, cout);
      day++;
    }
    ret = lanterns.size();
   // fprintf(KVERBOSE, "hello");
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
