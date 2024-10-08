#include "bits/stdc++.h"
using namespace std;

void storeDigitsInRectangle(int len1, int len2, vector<vector<long long>> &rectangle, string &s1, string &s2) {
    // Storing digit values
    for(int i = 0; i < len1; i++) {
        rectangle[i + 1][0] = s1[i] - '0';  // Storing digit directly
    }

    for(int i = 0; i < len2; i++) {
        rectangle[0][i + 1] = s2[i] - '0';  // Storing digit directly
    }
}

void fillRectangleProducts(int len1, int len2, vector<vector<long long>> &rectangle) {
    // Calculating the product
    for(int i = 1; i <= len1; i++) {
        for(int j = 1; j <= len2; j++) {
            rectangle[i][j] = rectangle[i][0] * rectangle[0][j];  // Store product of digits
        }
    }
}

long long accumulate(int len1, int len2, vector<vector<long long>> &rectangle) {
    long long ans = 0;
    for(int i = 1; i <= len1; i++) {
        for(int j = 1; j <= len2; j++) {
            long long positionMultiplier = pow(10, (len1 - i) + (len2 - j));
            ans += rectangle[i][j] * positionMultiplier;  // Adjusting for position value
        }
    }

    return ans;
}

long long rectangleMultiplication(long long num1, long long num2) {
    bool isNeg1 = false, isNeg2 = false;
    
    if (num1 < 0)
        isNeg1 = true;
    if (num2 < 0)
        isNeg2 = true;

    num1 = abs(num1);
    num2 = abs(num2);

    string s1 = to_string(num1);
    string s2 = to_string(num2);
    
    int len1 = s1.size();
    int len2 = s2.size();

    vector<vector<long long>> rectangle(len1 + 1, vector<long long> (len2 + 1));

    // Store digits in first row and first column of the rectangle
    storeDigitsInRectangle(len1, len2, rectangle, s1, s2);

    // Fill the rectangle by calculating the products
    fillRectangleProducts(len1, len2, rectangle);

    // Accumulate the results and return it to main function
    long long ans = accumulate(len1, len2, rectangle);

    // Adjust the sign of the result
    if ((isNeg1 && !isNeg2) || (!isNeg1 && isNeg2)) {
        return -ans;
    }

    return ans;
}

int main() {
    int testcase;
    cin >> testcase;

    for(int t = 0; t < testcase; t++) {
        cout << "Testcase " << t + 1 << ":" << endl;

        long long num1, num2;
        cin >> num1 >> num2;

        long long ans = rectangleMultiplication(num1, num2);

        cout << num1 << " * " << num2 << " = " << ans << endl;
        cout << "--------------------------------------------------------------------------------------------------\n";
    }  
    return 0;
}
