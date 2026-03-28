#include <algorithm>
#include <execution>
#include <vector>
#include <functional>
#include <ranges>
#include <iostream>
#include <numeric> // for std::reduce and std::transform_reduce
#include <tuple>

int main()
{
    try {
        std::cout << "=== Lambda functions and modern C++ examples ===\n\n";

        // 1. Basic Lambda
        std::cout << "1.1 Basic Lambda\n";
        auto add = [](int a, int b) { return a + b; };
        std::cout << "add(3,4) = " << add(3,4) << "\n\n";

        // 2. Lambda with Capture by Value
        std::cout << "1.2 Lambda with capture by value\n";
        int x_val = 10;
        auto f_val = [x_val]() { std::cout << "Captured x_val = " << x_val << "\n"; };
        f_val();
        std::cout << "\n";

        // 3. Lambda with Capture by Reference
        std::cout << "1.3 Lambda with capture by reference\n";
        int x_ref = 10;
        auto f_ref = [&x_ref]() { x_ref += 5; };
        f_ref();
        std::cout << "x_ref after lambda = " << x_ref << "\n\n";

        // 4. Mutable Lambda
        std::cout << "1.4 Mutable Lambda\n";
        int x_mut = 10;
        auto f_mut = [x_mut]() mutable {
            x_mut += 5;
            std::cout << "Inside lambda x_mut = " << x_mut << "\n";
        };
        f_mut();
        std::cout << "Outside lambda x_mut = " << x_mut << "\n\n";

        // 5. Lambda with STL for_each
        std::cout << "1.5 Lambda with std::for_each\n";
        std::vector<int> v1 = {1,2,3,4,5};
        std::for_each(v1.begin(), v1.end(), [](int x){ std::cout << x*x << " "; });
        std::cout << "\n\n";

        // 6. Lambda with sort
        std::cout << "1.6 Lambda with sort\n";
        std::vector<int> v2 = {5,1,4,2,3};
        std::sort(v2.begin(), v2.end(), [](int a, int b){ return a > b; });
        for (auto x : v2) std::cout << x << " ";
        std::cout << "\n\n";

        // 7. Generic Lambda (auto parameters)
        std::cout << "1.7 Generic Lambda\n";
        auto add_generic = [](auto a, auto b){ return a + b; };
        std::cout << add_generic(3,4) << ", " << add_generic(2.5,1.5) << "\n\n";

        // 8. Lambda returning lambda
        std::cout << "1.8 Lambda returning lambda\n";
        auto make_adder = [](int x) {
            return [x](int y){ return x + y; };
        };
        auto add5 = make_adder(5);
        std::cout << "add5(3) = " << add5(3) << "\n\n";

        // 9. Lambda in algorithms with capture
        std::cout << "1.9 Lambda in algorithms with capture\n";
        std::vector<int> v3 = {1,2,3,4,5,6};
        int threshold = 3;
        auto count = std::count_if(v3.begin(), v3.end(), [threshold](int x){ return x > threshold; });
        std::cout << "Elements > " << threshold << " = " << count << "\n\n";

        // 10. Lambda with std::function
        std::cout << "1.10 Lambda with std::function\n";
        std::function<int(int,int)> op = [](int a, int b){ return a * b; };
        std::cout << "op(3,4) = " << op(3,4) << "\n\n";

        // --- Modern C++ Ranges ---
        std::cout << "=== Modern C++ Ranges ===\n";

        // 11. Transform (lazy)
        std::vector<int> v4 = {1,2,3,4,5};
        auto squared = v4 | std::views::transform([](int x){ return x*x; });
        std::cout << "Squared: ";
        for (int x : squared) std::cout << x << " ";
        std::cout << "\n\n";

        // 12. Filter and transform pipeline
        std::vector<int> v5 = {1,2,3,4,5,6};
        auto pipeline = v5
                        | std::views::filter([](int x){ return x % 2 == 0; })
                        | std::views::transform([](int x){ return x * 10; });
        std::cout << "Even * 10: ";
        for (int x : pipeline) std::cout << x << " ";
        std::cout << "\n\n";

        // 13. Reduce
        std::vector<int> v6 = {1,2,3,4,5};
        int sum = std::reduce(v6.begin(), v6.end());
        std::cout << "Sum (reduce) = " << sum << "\n\n";

        // 14. Transform reduce
        std::vector<int> v7 = {1,2,3,4};
        int tr_sum = std::transform_reduce(v7.begin(), v7.end(), 0, std::plus<>(), [](int x){ return x*x; });
        std::cout << "Sum of squares (transform_reduce) = " << tr_sum << "\n\n";

        // 15. std::pair and std::tuple
        std::vector<int> a = {1,2,3};
        std::vector<int> b = {4,5,6};
        std::cout << "Pair-wise sum: ";
        for (size_t i = 0; i < a.size(); ++i){
            auto [x, y] = std::pair{a[i], b[i]};
            std::cout << x + y << " ";
        }
        std::cout << "\n";

        std::tuple<int,int,int> t = {1,2,3};
        auto [i1,i2,i3] = t;
        std::cout << "Tuple sum: " << i1 + i2 + i3 << "\n\n";

        std::cout << "=== End of examples ===\n";

    } catch(const std::exception& ex){
        std::cerr << "Exception: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}
