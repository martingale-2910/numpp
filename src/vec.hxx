#ifndef VEC_HXX
#define VEC_HXX

#include <iostream> // std::cout, std::endl, std::ostream
#include <iomanip> // ?
#include <type_traits> // std::enable_if, std::is_arithmetic, std::conjunction_v
#include <valarray> // std::valarray
#include <cassert> // std::assert
#include <string> // std::to_string
#include <numeric> // std::accumulate

enum struct Orientation { ROW, COL };

template<Orientation o, typename arithmetic_t, std::enable_if_t<std::is_arithmetic<arithmetic_t>::value, bool> = true>
struct vec
{
    std::valarray<arithmetic_t> data;
    static constexpr Orientation orientation = o;
    static constexpr Orientation coorientation = o == Orientation::ROW ? Orientation::COL : Orientation::ROW;

    vec(std::valarray<arithmetic_t> const & data): data(data) {}
    vec(vec<o, arithmetic_t> const & other): data(other.data) {}

    std::size_t size() const { return this->data.size(); }
    vec<coorientation, arithmetic_t> transpose() const { return vec<coorientation, arithmetic_t>(this->data); }
    
    arithmetic_t operator[](std::size_t i) const { return (this->data)[i]; }
    arithmetic_t& operator[](std::size_t i) { return (this->data)[i]; }
    vec operator[](vec<o, bool> const & b) const { return vec<o, arithmetic_t>((this->data)[b.data]); }
    arithmetic_t max() const { return (this->data).max(); }
    arithmetic_t min() const { return (this->data).min(); }
};

template<typename arithmetic_t, std::enable_if_t<std::is_arithmetic<arithmetic_t>::value, bool> = true>
using rvec = vec<Orientation::ROW, arithmetic_t>;

template<typename arithmetic_t, std::enable_if_t<std::is_arithmetic<arithmetic_t>::value, bool> = true>
using cvec = vec<Orientation::COL, arithmetic_t>;

using rvecd = rvec<double>;
using rvecb = rvec<bool>;
using cvecd = cvec<double>;
using cvecb = cvec<bool>;

template<template<typename> typename predicate, typename... ts>
using enable_if_all = std::enable_if_t<std::conjunction_v<predicate<ts>...>, bool>;

template<Orientation o, typename arithmetic_t1, typename arithmetic_t2, enable_if_all<std::is_arithmetic, arithmetic_t1, arithmetic_t2> = true>
vec<o, arithmetic_t1> operator+(vec<o, arithmetic_t1> const & v, arithmetic_t2 d) { return vec<o, arithmetic_t1>((v.data) + d); }

template<Orientation o, typename arithmetic_t1, typename arithmetic_t2, enable_if_all<std::is_arithmetic, arithmetic_t1, arithmetic_t2> = true>
vec<o, arithmetic_t1> operator+(arithmetic_t2 d, vec<o, arithmetic_t1> const & v) { return (v + d); }

template<Orientation o, typename arithmetic_t1, typename arithmetic_t2, enable_if_all<std::is_arithmetic, arithmetic_t1, arithmetic_t2> = true>
vec<o, arithmetic_t1> operator+(vec<o, arithmetic_t1> const & v1, vec<o, arithmetic_t2> const & v2)
{
    assert(v1.size() == v2.size());
    return vec<o, arithmetic_t1>(v1.data + v2.data);
}

template<Orientation o, typename arithmetic_t1, typename arithmetic_t2, enable_if_all<std::is_arithmetic, arithmetic_t1, arithmetic_t2> = true>
vec<o, arithmetic_t1> operator*(vec<o, arithmetic_t1> const & v, arithmetic_t2 d) { return vec<o, arithmetic_t1>(d*v.data); }

template<Orientation o, typename arithmetic_t1, typename arithmetic_t2, enable_if_all<std::is_arithmetic, arithmetic_t1, arithmetic_t2> = true>
vec<o, arithmetic_t1> operator*(arithmetic_t2 d, vec<o, arithmetic_t1> const & v) { return (v*d); }

template<Orientation o, typename arithmetic_t1, typename arithmetic_t2, enable_if_all<std::is_arithmetic, arithmetic_t1, arithmetic_t2> = true>
vec<o, arithmetic_t1> operator*(vec<o, arithmetic_t1> const & v1, vec<o, arithmetic_t2> const & v2)
{
    assert(v1.size() == v2.size());
    return vec<o, arithmetic_t1>(v1.data*v2.data);
}

template<typename arithmetic_t1, typename arithmetic_t2, enable_if_all<std::is_arithmetic, arithmetic_t1, arithmetic_t2> = true>
arithmetic_t1 operator*(rvec<arithmetic_t1> const & rv, cvec<arithmetic_t2> const & cv)
{
    assert(rv.size() == cv.size());
    return ((rv.data)*(cv.data)).sum();
}

template<Orientation o, typename arithmetic_t1, typename arithmetic_t2, enable_if_all<std::is_arithmetic, arithmetic_t1, arithmetic_t2> = true>
vec<o, arithmetic_t1> operator-(vec<o, arithmetic_t1> const & v, arithmetic_t2 d) { return vec<o, arithmetic_t1>(v.data - d); }

template<Orientation o, typename arithmetic_t1, typename arithmetic_t2, enable_if_all<std::is_arithmetic, arithmetic_t1, arithmetic_t2> = true>
vec<o, arithmetic_t1> operator-(arithmetic_t2 d, vec<o, arithmetic_t1> const & v) { return (v - d); }

template<Orientation o, typename arithmetic_t1, typename arithmetic_t2, enable_if_all<std::is_arithmetic, arithmetic_t1, arithmetic_t2> = true>
vec<o, arithmetic_t1> operator-(vec<o, arithmetic_t1> const & v1, vec<o, arithmetic_t2> const & v2)
{
assert(v1.size() == v2.size());
    return vec<o, arithmetic_t1>(v1.data - v2.data);
}

template<Orientation o, typename arithmetic_t1, typename arithmetic_t2, enable_if_all<std::is_arithmetic, arithmetic_t1, arithmetic_t2> = true>
vec<o, arithmetic_t1> operator/(vec<o, arithmetic_t1> const & v, arithmetic_t2 d) { return vec<o, arithmetic_t1>(v.data/d); }

template<Orientation o, typename arithmetic_t1, typename arithmetic_t2, enable_if_all<std::is_arithmetic, arithmetic_t1, arithmetic_t2> = true>
vec<o, arithmetic_t1> operator/(arithmetic_t2 d, vec<o, arithmetic_t1> const & v) { return vec<o, arithmetic_t1>(d/v.data); }

template<Orientation o, typename arithmetic_t1, typename arithmetic_t2, enable_if_all<std::is_arithmetic, arithmetic_t1, arithmetic_t2> = true>
vec<o, arithmetic_t1> operator/(vec<o, arithmetic_t1> const & v1, vec<o, arithmetic_t2> const & v2)
{
    assert(v1.size() == v2.size());
    return vec<o, arithmetic_t1>(v1.data/v2.data);
}

template<Orientation o, typename arithmetic_t, enable_if_all<std::is_arithmetic, arithmetic_t> = true>
std::ostream& operator<<(std::ostream& os, vec<o, arithmetic_t> const & vec)
{
    if (vec.orientation == Orientation::ROW)
    {
        std::string joined_inputs = std::accumulate(
            std::begin(vec.data), 
            std::end(vec.data), 
            std::string(), 
            [](std::string &acc, arithmetic_t const &elem) { return acc.empty() ? std::to_string(elem) : acc + ", " + std::to_string(elem); }
        );
        os << "[" << joined_inputs << "]";
    }
    else
    {
        std::string joined_inputs = std::accumulate(
            std::begin(vec.data), 
            std::end(vec.data), 
            std::string(), 
            [](std::string &acc, arithmetic_t const &elem) { return acc.empty() ? "|" + std::to_string(elem) + ";|" : acc + "\n" + "|" + std::to_string(elem) + ";|"; }
        );
        os << joined_inputs;
    }
    return os;
}

#endif // VEC_HXX