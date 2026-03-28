#include <algorithm>
#include <execution>
#include <vector>
#include <iostream>

/// multiply element
void multiplyElement(std::vector<int>& data, size_t start, size_t end, int multiplier) {
    for (size_t col=start;col<end;col++){
        data[col] *=multiplier;
    }
}

/// check values
bool checkValues(const std::vector<int>& data, int refValue){
    for (const auto& element : data){
        if (element != refValue){
            return false;
        }
    }
    return true;
}

int main()
{
    try {
        std::cout << "Execution example. Modern way of using parallel algorithms\n";

        // data
        std::vector<int> data(1000'000'000, 1);
        // multiplier
        int multiplier = 2;

        // measure time
        auto begin = std::chrono::steady_clock::now();
        for (size_t i=0;i<data.size();i++){
            data[i] = data[i] * multiplier;
        }
        // measure time
        auto end = std::chrono::steady_clock::now();
        // display output
        std::cout << "Time difference without threads (basic) = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        if (!checkValues(data, 2)){
            std::cout << "incorrect values\n";
            return 0;
        }

        std::fill(data.begin(),data.end(),1);
        // measure time
        begin = std::chrono::steady_clock::now();
        for (size_t i=0;i<data.size();i++){
            data[i] *= multiplier;
        }
        // measure time
        end = std::chrono::steady_clock::now();
        // display output
        std::cout << "Time difference without threads (in place multiplication) = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        if (!checkValues(data, 2)){
            std::cout << "incorrect values\n";
            return 0;
        }

        std::fill(data.begin(),data.end(),1);
        // measure time
        begin = std::chrono::steady_clock::now();
        for (auto& element : data){
            element *= multiplier;
        }
        // measure time
        end = std::chrono::steady_clock::now();
        // display output
        std::cout << "Time difference without threads (auto loop) = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        if (!checkValues(data, 2)){
            std::cout << "incorrect values\n";
            return 0;
        }


        std::fill(data.begin(),data.end(),1);
        // measure time
        begin = std::chrono::steady_clock::now();
        std::transform(data.begin(), data.end(), data.begin(),
                       [multiplier](auto x) { return x * multiplier; });
        // measure time
        end = std::chrono::steady_clock::now();
        // display output
        std::cout << "Time difference with std::transform = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        if (!checkValues(data, 2)){
            std::cout << "incorrect values\n";
            return 0;
        }

        std::fill(data.begin(),data.end(),1);
        // measure time
        begin = std::chrono::steady_clock::now();
        // Set number of threads
        size_t num_threads = 21;

        std::vector<std::thread> threads;
        size_t chunk_size = data.size() / size_t(num_threads);

        for (size_t i = 0; i < num_threads; ++i) {
            size_t startData = i * chunk_size;
            size_t endData = (i == num_threads - 1) ? data.size() : startData + chunk_size;
            threads.emplace_back(multiplyElement, std::ref(data), startData, endData, multiplier);
        }
        for (auto& t : threads) {
            t.join();
        }
        // measure time
        end = std::chrono::steady_clock::now();
        // display output
        std::cout << "Time difference with threads (classic) = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        if (!checkValues(data, 2)){
            std::cout << "incorrect values\n";
            return 0;
        }

        std::fill(data.begin(),data.end(),1);
        // measure time
        begin = std::chrono::steady_clock::now();
        std::transform(std::execution::par, data.begin(), data.end(), data.begin(),
                       [multiplier](int x) { return x * multiplier; });
        // measure time
        end = std::chrono::steady_clock::now();
        // display output
        std::cout << "Time difference with threads (execution with parameter) = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        if (!checkValues(data, 2)){
            std::cout << "incorrect values\n";
            return 0;
        }

        constexpr int multiplier2 = 2;
        std::fill(data.begin(),data.end(),1);
        // measure time
        begin = std::chrono::steady_clock::now();
        std::transform(std::execution::par, data.begin(), data.end(), data.begin(),
                       [](int x) { return x * multiplier2; });
        // measure time
        end = std::chrono::steady_clock::now();
        // display output
        std::cout << "Time difference with threads (execution with constexpr) = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        if (!checkValues(data, 2)){
            std::cout << "incorrect values\n";
            return 0;
        }
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
