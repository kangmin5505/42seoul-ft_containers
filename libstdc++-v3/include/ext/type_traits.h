#ifndef TYPE_TRAITS_H_
#define TYPE_TRAITS_H_

namespace ft {

// Define a nested type if some predicate holds.
template <bool, typename>
struct enable_if { };

template <typename Tp>
struct enable_if<true, Tp>
  { typedef Tp type; };

/// @brief helper classes
template <typename Tp, Tp v>
struct integral_constant
{
  static const Tp                   value = v;
  typedef Tp                        value_type;
  typedef integral_constant<Tp, v>  type;
};
typedef integral_constant<bool, true>     true_type;
typedef integral_constant<bool, false>    false_type;

// template <typename Tp, Tp v>
// const Tp integral_constant<Tp, v>::value;

template <typename>
struct is_integral
: public false_type { };

template <>
struct is_integral<bool>
: public integral_constant<bool, true> { };

template <>
struct is_integral<char>
: public integral_constant<char, true> { };

template <>
struct is_integral<signed char>
: public integral_constant<signed char, true> { };

template <>
struct is_integral<unsigned char>
: public integral_constant<unsigned char, true> { };

template <>
struct is_integral<wchar_t>
: public integral_constant<wchar_t, true> { };

template <>
struct is_integral<short>
: public integral_constant<short, true> { };

template <>
struct is_integral<unsigned short>
: public integral_constant<unsigned short, true> { };

template <>
struct is_integral<int>
: public integral_constant<int, true> { };

template <>
struct is_integral<unsigned int>
: public integral_constant<unsigned int, true> { };

template <>
struct is_integral<long>
: public integral_constant<long, true> { };

template <>
struct is_integral<unsigned long>
: public integral_constant<unsigned long, true> { };

template <>
struct is_integral<long long>
: public integral_constant<long long, true> { };

template <>
struct is_integral<unsigned long long>
: public integral_constant<unsigned long long, true> { };

template <>
struct is_integral<bool const>
: public integral_constant<bool, true> { };

template <>
struct is_integral<char const>
: public integral_constant<char, true> { };

template <>
struct is_integral<signed char const>
: public integral_constant<signed char, true> { };

template <>
struct is_integral<unsigned char const>
: public integral_constant<unsigned char, true> { };

template <>
struct is_integral<wchar_t const>
: public integral_constant<wchar_t, true> { };

template <>
struct is_integral<short const>
: public integral_constant<short, true> { };

template <>
struct is_integral<unsigned short const>
: public integral_constant<unsigned short, true> { };

template <>
struct is_integral<int const>
: public integral_constant<int, true> { };

template <>
struct is_integral<unsigned int const>
: public integral_constant<unsigned int, true> { };

template <>
struct is_integral<long const>
: public integral_constant<long, true> { };

template <>
struct is_integral<unsigned long const>
: public integral_constant<unsigned long, true> { };

template <>
struct is_integral<long long const>
: public integral_constant<long long, true> { };

template <>
struct is_integral<unsigned long long const>
: public integral_constant<unsigned long long, true> { };

} // ft
#endif // TYPE_TRAITS_H_