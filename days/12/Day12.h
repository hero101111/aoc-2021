#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day12 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day12(){ }

  ~Day12() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "12";
  }

  set<string> choseTwice;

  void explore(unordered_map<string, unordered_set<string>> & links,
    vector<string> crtNodes, vector<vector<string>> & paths, string dup)
  {
    string crtNode = crtNodes.back();
    if (crtNode == "end")
    {
      paths.push_back(crtNodes);
      return;
    }

    auto nodeLinks = links[crtNode];
    for (auto nl : nodeLinks)
    {
      if (islower(nl[0]))
      {
        // visit at most once
        size_t visitedCount = count(begin(crtNodes), end(crtNodes), nl);

        if (nl == "start")
        {
          int i = 0; ++i;
        }
        
        bool alreadyVisited = visitedCount > 0;

        if (dup == nl && visitedCount >= 2)
          continue;

        if (dup != nl && visitedCount >= 1)
          continue;
      }
      auto nodes = crtNodes;
      nodes.push_back(nl);
      explore(links, nodes, paths, dup);
    }
  }

  LL DoWork1()
  {
    LL ret = 0;

    unordered_map<string, unordered_set<string>> links;


    for (auto d : mData)
    {
      auto tokens = tok(d, '-');
      string first = tokens[0];
      string second = tokens[1];
      auto& me = links[first];
      me.insert(end(me), second);

      auto& em = links[second];
      em.insert(end(em), first);
    }

    vector<vector<string>> paths;
    vector<string> crtPath{ "start" };
    
    vector<string> smalls;
    for (auto d : links)
    {
      if (islower(d.first[0]) && d.first != "start" && d.first != "end")
      {
        smalls.push_back(d.first);
      }
    }
    for (auto s : smalls)
      explore(links, crtPath, paths, s);

    set<string> uniquePaths;
    for (auto p : paths)
      uniquePaths.insert(join(p));
    ret = uniquePaths.size();

    for (auto v : uniquePaths)
    {
      
      //cout << endl;
    }
    cout << mCurrentInput << " P1: " << ret << endl;
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
    Part1();
    return true;
  }
};
