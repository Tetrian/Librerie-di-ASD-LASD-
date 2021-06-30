
#ifndef MATRIXVEC_HPP
#define MATRIXVEC_HPP

/* ************************************************************************** */

#include "../matrix.hpp"

#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MatrixVec : virtual public Matrix<Data>,
                  virtual protected Vector<Data> { // Must extend Matrix<Data>

private:

  // ...

protected:

  using Matrix<Data>::row;
  using Matrix<Data>::clm;

  using Vector<Data>::size;
  using Vector<Data>::Elements;

public:

  // Default constructor
  MatrixVec();

  /* ************************************************************************ */

  // Specific constructors
  MatrixVec(const ulong, const ulong); // A matrix of some specified dimension

  /* ************************************************************************ */

  // Copy constructor
  MatrixVec(const MatrixVec&);

  // Move constructor
  MatrixVec(MatrixVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~MatrixVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  MatrixVec& operator=(const MatrixVec&);

  // Move assignment
  MatrixVec& operator=(MatrixVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MatrixVec&) const noexcept;
  bool operator!=(const MatrixVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Matrix)

  void RowResize(const ulong) override; // Override Matrix member
  void ColumnResize(const ulong) override; // Override Matrix member

  inline bool ExistsCell(const ulong irow, const ulong iclm) const noexcept override { return (irow < row && iclm < clm); } // Override Matrix member (should not throw exceptions)

  Data& operator()(const ulong, const ulong) override; // Override Matrix member (mutable access to the element; throw out_of_range when out of range)
  Data const& operator()(const ulong, const ulong) const override; // Override Matrix member (immutable access to the element; throw out_of_range when out of range and length_error when not present)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

  /* ************************************************************************ */

  // essendo un unico vettore, non ho nessun bisogno di riscrivere
  // le funzioni map e fold, infatti eredito quelle da vector

  // Specific member functions (inherited from MappableContainer)
  
  using typename Vector<Data>::MapPreOrder; // Override MappableContainer member
  using typename Vector<Data>::MapPostOrder; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename Vector<Data>::FoldPreOrder; // Override FoldableContainer member
  using typename Vector<Data>::FoldPostOrder; // Override FoldableContainer member

};

/* ************************************************************************** */

}

#include "matrixvec.cpp"

#endif
