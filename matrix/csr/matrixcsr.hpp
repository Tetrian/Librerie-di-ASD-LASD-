
#ifndef MATRIXCSR_HPP
#define MATRIXCSR_HPP

/* ************************************************************************** */

#include "../matrix.hpp"

#include "../../list/list.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MatrixCSR : virtual public Matrix<Data>,
                  virtual protected List<std::pair<Data, ulong>> { // Must extend Matrix<Data>
                  // la pair è praticamente una coppia con primo dato l'elemento
                  // nella mia cella e secondo dato la colonna corrispondente
private:

  // ...

protected:

  using Matrix<Data>::row;
  using Matrix<Data>::clm;

  using List<std::pair<Data, ulong>>::size;
  using List<std::pair<Data, ulong>>::head;

  using typename List<std::pair<Data, ulong>>::Node; // così posso usare semplicemente Node invece di
  Vector<Node**> RowVec;                             // typename List<std::pair<Data, ulong>>::Node

  // ...

public:

  // Default constructor
  MatrixCSR();

  /* ************************************************************************ */

  // Specific constructors
  MatrixCSR(const ulong, const ulong); // A matrix of some specified dimension

  /* ************************************************************************ */

  // Copy constructor
  MatrixCSR(const MatrixCSR&);

  // Move constructor
  MatrixCSR(MatrixCSR&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~MatrixCSR() = default;

  /* ************************************************************************ */

  // Copy assignment
  MatrixCSR& operator=(const MatrixCSR&);

  // Move assignment
  MatrixCSR& operator=(MatrixCSR&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MatrixCSR&) const noexcept;
  bool operator!=(const MatrixCSR&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Matrix)

  void RowResize(const ulong) override; // Override Matrix member
  void ColumnResize(const ulong) override; // Override Matrix member

  bool ExistsCell(const ulong, const ulong) const noexcept override; // Override Matrix member (should not throw exceptions)

  Data& operator()(const ulong, const ulong) override; // Override Matrix member (mutable access to the element; throw out_of_range when out of range)
  Data const& operator()(const ulong, const ulong) const override; // Override Matrix member (immutable access to the element; throw out_of_range when out of range and length_error when not present)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void MapPreOrder(const MapFunctor, void*) override; // Override MappableContainer member
  void MapPostOrder(const MapFunctor, void*) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void FoldPreOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member
  void FoldPostOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

protected:

  // Auxiliary member functions

  void DeleteSubList(Node*); // delete starting from the current node

  void UpdateRowVec(ulong, Node*&); // change the equal cells of the vector starting from the input row with the address node;

  void MapPostOrder(const MapFunctor, void*, Node*); // Accessory function executing from one point of the list onwards

  void FoldPostOrder(const FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one point of the list onwards

};

/* ************************************************************************** */

}

#include "matrixcsr.cpp"

#endif
