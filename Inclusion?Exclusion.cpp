#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Function to find the prime factors of n
vector<int> primeFactors(int n) {
    vector<int> primes;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            primes.push_back(i);
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        primes.push_back(n); // n itself is a prime
    }
    return primes;
}

// Function to compute the count of numbers coprime with n in [a, b]
int coprimeCount(int a, int b, int n) {
    vector<int> primes = primeFactors(n);
    int total = b - a + 1; // Total numbers in the range [a, b]
    int m = primes.size();

    int count = 0;
    // Use bitmask to compute inclusion-exclusion
    for (int mask = 1; mask < (1 << m); ++mask) {
        int product = 1;
        int bits = __builtin_popcount(mask); // Count the number of set bits in the mask

        for (int i = 0; i < m; ++i) {
            if (mask & (1 << i)) {
                product *= primes[i];
                if (product > b) break; // Avoid overflow
            }
        }

        if (product > b) continue;

        // Count numbers divisible by product in [a, b]
        int divisible = (b / product) - ((a - 1) / product);

        // Add or subtract based on the number of factors in the subset
        if (bits % 2 == 1) {
            count += divisible; // Add for odd-sized subsets
        } else {
            count -= divisible; // Subtract for even-sized subsets
        }
    }

    return total - count;
}

int main() {
    int a, b, n;
    cout << "Enter a, b, n: ";
    cin >> a >> b >> n;

    int result = coprimeCount(a, b, n);
    cout << "Count of numbers coprime with " << n << " in [" << a << ", " << b << "] is: " << result << endl;

    return 0;
}
