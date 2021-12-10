#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day10 : public ISolutionDay
{
private:

  using DT = set<int>;
  vector<string> mData;

public:

  Day10(){ }

  ~Day10() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "10";
  }

  long DoWork1()
  {
    /*string text2 = RegexReplace(text, R"(\d)", "more than $1");
    auto [kv] = RegExMatch1(text, R"(we have (\d) monkeys)");
    fprintf(KVERBOSE, "hello man " + kv);
    fprintf(KVERBOSE, text2); */
    LL ret = 0;

    set<char> fs = { '(', '[', '{', '<' };
  
    for (auto d : mData)
    {
      bool isValid = true;

      stack<char> st;
      for (char c : d)
      {
        if (setContains(fs, c))
          st.push(c);
        else
        {
          char sTop = st.top();
          st.pop();
          if (sTop == '(' && c != ')')
          {
            isValid = false;
          }

          if (sTop == '{' && c != '}')
          {
            isValid = false;
          }
          if (sTop == '<' && c != '>')
          {
            isValid = false;
          }
          if (sTop == '[' && c != ']')
          {
            isValid = false;
          }
          if (!isValid && c == ')')
            ret += 3;
          if (!isValid && c == ']')
            ret += 57;
          if (!isValid && c == '}')
            ret += 1197;
          if (!isValid && c == '>')
            ret += 25137;          
        }
        if (!isValid)
          break;
      }

      if (!isValid)
      {
       // cout << d << endl;
        continue;
      }

    }
    cout << mCurrentInput << " P1 " << ret << endl;
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
    mCurrentInput = "test";
    Part1();
    return true;
  }
};
