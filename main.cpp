#include <thread>
#include <iostream>

int main()
{
    try {
        std::cout << "Thread examples. Run demo programs:\n";
        std::cout << "threads_demo - single thread\n";
        std::cout << "async_demo - asynchronous demo\n";
        std::cout << "false_sharing_demo - false sharing demo\n";
        std::cout << "mutex_demo - mutex demo\n";
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
