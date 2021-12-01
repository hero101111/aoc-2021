#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day1 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day1(){ }

  ~Day1() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "1";
  }

  long DoWork1()
  {
    LL ret = 0;
    LL prev = -1;
    for (auto d : mData)
    {
      LL dd = stoll(d);
      if (prev >= 0 && dd > prev )
        ret++;
     
      prev = stoll(d);
    }
    return ret;
  }

  long DoWork2()
  {
    vector<pair<int, LL>> windows;
    
    for (auto d : mData)
    {
      LL dd = stoll(d);
      
      for (auto & pp : windows)
      {
        if (pp.first < 3)
        {
          pp.second += dd;
        }
        pp.first += 1;
      }
      
      windows.push_back(make_pair(1, dd));
    }
    
    LL ret = 0, prev = -1;
    for (auto d : windows)
    {
      if (prev >= 0 && d.second > prev )
        ret++;
     
      prev = d.second;
    }
    windows.erase(windows.end() - 1);
    windows.erase(windows.end() - 1);
    return ret;
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
    return true;
  }
};
