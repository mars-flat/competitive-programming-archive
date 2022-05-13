#include <iostream>

using namespace std;

/**
* N Choose K modulo P in constant time with preprocessing
*/

int const MN = 1000000;
int const MOD = 1000000007;

// fastpow function
long long fastPow(long long base, long long power, long long mod) {
    long long ret = 1;
    while (power > 0) {
        if (power & 1) ret = (ret * base) % mod;
        base = (base * base) % mod;
        power >>= 1;
    }
    return ret;
}

// factorial and inverse lookup tables
long long fact[MN+5], inv[MN+5];

// build
void build() {
    fact[1] = inv[1] = 1;
    for (int i = 2; i <= 1000000; ++i) {
        fact[i] = (fact[i-1] * i) % MOD;

        // some random math property states that
        // i can raise fact[i] to MOD-2 mod MOD
        // to get the inverse :blobspin:
        inv[i] = fastPow(fact[i], MOD-2, MOD);
    }
}

long long choose(int n, int k) {
    return fact[n] * inv[k] % MOD * inv[n-k] % MOD;
}

int main() {
    build();
    cout << choose(10, 3) << '\n';
    // ans = 120
}
