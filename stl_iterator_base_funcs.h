#ifndef STL_ITERATOR_BASE_FUNCS_H_
#define STL_ITERATOR_BASE_FUNCS_H_

#include "stl_iterator_base_types.h"

namespace ft {

template <typename InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last,
          std::input_iterator_tag)
{
  typename ft::iterator_traits<InputIterator>::difference_type n = 0;
  while (first != last)
  {
    ++first;
    ++n;
  }
  return n;
}

template <typename RandomAccessIterator>
typename ft::iterator_traits<RandomAccessIterator>::difference_type
__distance(RandomAccessIterator first, RandomAccessIterator last,
          std::random_access_iterator_tag)
{
  return last - first;
}

template <typename InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last)
{
  return ft::__distance(first, last,
        ft::iterator_category(first));
}


template <typename InputIterator, typename Distance>
void
__advance(InputIterator& i, Distance n, std::input_iterator_tag)
{
  while (n--)
    ++i;
}

template <typename BidirectionalIterator, typename Distance>
void
__advance(BidirectionalIterator& i, Distance n, std::bidirectional_iterator_tag)
{
  if (n > 0)
    while (n--)
      ++i;
  else
    while (n++)
      --i;
}

template <typename RandomAccessIterator, typename Distance>
void
__advance(RandomAccessIterator& i, Distance n, std::random_access_iterator_tag)
{
  if (__builtin_constant_p(n) && n == 1)
    ++i;
  else if (__builtin_constant_p(n) && n == -1)
    --i;
  else
    i += n;
}

/**
 * @brief A generalization of pointer arithmetic.
 * @param i An input iterator.
 * @param n The @a delta by which to change @p i.
 * @return Nothing.
 * 
 * This increments @p i by @p n. For bidirectional and random access
 * iterators, @p n may be negative, in which case @p i is decremented.
 * 
 * For random access iterators, thie uses their @c + and @c - operations
 * and are constant time. For other %iterator classes they are linear time.
 */
template <typename InputIterator, typename Distance>
void
advance(InputIterator& i, Distance n)
{
  typename iterator_traits<InputIterator>::difference_type d = n;
  ft::__advance(i, d, ft::iterator_category(i));
}

} // ft
#endif // STL_ITERATOR_BASE_FUNCS_H_