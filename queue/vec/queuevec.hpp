
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec: virtual public Queue<Data>,
                virtual protected Vector<Data> { // Must extend Queue<Data> and Vector<Data>
                // eredita da vettore in maniera protetta, poichè l'utente non deve poter usare le
                // funzioni di vettore, quindi ciò che era pubblico in vettore è protetto in codav

private:

  // ...

protected:

  using Vector<Data>::size;
  using Vector<Data>::Elements;

  ulong head = 0; // index of the first element

  ulong tail = 0; // index of the first free cell

  ulong sentry = 0; // index of the last free cell

  // ...

public:

  // Default constructor
  QueueVec();

  /* ************************************************************************ */

  // Specific constructor
  QueueVec(const LinearContainer<Data>&); // A queue obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueVec(const QueueVec&);

  // Move constructor
  QueueVec(QueueVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  QueueVec& operator=(const QueueVec&);

  // Move assignment
  QueueVec& operator=(QueueVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueVec&) const noexcept;
  bool operator!=(const QueueVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  void Enqueue(const Data&) override; // Override Queue member (copy of the value)
  void Enqueue(Data&&) noexcept override; // Override Queue member (move of the value)
  Data& Head() const override; // Override Queue member (must throw std::length_error when empty)
  void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept override { return (head == tail); } // Override Container member

  ulong Size() const noexcept override; // Override Container member

  void Clear() override; // Override Container member

protected:

  // Auxiliary member functions

  void Expand();
  void Reduce();
  // type SwapVectors(arguments) specifiers;

};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif
