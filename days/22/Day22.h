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

  struct Cuboid
  {
    Point pMin, pMax;
    bool isOn;
  };

  auto DoWork1() -> LL
  {
    vector<Cuboid> steps;
    for (auto d : mData)
    {
      auto [on, xMin, xMax, yMin, yMax, zMin, zMax] = RegExMatch7(d, R"((on|off) x=(-?\d+)..(-?\d+),y=(-?\d+)..(-?\d+),z=(-?\d+)..(-?\d+))");
      Cuboid s;
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
      Cuboid s = s2;
      bool toBreak = false;

       for (auto x : rangeint(-50, 50))
         for (auto y : rangeint(-50, 50))
           for (auto z : rangeint(-50, 50))
             if (x >= s.pMin.x && x <= s.pMax.x && y >= s.pMin.y && y <= s.pMax.y && z >= s.pMin.z && z <= s.pMax.z)
               s.isOn = myMap[{x, y, z}] = 1;
    }
    
    LL ret = 0;
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
    vector<Cuboid> cuboids;

    for (auto d : mData)
    {
      auto [on, xMin, xMax, yMin, yMax, zMin, zMax] = RegExMatch7(d, R"((on|off) x=(-?\d+)..(-?\d+),y=(-?\d+)..(-?\d+),z=(-?\d+)..(-?\d+))");
      Cuboid readCuboid;
      readCuboid.isOn = on == "on";
      readCuboid.pMin = { xMin, yMin, zMin };
      readCuboid.pMax = { xMax, yMax, zMax };

      vector<Cuboid> subCuboids;
      for (auto existingCuboid : cuboids)
      {
        bool sharesSpace = true;
        for (int i : rangeint(0, 2))
          sharesSpace &= (readCuboid.pMin[i] <= existingCuboid.pMax[i] && readCuboid.pMax[i] >= existingCuboid.pMin[i]);

        if (!sharesSpace)
          subCuboids.push_back(existingCuboid);
        else
        {
          // get to splitting this baby up
          for (auto i : rangeint(0, 2))
          {
            if (existingCuboid.pMin[i] <= readCuboid.pMin[i])
            {
              Cuboid newCube = existingCuboid;
              newCube.pMax[i] = readCuboid.pMin[i] - 1;
              existingCuboid.pMin[i] = readCuboid.pMin[i];
              subCuboids.push_back(newCube);
            }
            if (existingCuboid.pMax[i] >= readCuboid.pMax[i])
            {
              Cuboid newCube = existingCuboid;
              newCube.pMin[i] = readCuboid.pMax[i] + 1;
              existingCuboid.pMax[i] = readCuboid.pMax[i];
              subCuboids.push_back(newCube);
            }
          }
        }
      }
      subCuboids.push_back(readCuboid);

      cuboids = subCuboids;
    }

    LL ret = 0;
    for (auto c : cuboids)
    {
      if (c.isOn)
      {
        LL r = 1;
        for (int i : rangeint(0, 2))
          r *= (c.pMax[i] - c.pMin[i] + 1);
        ret += r;
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
