#ifndef CPP_TYPE_TRATIS_H_
#define CPP_TYPE_TRATIS_H_

//
//  This file provides some compile-time information about various types.
//  These representations were designed, on purpose, to be constant-expressions
//  and not types as found in <type_traits.h>. In particular, they
//  can be used in control structures and the optimizer hopefully will do
//  the obvious thing.

namespace ft {

struct __true_type { };
struct __false_type { };

template <bool>
struct truth_type
{ typedef __false_type type; };

template <>
struct truth_type<true>
{ typedef __true_type type; };

// N.B. The conversions to bool are needed due to the issue
// explained in c++/19404.
template <class Sp, class Tp>
struct traitor
{
  enum { value = bool(Sp::value) || bool(Tp::value) };
  typedef typename truth_type<value>::type type;
};

// Compare for equality of types.
template <typename, typename>
struct are_same
{
  enum { value = 0 };
  typedef __false_type type;
};

template<typename Tp>
struct are_same<Tp, Tp>
{
  enum { value = 1 };
  typedef __true_type type;
};

//
// Integer types
//
template <typename Tp>
struct is_integer
{
  enum { value = 0 };
  typedef __false_type type;
};

// Thirteen specializations (yes there are eleven standard integer
// types; <em>long long</em> and <em>unsigned long long</em> are
// supported as extensions). Up to four target-specific __int<N>
// types are supported as well.
template<>
struct is_integer<bool>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<char>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<signed char>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<unsigned char>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<short>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<unsigned short>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<int>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<unsigned int>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<long>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<unsigned long>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<long long>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<unsigned long long>
{
  enum { value = 1 };
  typedef __true_type type;
};

//
// Floating point types
//
template <typename Tp>
struct is_floating
{
  enum { value = 0 };
  typedef __false_type type;
};

// three specializations (float, double and 'long double')
template <>
struct is_floating<float>
{
  enum { value = 1 };
  typedef __true_type type;
};

template <>
struct is_floating<double>
{
  enum { value = 1 };
  typedef __true_type type;
};

template <>
struct is_floating<long double>
{
  enum { value = 1 };
  typedef __true_type type;
};


//
// Pointer types
//
template <typename Tp>
struct is_pointer
{
  enum { value = 0 };
  typedef __false_type type;
};

template <typename Tp>
struct is_pointer<Tp*>
{
  enum { value = 1 };
  typedef __true_type type;
};

//
// A arithmetic type is an integer type or a floating point type
//
template <typename Tp>
struct is_arithmetic
: public traitor<is_integer<Tp>, is_floating<Tp> >
{ };

//
// A scalar type is an arithmetic type or a pointer type
//
template <typename Tp>
struct is_scalar
: public traitor<is_arithmetic<Tp>, is_pointer<Tp> >
{ };

} // ft
#endif // CPP_TYPE_TRATIS_H_