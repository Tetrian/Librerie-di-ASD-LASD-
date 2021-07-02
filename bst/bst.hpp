
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST: virtual public BinaryTreeLnk<Data> { // Must extend BinaryTreeLnk<Data>

private:

  // ...

protected:

  using BinaryTreeLnk<Data>::size;
  using BinaryTreeLnk<Data>::root;

  // ...

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const LinearContainer<Data>&); // A bst obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST&); // eredita da binarytreelnk

  // Move constructor
  BST(BST&&) noexcept; // eredita da binarytreelnk

  /* ************************************************************************ */

  // Destructor
  ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST& operator=(const BST&); // eredita da binarytreelnk

  // Move assignment
  BST& operator=(BST&&) noexcept; // eredita da binarytreelnk

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BST&) const noexcept;
  bool operator!=(const BST&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void Insert(const Data&) noexcept; // Copy of the value
  void Insert(Data&&) noexcept; // Move of the value
  void Remove(const Data&) noexcept;

  const Data& Min() const; // (concrete function must throw std::length_error when empty)
  Data MinNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMin(); // (concrete function must throw std::length_error when empty)

  const Data& Max() const; // (concrete function must throw std::length_error when empty)
  Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMax(); // (concrete function must throw std::length_error when empty)

  const Data& Predecessor(const Data&) const; // (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data&); // (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data&); // (concrete function must throw std::length_error when not found)

  const Data& Successor(const Data&) const; // (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data&); // (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data&); // (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

protected:

  // Auxiliary member functions

  bool ComparisonInOrder(bool&, const typename BinaryTreeLnk<Data>::NodeLnk*, BTInOrderIterator<Data>&) const noexcept;

  Data DataNDelete(typename BinaryTreeLnk<Data>::NodeLnk*) noexcept;

  typename BinaryTreeLnk<Data>::NodeLnk* Detach(typename BinaryTreeLnk<Data>::NodeLnk*&) noexcept;

  typename BinaryTreeLnk<Data>::NodeLnk* DetachMin(typename BinaryTreeLnk<Data>::NodeLnk*&) noexcept;
  typename BinaryTreeLnk<Data>::NodeLnk* DetachMax(typename BinaryTreeLnk<Data>::NodeLnk*&) noexcept;

  typename BinaryTreeLnk<Data>::NodeLnk* SkipOnLeft(typename BinaryTreeLnk<Data>::NodeLnk*&) noexcept;
  typename BinaryTreeLnk<Data>::NodeLnk* SkipOnRight(typename BinaryTreeLnk<Data>::NodeLnk*&) noexcept;

  // NOTA BENE: per le successive funzioni dovete ritornare un doppio puntatore e non un riferimento al puntatore perché
  // se il prof vi becca con questo all'orale da di matto e vi toglie almeno un punto xD Quindi modificate il codice di
  // conseguenza, scusate se non lo faccio io ma mi pesa davvero troppo il culo, BUONA FORTUNA.
  typename BinaryTreeLnk<Data>::NodeLnk* const& FindPointerToMin(typename BinaryTreeLnk<Data>::NodeLnk* const&) const noexcept;
  typename BinaryTreeLnk<Data>::NodeLnk*& FindPointerToMin(typename BinaryTreeLnk<Data>::NodeLnk* const&) noexcept;
  typename BinaryTreeLnk<Data>::NodeLnk* const& FindPointerToMax(typename BinaryTreeLnk<Data>::NodeLnk* const&) const noexcept;
  typename BinaryTreeLnk<Data>::NodeLnk*& FindPointerToMax(typename BinaryTreeLnk<Data>::NodeLnk* const&) noexcept;

  typename BinaryTreeLnk<Data>::NodeLnk* const& FindPointerTo(const Data&, typename BinaryTreeLnk<Data>::NodeLnk* const&) const noexcept;
  typename BinaryTreeLnk<Data>::NodeLnk*& FindPointerTo(const Data&, typename BinaryTreeLnk<Data>::NodeLnk* const&) noexcept;

  typename BinaryTreeLnk<Data>::NodeLnk* const& FindPointerToPredecessor(const Data&) const noexcept;
  typename BinaryTreeLnk<Data>::NodeLnk*& FindPointerToPredecessor(const Data&) noexcept;
  typename BinaryTreeLnk<Data>::NodeLnk* const& FindPointerToSuccessor(const Data&) const noexcept;
  typename BinaryTreeLnk<Data>::NodeLnk*& FindPointerToSuccessor(const Data&) noexcept;

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
