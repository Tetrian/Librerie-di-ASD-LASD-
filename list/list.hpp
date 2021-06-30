#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List: virtual public LinearContainer<Data>,
            virtual public MappableContainer<Data>,
            virtual public FoldableContainer<Data> { // Must extend LinearContainer<Data>, MappableContainer<Data>, and FoldableContainer<Data>

private:

  // ...

protected:

  using LinearContainer<Data>::size;

  struct Node {

    // Data
    Data info;
    Node *next = nullptr;
    Node *prev = nullptr; // si può benissimo evitare il successore prev, non è
                          // richiesto nella traccia ed è più semplice collegare
                          // i puntatori evitando potenziali errori

    /* ********************************************************************** */

    // Default constructor
    Node() = default;

    // Specific constructors
    Node(const Data& value) {
      info = value; // copy of the value
    };

    Node(Data&& value) noexcept {
      info = std::move(value); // move of the value
    };

    /* ********************************************************************** */

    // Copy constructor

    //  ...

    // Move constructor

    // ...

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Comparison operators

    // ...

    /* ********************************************************************** */

    // Specific member functions

    // ...

  };

  // ...

public:

  // Data
  Node *head = nullptr;
  Node *tail = nullptr;

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  List(const LinearContainer<Data>&); // A list obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  List(const List&);

  // Move constructor
  List(List&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~List();

  /* ************************************************************************ */

  // Copy assignment
  List& operator=(const List&);

  // Move assignment
  List& operator=(List&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List&) const noexcept;
  bool operator!=(const List&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data&); // Copy of the value
  void InsertAtFront(Data&&) noexcept; // Move of the value

  void RemoveFromFront(); // (must throw std::length_error when empty)
  Data FrontNRemove(); // (must throw std::length_error when empty)

  void InsertAtBack(const Data&); // Copy of the value
  void InsertAtBack(Data&&) noexcept; // Move of the value

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  Data& Front() const override; // Override LinearContainer member (must throw std::length_error when empty)
  Data& Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

  Data& operator[](const ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

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

  // Le seguenti funzioni ausiliarie servono nel caso si volesse applicare la ricorsione, con il doppio puntatore
  // non è necessario mentre se si usa solo il puntatore next è utile per la complessità nelle post order, vedi
  // codice di matrixcsr per un esempio, le ho usate lì.

  // Auxiliary member functions (for MappableContainer)

  // type MapPreOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards
  // type MapPostOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards

  /* ************************************************************************ */

  // Auxiliary member functions (for FoldableContainer)

  // type FoldPreOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards
  // type FoldPostOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
