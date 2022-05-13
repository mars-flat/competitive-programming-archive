// author: Shane Chen (MarsFlat)
// concepts: bitwise math

#include <iostream>
#include <bitset>

using namespace std;

#define boost() ios_base::sync_with_stdio(false); cin.tie(NULL);
#define SZ 100001

bitset<SZ> cur, nxt;
long long n, t;

int main() {
    boost();
    cin >> n >> t;
    bitset<50> dt (t);
    
    for (int i = n-1; i >= 0; --i) {
        char c; cin >> c;
        cur[i] = c == '1' ? 1 : 0;
    }

    for (int i = 49; i >= 0; --i) {
        if (dt[i]) {
            int k = (1ULL << i) % n; 
            for (int j = n-1; j >= 0; --j) {
                nxt[j] = cur[(j + k) % n] ^ cur[(j + ((n - k) % n)) % n]; 
            }
            swap(cur, nxt);
        }
    }   

    for (int j = n-1; j >= 0; --j) {
        cout << cur[j];
    }
}
