#include "utility.h"

using namespace std;

inline bool IsNumber(char ch) {
    return ch >= '0' && ch <= '9';
}

inline bool IsOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^';
}

Suffix::Suffix(string& _s, bool& flag) {
    flag = 1;
    stack<char> SOptr;
    for (; !SOptr.empty(); SOptr.pop());
    map<char, int> prio;
    prio['='] = 1;
    prio['('] = prio[')'] = 2;
    prio['+'] = prio['-'] = 3;
    prio['*'] = prio['/'] = prio['%'] = 4;
    prio['^'] = 5;
    SOptr.push('=');
    vs.clear();
    string s = "", s1;
    char c, pre = '\0';
    int i = 0;
    for (char ch: _s) {
        i ++;
        if (ch == ' ') {
            continue;
        }
        if (IsNumber(ch) || ch == '.') {
            if (ch == '.' && pre == '.') {
                cout << "The expression is illegal!" << endl;
                flag = 0;
                return ;
            }
            s = s + ch;
        }
        else {
            if (s.length()) {
                vs.push_back(s);
                s = "";
            }
            if (ch == '=') {
                break;
            }
            if (ch == '(') {
                SOptr.push('(');
            }
            else if (ch == ')') {
                for (; (c = SOptr.top()) != '('; SOptr.pop()) {
                    vs.push_back(s1 = c);
                }
                if (SOptr.top() != '(') {
                    cout << "The expression is illegal!" << endl;
                    flag = 0;
                    return ;
                }
                SOptr.pop();
            }
            else {
                if (!IsNumber(pre) && pre != ')') {
                    if (ch != '-') {
                        cout << "The expression is illegal!" << endl;
                        flag = 0;
                        return ;
                    }
                    if (pre != '\0' && pre != '(') {
                        cout << "The expression is illegal!(A bracket is required before '-')" << endl;
                        flag = 0;
                        return ;
                    }
                    vs.push_back("0");
                }
                for (; prio[c = SOptr.top()] >= prio[ch]; SOptr.pop()) {
                    vs.push_back(s1 = c);
                }
                SOptr.push(ch);
            }
        }
        pre = ch;
    }
    if (s.length()) {
        vs.push_back(s);
    }
    if (i < _s.length()) {
        for (; i < s.length() && s[i] == ' '; i ++);
        if (i < s.length()) {
            cout << "The expression is illegal!" << endl;
            flag = 0;
            return ;
        }
    }
    for (; (c = SOptr.top()) != '=' && c != '('; SOptr.pop()) {
        vs.push_back(s1 = c);
    }
    if (c == '(') {
        cout << "The expression is illegal!" << endl;
        flag = 0;
    }
}

void Suffix::Display() {
    int sz = vs.size();
    for (int i = 0; i < sz - 1; i ++) {
        cout << vs[i] << " ";
    }
    cout << vs[sz - 1] << endl;
}

Calculator::Calculator() {
    res = 0;
}

double Calculator::Calc(string& _s) {
    stack<double> SOpnd;
    for (; !SOpnd.empty(); SOpnd.pop());
    bool flag;
    Suffix suff(_s, flag);
    if (!flag) {
        return -3;
    }
    res = 0;
    char ch;
    int i, sz;
    double val, bas, x1, x2;
    for (string& s: suff.vs) {
        if (s.length() == 1 && IsOperator(ch = s[0])) {
            switch (ch) {
                case '+': {
                    x2 = SOpnd.top(); SOpnd.pop();
                    x1 = SOpnd.top(); SOpnd.pop();
                    SOpnd.push(x1 + x2);
                    break;
                }
                case '-': {
                    x2 = SOpnd.top(); SOpnd.pop();
                    x1 = SOpnd.top(); SOpnd.pop();
                    SOpnd.push(x1 - x2);
                    break;
                }
                case '*': {
                    x2 = SOpnd.top(); SOpnd.pop();
                    x1 = SOpnd.top(); SOpnd.pop();
                    SOpnd.push(x1 * x2);
                    break;
                }
                case '/': {
                    x2 = SOpnd.top(); SOpnd.pop();
                    x1 = SOpnd.top(); SOpnd.pop();
                    if (x2 == 0) {
                        return -1;
                    }
                    SOpnd.push(x1 / x2);
                    break;
                }
                case '%': {
                    x2 = SOpnd.top(); SOpnd.pop();
                    x1 = SOpnd.top(); SOpnd.pop();
                    if (x2 == 0) {
                        return -1;
                    }
                    SOpnd.push(((int)x1) % ((int)x2));
                    break;
                }
                case '^': {
                    x2 = SOpnd.top(); SOpnd.pop();
                    x1 = SOpnd.top(); SOpnd.pop();
                    if (x1 == 0 && x2 == 0) {
                        return -2;
                    }
                    SOpnd.push((x1 == 0) ? 1: pow(x1, x2));
                    break;
                }
            }
        }
        else {
            val = 0;
            i = 0;
            for (ch: s) {
                i ++;
                if (ch == '.') {
                    break;
                }
                val = val * 10 + ch - '0';
            }
            if (i < (sz = s.length())) {
                for (bas = 0.1; i < sz; i ++) {
                    val = val + bas * (s[i] - '0');
                    bas /= 10;
                }
            }
            SOpnd.push(val);
        }
    }
    return res = SOpnd.top();
}

/*
123+45*(((4+7)-8*5)/33+21)*15
*/
