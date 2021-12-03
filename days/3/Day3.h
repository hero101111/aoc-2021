#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day3 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day3(){ }

  ~Day3() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "3";
  }

  long DoWork1()
  {
    int total = 0;
    unordered_map<int, int> oneCounts;
    unordered_map<int, int> zeroCounts;
    for (auto d : mData)
    {
      total +=1;
      for (size_t i = 0; i < d.size(); ++i)
      {
        char c = d[i];
        if (c == '1')
          oneCounts[i] += 1;
        else
          zeroCounts[i] +=1;
      }
    }
    
    string gamma;
    string epsilon;
    for (size_t i = 0; i < 12; ++i)
    {
      if (oneCounts[i] >= total / 2)
      {
        gamma += "1";
        epsilon += "0";
      }
      else
      {
        gamma += "0";
        epsilon += "1";
      }
    }
    
    bitset<12> gammaBin(gamma);
    bitset<12> epsilonBin(epsilon);
    int gammaV = gammaBin.to_ulong(), epsilonV = epsilonBin.to_ulong();
    
    return gammaV * epsilonV;
  }

  long DoWork2()
  {
    int total = 0;
    
    vector<string> filtered = mData;
    
    while (filtered.size() > 1)
    {
      
      for (size_t i = 0; i < 12; ++i)
      {
        vector<string> filtered2;
        int oneCounts = 0, zeroCounts = 0;
        for (auto d : filtered)
        {
          total +=1;
       
            char c = d[i];
            if (c == '1')
              oneCounts += 1;
            else
              zeroCounts += 1;
          
        }
      
        for (auto d : filtered)
        {
          char bitSearched = '1';
          if (oneCounts > zeroCounts)
          {
          }
          if (zeroCounts > oneCounts)
          {
            bitSearched = '0';
          }
          if (d[i] == bitSearched)
          {
            filtered2.push_back(d);
          }
        }
        filtered = filtered2;
      }
    }
  string oxygenRating = filtered[0];
    
    
    
    filtered = mData;
    
    while (filtered.size() > 1)
    {
      
      for (size_t i = 0; i < 12; ++i)
      {
        vector<string> filtered2;
        int oneCounts = 0, zeroCounts = 0;
        for (auto d : filtered)
        {
          total +=1;
       
            char c = d[i];
            if (c == '1')
              oneCounts += 1;
            else
              zeroCounts += 1;
          
        }
      
        for (auto d : filtered)
        {
          char bitSearched = '0';
          if (oneCounts > zeroCounts)
          {
          }
          if (zeroCounts > oneCounts)
          {
            bitSearched = '1';
          }
          if (d[i] == bitSearched)
          {
            filtered2.push_back(d);
          }
        }
        filtered = filtered2;
      }
    }
  string scrubber = filtered[0];
    
    
    bitset<12> gammaBin(oxygenRating);
    bitset<12> epsilonBin(scrubber);
    int gammaV = gammaBin.to_ulong(), epsilonV = epsilonBin.to_ulong();
    
    return gammaV * epsilonV;
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
    //assert(Part1() == "150");
    //assert(Part2() == "900");
    return true;
  }
};
