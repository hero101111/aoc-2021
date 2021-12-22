#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day22 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day22()= default;

  ~Day22() override = default;

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  auto GetDay() -> string override
  {
    return "22";
  }

  struct Step
  {
    Point pMin, pMax;
    bool isOn;
  };

  auto DoWork1() -> LL
  {
    LL ret = 0;

    vector<Step> steps;
    for (auto d : mData)
    {
      auto [on, xMin, xMax, yMin, yMax, zMin, zMax] = RegExMatch7(d, R"((on|off) x=(-?\d+)..(-?\d+),y=(-?\d+)..(-?\d+),z=(-?\d+)..(-?\d+))");
      Step s;
      s.isOn = on == "on";
      s.pMin = { xMin, yMin, zMin };
      s.pMax = { xMax, yMax, zMax };
      steps.push_back(s);
    }

    for (auto s : steps)
    {
      string t = s.isOn ? "on " : "off ";
      cout << t << "x=" << s.pMin[0] << ".." << s.pMax[0] << ",y=" << s.pMin[1] << ".." << s.pMax[1] << ",z=" << s.pMin[2] << ".." << s.pMax[2] << endl;
    }


    unordered_map<Point, int> myMap;
    cout << steps.size() << " steps" << endl;
    int step = 0;
    for (auto s2 : steps)
    {
      cout << step++ << endl;
      Step s = s2;
      bool toBreak = false;

       for (auto x : rangeint(-50, 50))
         for (auto y : rangeint(-50, 50))
           for (auto z : rangeint(-50, 50))
           {
             if (x >= s.pMin.x && x <= s.pMax.x && y >= s.pMin.y && y <= s.pMax.y && z >= s.pMin.z && z <= s.pMax.z)
             {
               if (s.isOn)
               {
               //  m[{x, y, z}] = 1;
                 myMap[{x, y, z}] = 1;
               }
               else
               {
                // m[{x, y, z}] = 0;
                 myMap[{x, y, z}] = 0;
               }
             }
           }
      //LL p = m.for_each([](int v) { return v == 1; });
      //int k = 0; ++k;
    }
    
    ret = 0;
    for (auto p : myMap)
    {
      if (p.second == 1)
        ret++;
    }
    cout << "Day22 " << mCurrentInput << " P1: " << ret << endl;
    return ret;
  }

  auto DoWork2() -> LL
  {
    vector<Step> cubes;

    int c = 0;
    for (auto d : mData)
    {
      c++;

      //if (c == 150)
      //  break;
     // cout << c << endl;
      auto [on, xMin, xMax, yMin, yMax, zMin, zMax] = RegExMatch7(d, R"((on|off) x=(-?\d+)..(-?\d+),y=(-?\d+)..(-?\d+),z=(-?\d+)..(-?\d+))");
      Step readCube;
      readCube.isOn = on == "on";
      readCube.pMin = { xMin, yMin, zMin };
      readCube.pMax = { xMax, yMax, zMax };

      vector<Step> subCubes;
      for (auto existingCube : cubes)
      {
        bool sharesSpace = true;
        for (int i : rangeint(0, 2))
          sharesSpace &= (readCube.pMin[i] <= existingCube.pMax[i] && readCube.pMax[i] >= existingCube.pMin[i]);

        if (!sharesSpace)
          subCubes.push_back(existingCube);
        else
        {
          // go to splitting this baby up

          for (auto i : rangeint(0, 2))
          {
            if (existingCube.pMin[i] <= readCube.pMin[i])
            {
              Step newCube = existingCube;
              newCube.pMax[i] = readCube.pMin[i] - 1;
              existingCube.pMin[i] = readCube.pMin[i];
              subCubes.push_back(newCube);
            }
            if (existingCube.pMax[i] >= readCube.pMax[i])
            {
              Step newCube = existingCube;
              newCube.pMin[i] = readCube.pMax[i] + 1;
              existingCube.pMax[i] = readCube.pMax[i];
              subCubes.push_back(newCube);
            }
          }
        }
      }

      subCubes.push_back(readCube);

      cubes = subCubes;
      //cout << cubes.size() << endl;
    }

    LL ret = 0;
    for (auto c : cubes)
    {
      if (c.isOn)
      {
        LL r = 1;
        for (int i : rangeint(0, 2))
          r *= (c.pMax[i] - c.pMin[i] + 1);
        ret += r;
      }
      else
      {
        //assert(false);
      }
    }

    return ret;
  }
  
  auto Part1() -> string override
  {
    ReadData();

    return std::to_string(DoWork1());
  }

  auto Part2() -> string override
  {
    ReadData();

    return std::to_string(DoWork2());
  }

  auto Test() -> bool override
  {
    mCurrentInput = "test";
   // Part1();
    return true;
  }
};
