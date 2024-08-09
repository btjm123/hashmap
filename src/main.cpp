#include "ChainingHashMap.hpp"
#include "OpenAddressingHashMap.hpp"

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

    std::cout << "\n\n\n\n";

    benn::OpenAddressingHashMap<int, int> yay2;
    yay2[0] = 1;
    std::cout << yay2[0] << "\n";

    std::cout << yay2[10] << "\n";

    yay2[1] = 10;
    std::cout << yay2[1] << "\n";

    yay2[2] = 100;
    std::cout << yay2[2] << "\n";

    yay2[2] = 69;
    std::cout << yay2[2] << "\n";

    std::cout << yay2.size() << "\n";
    yay2.remove(5);
    std::cout << yay2.size() << "\n";
    yay2.remove(2);
    std::cout << yay2.size() << "\n";
    return 0;
}