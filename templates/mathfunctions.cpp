#include <iostream>

using namespace std;

/**
* A collection of constant memory math functions
*/

long long fastPow(long long base, long long power, long long mod) {
    long long ret = 1;
    while (power > 0) {
        if (power & 1) ret = (ret * base) % mod;
        base = (base * base) % mod;
        power >>= 1;
    }
    return ret;
}

bool isPrime(int x) {
    if (x & 1) {
        if (x == 1) return 0;
        for (int i = 3; i * i <= x; i += 2) {
            if (x % i == 0) return 0;
        }
        return 1;
    } else return x == 2;
}

int main() {
    cout << fastPow(4,12,1000000007) << '\n';
    // ans = 16777216
    cout << fastPow(4, 12, 107) << '\n';
    // ans = 44
    cout << isPrime(131) << '\n';
    // ans = 1
    cout << isPrime(24) << '\n';
    // ans = 0;
}