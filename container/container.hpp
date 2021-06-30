
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

// // Se usate windows aggiungere queste due linee di codice, poiché
// // il compilatore non accetta uint come abbreviazione di unsigned int
// #define uint unsigned int
// #define ulong unsigned long

/* ************************************************************************** */

#include <stdexcept>
#include <functional> // libreria necessaria per i puntatori a funzione

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

class Container {

private:

  // ...

protected:

  ulong size = 0;

public:

  // Destructor
  virtual ~Container() = default; // definire i distruttori virtuali serve
                                  // per evitare problemi di segmentazione
                                  // (eliminare la classe padre lasciando
                                  //  intatta la classe figlio)

  /* ************************************************************************ */

  // Copy assignment
  Container& operator=(const Container&) = delete;  // essendo una classe astratta
                                                    // dunque non instanziabile
                                                    // non è possibile definire
                                                    // queste espressioni, quindi
                                                    // = delete
  // Move assignment
  Container& operator=(Container&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Container&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const Container&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  // la inline dice al compilatore di sostituire direttamente il corpo delle funzioni
  // quando vede il nome della funzione (valido solo per funzioni molto brevi)
  virtual inline bool Empty() const noexcept { return (size == 0); } // (concrete function should not throw exceptions)

  virtual inline ulong Size() const noexcept { return size; } // (concrete function should not throw exceptions)

  virtual void Clear() = 0;

};

/* ************************************************************************** */

template <typename Data>
class LinearContainer: virtual public Container { // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer& operator=(const LinearContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  LinearContainer& operator=(LinearContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const LinearContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const LinearContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions
  // i linear conteiner contengono dati ordinati linearmente secondo l'occupazione in memoria
  // e questo ci permette di poter assegnare un indice agli elementi, da cui le seguenti funzioni

  virtual Data& Front() const = 0; // (concrete function must throw std::length_error when empty)
  virtual Data& Back() const = 0; // (concrete function must throw std::length_error when empty)

  virtual Data& operator[](const ulong) const = 0; // (concrete function must throw std::out_of_range when out of range)

};

/* ************************************************************************** */

template <typename Data>
class TestableContainer: virtual public Container { // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~TestableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  TestableContainer& operator=(const TestableContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  TestableContainer& operator=(TestableContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const TestableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const TestableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions
  // contenitori testabili, da cui la funzione Exist (non implementabile a questo livello)
  virtual bool Exists(const Data&) const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class MappableContainer: virtual public Container { // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~MappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MappableContainer& operator=(const MappableContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  MappableContainer& operator=(MappableContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MappableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const MappableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions
  // definizione di puntatore a funzione con ritorno void e parametri Data&, void*
  typedef std::function<void(Data&, void*)> MapFunctor;

  virtual void MapPreOrder(const MapFunctor, void*) = 0;
  virtual void MapPostOrder(const MapFunctor, void*) = 0;

};

/* ************************************************************************** */

template <typename Data>
class FoldableContainer: virtual public TestableContainer<Data> { // Must extend TestableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~FoldableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  FoldableContainer& operator=(const FoldableContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  FoldableContainer& operator=(FoldableContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const FoldableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const FoldableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions
  // definizione di puntatore a funzione con ritorno void e parametri Data&, const void*, void*
  typedef std::function<void(const Data&, const void*, void*) noexcept> FoldFunctor;

  virtual void FoldPreOrder(const FoldFunctor, const void*, void*) const = 0;
  virtual void FoldPostOrder(const FoldFunctor, const void*, void*) const = 0;

  // grazie alle fold è possibile definire la funzione Exists di TestableContainer
  virtual bool Exists(const Data&) const noexcept override; // Override TestableContainer member

};

/* ************************************************************************** */

// Di seguito classi di contenitore astratte navigabili in InOrder e in Ampiezza

template <typename Data>
class InOrderMappableContainer: virtual public MappableContainer<Data> { // Must extend MappableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~InOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  InOrderMappableContainer& operator=(const InOrderMappableContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  InOrderMappableContainer& operator=(InOrderMappableContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const InOrderMappableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const InOrderMappableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  using typename MappableContainer<Data>::MapFunctor;

  virtual void MapInOrder(const MapFunctor, void*) = 0;

};

/* ************************************************************************** */

template <typename Data>
class InOrderFoldableContainer: virtual public FoldableContainer<Data> { // Must extend FoldableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~InOrderFoldableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  InOrderFoldableContainer& operator=(const InOrderFoldableContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  InOrderFoldableContainer& operator=(InOrderFoldableContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const InOrderFoldableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const InOrderFoldableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  using typename FoldableContainer<Data>::FoldFunctor;

  virtual void FoldInOrder(const FoldFunctor, const void*, void*) const = 0;

};

/* ************************************************************************** */

template <typename Data>
class BreadthMappableContainer: virtual public MappableContainer<Data> { // Must extend MappableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~BreadthMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  BreadthMappableContainer& operator=(const BreadthMappableContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  BreadthMappableContainer& operator=(BreadthMappableContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BreadthMappableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const BreadthMappableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  using typename MappableContainer<Data>::MapFunctor;

  virtual void MapBreadth(const MapFunctor, void*) = 0;

};

/* ************************************************************************** */

template <typename Data>
class BreadthFoldableContainer: virtual public FoldableContainer<Data> { // Must extend FoldableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~BreadthFoldableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  BreadthFoldableContainer& operator=(const BreadthFoldableContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  BreadthFoldableContainer& operator=(BreadthFoldableContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BreadthFoldableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const BreadthFoldableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  using typename FoldableContainer<Data>::FoldFunctor;

  virtual void FoldBreadth(const FoldFunctor, const void*, void*) const = 0;

};

/* ************************************************************************** */

}

#include "container.cpp"

#endif
