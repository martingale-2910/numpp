#include <iostream> // std::cout, std::endl, std::ostream
#include "vec.hxx"

int main(int argc, char** argv)
{
    auto rvd = rvecd(std::valarray<double>{0.0, 1.0, 2.0, 3.0, 4.0});
    auto cvd = cvecd(std::valarray<double>{0.0, 1.0, 2.0, 3.0, 4.0});
    auto rvb = rvecb(std::valarray<bool>{false, true, true, true});
    std::cout << ((((2.0*rvd)/2.0)+1)-1) << std::endl;
    std::cout << 3.0/rvd << std::endl;
    std::cout << rvd/2.0 << std::endl;
    std::cout << cvd+cvd << std::endl;
    std::cout << rvd*cvd << std::endl;
    std::cout << rvd[rvb] << std::endl;
    return 0;
}   