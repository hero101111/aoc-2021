#pragma once

#include "SolutionDay.h"
#include "util/util.h"

struct WorldView
{
  Point forwards;
  Point upwards;
  Point rightside;
};

class Scanner
{
public:
  int id{ 0 };
  unordered_set<Point> beacons;
  Point location;

  auto transformBeacons(WorldView worldView) -> unordered_set<Point>
  {
    auto transformPoint = [](Point p, WorldView worldLine) -> Point
    {
      auto pxw1 = worldLine.forwards * p.x;
      auto pyw2 = worldLine.upwards * p.y;
      auto pzw3 = worldLine.rightside * p.z;
      Point ret = { pxw1[0] + pyw2[0] + pzw3[0], pxw1[1] + pyw2[1] + pzw3[1] , pxw1[2] + pyw2[2] + pzw3[2] };
      return ret;
    };
    unordered_set<Point> ret;
    for (auto b : beacons)
    {
      Point transformed = transformPoint(b, worldView);
      ret.insert(transformed);
    }
    return ret;
  }

};

class Day19 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day19()= default;

  ~Day19() override = default;

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  auto GetDay() -> string override
  {
    return "19";
  }

  static auto getWorldViews() -> vector<WorldView>
  {
    vector<WorldView> worlds;
    vector<Point> directions =
    {
      { 1,  0,  0},
      {-1,  0,  0},
      { 0,  1,  0},
      { 0, -1,  0},
      { 0,  0,  1},
      { 0,  0, -1}
    };

    int totalWorlds = 0;
    for (auto facing : directions)
    {
      for (auto upwards : directions)
      {
        if ((facing + upwards) != Point{ 0, 0, 0 } && (facing - upwards) != Point{ 0, 0, 0 })
        {
          auto rightside = facing.crossProduct(upwards);
          totalWorlds++;
          worlds.push_back({facing, upwards, rightside});
        }
      }
    }
    assert(totalWorlds == 24);

    return worlds;
  }


  auto DoWork1() -> LL
  {
    LL ret = 0;

    vector<Scanner> scanners;

    int crtScannerId = -1;
    Scanner crtScanner;
    for (auto d : mData)
    {
      if (d.empty()) {
        continue;
}
      if (d[0] == '-' && d[1] == '-')
      {
        if (crtScannerId >= 0) {
          scanners.push_back(crtScanner);
}
        
        crtScanner = Scanner();
        crtScanner.id = ++crtScannerId;
      }
      else
      {
        Point p = Point::Parse(d);
        crtScanner.beacons.insert(p);
      }
    }
    scanners.push_back(crtScanner);

    unordered_set<Point> worldBeacons;
    unordered_set<int> unlockedScanners;
    unlockedScanners.insert(0);
    for (auto b : scanners[0].beacons) {
      worldBeacons.insert(b);
}

    auto worlds = getWorldViews();

    set<pair<int, int>> checkedPairs;

    bool isDirty = false;
    do
    {
      isDirty = false;
      for (auto scannerBase = begin(unlockedScanners); scannerBase != end(unlockedScanners); ++scannerBase)
      {
        for (int scannerSeek = 0; scannerSeek < scanners.size(); scannerSeek++)
        {
          if (scannerSeek == *scannerBase) {
            continue;
}
          if (unlockedScanners.find(scannerSeek) != end(unlockedScanners)) {
            continue;
}
          if (checkedPairs.find(make_pair(*scannerBase, scannerSeek)) != end(checkedPairs)) {
            continue;
}

          if (*scannerBase == 1 && scannerSeek == 4)
          {
            int k = 0; ++k;
          }

          checkedPairs.insert(make_pair(*scannerBase, scannerSeek));

          auto& baseScanner = scanners[*scannerBase];
          auto& otherScanner = scanners[scannerSeek];

          int crtWorld = 0;
          int maxDiff = -1;
          for (auto world : worlds)
          {
            crtWorld++;
            auto otherBeaconsTransformed = otherScanner.transformBeacons(world);

            for (auto baseBeacon : baseScanner.beacons)
            {
              for (auto otherBeacon : otherBeaconsTransformed)
              {
                //Point worldDelta = baseBeacon - *otherBeaconsTransformed.begin();

                Point worldDelta = baseBeacon - otherBeacon;

                if (*scannerBase == 1 && scannerSeek == 4 && worldDelta == Point{ -20, -1133, 1061 })
                {
                int pp = 1; pp++;
                }
                unordered_set<Point> transformedWithDelta;
                for (auto b : otherBeaconsTransformed) {
                  transformedWithDelta.insert(b + worldDelta);
}

                LL diffCount = getSetEqCount(transformedWithDelta, baseScanner.beacons);
                if (diffCount > maxDiff) {
                  maxDiff = diffCount;
}

                if (diffCount >= 12)
                {
                  cout << "YO " << endl << endl;
                  for (auto b : transformedWithDelta)
                  {
                    worldBeacons.insert(b);
                    //cout << b.ToString3() << endl;
                  }


                  otherScanner.beacons = transformedWithDelta;

                  //for (auto b : transformedWithDelta)
                  //  cout << b.ToString3() << endl;

                 // for (auto b : scanners[1].beacons)
                //    cout << b.ToString3() << endl;


                  otherScanner.location = worldDelta;

                  unlockedScanners.insert(scannerSeek);


                  cout << "Unlocked scanner " << scannerSeek << endl;

                  isDirty = true;

                  break;
                }
                if (isDirty) {
                  break;
}
              }
              if (isDirty) {
                break;
}
            }
            if (isDirty) {
              break;
}
          }
          if (isDirty) {
            break;
}
        }
        if (isDirty) {
          break;
}
      }

    } while (isDirty);

     for (auto b : worldBeacons) {
       cout << b.ToString3() << endl;
}
    
     ret = worldBeacons.size();

     cout << "Day19 " << mCurrentInput << " P1: " << ret << endl;
     LL maxManh = -1;
     for (auto scanner1 : scanners)
     {
       for (auto scanner2 : scanners)
       {
         if (scanner1.id != scanner2.id)
         {
           LL manh = scanner1.location.ManhattanDist(scanner2.location);
           if (manh > maxManh) {
             maxManh = manh;
}
         }
       }
     }
     ret = maxManh;

    cout << "Day19 " << mCurrentInput << " P2: " << ret << endl;
    return ret;
  }

  static auto DoWork2() -> LL
  {

    return 0;
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
    Part1();
    return true;
  }
};
