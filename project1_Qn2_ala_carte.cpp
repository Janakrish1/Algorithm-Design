#include "bits/stdc++.h"
using namespace std;

/*
* Time Complexity - O(log(num2))
* Space Complexity - O(1)
*/
long long alaCarteMultiplication(long long num1, long long num2) {
    long long ans = 0;
    bool isNeg1 = false, isNeg2 = false;
    if(num1 < 0)
        isNeg1 = true;
    if(num2 < 0)
        isNeg2 = true;

    num1 = abs(num1);
    num2 = abs(num2);

    while(num2 > 0) {
        if(num2 & 1) 
            ans += num1;
        num1 <<= 1; // Bitwise to multiply by 2
        num2 >>= 1; // Bitwise to divide by 2
    }

    // Checking if ans should be positive or not
    if((!isNeg1 && !isNeg2) || (isNeg1 && isNeg2))
        return ans;

    return -ans;
}

int main() {
    int testcase;

    cin >> testcase;

    for(int t = 0;t < testcase;t++) {
        cout << "Testcase " << t + 1 << ":" << endl;

        long long num1, num2;
        cin >> num1 >> num2;

        long long ans = alaCarteMultiplication(num1, num2);

        cout << num1 << " * " << num2 << " = " << ans;

        cout << "\n--------------------------------------------------------------------------------------------------\n";
    }  
    return 0;
}
