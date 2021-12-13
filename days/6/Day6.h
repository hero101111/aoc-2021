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
    list<LL> lan;
    for (int i = 0; i < lanterns.size(); ++i)
      lan.insert(end(lan), lanterns[i]);

    int day = 0;

    while (day < 256)
    {
      int lim = (int)lan.size();
      int crt = 0;
      for (auto it = lan.begin(); it != end(lan) && crt < lim; ++it, ++crt)
      {
        if (*it > 0)
        {
          *it -= 1;
        }
        else
        {
          *it = 6;
          lan.insert(end(lan), 8);
        }
      }
     //  printvec(lanterns, cout);
      day++;

      cout << day << " : " << lan.size() <<  endl;
    }
    ret = lan.size();
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
   // Part1();
    return true;
  }
};
