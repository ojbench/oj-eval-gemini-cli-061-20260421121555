#include "complex.hpp"
#include <iostream>
#include <cassert>

int main() {
    using sjtu::complex;

    // 1. Constructors
    complex z;
    assert(z.real() == 0 && z.imag() == 0);

    complex z1 = 1;
    assert(z1.real() == 1 && z1.imag() == 0);

    complex z2 = 2.22;
    assert(z2.real() == 2.22 && z2.imag() == 0);

    complex z3(114.514);
    assert(z3.real() == 114.514 && z3.imag() == 0);

    complex z4(1, 2);
    assert(z4.real() == 1 && z4.imag() == 2);

    complex z5(2.22, 3.33);
    assert(z5.real() == 2.22 && z5.imag() == 3.33);

    complex x;
    complex y = x;
    assert(y.real() == 0 && y.imag() == 0);
    x = y = 2;
    assert(x.real() == 2 && x.imag() == 0);
    assert(y.real() == 2 && y.imag() == 0);

    // 2. Accessors
    complex za(1, 2);
    std::cout << za.real() << "," << za.imag() << std::endl;
    za.real() = 3;
    za.imag() = 4;
    assert(za.real() == 3 && za.imag() == 4);

    // 3. Comparison
    complex a = 1, b = 2, c = 2;
    std::cout << "a == b: " << (a == b) << std::endl;
    std::cout << "b == c: " << (b == c) << std::endl;
    assert(!(a == b));
    assert(b == c);

    // 4. Arithmetic
    complex a1(1, 2), b1(3, 4);
    complex c1 = a1 + b1;
    assert(c1.real() == 4 && c1.imag() == 6);
    
    complex d1 = a1 - b1;
    assert(d1.real() == -2 && d1.imag() == -2);

    complex e1 = a1 * b1; // (1+2i)(3+4i) = 3 + 4i + 6i - 8 = -5 + 10i
    assert(e1.real() == -5 && e1.imag() == 10);

    complex f1 = complex(1, 2) / complex(3, 4); 
    // (1+2i)/(3+4i) = (1+2i)(3-4i)/25 = (3 - 4i + 6i + 8)/25 = (11 + 2i)/25 = 0.44 + 0.08i
    assert(std::abs(f1.real() - 0.44) < 1e-6);
    assert(std::abs(f1.imag() - 0.08) < 1e-6);

    complex g1 = -a1;
    assert(g1.real() == -1 && g1.imag() == -2);

    complex h1 = ~a1;
    assert(h1.real() == 1 && h1.imag() == -2);

    // Exception
    complex az = 1, bz = 0;
    try {
        az /= bz;
    } catch(const std::exception &err) {
        std::cout << "Caught expected exception: " << err.what() << std::endl;
    }

    // 5. Output
    complex oa(-2,0);
    complex ob(0,-2);
    complex oc(1,-1e-10);
    complex od(-1e-10,1);
    std::cout << "oa: " << oa << std::endl; // -2.000000+0.000000i
    std::cout << "ob: " << ob << std::endl; // 0.000000-2.000000i
    std::cout << "oc: " << oc << std::endl; // 1.000000+0.000000i
    std::cout << "od: " << od << std::endl; // 0.000000+1.000000i

    // 6. Bool
    complex b1_true(1, 0);
    complex b2_false(0, 0);
    if (b1_true) std::cout << "b1_true is true" << std::endl;
    if (!b2_false) std::cout << "b2_false is false" << std::endl;

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
