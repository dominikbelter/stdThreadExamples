#include <thread>
#include <iostream>
#include <chrono>
#include <random>
#include "Defs/eigen3.h"

typedef std::array<std::array<double, 10000>, 10000> Array2D;

///create 1000x1000 matrix filled with random numbers
Array2D matGlob;

/// fill in with random numbers
void fillInRand(Array2D& mat){
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(5.0,2.0);
    for (size_t col=0;col<(size_t)mat.size();col++){
        for (size_t row=0;row<(size_t)mat[col].size();row++){
            mat[row][col] = distribution(generator);
        }
    }
}

/// find max value in the matrix
double findMax(const Array2D& mat) {
    double max = std::numeric_limits<double>::min();
    for (size_t col=0;col<(size_t)mat.size();col++){
        for (size_t row=0;row<(size_t)mat[col].size();row++){
            if (mat[row][col]>max){
                max = mat[row][col];
            }
        }
    }
    return max;
}

/// find min value in the matrix
void findMaxArea(const Array2D& mat, size_t startCol, size_t endCol, size_t startRow, size_t endRow, double &max) {
    max = std::numeric_limits<double>::min();
    for (size_t col=startCol;col<endCol;col++){
        for (size_t row=startRow;row<endRow;row++){
            if (mat[row][col]>max){
                max = mat[row][col];
            }
        }
    }
}

int main()
{
    try {
        std::cout << "Thread example. How to start thread\n";
        //fill in the array
        fillInRand(matGlob);

        /// standard way of calling function
        // measure time
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        // find max
        std::cout << "Max value in the matrix is: " << findMax(matGlob) << "\n";
        // measure time
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        // display output
        std::cout << "Time difference when function is called = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

        /// now we run two threads
        // measure time
        begin = std::chrono::steady_clock::now();
        // create thread and pass argument
        // important! Use std::ref if passed by reference
        double max1;
        std::thread threadMax1(findMaxArea, std::ref(matGlob), 0, matGlob.size(), 0, matGlob.size()/2, std::ref(max1));
        // create thread and pass argument
        double max2;
        std::thread threadMax2(findMaxArea, std::ref(matGlob), 0, matGlob.size(), matGlob.size()/2+1, matGlob.size(), std::ref(max2));
        /// synchronize threads
        threadMax1.join();
        threadMax2.join();
        std::cout << "Max value in the matrix is: " << std::max(max1,max2) << "\n";
        // measure time
        end = std::chrono::steady_clock::now();
        // display output
        std::cout << "Time difference with threads = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
