
#ifndef MATRIX_HPP
#define MATRIX_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Matrix: virtual public MappableContainer<Data>,
              virtual public FoldableContainer<Data> { // Must extend MappableContainer<Data> and FoldableContainer<Data>

private:

  // ...

protected:

  ulong row = 0;
  ulong clm = 0;

public:

  // Destructor
  virtual ~Matrix() = default;

  /* ************************************************************************ */

  // Copy assignment
  Matrix& operator=(const Matrix&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  Matrix& operator=(Matrix&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Matrix&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const Matrix&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual inline ulong RowNumber() const noexcept { return row; } // (concrete function should not throw exceptions)
  virtual inline ulong ColumnNumber() const noexcept { return clm; } // (concrete function should not throw exceptions)

  virtual void RowResize(const ulong) = 0;
  virtual void ColumnResize(const ulong) = 0;

  virtual bool ExistsCell(const ulong, const ulong) const noexcept = 0; // (concrete function should not throw exceptions)

  virtual Data& operator()(const ulong, const ulong) = 0; // Mutable access to the element (concrete function should throw exceptions only when out of range)
  virtual Data const& operator()(const ulong, const ulong) const = 0; // Immutable access to the element (concrete function should throw exceptions when not present)

};

/* ************************************************************************** */

}

#include "matrix.cpp"

#endif
