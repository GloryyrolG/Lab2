#include "utility.h"

using namespace std;

const int maxn = 110;

int main() {
    ios::sync_with_stdio(0);
    char con;
    int res;
    string s;
    char str[maxn];
    Calculator c;
    for (; 1; ) {
        cout << "Please input expression(without blanks like 'a+b='): ";
        cin.getline(str, 100);
        s = str;
        res = c.Calc(s);
        if (res == -1) {
            cout << "The divisor can not be '0'!" << endl;
        }
        else if (res == -2) {
            cout << "'0^0' is undefined!" << endl;
        }
        else if (res == -3) {
        }
        else {
            cout << "The answer is ";
            cout.precision(10);
            cout << fixed << c.Calc(s) << endl;
        }
    }
    return 0;
}
