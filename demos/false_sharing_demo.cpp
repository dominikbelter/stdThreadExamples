#include <thread>
#include <iostream>
#include <chrono>
#include "Defs/eigen3.h"

///create 1000x1000 matrix filled with random numbers
Eigen::MatrixXd matGlob = Eigen::MatrixXd::Random(1000,1000);

/// find max value in the matrix
double findMax(const Eigen::MatrixXd& mat) {
    double max = std::numeric_limits<double>::min();
    for (size_t col=0;col<(size_t)mat.cols();col++){
        for (size_t row=0;row<(size_t)mat.cols();row++){
            if (mat(row,col)>max){
                max = mat(row,col);
            }
        }
    }
    return max;
}

/// find min value in the matrix
double findMin(const Eigen::MatrixXd& mat) {
    double min = std::numeric_limits<double>::max();
    for (size_t col=0;col<(size_t)mat.cols();col++){
        for (size_t row=0;row<(size_t)mat.cols();row++){
            if (mat(row,col)<min){
                min = mat(row,col);
            }
        }
    }
    return min;
}

int main()
{
    try {
        std::cout << "Thread example. How to start thread\n";

        /// standard way of calling function
        // measure time
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        // find max
        std::cout << "Max value in the matrix is: " << findMax(matGlob) << "\n";
        // find min
        std::cout << "Min value in the matrix is: " << findMin(matGlob) << "\n";
        // measure time
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        // display output
        std::cout << "Time difference when functions are called = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

        /// now we run two threads
        // measure time
        begin = std::chrono::steady_clock::now();
        // create thread and pass argument
        std::thread threadMax(findMax, matGlob);
        // create thread and pass argument
        std::thread threadMin(findMin, matGlob);
        /// synchronize threads
        threadMax.join();
        threadMin.join();
        // measure time
        end = std::chrono::steady_clock::now();
        // display output
        std::cout << "Time difference with threads = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

        std::cout << "Why two threads are slower than a single thread?\n";
        std::cout << "See \'false sharing\': https://en.wikipedia.org/wiki/False_sharing\n";
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
