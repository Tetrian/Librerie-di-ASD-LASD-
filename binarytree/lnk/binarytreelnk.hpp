
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk: virtual public BinaryTree<Data> { // Must extend BinaryTree<Data>

private:

  // ...

protected:

  using BinaryTree<Data>::size;

  // ...

  struct NodeLnk: virtual public BinaryTree<Data>::Node { // Must extend Node

  private:

    // ...

  protected:

    // ...

  public:

    // Fields
    Data info;
    NodeLnk *left = nullptr;
    NodeLnk *right = nullptr;

    /* ********************************************************************** */

    // Default constructor
    NodeLnk() = default;

    // Specific constructors
    NodeLnk(const Data&); // Copy of the value

    NodeLnk(Data&&) noexcept; // Move of the value

    /* ********************************************************************** */

    // Destructor
    virtual ~NodeLnk();

    /* ********************************************************************** */

    // Copy assignment
    NodeLnk& operator=(const NodeLnk&);

    // Move assignment
    NodeLnk& operator=(NodeLnk&&) noexcept;

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const NodeLnk&) const noexcept;
    bool operator!=(const NodeLnk&) const noexcept;

    /* ********************************************************************** */

    // Specific member functions

    inline Data& Element() noexcept override { return info; } // Mutable access to the element (concrete function should not throw exceptions)
    const inline Data& Element() const noexcept override { return info; } // Immutable access to the element (concrete function should not throw exceptions)

    // type IsLeaf() specifiers; // (concrete function should not throw exceptions)
    inline bool HasLeftChild() const noexcept override { return (left != nullptr); } // (concrete function should not throw exceptions)
    inline bool HasRightChild() const noexcept override { return (right != nullptr); } // (concrete function should not throw exceptions)

    NodeLnk& LeftChild() const override; // (concrete function must throw std::out_of_range when not existent)
    NodeLnk& RightChild() const override; // (concrete function must throw std::out_of_range when not existent)

  };

  NodeLnk *root = nullptr;

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk&);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators (uso quelle implementate in BinaryTree.cpp)
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeLnk& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

protected:

  // Auxiliary member function for the BinaryTreeLnk specific constructor

  NodeLnk* AuxBTLcon(const LinearContainer<Data>&, NodeLnk*, ulong);

  /* ************************************************************************ */

  // Auxiliary member function for the BinaryTreeLnk copy constructor

  NodeLnk* AuxBTLcopy(const NodeLnk*, NodeLnk*);

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
