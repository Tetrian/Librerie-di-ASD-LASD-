
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec: virtual public BinaryTree<Data> { // Must extend BinaryTree<Data>

private:

  // ...

protected:

  using BinaryTree<Data>::size;

  // ...

  struct NodeVec: virtual public BinaryTree<Data>::Node { // Must extend Node

  private:

    // ...

  protected:

    // ...

  public:

    // Fields
    Data info;
    ulong current = 0;
    Vector<NodeVec> *vecptr = nullptr; // mi serve tener traccia del vettore dei nodi
                                       // altrimenti non potrei accedere ai figli

    /* ********************************************************************** */

    // Default constructor
    NodeVec() = default;

    /* ********************************************************************** */

    // Destructor
    virtual ~NodeVec() = default;

    /* ********************************************************************** */

    // Copy assignment
    NodeVec& operator=(const NodeVec&);

    // Move assignmente
    NodeVec& operator=(NodeVec&&) noexcept;

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const NodeVec&) const noexcept;
    bool operator!=(const NodeVec&) const noexcept;

    /* ********************************************************************** */

    // Specific member functions

    inline Data& Element() noexcept override { return info; } // Mutable access to the element (concrete function should not throw exceptions)
    const inline Data& Element() const noexcept override { return info; } // Immutable access to the element (concrete function should not throw exceptions)

    inline bool IsLeaf() const noexcept override { return ((2*current + 1) > vecptr->Size()); } // (concrete function should not throw exceptions)
    inline bool HasLeftChild() const noexcept override { return ((2*current + 1) < vecptr->Size()); } // (concrete function should not throw exceptions)
    inline bool HasRightChild() const noexcept override { return ((2*current + 2) < vecptr->Size()); } // (concrete function should not throw exceptions)

    NodeVec& LeftChild() const override; // (concrete function must throw std::out_of_range when not existent)
    NodeVec& RightChild() const override; // (concrete function must throw std::out_of_range when not existent)

  };

  Vector<NodeVec> *vec = nullptr;

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec&);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec& operator=(const BinaryTreeVec&);

  // Move assignment
  BinaryTreeVec& operator=(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // vanno bene quelle implementate in binarytree.cpp ma volendo potrei
  // ottimizzare queste funzioni sfruttando il fatto che sia un vettore
  // bool operator==(const BinaryTreeVec&) const noexcept;
  // bool operator!=(const BinaryTreeVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeVec& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
