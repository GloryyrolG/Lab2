#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <bits/stdc++.h>

using namespace std;

class Calculator;

class Suffix {
    friend class Calculator;

    private:
        vector<string> vs;

    public:
        Suffix(string& _s, bool& flag);
        void Display();
};

class Calculator {
    private:
        double res;

    public:
        Calculator();
        double Calc(string& _s);
};

inline bool IsNumber(char ch);

inline bool IsOperator(char ch);

#endif
