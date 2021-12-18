#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class INumber
{
public:
  enum class Type
  {
    Regular = 0,
    Couple
  };

  virtual Type GetType() = 0;

  INumber* mParent{ nullptr };

  bool mReadLeft{ false };
};

class RegularNumber : public INumber
{
public:
  INumber::Type GetType() override { return INumber::Type::Regular;  }
  int mValue{ 0 };
};

class CoupleNumber : public INumber
{
public:
  INumber::Type GetType() override { return INumber::Type::Couple;  }

  INumber* left = nullptr;
  INumber* right = nullptr;
};

class Day18 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day18()= default;

  ~Day18() override = default;


  vector<CoupleNumber> cnums;
  vector<RegularNumber> rnums;
  vector<INumber*> nums;

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());

    cnums.reserve(100000);
    rnums.reserve(100000);

    for (auto d : mData)
    {
      stack<INumber*> numStack;
      for (char c : d)
      {
        if (c == '[')
        {
          cnums.push_back(CoupleNumber());
          INumber* newCouple = &cnums.back();
          numStack.push(newCouple);
        }
        else if (c == ']')
        {
          INumber* crtNum = numStack.top();
          assert(crtNum->GetType() == INumber::Type::Couple);
          CoupleNumber* cNum = static_cast<CoupleNumber*>(crtNum);
          numStack.pop();

          if (!numStack.empty())
          {
            INumber* parent = numStack.top();
            assert(parent->GetType() == INumber::Type::Couple);
            CoupleNumber* cParent = static_cast<CoupleNumber*>(parent);
            if (cParent->mReadLeft)
            {
              cParent->right = cNum;
            }
            else
            {
              cParent->left = cNum;
            }
            cNum->mParent = cParent;
          }
          else
          {
            nums.push_back(cNum);
          }
        }
        else if (c == ',')
        {
          INumber* crtNum = numStack.top();
          assert(crtNum->GetType() == INumber::Type::Couple);
          static_cast<CoupleNumber*>(crtNum)->mReadLeft = true;
        }
        else if (isdigit(c))
        {
          rnums.push_back(RegularNumber());
          RegularNumber* rNum = &rnums.back();
          rNum->mValue = c - '0';

          INumber* crtNum = numStack.top();
          assert(crtNum->GetType() == INumber::Type::Couple);
          CoupleNumber* cNum = static_cast<CoupleNumber*>(crtNum);
          if (cNum->mReadLeft)
          {
            cNum->right = rNum;
          }
          else
          {
            cNum->left = rNum;
          }
          rNum->mParent = cNum;
        }
        else
        {
          //assert(!"unsupported value");
        }
      }
    }
  }
  
  auto GetDay() -> string override
  {
    return "18";
  }

  RegularNumber* getLeftMostRegular(INumber* start)
  {
    if (start->GetType() == INumber::Type::Regular)
      return static_cast<RegularNumber *>(start);
    else if (start->GetType() == INumber::Type::Couple)
    {
      auto cNum = static_cast<CoupleNumber*>(start);
      return getLeftMostRegular(cNum->left);
    } else 
    return nullptr;
  }

  RegularNumber* getRightMostRegular(INumber* start)
  {
    if (start->GetType() == INumber::Type::Regular)
      return static_cast<RegularNumber*>(start);
    else if (start->GetType() == INumber::Type::Couple)
    {
      auto cNum = static_cast<CoupleNumber*>(start);
      return getRightMostRegular(cNum->right);
    }
    else
      return nullptr;
  }

  //unique_ptr<INumber> readNumber()

  bool explode(INumber* num, int depth = 0)
  {
    if (num->GetType() == INumber::Type::Couple)
    {
      auto cNum = static_cast<CoupleNumber*>(num);
      if (depth == 4 && cNum->left->GetType() == INumber::Type::Regular && 
                        cNum->right->GetType() == INumber::Type::Regular)
      {
        INumber* parent = num->mParent;
        if (parent != nullptr)
        {
          assert(parent->GetType() == INumber::Type::Couple);

          {
            INumber* searchNum = num;
            INumber* searchParent = parent;
            auto parentC = static_cast<CoupleNumber*>(parent);
            RegularNumber* searchedAtLeft = nullptr;

            if (parentC->left == num)
            {
              bool foundRightHook = false;
              while (searchParent && !foundRightHook)
              {
                if (searchParent->GetType() == INumber::Type::Couple &&
                  static_cast<CoupleNumber*>(searchParent)->right == searchNum)
                {
                  foundRightHook = true;
                  break;
                }

                searchNum = searchParent;
                searchParent = searchParent->mParent;
              }
              if (foundRightHook)
              {
                searchedAtLeft = getRightMostRegular(static_cast<CoupleNumber*>(searchParent)->left);
              }
            }
            else
            {
              searchedAtLeft = getRightMostRegular(static_cast<CoupleNumber*>(parentC)->left);
            }
            if (searchedAtLeft)
              searchedAtLeft->mValue += static_cast<RegularNumber*>(cNum->left)->mValue;
          }

          {
            INumber* searchNum = num;
            INumber* searchParent = parent;
            auto parentC = static_cast<CoupleNumber*>(parent);
            RegularNumber* searchedAtRight = nullptr;

            if (parentC->right == num)
            {
              bool foundLeftHook = false;
              while (searchParent && !foundLeftHook)
              {
                if (searchParent->GetType() == INumber::Type::Couple &&
                  static_cast<CoupleNumber*>(searchParent)->left == searchNum)
                {
                  foundLeftHook = true;
                  break;
                }
                searchNum = searchParent;
                searchParent = searchParent->mParent;
              }
              if (foundLeftHook)
              {
                searchedAtRight = getLeftMostRegular(static_cast<CoupleNumber*>(searchParent)->right);
              }
            }
            else
            {
              searchedAtRight = getLeftMostRegular(static_cast<CoupleNumber*>(parentC)->right);
            }
            if (searchedAtRight)
              searchedAtRight->mValue += static_cast<RegularNumber*>(cNum->right)->mValue;
          }

          // replace with zero
          rnums.push_back(RegularNumber());
          RegularNumber* rNum = &rnums.back();

          CoupleNumber* cParent = static_cast<CoupleNumber*>(parent);
          if (cParent->left == num)
            cParent->left = rNum;
          if (cParent->right == num)
            cParent->right = rNum;
          rNum->mParent = parent;

          return true;
        }
        return false;
      }
      else
      {
        bool left = explode(cNum->left, depth + 1);
        if (left) return true;
        bool right = explode(cNum->right, depth + 1);
        if (right) return true;
        return false;
      }
    }
    else
    {
      return false;
    }
  }

  bool split(INumber* num)
  {
    if (num->GetType() == INumber::Type::Regular)
    {
      auto rNum = static_cast<RegularNumber*>(num);
      if (rNum->mValue >= 10)
      {
        cnums.push_back(CoupleNumber());
        CoupleNumber* cNum = &cnums.back();
        cNum->mParent = num->mParent;

        rnums.push_back(RegularNumber());
        RegularNumber* rLeft = &rnums.back();
        rLeft->mValue = floor( (double)rNum->mValue / 2);
        rnums.push_back(RegularNumber());
        RegularNumber* rRight = &rnums.back();
        rRight->mValue = ceil( (double)rNum->mValue / 2);
        cNum->left = rLeft;
        cNum->right = rRight;
        rLeft->mParent = cNum;
        rRight->mParent = cNum;

        // replace in parent
        CoupleNumber* parent = static_cast<CoupleNumber *>(num->mParent);
        if (parent->left == num)
          parent->left = cNum;
        if (parent->right == num)
          parent->right = cNum;
        return true;
      }
      return false;
    }
    else
    {
      auto cNum = static_cast<CoupleNumber*>(num);
      bool left = split(cNum->left);
      if (left) return true;
      bool right = split(cNum->right);
      if (right) return true;
      return false;
    }
  }

  INumber* add(INumber* first, INumber* second)
  {
    cnums.push_back(CoupleNumber());
    CoupleNumber* cNum = &cnums.back();
    cNum->left = first;
    cNum->right = second;
    first->mParent = cNum;
    second->mParent = cNum;
    return cNum;
  }

  LL getMagnitude(INumber* num)
  {
    if (num->GetType() == INumber::Type::Regular)
    {
      return static_cast<RegularNumber*>(num)->mValue;
    }
    else
    {
      auto cNum = static_cast<CoupleNumber*>(num);
      LL lVal = getMagnitude(cNum->left);
      LL rVal = getMagnitude(cNum->right);
      return 3 * lVal + 2 * rVal;
    }
  }

  string printnum(INumber* num)
  {
    if (num->GetType() == INumber::Type::Regular)
    {
      return to_string(static_cast<RegularNumber*>(num)->mValue);
    }
    else
    {
      auto cNum = static_cast<CoupleNumber*>(num);
      INumber* left = cNum->left;
      INumber* right = cNum->right;
      return string("[") + printnum(left) + "," + printnum(right) + "]";
    }
  }

  void reduce(INumber* num)
  {
    while (true)
    {
      bool b1 = explode(num, 0);
      bool b2 = false;
      if (!b1)
      {
        b2 = split(num);
       // if (b2)
       //   cout << "Split " << printnum(num) << endl;
      }
      else
      {
       // cout << "Exploded " << printnum(num) << endl;
      }

      if (!b1 && !b2)
        break;
    }
  }

  auto DoWork1() -> LL
  {
    LL ret = 0;
    //explode(nums[0]);

   /* INumber* crtNum = nums[0];
   // cout << printnum(crtNum) << endl;
   // reduce(crtNum);
   // explode(crtNum, 0);
  //  cout << printnum(crtNum) << endl;

    for (int i : rangeint(1, nums.size() - 1))
    {
      cout << i << endl;
      crtNum = add(crtNum, nums[i]);
      cout << "Add " << printnum(crtNum) << endl;
     
      reduce(crtNum);
      cout << "Reduced " << printnum(crtNum) << endl;
    }*/

    LL maxM = -1;
    INumber* a = nums[0];
    INumber* b = nums[1];
    INumber* c = add(a, b);
    reduce(c);

    LL mag = getMagnitude(c);
    fprintf(R"(C:\Repos\aoc-2021\inputs\Day18\out.txt)", to_string(mag), true);

    /*for (int i : rangeint(0, nums.size() - 2))
    {
      for (int j : rangeint(i + 1, nums.size() - 1))
      {
        if (i == j) continue;

        INumber* a = nums[j];
        INumber* b = nums[i];
        INumber* c = add(a, b);
        reduce(c);

       // cout << "Reduced " << printnum(c) << endl;
        LL mag = getMagnitude(c);
        if (mag > maxM)
          maxM = mag;
      }
    }*/
    
    ret = maxM;
    //ret = getMagnitude(crtNum);

    cout << "Day18 " << mCurrentInput << " P1: " << ret << endl;

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
   // Part1();
    return true;
  }
};
