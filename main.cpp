#include <thread>
#include <iostream>

int main()
{
    try {
        std::cout << "Thread examples. Run demo programs:\n";
        std::cout << " - threads_demo - single thread\n";
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
