#include <iostream>

int main() {
    int wyn = 0;

    while (1) {

        int a, b, c;
        std::cin >> a >> b >> c;

        if (a == 0 && b == 0 && c == 0)
            break;
        else if ( a+b > c &&
                  a+c > b &&
                  b+c > a && (
                  a*a > b*b + c*c ||
                  b*b > a*a + c*c ||
                  c*c > a*a + b*b ))
            wyn++;
    }

    std::cout << wyn;

    return 0;
}
