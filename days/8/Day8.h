#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day8 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day8(){ }

  ~Day8() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "8";
  }
  
  set<char> fromS(string s)
  {
    set<char> ret;
    for (char c : s)
      ret.insert(c);
    return ret;
  }

  long DoWork1()
  {
    //    auto [x1, y1, x2, y2] = RegExMatch4(d, R"((\d+),(\d+) -> (\d+),(\d+))");
    unordered_map<char, unordered_set<char>> letters;
    letters['0'] = {'a', 'b', 'c', 'e', 'f', 'g'}; // t6
    letters['1'] = {'c', 'f'};                     // t2
    letters['2'] = {'a', 'c', 'd', 'e', 'g'};      // t5
    letters['3'] = {'a', 'c', 'd', 'f', 'g'};      // t5
    letters['4'] = {'b', 'c', 'd', 'f'};           // t4
    letters['5'] = {'a', 'b', 'd', 'f', 'g'};      // t5
    letters['6'] = {'a', 'b', 'd', 'e', 'f', 'g'}; // t6
    letters['7'] = {'a', 'c', 'f'};                // t3
    letters['8'] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'}; // t7
    letters['9'] = {'a', 'b', 'c', 'd', 'f', 'g'};      // t6
    
    LL ret = 0;
    for (auto d : mData)
    {
      auto data = tok(d, '|');
      auto randomData = data[0];
      auto outputValue = data[1];
      
      auto tokens = tok(randomData, ' ');
      auto outTokens = tok(outputValue, ' ');
      
      unordered_map<char, set<char>> mappings;
      vector<set<char>> allMappings;
      
      /*for (auto t : outTokens)
      {
        if (t.empty()) continue;
        //if (t.size() == 7) ret++; // 8
        //if (t.size() == 3) ret++; // 7
        //if (t.size() == 4) ret++; // 4
        
        // 1
        //if (t.size() == 2) ret++;
//        for (auto )
        auto mapp = fromS(t);
      }*/
      
      for (auto t : tokens)
      {
        auto mapp = fromS(t);
        
        allMappings.insert(end(allMappings), mapp);
        
        
        if (t.size() == 7) // 8
          mappings['8'] = mapp;
        if (t.size() == 3) // 7
          mappings['7'] = mapp;
        if (t.size() == 4) // 4
          mappings['4'] = mapp;
        if (t.size() == 2) // 1
          mappings['1'] = mapp;
      }
      
      char aMapping = ' ';
      for (auto l : mappings['7'])
        if (mappings['1'].find(l) == end(mappings['1']))
        {
          aMapping = l;
        }
      
      char cMapping = ' ';
      vector<set<char>> mapsWithCount6;
      for (auto mapp : allMappings)
      {
        if (mapp.size() == 6) // 0, 6  or 9
        {
          mapsWithCount6.push_back(mapp);
        }
      }
      vector<char> toRemove;
      for (char c : mapsWithCount6[0])
      {
        if (mapsWithCount6[1].find(c) != end(mapsWithCount6[1]) &&
            mapsWithCount6[2].find(c) != end(mapsWithCount6[2]))
        {
          toRemove.push_back(c);
        }
      }
      
      auto mapsWithCount6Reduced = mapsWithCount6;
      for (char c : toRemove)
        for (auto & m : mapsWithCount6Reduced)
          m.erase(c);
      
      for (int i = 0; i < mapsWithCount6Reduced.size(); ++i)
      {
        auto & mapp = mapsWithCount6Reduced[i];
        
        for (char c : mappings['1'])
        {
          if (mapp.find(c) != end(mapp))
          {
           // mappings['6'] = mapsWithCount6[i];
            cMapping = c;
          }
        }
      }
      
      char fMapping = ' ';
      for (char c : mappings['1'])
        if (c != cMapping)
          fMapping = c;
      
      char eMapping = ' ';
      // e is in only two of them
      vector<char> dOrE;
      
      for (auto mapp : mapsWithCount6Reduced)
      {
        bool hasC = mapp.find(cMapping) != end(mapp);
        if (hasC)
        {
          for (char c : mapp)
          {
            if (c != cMapping)
            {
              dOrE.push_back(c);
              // d or e, but e is NOT in 4
              if (mappings['4'].find(c) == end(mappings['4']))
                eMapping = c;
            }
          }
        }
      }
      
      char dMapping = ' ';
      for (auto c : dOrE)
        if (c != eMapping)
          dMapping = c;
      
      char bMapping = ' ';
      for (auto c : mappings['4'])
      {
        if (c != cMapping && c != dMapping && c != fMapping)
          bMapping = c;
      }
      
      char gMapping = ' ';
      for (auto c : mappings['8'])
      {
        if (c != aMapping && c != bMapping && c != cMapping && c != dMapping &&
            c != eMapping && c != fMapping)
        {
          gMapping = c;
        }
      }
      
      
      /*
       
       letters['0'] = {'a', 'b', 'c', 'e', 'f', 'g'}; // t6
       letters['1'] = {'c', 'f'};                     // t2
       letters['2'] = {'a', 'c', 'd', 'e', 'g'};      // t5
       letters['3'] = {'a', 'c', 'd', 'f', 'g'};      // t5
       letters['4'] = {'b', 'c', 'd', 'f'};           // t4
       letters['5'] = {'a', 'b', 'd', 'f', 'g'};      // t5
       letters['6'] = {'a', 'b', 'd', 'e', 'f', 'g'}; // t6
       letters['7'] = {'a', 'c', 'f'};                // t3
       letters['8'] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'}; // t7
       letters['9'] = {'a', 'b', 'c', 'd', 'f', 'g'};      // t6
       
       */
      mappings['0'] = {aMapping, bMapping, cMapping, eMapping, fMapping, gMapping};
      mappings['2'] = {aMapping, cMapping, dMapping, eMapping, gMapping};
      mappings['3'] = {aMapping, cMapping, dMapping, fMapping, gMapping};
      mappings['5'] = {aMapping, bMapping, dMapping, fMapping, gMapping};
      mappings['6'] = {aMapping, bMapping, dMapping, eMapping, fMapping, gMapping};
      mappings['9'] = {aMapping, bMapping, cMapping, dMapping, fMapping, gMapping};
      
      string num;
      for (auto tk : outTokens)
      {
        set<char> tkSet = fromS(tk);
        
        for (auto mapp : mappings)
        {
          if (mapp.second == tkSet)
          {
           // string s(1, mapp.first);
            num.push_back(mapp.first);
           // ret += stoi(s);
          }
        }
      }
      ret += stoi(num);
    /*  unordered_set<char> bdegMapping;
      for (auto l : mappings['8'])
      {
        if (l != aMapping && )
      }*/
    }
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
    return true;
  }
};
