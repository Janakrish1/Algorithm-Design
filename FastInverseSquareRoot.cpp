#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <fstream>
#include <numeric> // For std::accumulate

// Fast Inverse Square Root Algorithm
float fastInverseSqrt(float number) {
    const float threehalfs = 1.5F;

    float x2 = number * 0.5F;
    float y = number;

    long i = *reinterpret_cast<long*>(&y); // Bit level manipulation
    i = 0x5f3759df - (i >> 1); // Magic number and bit shift
    y = *reinterpret_cast<float*>(&i); // Back to float

    y = y * (threehalfs - (x2 * y * y)); // One iteration of Newton's method

    return y;
}

// Function to export data to CSV
void exportToCSV(const std::string& filename, const std::vector<double>& data1, const std::vector<double>& data2) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Standard Sqrt Time,Fast Inverse Sqrt Time\n";
        for (size_t i = 0; i < data1.size(); ++i) {
            file << data1[i] << "," << data2[i] << "\n";
        }
        file.close();
        std::cout << "Data exported to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int main() {
    const int times = 10000;
    float testNum = 999;
    std::vector<double> sqrtTimes, fastInverseTimes;

    // Measure total time for standard 1/sqrt(x)
    auto startTotalStd = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < times; ++i) {
        auto startStd = std::chrono::high_resolution_clock::now();
        float result = 1.0F / sqrt(testNum);
        auto endStd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time = endStd - startStd;
        sqrtTimes.push_back(time.count());
    }
    auto endTotalStd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> totalStdTime = endTotalStd - startTotalStd;

    // Measure total time for fast inverse square root
    auto startTotalFast = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < times; ++i) {
        auto startFast = std::chrono::high_resolution_clock::now();
        float result = fastInverseSqrt(testNum);
        auto endFast = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time = endFast - startFast;
        fastInverseTimes.push_back(time.count());
    }
    auto endTotalFast = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> totalFastTime = endTotalFast - startTotalFast;

    // Calculate the average time per iteration
    double avgStdTime = totalStdTime.count() / times;
    double avgFastTime = totalFastTime.count() / times;

    // Calculate the average time difference per iteration
    double timeDifference = abs(avgStdTime - avgFastTime);

    // Export results to CSV
    exportToCSV("sqrtTimes.csv", sqrtTimes, fastInverseTimes);

    // Output analysis
    std::cout << "x = 999 // Test Number \n";
    std::cout << "Total number of iterations = 10000\n";
    std::cout << "Total time for standard 1/sqrt(x): " << totalStdTime.count() << " seconds\n";
    std::cout << "Total time for Fast Inverse Sqrt: " << totalFastTime.count() << " seconds\n";
    std::cout << "Average time for standard 1/sqrt(x): " << avgStdTime << " seconds\n";
    std::cout << "Average time for Fast Inverse Sqrt: " << avgFastTime << " seconds\n";
    std::cout << "Time difference per iteration: " << timeDifference << " seconds\n";

    // Accuracy comparison
    float stdResult = 1.0F / sqrt(testNum);
    float fastResult = fastInverseSqrt(testNum);
    std::cout << "Standard Square Root Result: " << stdResult << "\n";
    std::cout << "Fast Inverse Sqrt Result: " << fastResult << "\n";
    std::cout << "Difference in results: " << fabs(stdResult - fastResult) << "\n";

    return 0;
}
