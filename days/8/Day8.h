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
              if (setContains(mapsWithCount6[1], c) && setContains(mapsWithCount6[2], c))
              {
                  toRemove.push_back(c);
              }
          }

          auto mapsWithCount6Reduced = mapsWithCount6;
          for (char c : toRemove)
              for (auto& m : mapsWithCount6Reduced)
                  m.erase(c);

          for (int i = 0; i < mapsWithCount6Reduced.size(); ++i)
          {
              auto& mapp = mapsWithCount6Reduced[i];

              for (char c : mappings['1'])
              {
                  if (mapp.find(c) != end(mapp))
                  {
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
                          if (!setContains(mappings['4'], c))
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

          mappings['0'] = { aMapping, bMapping, cMapping, eMapping, fMapping, gMapping };
          mappings['2'] = { aMapping, cMapping, dMapping, eMapping, gMapping };
          mappings['3'] = { aMapping, cMapping, dMapping, fMapping, gMapping };
          mappings['5'] = { aMapping, bMapping, dMapping, fMapping, gMapping };
          mappings['6'] = { aMapping, bMapping, dMapping, eMapping, fMapping, gMapping };
          mappings['9'] = { aMapping, bMapping, cMapping, dMapping, fMapping, gMapping };

          string num;
          for (auto tk : outTokens)
          {
              set<char> tkSet = fromS(tk);

              for (auto mapp : mappings)
                  if (mapp.second == tkSet)
                      num.push_back(mapp.first);

          }
          ret += stoi(num);
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
