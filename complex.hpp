#ifndef SJTU_COMPLEX_HPP
#define SJTU_COMPLEX_HPP

#include <cmath>     // 数学函数
#include <iomanip>   // 控制输出格式
#include <iostream>  // 输入输出
#include <stdexcept> // 异常处理
// 你不可以使用任何其他的头文件!

namespace sjtu {

class divided_by_zero final : public std::exception {
public:
  divided_by_zero() = default;
  ~divided_by_zero() = default;
  const char *what() const noexcept override {
    return "complex divided by zero!";
  }
};

// 用于判断浮点数的符号.
inline int sign(double x) {
  const double eps = 1e-6;
  return (x > eps) - (x < -eps);
}

// 请保留所有的接口声明，即使你没有实现它们。
// 否则可能出现编译错误，无法通过部分测试点。
class complex {
private:
  double a, b; // a + bi
public:
  complex() : a(0), b(0) {}                   // 默认构造函数 0+0i
  complex(double a) : a(a), b(0) {}           // 构造函数 a+0i
  complex(double a, double b) : a(a), b(b) {} // 构造函数 a+bi

  double &real() { return a; } // 返回实部
  double &imag() { return b; } // 返回虚部

  complex operator-() const { return complex(-a, -b); } // 返回负数
  complex operator~() const { return complex(a, -b); } // 返回共轭复数

  complex operator+(const complex &rhs) const { return complex(a + rhs.a, b + rhs.b); } // 加法
  complex operator-(const complex &rhs) const { return complex(a - rhs.a, b - rhs.b); } // 减法
  complex operator*(const complex &rhs) const {
    return complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a);
  } // 乘法
  complex operator/(const complex &rhs) const {
    double denom = rhs.a * rhs.a + rhs.b * rhs.b;
    if (sign(rhs.a) == 0 && sign(rhs.b) == 0) {
      throw divided_by_zero();
    }
    return complex((a * rhs.a + b * rhs.b) / denom, (b * rhs.a - a * rhs.b) / denom);
  } // 除法

  complex &operator+=(const complex &rhs) {
    a += rhs.a;
    b += rhs.b;
    return *this;
  }
  complex &operator-=(const complex &rhs) {
    a -= rhs.a;
    b -= rhs.b;
    return *this;
  }
  complex &operator*=(const complex &rhs) {
    double new_a = a * rhs.a - b * rhs.b;
    double new_b = a * rhs.b + b * rhs.a;
    a = new_a;
    b = new_b;
    return *this;
  }
  complex &operator/=(const complex &rhs) {
    double denom = rhs.a * rhs.a + rhs.b * rhs.b;
    if (sign(rhs.a) == 0 && sign(rhs.b) == 0) {
      throw divided_by_zero();
    }
    double new_a = (a * rhs.a + b * rhs.b) / denom;
    double new_b = (b * rhs.a - a * rhs.b) / denom;
    a = new_a;
    b = new_b;
    return *this;
  }

  bool operator==(const complex &rhs) const {
    return sign(a - rhs.a) == 0 && sign(b - rhs.b) == 0;
  } // 判断相等

  explicit operator bool() const {
    return sign(a) != 0 || sign(b) != 0;
  } // 转换为 bool

  friend std::ostream &operator<<(std::ostream &os, const complex &x) {
    os << std::fixed << std::setprecision(6) << (sign(x.a) == 0 ? 0.0 : x.a);
    if (sign(x.b) >= 0) {
      os << "+";
    }
    os << (sign(x.b) == 0 ? 0.0 : x.b) << "i";
    return os;
  }
};

} // namespace sjtu

#endif
