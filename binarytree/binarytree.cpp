
#include "../queue/lst/queuelst.hpp"

namespace lasd {

/* ************************************************************************** */

// Di seguito le funzioni implementabili a livello astratto della struttura Node

// Specific member functions (Node)
template<typename Data>
bool BinaryTree<Data>::Node::IsLeaf() const noexcept {
  if (HasLeftChild() || HasRightChild()) {
    return false;
  }
  else {
    return true;
  }
}

// Comparison operators (Node)
template<typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& key) const noexcept {
  // sfrutto il fatto che due nodi sono uguali se hanno anche i sottoalberi uguali
  // così da semplificare di molto la comparazione tra alberi
  bool areEqual = true;
  if (Element() != key.Element()) {
    return false;
  }
  if (areEqual) {
    if (HasLeftChild() == key.HasLeftChild()) {
      if (HasLeftChild()) { // se entrambi hanno sottoalbero sinistro
                            // confronto i due sottoalberi sinistri
        areEqual = (LeftChild() == key.LeftChild());
      }
      else {
        // se entrambi non hanno sottoalberi sinistri la mia flag è ancora true
        areEqual = true;
      }
    }
    else {
      return false;
    }
  }
  if (areEqual) {
    if (HasRightChild() == key.HasRightChild()) {
      if (HasRightChild()) { // se entrambi hanno sottoalbero destro
                             // confronto i due sottoalberi destri
        areEqual = (RightChild() == key.RightChild());
      }
      else {
        // se entrambi non hanno sottoalberi destri la mia flag è ancora true
        areEqual = true;
      }
    }
    else {
      return false;
    }
  }
  return areEqual;
}

template<typename Data>
bool BinaryTree<Data>::Node::operator!=(const Node& key) const noexcept{
  return !(*this == key);
}

// Comparison operators
template<typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree<Data>& bt) const noexcept {
  if (size == bt.size) {
    if (size == 0) {
      return true;
    }
    else {
      // data la comparazione dei nodi soprascritta, due alberi sono uguali
      // se e soltanto se le radici sono uguali
      return (Root() == bt.Root());
    }
  }
  else {
    return false;
  }
}

template<typename Data>
bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& bt) const noexcept {
  return !(*this == bt);
}

/* ************************************************************************** */

// Auxiliary member functions (for MappableContainer)

template<typename Data>
void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void* par, Node& key) {
  fun(key.Element(), par);
  if (key.HasLeftChild()) {
    MapPreOrder(fun, par, key.LeftChild());
  }
  if (key.HasRightChild()) {
    MapPreOrder(fun, par, key.RightChild());
  }
}

template<typename Data>
void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void* par, Node& key) {
  if (key.HasLeftChild()) {
    MapPostOrder(fun, par, key.LeftChild());
  }
  if (key.HasRightChild()) {
    MapPostOrder(fun, par, key.RightChild());
  }
  fun(key.Element(), par);
}

// Specific member functions (inherited from MappableContainer)

template<typename Data>
void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void* par) {
  if (size != 0) { // condizione necessaria per evitare di accedere ad una radice vuota
                   // e che quindi le map/fold lancino l'eccezione definita in Root()
    MapPreOrder(fun, par, Root());
  }
}

template<typename Data>
void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void* par) {
  if (size != 0) {
    MapPostOrder(fun, par, Root());
  }
}

/* ************************************************************************** */

// Auxiliary member functions (for FoldableContainer)

template<typename Data>
void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc, Node& key) const {
  fun(key.Element(), par, acc);
  if (key.HasLeftChild()) {
    FoldPreOrder(fun, par, acc, key.LeftChild());
  }
  if (key.HasRightChild()) {
    FoldPreOrder(fun, par, acc, key.RightChild());
  }
}

template<typename Data>
void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc, Node& key) const {
  if (key.HasLeftChild()) {
    FoldPostOrder(fun, par, acc, key.LeftChild());
  }
  if (key.HasRightChild()) {
    FoldPostOrder(fun, par, acc, key.RightChild());
  }
  fun(key.Element(), par, acc);
}

// Specific member functions (inherited from FoldableContainer)

template<typename Data>
void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const {
  if (size != 0) {
    FoldPreOrder(fun, par, acc, Root());
  }
}

template<typename Data>
void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const {
  if (size != 0) {
    FoldPostOrder(fun, par, acc, Root());
  }
}

/* ************************************************************************** */

// Auxiliary member functions (for InOrderMappableContainer)

template<typename Data>
void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void* par, Node& key) {
  if (key.HasLeftChild()) {
    MapInOrder(fun, par, key.LeftChild());
  }
  fun(key.Element(), par);
  if (key.HasRightChild()) {
    MapInOrder(fun, par, key.RightChild());
  }
}

// Specific member functions (inherited from InOrderMappableContainer)

template<typename Data>
void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void* par) {
  if (size != 0) {
    MapInOrder(fun, par, Root());
  }
}

/* ************************************************************************** */

// Auxiliary member functions (for InOrderFoldableContainer)

template<typename Data>
void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void* par, void* acc, Node& key) const {
  if (key.HasLeftChild()) {
    FoldInOrder(fun, par, acc, key.LeftChild());
  }
  fun(key.Element(), par, acc);
  if (key.HasRightChild()) {
    FoldInOrder(fun, par, acc, key.RightChild());
  }
}

// Specific member functions (inherited from InOrderFoldableContainer)

template<typename Data>
void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void* par, void* acc) const {
  if (size != 0) {
    FoldInOrder(fun, par, acc, Root());
  }
}

/* ************************************************************************** */

// Specific member functions (inherited from BreadthMappableContainer)

template<typename Data>
void BinaryTree<Data>::MapBreadth(const MapFunctor fun, void* par) {
  if (size != 0) {
    QueueLst<Node*> q;
    q.Enqueue(&Root());
    while (!q.Empty()) {
      // Use map on front of the queue and remove it from queue
      Node *key = q.HeadNDequeue();
      fun(key->Element(), par);
      // Enqueue left child
      if (key->HasLeftChild())
        q.Enqueue(&key->LeftChild());
      }
      // Enqueue right child
      if (key->HasRightChild()) {
        q.Enqueue(&key->RightChild());
      }
    }
  }
}

/* ************************************************************************** */

// Specific member functions (inherited from BreadthFoldableContainer)

template<typename Data>
void BinaryTree<Data>::FoldBreadth(const FoldFunctor fun, const void* par, void* acc) const {
  if (size != 0) {
    QueueLst<Node*> q;
    q.Enqueue(&Root());
    while (!q.Empty()) {
      // Use map on front of the queue and remove it from queue
      Node *key = q.HeadNDequeue();
      fun(key->Element(), par, acc);
      // Enqueue left child
      if (key->HasLeftChild()) {
        q.Enqueue(&key->LeftChild());
      }
      // Enqueue right child
      if (key->HasRightChild()) {
        q.Enqueue(&key->RightChild());
      }
    }
  }
}

/* ************************************************************************** */

/* BTPreOrderIterator */

// Specific constructors
template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& bt) {
  if (bt.Size() != 0) {
    current = &bt.Root();
  }
  else {
    current = nullptr;
  }
}

// Copy constructor
template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& bti) {
  current = bti.current;
  stk = bti.stk;
}

// Move constructor
template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& bti) noexcept {
  std::swap(current, bti.current);
  stk = std::move(bti.stk);
}

// Copy assignment
template<typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& bti) {
  BTPreOrderIterator<Data> *tmp = new BTPreOrderIterator<Data>(bti);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

// Move assignment
template<typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& bti) noexcept {
  std::swap(current, bti.current);
  stk = std::move(bti.stk);
  return *this;
}

// Comparison operators
template<typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data>& bti) const noexcept {
  return ((current == bti.current) && (stk == bti.stk));
}

template<typename Data>
bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data>& bti) const noexcept {
  return !(*this == bti);
}

// Specific member functions (inherited from Iterator)
template<typename Data>
Data& BTPreOrderIterator<Data>::operator*() const {
  if (!Terminated()) {
    return current->Element();
  }
  else {
    throw std::out_of_range("Access to a non-existent node");
  }
}

// Specific member functions (inherited from ForwardIterator)
template<typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++() {
  if (!Terminated()) {
    if (current->HasLeftChild()) {
      if (current->HasRightChild()) {
        stk.Push(&(current->RightChild()));
      }
      current = &(current->LeftChild());
      return *this;
    }
    if (current->HasRightChild()) {
      current = &(current->RightChild());
      return *this;
    }
    if (!stk.Empty()) {
      current = stk.TopNPop();
      return *this;
    }
    else {
      current = nullptr;
      return *this;
    }
  }
  else {
    throw std::length_error("The iterator was terminated yet");
  }
}

/* ************************************************************************** */

/* BTPostOrderIterator */

// Specific constructors
template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt) {
  if (bt.Size() != 0) {
    current = &bt.Root();
    current = LeftMostLeaf(current, stk);
  }
  else {
    current = nullptr;
  }
}

// Copy constructor
template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data>& bti) {
  current = bti.current;
  stk = bti.stk;
}

// Move constructor
template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data>&& bti) noexcept {
  std::swap(current, bti.current);
  stk = std::move(bti.stk);
}

// Copy assignment
template<typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& bti) {
  BTPostOrderIterator<Data> *tmp = new BTPostOrderIterator<Data>(bti);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

// Move assignment
template<typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data>&& bti) noexcept {
  std::swap(current, bti.current);
  stk = std::move(bti.stk);
  return *this;
}

// Comparison operators
template<typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data>& bti) const noexcept {
  return ((current == bti.current) && (stk == bti.stk));
}

template<typename Data>
bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data>& bti) const noexcept {
  return !(*this == bti);
}

// Specific member functions (inherited from Iterator)
template<typename Data>
Data& BTPostOrderIterator<Data>::operator*() const {
  if (!Terminated()) {
    return current->Element();
  }
  else {
    throw std::out_of_range("Access to a non-existent node");
  }
}

// Specific member functions (inherited from ForwardIterator)
template<typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++() {
  if (!Terminated()) {
    if (stk.Empty()) {
      current = nullptr;
      return *this;
    }
    else {
      if ((stk.Top()->HasRightChild()) && (&(stk.Top()->RightChild()) != current)) {
        current = &(stk.Top()->RightChild());
        current = LeftMostLeaf(current, stk);
        return *this;
      }
      else {
        current = stk.TopNPop();
        return *this;
      }
    }
  }
  else {
    throw std::length_error("The iterator was terminated yet");
  }
}

// Auxiliary member functions (Search for the leftmost leaf and filling the stack)
template<typename Data>
typename BinaryTree<Data>::Node* BTPostOrderIterator<Data>::LeftMostLeaf(typename BinaryTree<Data>::Node* curr, StackLst<typename BinaryTree<Data>::Node*>& stk) {
  // arrivo alla foglia più a sinistra e metto nello stack tutti i nodi visitati
  while (!(curr->IsLeaf())) {
    while (curr->HasLeftChild()) {
      stk.Push(curr);
      curr = &(curr->LeftChild());
    }
    if (curr->HasRightChild()) {
      stk.Push(curr);
      curr = &(curr->RightChild());
    }
  }
  return curr;
}

/* ************************************************************************** */

/* BTInOrderIterator */

// Specific constructors
template<typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt) {
  if (bt.Size() != 0) {
    current = &bt.Root();
    current = LeftMostNode(current, stk);
  }
  else {
    current = nullptr;
  }
}

// Copy constructor
template<typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data>& bti) {
  current = bti.current;
  stk = bti.stk;
}

// Move constructor
template<typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data>&& bti) noexcept {
  std::swap(current, bti.current);
  stk = std::move(bti.stk);
}

// Copy assignment
template<typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data>& bti) {
  BTInOrderIterator<Data> *tmp = new BTInOrderIterator<Data>(bti);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

// Move assignment
template<typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data>&& bti) noexcept {
  std::swap(current, bti.current);
  stk = std::move(bti.stk);
  return *this;
}

// Comparison operators
template<typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data>& bti) const noexcept {
  return ((current == bti.current) && (stk == bti.stk));
}

template<typename Data>
bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& bti) const noexcept {
  return !(*this == bti);
}

// Specific member functions (inherited from Iterator)
template<typename Data>
Data& BTInOrderIterator<Data>::operator*() const {
  if (!Terminated()) {
    return current->Element();
  }
  else {
    throw std::out_of_range("Access to a non-existent node");
  }
}

// Specific member functions (inherited from ForwardIterator)
template<typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++() {
  if (!Terminated()) {
    if (current->HasRightChild()) {
      current = LeftMostNode(&current->RightChild(), stk);
      return *this;
    }
    else {
      if (stk.Empty()) {
        current = nullptr;
        return *this;
      }
      else {
        current = stk.TopNPop();
        return *this;
      }
    }
  }
  else {
    throw std::length_error("The iterator was terminated yet");
  }
}

// Auxiliary member functions (Search for the leftmost leaf and filling the stack)
template<typename Data>
typename BinaryTree<Data>::Node* BTInOrderIterator<Data>::LeftMostNode(typename BinaryTree<Data>::Node* curr, StackLst<typename BinaryTree<Data>::Node*>& stk) {
  // si sposta nel nodo più a sinistra dell'albero con radice curr e mette nello stack i nodi visitati
  while (curr->HasLeftChild()) {
    stk.Push(curr);
    curr = &(curr->LeftChild());
  }
  return curr;
}

/* ************************************************************************** */

/* BTBreadthIterator */

// Specific constructors
template<typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bt) {
  if (bt.Size() != 0) {
    current = &bt.Root();
    EnqueueChilds(current, que);
  }
  else {
    current = nullptr;
  }
}

// Copy constructor
template<typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& bti) {
  current = bti.current;
  que = bti.que;
}

// Move constructor
template<typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& bti) noexcept {
  std::swap(current, bti.current);
  que = std::move(bti.que);
}

// Copy assignment
template<typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data>& bti) {
  BTBreadthIterator<Data> *tmp = new BTBreadthIterator<Data>(bti);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

// Move assignment
template<typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data>&& bti) noexcept {
  std::swap(current, bti.current);
  que = std::move(bti.que);
  return *this;
}

// Comparison operators
template<typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data>& bti) const noexcept {
  return ((current == bti.current) && (que == bti.que));
}

template<typename Data>
bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& bti) const noexcept {
  return !(*this == bti);
}

// Specific member functions (inherited from Iterator)
template<typename Data>
Data& BTBreadthIterator<Data>::operator*() const {
  if (!Terminated()) {
    return current->Element();
  }
  else {
    throw std::out_of_range("Access to a non-existent node");
  }
}

// Specific member functions (inherited from ForwardIterator)
template<typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() {
  if (!Terminated()) {
    if (!que.Empty()) {
      current = que.HeadNDequeue();
      EnqueueChilds(current, que);
      return *this;
    }
    else {
      current = nullptr;
      return *this;
    }
  }
  else {
    throw std::length_error("The iterator was terminated yet");
  }
}

// Auxiliary member functions (Enqueue the node's childs)
template<typename Data>
void BTBreadthIterator<Data>::EnqueueChilds(typename BinaryTree<Data>::Node* curr, QueueLst<typename BinaryTree<Data>::Node*>& que) {
  if (curr->HasLeftChild()) {
    que.Enqueue(&curr->LeftChild());
  }
  if (curr->HasRightChild()) {
    que.Enqueue(&curr->RightChild());
  }
}

/* ************************************************************************** */

}
