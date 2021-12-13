#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day4 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day4(){ }

  ~Day4() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "4";
  }
  
  bool setContains(set<LL> big, set<LL> small)
  {
    for (auto el : small)
    {
      if (big.find(el) == end(big))
        return false;
    }
    return true;
  }
  
  set<LL> getDifference(set<LL> a, set<LL> b)
  {
    set<LL> ret;
    for (auto el : a)
    {
      if (b.find(el) == end(b))
      {
        ret.insert(el);
      }
    }
    return ret;
  }
  
  set<LL> extract(DynamicMap<LL> m)
  {
    set<LL> ret;
    m.for_each([&](LL i){ret.insert(i); return true;});
    return ret;
  }
  
  set<LL> vec2set(vector<LL> v)
  {
    set<LL> ret;
    for (auto d : v)
      ret.insert(d);
    return ret;
  }

  LL DoWork1()
  {
    /*string text{"we have 5 monkeys"};
    string text2 = RegexReplace(text, R"(\d)", "more than $1");
    auto [kv] = RegExMatch1(text, R"(we have (\d) monkeys)");
    fprintf(KVERBOSE, "hello man " + kv);
    fprintf(KVERBOSE, text2);*/
    
    vector<LL> numbers;
    
    vector<DynamicMap<LL>> maps;
    
    DynamicMap<LL> currentMap;
    bool mapIsInit = false;
    
    bool readNumbers = false;
    
    LL crtLine = 0;
    for (auto d : mData)
    {
      if (!readNumbers)
      {
        numbers = stoll(tok(d, ','));
   
        readNumbers = true;
        continue;
      }
      if (d == "")
      {
        if (!mapIsInit)
          continue;
        
        if (mapIsInit)
          maps.push_back(currentMap);
        
        currentMap = DynamicMap<LL>();
        crtLine = 0;
      }
      vector<LL> crtLineItems = stoll(tok(d, ' '));
      for (LL i = 0; i < crtLineItems.size(); ++i)
      {
        currentMap[{i, crtLine}] = crtLineItems[i];
      }
      crtLine++;
      mapIsInit = true;
    }
    maps.push_back(currentMap);
    
    
    set<LL> extracted;
  
    set<int> bucket;
    for (int i = 0; i < (int)maps.size(); ++i)
      bucket.insert(i);
    
    bool foundSolution = false;
    
    while (extracted.size() < numbers.size())
    {
      if (!foundSolution)
        extracted.insert(numbers[extracted.size()]);
      
      foundSolution = false;
      size_t crtMapIndex = 0;
      
      for (auto b : bucket)
      {
        auto & currentMap = maps[b];
        
        for (auto line : currentMap.range_y())
        {
          auto lineItems = vec2set(currentMap.GetLine(line));
          if (setContains(extracted, lineItems))
          {
            set<LL> boardItems = extract(currentMap);
            set<LL> unmarked = getDifference(boardItems, extracted);
            LL sum = 0;
            for (auto ix : unmarked)
            {
              sum += ix;
            }
            
            auto val = sum * numbers[extracted.size() - 1];
            cout << b << " " << val << endl;
            if (val == 0)
            {
              int k = 0; ++k;
            }
            
            bucket.erase(b);
      
            foundSolution = true;
            break;
          }
        }
      
        if (!foundSolution)
        {
          for (auto column : currentMap.range_x())
          {
            auto columnItems = vec2set(currentMap.GetColumn(column));
            if (setContains(extracted, columnItems))
            {
              set<LL> boardItems = extract(currentMap);
              set<LL> unmarked = getDifference(boardItems, extracted);
              LL sum = 0;
              for (auto ix : unmarked)
              {
                sum += ix;
              }
              
              auto val = sum * numbers[extracted.size() - 1];
              cout << b << " " << val << endl;
              if (val == 0)
              {
                int k = 0; ++k;
              }
              
              foundSolution = true;
              
              bucket.erase(b);
              break;
              
            }
          }
        }
        
        if (foundSolution)
          break;
        else if (crtMapIndex == maps.size() - 1)
          break;
        else crtMapIndex++;
      }
    }
    
    
    return 123;
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
    //mCurrentInput = "test";
    //string part1 = Part1();
    //part1;
    return true;
  }
};
