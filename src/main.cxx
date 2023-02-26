#include <iostream> // std::cout, std::endl, std::ostream
#include "vec.hxx"

int main(int argc, char** argv)
{
    auto rvd = rvecd(std::valarray<double>{0.0, 1.1, 2.2, 3.3, 4.4});
    auto cvd = cvecd(std::valarray<double>{0.0, 1.1, 2.2, 3.3, 4.4});
    auto rvb = rvd > 1.0;
    std::cout << rvb << std::endl;
    std::cout << rvd[rvb] << std::endl;
    std::cout << rvd.transpose() << std::endl;
    std::cout << ((((2.0*rvd)/2.0)+1)-1) << std::endl;
    std::cout << 3.0/rvd << std::endl;
    std::cout << rvd/2.0 << std::endl;
    std::cout << cvd+cvd << std::endl;
    std::cout << rvd*cvd << std::endl;
    std::cout << abs(rvd) << std::endl;
    std::cout << pow(rvd, 2) << std::endl;
    std::cout << sqrt(rvd) << std::endl;
    std::cout << exp(rvd) << std::endl;
    std::cout << log(rvd) << std::endl;
    std::cout << ceil(rvd) << std::endl;
    std::cout << floor(rvd) << std::endl;
    auto c = 3.14;
    auto fn = [c](auto x){ return x + c; };
    std::cout << rvd.apply(fn) << std::endl;
    return 0;
}   