// RB tree implementation -*- C++ -*-

/** @file stl_tree.h
 *  This is an internal header file, included by other library headers.
 *  You should not attempt to use it directly.
 */

#ifndef STL_TREE_H_
#define STL_TREE_H_

#include <memory>
#include "cpp_type_traits.h"

namespace ft {
// Red-black tree class, designed for use in implementing STL
// associative containers (set, multiset, map, and multimap). The
// insertion and deletion algorithms are based on those in Cormen,
// Leiserson, and Rivest, Introduction to Algorithms (MIT Press,
// 1990), except that
//
// (1) the header cell is maintained with links not only to the root
// but also to the leftmost node of the tree, to enable constant
// time begin(), and to the rightmost node of the tree, to enable
// linear time performance when used with the generic set algorithms
// (set_union, etc.)
// 
// (2) when a node being deleted has two children its successor node
// is relinked into its place, rather than copied, so that the only
// iterators invalidated are those referring to the deleted node.

enum Rb_tree_color { S_red = false, S_black = true; }

struct Rb_tree_node_base
{
  typedef Rb_tree_node_base*        Base_ptr;
  typedef const Rb_tree_node_base*  Const_Base_ptr;

  Rb_tree_color   M_color;
  Base_ptr        M_parent;
  Base_ptr        M_left;
  Base_ptr        M_right;

  static Base_ptr
  S_minimum(Base_ptr x)
  {
    while (x->M_left != 0) x = x->M_left;
    return x;
  }
  
  static Const_Base_ptr
  S_minimum(Const_Base_ptr x)
  {
    while (x->M_left != 0) x = x->M_left;
    return x;
  }
  
  static Base_ptr
  S_maximum(Base_ptr x)
  {
    while (x->M_right != 0) x = x->M_right;
    return x;
  }
  
  static Const_Base_ptr
  S_maximum(Const_Base_ptr x)
  {
    while (x->M_right != 0) x = x->M_right;
    return x;
  }
};

template <typename Val>
struct Rb_tree_node : public Rb_tree_node_base
{
  typedef Rb_tree_node<Val>*  Link_type;
  Val                         M_value_field;
};

Rb_tree_node_base*
Rb_tree_increment(Rb_tree_node_base* x)
{
  if (x->M_right != 0)
  {
    x = x->M_right;
    while (x->M_left != 0)
      x = x->M_left;
  }
  else
  {
    Rb_tree_node_base* y = x->M_parent;
    while (x == y->M_right)
    {
      x = y;
      y = y->M_parent;
    }
    //
    // Can't understand
    //
    if (x->M_right != y)
      x = y;
  }
  return x;
}

const Rb_tree_node_base*
Rb_tree_increment(const Rb_tree_node_base* x)
{
  return Rb_tree_increment(const_cast<Rb_tree_node_base*>(x));
}

Rb_tree_node_base*
Rb_tree_decrement(Rb_tree_node_base* x)
{
  //
  // Can't understand
  //
  if (x->M_color == S_red
      && x->M_parent->M_parent == x)
      x = x->M_right;
  else if (x->M_left != 0)
  {
    Rb_tree_node_base* y = x->M_left;
    while (y->M_right != 0)
      y = y->M_right;
    x = y;
  }
  else
  {
    Rb_tree_node_base* y = x->M_parent;
    while (x == y->M_left)
    {
      x = y;
      y = y->M_parent;
    }
    x = y;
  }
  return x;
}

const Rb_tree_node_base*
Rb_tree_decrement(const Rb_tree_node_base* x)
{
  return Rb_tree_decrement(const_cast<Rb_tree_node_base*>(x));
}

template <typename Tp>
struct Rb_tree_iterator
{
  typedef Tp                          value_type;
  typedef Tp&                         reference;
  typedef Tp*                         pointer;

  typedef bidirectional_iterator_tag  iterator_category;
  typedef ptrdiff_t                   difference_type;

  typedef Rb_tree_iterator<Tp>        Self;
  typedef Rb_tree_node_base::Base_ptr Base_ptr;
  typedef Rb_tree_node<Tp>*           Link_type;

  Base_ptr M_node;

  Rb_tree_iterator()
  : M_node() { }

  explicit
  Rb_tree_iterator(Link_type x)
  : M_node(x) { }

  reference
  operator*() const
  { return static_cast<Link_type>(M_node)->M_value_field; }

  pointer
  operator->() const
  { return &static_cast<Link_type>(M_node)->M_value_field; }

  Self&
  operator++()
  {
    M_node = Rb_tree_increment(M_node);
    return *this;
  }

  Self&
  operator++(int)
  {
    Self tmp = *this;
    M_node = Rb_tree_increment(M_node);
    return tmp;
  }

  Self&
  operator--()
  {
    M_node = Rb_tree_decrement(M_node);
    return *this;
  }

  Self&
  operator--(int)
  {
    Self tmp = *this;
    M_node = Rb_tree_decrement(M_node);
    return tmp;
  }

  bool
  operator==(const Self& x) const
  { return M_node == x.M_node; }

  bool
  operator!=(const Self& x) const
  { return M_node != x.M_node; }
};

template <typename Tp>
struct Rb_tree_const_iterator
{
  typedef Tp                                value_type;
  typedef const Tp&                         reference;
  typedef const Tp*                         pointer;

  typedef Rb_tree_iterator<Tp>              iterator;

  typedef bidirectional_iterator_tag        iterator_category;
  typedef ptrdiff_t                         difference_type;

  typedef Rb_tree_const_iterator<Tp>        Self;
  typedef Rb_tree_node_base::Const_Base_ptr Base_ptr;
  typedef constRb_tree_node<Tp>*            Link_type;

  Base_ptr M_node;

  Rb_tree_const_iterator()
  : M_node() { }

  explicit
  Rb_tree_const_iterator(Link_type x)
  : M_node(x) { }

  Rb_tree_const_iterator(const iterator& it)
  : M_node(it.M_node) { }

  reference
  operator*() const
  { return static_cast<Link_type>(M_node)->M_value_field; }

  pointer
  operator->() const
  { return &static_cast<Link_type>(M_node)->M_value_field; }

  Self&
  operator++()
  {
    M_node = Rb_tree_increment(M_node);
    return *this;
  }

  Self&
  operator++(int)
  {
    Self tmp = *this;
    M_node = Rb_tree_increment(M_node);
    return tmp;
  }

  Self&
  operator--()
  {
    M_node = Rb_tree_decrement(M_node);
    return *this;
  }

  Self&
  operator--(int)
  {
    Self tmp = *this;
    M_node = Rb_tree_decrement(M_node);
    return tmp;
  }

  bool
  operator==(const Self& x) const
  { return M_node == x.M_node; }

  bool
  operator!=(const Self& x) const
  { return M_node != x.M_node; }
};

template <typename Val>
bool
operator==(const Rb_tree_iterator<Val>& x,
          const Rb_tree_const_iterator<Val>& y)
{ return x.M_node == y.M_node; }

template <typename Val>
bool
operator!=(const Rb_tree_iterator<Val>& x,
          const Rb_tree_const_iterator<Val>& y)
{ return x.M_node != y.M_node; }

void
Rb_tree_rotate_left(Rb_tree_node_base* const x,
                    Rb_tree_node_base*& root)
{
  Rb_tree_node_base* const y = x->M_right;

  x->M_right = y->M_left;
  if (y->M_left != 0)
    y->M_left->M_parent = x;
  y->M_parent = x->M_parent;

  if (x == root)
    root = y;
  else if (x == x->M_parent->M_left)
    x->M_parent->M_left = y;
  else
    x->M_parent->M_right = y;
  y->M_left = x;
  x->M_parent = y;
}

void
Rb_tree_rotate_right(Rb_tree_node_base* const x,
                    Rb_tree_node_base*& root)
{
  Rb_tree_node_base* const y = x->M_left;

  x->M_left = y->M_right;
  if (y->M_right != 0)
    y->M_right->M_parent = x;
  y->M_parent = x->M_parent;

  if (x == root)
    root = y;
  else if (x == x->M_parent->M_right)
    x->M_parent->M_right = y;
  else
    x->M_parent->M_left = y;
  y->M_right = x;
  x->M_parent = y;
}

void
Rb_tree_insert_and_rebalance(const bool insert_left,
                            Rb_tree_node_base* x,
                            Rb_tree_node_base* p,
                            Rb_tree_node_base& header)
{
  Rb_tree_node_base*& root = header.M_parent;

  // Initialize fields in new node to insert.
  x->M_parent = p;
  x->M_left = 0;
  x->M_right = 0;
  x->M_color = S_red;

  // Insert.
  // Make new node child of parent and maintain root, leftmost and
  // rightmost nodes.
  // N.B. First node is always inserted left.
  if (insert_left)
  {
    p->M_left = x; // also makes leftmost = x when p == &header

    if (p == &header)
    {
      header.M_parent = x;
      header.M_right = x;
    }
    else if (p == header.M_left)
      header.M_left = x; // maintain leftmost pointing to min node
  }
  else
  {
    p->M_right = x;

    if (p == header.M_right)
      header.M_right = x; // maintain rightmost pointing to max node
  }
  // Rebalance.
  while (x != root
    && x->M_parent->M_color == S_red)
  {
    Rb_tree_node_base* const xpp = x->M_parent->M_parent;

    if (x->M_parent == xpp->M_left)
    {
      Rb_tree_node_base* const y = xpp->M_right;

      if (y && y->M_color == S_red) // Case 1
      {
        x->M_parent->M_color = S_black;
        y->M_color = S_black;
        xpp->M_color = S_red;
        x = xpp;
      }
      else  // Case 2
      {
        if (x == x->M_parent->M_right)
        {
          x = x->M_parent;
          Rb_tree_rotate_left(x, root);
        }
        x->M_parent->M_color = S_black;
        xpp->M_color = S_red;
        Rb_tree_rotate_right(xpp, root);
      }
    }
    else
    {
      Rb_tree_node_base* const y = xpp->M_left;

      if (y && y->M_color == S_red) // Case 1
      {
        x->M_parent->M_color = S_black;
        y->M_color = S_black;
        xpp->M_color = S_red;
        x = xpp;
      }
      else  // Case 2
      {
        if (x == x->M_parent->M_left)
        {
          x = x->M_parent;
          Rb_tree_rotate_right(x, root);
        }
        x->M_parent->M_color = S_black;
        xpp->M_color = S_red;
        Rb_tree_rotate_left(xpp, root);
      }
    }
  }
  root->M_color = S_black;
}

Rb_tree_node_base*
Rb_tree_rebalance_for_erase(Rb_tree_node_base* const z,
                            Rb_tree_node_base& header)
{
  Rb_tree_node_base*& root = header.M_parent;
  Rb_tree_node_base*& leftmost = header.M_left;
  Rb_tree_node_base*& rightmost = header.M_right;
  Rb_tree_node_base* y = z;
  Rb_tree_node_base* x = 0;
  Rb_tree_node_base* x_parent = 0;

  if (y->M_left == 0)     // z has at most one non-null child. y == z.
    x = y->M_right;       // x might be null.
  else
  {
    if (y->M_right == 0)  // z has exactly one non-null child. y == z.
      x = y->M_left;
    else
    {
	    // z has two non-null children.
      y = y->M_right;   // Set y to z's successor.  x might be null.
      while (y->M_left != 0)
        y = y->M_left;
      x = y->M_right;
    }
  }

  if (y != z)
  {
  	// relink y in place of z.  y is z's successor
    z->M_left->M_parent = y;
    y->M_left = z->M_left;
    if (y != z->M_right)
    {
      x_parent = y->M_parent;
      if (x) x->M_parent = y->M_parent;
      y->M_parent->M_left = x;   // y must be a child of M_left
      y->M_right = z->M_right;
      z->M_right->M_parent = y;
    }
    else
      x_parent = y;

    if (root == z)
      root = y;
    else if (z->M_parent->M_left == z)
      z->M_parent->M_left = y;
    else
      z->M_parent->M_right = y;
    y->M_parent = z->M_parent;
    std::swap(y->M_color, z->M_color);
    y = z;
	  // y now points to node to be actually deleted
  }
  else
  {
    // y == z
    x_parent = y->M_parent;
    if (x)
      x->M_parent = y->M_parent;

    if (root == z)
      root = x;
    else
    {
      if (z->M_parent->M_left == z)
        z->M_parent->M_left = x;
      else
        z->M_parent->M_right = x;
    }

    if (leftmost == z)
    {
      if (z->M_right == 0)        // __z->_M_left must be null also
        leftmost = z->M_parent;
	    else                        // makes __leftmost == _M_header if __z == __root
        leftmost = Rb_tree_node_base::S_minimum(x);
    }

    if (rightmost == z)
    {
      if (z->M_left == 0)         // __z->_M_right must be null also
        rightmost = z->M_parent;
      else                        	// makes __rightmost == _M_header if __z == __root
        rightmost = Rb_tree_node_base::S_maximum(x);  // __x == __z->_M_left
    }
  }

  if (y->M_color != S_red)
  {
    while (x != root && (x == 0 || x->M_color == S_black))
    {
      if (x == x_parent->M_left)
      {
        Rb_tree_node_base* w = x_parent->M_right;
        if (w->M_color == S_red)  // Case 1
        {
          w->M_color = S_black;
          x_parent->M_color = S_red;
          Rb_tree_rotate_left(x_parent, root);
          w = x_parent->M_right;
        }

        if ((w->M_left == 0 ||
            w->M_left->M_color == S_black) &&
            (w->M_right == 0 ||
            w->M_right->M_color == S_black))  // Case 2
        {
          w->M_color = S_red;
          x = x_parent;
          x_parent = x->M_parent->M_parent
        }
        else
        {
          if (w->M_right == 0
            || w->M_right->M_color == S_black) // Case 3
          {
            w->M_left->M_color = S_black;
            w->M_color = S_red;
            Rb_tree_rotate_right(w, root);
            w = x_parent->M_right;
          }
          w->M_color = x_parent->M_color; // Case 4
          x_parent->M_color = S_black;
          if (w->M_right)
            w->M_right->M_color = S_black;
          Rb_tree_rotate_left(x_parent, root);
          break;
        }
      }
      else
      {
 	      // same as above, with _M_right <-> _M_left.
        Rb_tree_node_base* w = x_parent->M_left;
        if (w->M_color == S_red)  // Case 1
        {
          w->M_color = S_black;
          x_parent->M_color = S_red;
          Rb_tree_rotate_right(x_parent, root);
          w = x_parent->M_left;
        }

        if ((w->M_right == 0 ||
            w->M_right->M_color == S_black) &&
            (w->M_left == 0 ||
            w->M_left->M_color == S_black))  // Case 2
        {
          w->M_color = S_red;
          x = x_parent;
          x_parent = x->M_parent->M_parent
        }
        else
        {
          if (w->M_left == 0
            || w->M_left->M_color == S_black)  // Case 3
          {
            w->M_right->M_color = S_black;
            w->M_color = S_red;
            Rb_tree_rotate_left(w, root);
            w = x_parent->M_left;
          }
          w->M_color = x_parent->M_color; // Case 4
          x_parent->M_color = S_black;
          if (w->M_left)
            w->M_left->M_color = S_black;
          Rb_tree_rotate_right(x_parent, root);
          break;
        }
      }
    }
    if (x) x->M_color = S_black;
  }
  return y;
}


template <typename Key, typename Val, typename KeyOfValue,
          typename Compare, typename Alloc = std::allocator<Val> >
class Rb_tree
{
  typedef typename Alloc:template std::rebind<Rb_tree_node<Val> >::other
          Node_allocator;

  protected:
    typedef Rb_tree_node_base*        Base_ptr;
    typedef const Rb_tree_node_base*  Const_Base_ptr;
    typedef Rb_tree_node<Val>         Rb_tree_node;

    template <typename Key_compare,
              bool Is_pod_comparator = std::__is_pod<Key_compare>::__value>
    struct Rb_tree_impl : public Node_allocator
    {
      Key_compare       M_key_compare;
      Rb_tree_node_base M_header;
      size_type         M_node_count; // Keeps track of size of tree.

      Rb_tree_impl(const Node_allocator& a = Node_allocator(),
        const Key_compare& comp = Key_compare())
      : Node_allocator(a), M_key_compare(comp), M_header(),
        M_node_count(0)
      {
        this->M_header.M_color = S_red;
        this->M_header.M_parent = 0;
        this->M_header.M_left = &this->M_header;
        this->M_header.M_right = &this->M_header;
      }
    };

    // Specialization for Comparison types that are not capable of
    // being base classes / super classes.
    template <typename Key_compare>
    struct Rb_tree_impl<Key_compare, true> : public Node_allocator
    {
      Key_compare       M_key_compare;
      Rb_tree_node_base M_header;
      size_type         M_node_count; // Keeps track of size of tree.

      Rb_tree_impl(const Node_allocator& a = Node_allocator(),
        const Key_compare& comp = Key_compare())
      : Node_allocator(a), M_key_compare(comp), M_header(),
        M_node_count(0)
      {
        this->M_header.M_color = S_red;
        this->M_header.M_parent = 0;
        this->M_header.M_left = &this->M_header;
        this->M_header.M_right = &this->M_header;
      }
    }

    Rb_tree_impl<Compare>       M_impl;

  public:
    typedef Key                 key_type;
    typedef Val                 value_type;
    typedef value_type*         pointer;
    typedef const value_type*   const_pointer;
    typedef value_type&         reference;
    typedef const value_type&   const_reference;
    typedef Rb_tree_node*       Link_type;
    typedef const Rb_tree_node* Const_Link_type;
    typedef std::size_t         size_type;
    typedef std::ptrdiff_t      differnece_type;
    typedef Alloc               allocator_type;

    Node_allocator&
    M_get_Node_allocator()
    { }


}

} // ft
#endif // STL_TREE_H_