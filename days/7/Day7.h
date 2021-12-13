#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day7 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day7(){ }

  ~Day7() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "7";
  }

  long DoWork1()
  {
    //    auto [x1, y1, x2, y2] = RegExMatch4(d, R"((\d+),(\d+) -> (\d+),(\d+))");
    
    //for (auto d : mData)
    //{
    //}
    vector<LL> inputs = stoll(tok(mData[0], ','));
    
    
    LL minChoice = numeric_limits<LL>::max();
    
    
    LL minV = *min_element(begin(inputs), end(inputs));
    LL maxV = *max_element(begin(inputs), end(inputs));
    for (auto el : rangeint(minV, maxV))
    {
      
    //LL minVal = *min_element(begin(inputs), end(inputs));
    
      LL t = 0;
      
      for (auto i : inputs)
      {
        t += (abs(el - i) * (abs(el - i) + 1))  / 2;
      }
        
        if (t < minChoice)
        {
          minChoice = t;
        }
    }
    
    cout << minChoice << endl;
    return minChoice;
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
