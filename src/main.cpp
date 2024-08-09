#include "ChainingHashMap.h"

#include <algorithm>
int main()
{
    benn::ChainingHashMap<int, int> yay;
    yay[0] = 10;
    std::cout << yay[0] << '\n';

    yay[1] = 100;
    std::cout << yay[1] << '\n';

    yay.insert(std::pair<int, int>{2, 1000});
    std::cout << yay[2] << '\n';

    yay.insert(std::pair<int, int>{1, 69});
    std::cout << yay[1] << '\n';

    yay.remove(5);
    std::cout << yay.size() << '\n';
    yay.remove(1);
    std::cout << yay.size() << '\n';
    std::cout << yay[1] << '\n';
    std::cout << yay.size() << '\n';

    return 0;
}