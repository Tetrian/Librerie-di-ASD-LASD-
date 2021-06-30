
namespace lasd {

/* ************************************************************************** */

// Specific constructors
template<typename Data>
BST<Data>::BST(const LinearContainer<Data>& con) {
  for (ulong index = 0; index < con.Size(); ++index) {
    Insert(con[index]);
  }
}

// Copy constructor
template<typename Data>
BST<Data>::BST(const BST<Data>& bst) :
  BinaryTreeLnk<Data>(bst) {

}

// Move constructor
template<typename Data>
BST<Data>::BST(BST<Data>&& bst) noexcept :
  BinaryTreeLnk<Data>(std::move(bst)) {

}

// Copy assignment
template<typename Data>
BST<Data>& BST<Data>::operator=(const BST<Data>& bst) {
  BinaryTreeLnk<Data>::operator=(bst);
  return *this;
}

// Move assignment
template<typename Data>
BST<Data>& BST<Data>::operator=(BST<Data>&& bst) noexcept {
  BinaryTreeLnk<Data>::operator=(std::move(bst));
  return *this;
}

// Comparison operator
template<typename Data>
bool BST<Data>::operator==(const BST<Data>& bst) const noexcept {
  if (size == bst.size) {
    if (size == 0) {
      return true;
    }
    else {
      bool areEqual = true;
      BTInOrderIterator<Data> iter(bst);
      return ComparisonInOrder(areEqual, root, iter);
      // si può benissimo fare con due iteratori, uno per albero e poi
      // scorrerli entrambi con un ciclo for e infine confrontarli.
    }
  }
  else {
    return false;
  }
}

template<typename Data>
bool BST<Data>::operator!=(const BST<Data>& bst) const noexcept {
  return !(*this == bst);
}

// Specific member functions
template<typename Data>
void BST<Data>::Insert(const Data& dat) noexcept {
  typename BinaryTreeLnk<Data>::NodeLnk*& tmp = FindPointerTo(dat, root);
  if (tmp == nullptr) {
    tmp = new typename BinaryTreeLnk<Data>::NodeLnk(dat);
    ++size;
  }
}

template<typename Data>
void BST<Data>::Insert(Data&& dat) noexcept {
  typename BinaryTreeLnk<Data>::NodeLnk*& tmp = FindPointerTo(dat, root);
  if (tmp == nullptr) {
    tmp = new typename BinaryTreeLnk<Data>::NodeLnk(std::move(dat));
    ++size;
  }
}

template<typename Data>
void BST<Data>::Remove(const Data& dat) noexcept {
  typename BinaryTreeLnk<Data>::NodeLnk*& tmp = FindPointerTo(dat, root);
  if (tmp != nullptr) {
    delete Detach(tmp);
    --size;
  }
}

template<typename Data>
const Data& BST<Data>::Min() const {
  if (size != 0) {
    return FindPointerToMin(root)->info;
  }
  else {
    throw std::length_error("Access to an empty binary search tree.");
  }
}

template<typename Data>
Data BST<Data>::MinNRemove() {
  if (size != 0) {
    --size;
    return DataNDelete(DetachMin(root));
  }
  else {
    throw std::length_error("Access to an empty binary search tree.");
  }
}

template<typename Data>
void BST<Data>::RemoveMin() {
  if (size != 0) {
    --size;
    delete DetachMin(root);
  }
  else {
    throw std::length_error("Access to an empty binary search tree.");
  }
}

template<typename Data>
const Data& BST<Data>::Max() const {
  if (size != 0) {
    return FindPointerToMax(root)->info;
  }
  else {
    throw std::length_error("Access to an empty binary search tree.");
  }
}

template<typename Data>
Data BST<Data>::MaxNRemove() {
  if (size != 0) {
    --size;
    return DataNDelete(DetachMax(root));
  }
  else {
    throw std::length_error("Access to an empty binary search tree.");
  }
}

template<typename Data>
void BST<Data>::RemoveMax() {
  if (size != 0) {
    --size;
    delete DetachMax(root);
  }
  else {
    throw std::length_error("Access to an empty binary search tree.");
  }
}

template<typename Data>
const Data& BST<Data>::Predecessor(const Data& dat) const {
  typename BinaryTreeLnk<Data>::NodeLnk* const*tmp = &FindPointerToPredecessor(dat);
  if (tmp != nullptr) {
    return (*tmp)->info;
  }
  else {
    throw std::length_error("Predecessor not found.");
  }
}

template<typename Data>
Data BST<Data>::PredecessorNRemove(const Data& dat) {
  typename BinaryTreeLnk<Data>::NodeLnk* *tmp = &FindPointerToPredecessor(dat);
  if (tmp != nullptr) {
    --size;
    return DataNDelete(Detach(*tmp));
  }
  else {
    throw std::length_error("Predecessor not found.");
  }
}

template<typename Data>
void BST<Data>::RemovePredecessor(const Data& dat) {
  typename BinaryTreeLnk<Data>::NodeLnk* *tmp = &FindPointerToPredecessor(dat);
  if (tmp != nullptr) {
    --size;
    delete Detach(*tmp);
  }
  else {
    throw std::length_error("Predecessor not found.");
  }
}

template<typename Data>
const Data& BST<Data>::Successor(const Data& dat) const {
  typename BinaryTreeLnk<Data>::NodeLnk* const*tmp = &FindPointerToSuccessor(dat);
  if (tmp != nullptr) {
    return (*tmp)->info;
  }
  else {
    throw std::length_error("Predecessor not found.");
  }
}

template<typename Data>
Data BST<Data>::SuccessorNRemove(const Data& dat) {
  typename BinaryTreeLnk<Data>::NodeLnk* *tmp = &FindPointerToSuccessor(dat);
  if (tmp != nullptr) {
    --size;
    return DataNDelete(Detach(*tmp));
  }
  else {
    throw std::length_error("Predecessor not found.");
  }
}

template<typename Data>
void BST<Data>::RemoveSuccessor(const Data& dat) {
  typename BinaryTreeLnk<Data>::NodeLnk* *tmp = &FindPointerToSuccessor(dat);
  if (tmp != nullptr) {
    delete Detach(*tmp);
    --size;
  }
  else {
    throw std::length_error("Predecessor not found.");
  }
}

// Specific member functions (inherited from TestableContainer)
template<typename Data>
bool BST<Data>::Exists(const Data& dat) const noexcept {
  if (FindPointerTo(dat, root) != nullptr) {
    return true;
  }
  else {
    return false;
  }
}

/* ************************************************************************** */

// Auxiliary member functions
template<typename Data>
bool BST<Data>::ComparisonInOrder(bool& equal, const typename BinaryTreeLnk<Data>::NodeLnk* key, BTInOrderIterator<Data>& iter) const noexcept {
  if (equal) {
    if (key->HasLeftChild()) {
      ComparisonInOrder(equal, key->left, iter);
    }
    equal = (key->info == *iter);
    ++iter;
    if (key->HasRightChild()) {
      ComparisonInOrder(equal, key->right, iter);
    }
  }
  return equal;
}

template<typename Data>
Data BST<Data>::DataNDelete(typename BinaryTreeLnk<Data>::NodeLnk* key) noexcept {
  Data dat = key->info;
  delete key;
  return dat;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::Detach(typename BinaryTreeLnk<Data>::NodeLnk*& key) noexcept {
  if (key->HasLeftChild() && key->HasRightChild()) {
    typename BinaryTreeLnk<Data>::NodeLnk *ptr = DetachMax(key->left);
    std::swap(key->info, ptr->info);
    return ptr;
  }
  else if (key->HasLeftChild() && !(key->HasRightChild())) {
    return SkipOnLeft(key);
  }
  else /* key has just right child or it is leaf */ {
    return SkipOnRight(key);
  }
  return key; // key == nullptr;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::DetachMin(typename BinaryTreeLnk<Data>::NodeLnk*& key) noexcept {
  return SkipOnRight(FindPointerToMin(key));
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::DetachMax(typename BinaryTreeLnk<Data>::NodeLnk*& key) noexcept {
  return SkipOnLeft(FindPointerToMax(key));
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::SkipOnLeft(typename BinaryTreeLnk<Data>::NodeLnk*& key) noexcept {
  typename BinaryTreeLnk<Data>::NodeLnk *ptr = nullptr;
  if (key != nullptr) {
    std::swap(ptr, key->left);
    std::swap(ptr, key);
  }
  return ptr;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::SkipOnRight(typename BinaryTreeLnk<Data>::NodeLnk*& key) noexcept {
  typename BinaryTreeLnk<Data>::NodeLnk *ptr = nullptr;
  if (key != nullptr) {
    std::swap(ptr, key->right);
    std::swap(ptr, key);
  }
  return ptr;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(typename BinaryTreeLnk<Data>::NodeLnk* const& key) const noexcept {
  typename BinaryTreeLnk<Data>::NodeLnk* const*ptr = &key;
  while ((*ptr)->left != nullptr) {
    ptr = &((*ptr)->left);
  }
  return *ptr;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerToMin(typename BinaryTreeLnk<Data>::NodeLnk* const& key) noexcept {
  return const_cast<typename BinaryTreeLnk<Data>::NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMin(key));
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(typename BinaryTreeLnk<Data>::NodeLnk* const& key) const noexcept {
  typename BinaryTreeLnk<Data>::NodeLnk* const*ptr = &key;
  while ((*ptr)->right != nullptr) {
    ptr = &((*ptr)->right);
  }
  return *ptr;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerToMax(typename BinaryTreeLnk<Data>::NodeLnk* const& key) noexcept {
  return const_cast<typename BinaryTreeLnk<Data>::NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMax(key));
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* const& BST<Data>::FindPointerTo(const Data& dat, typename BinaryTreeLnk<Data>::NodeLnk* const& key) const noexcept {
  typename BinaryTreeLnk<Data>::NodeLnk* const*ptr = &key;
  if (*ptr != nullptr) {
    if (key->info == dat) {
      return *ptr;
    }
    else if (key->info > dat) {
      ptr = &(FindPointerTo(dat, key->left));
    }
    else /* key->info < dat */ {
      ptr = &(FindPointerTo(dat, key->right));
    }
  }
  return *ptr;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerTo(const Data& dat, typename BinaryTreeLnk<Data>::NodeLnk* const& key) noexcept {
  return const_cast<typename BinaryTreeLnk<Data>::NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerTo(dat, key));
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* const& BST<Data>::FindPointerToPredecessor(const Data& dat) const noexcept {
  typename BinaryTreeLnk<Data>::NodeLnk* const*current = &root;
  typename BinaryTreeLnk<Data>::NodeLnk* const*estimate = nullptr;
  // standard update estimate
  while (*current != nullptr && (*current)->info != dat) {
    if ((*current)->info > dat) {
      current = &((*current)->left);
    }
    else /* (*current)->info < dat */ {
      estimate = current;
      current = &((*current)->right);
    }
  }
  // update estimate when (*current)->info == dat AND it has left child
  if (*current != nullptr && (*current)->HasLeftChild()) {
    estimate = &(FindPointerToMax((*current)->left));
  }
  return *estimate;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerToPredecessor(const Data& dat) noexcept {
  return const_cast<typename BinaryTreeLnk<Data>::NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToPredecessor(dat));
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* const& BST<Data>::FindPointerToSuccessor(const Data& dat) const noexcept {
  typename BinaryTreeLnk<Data>::NodeLnk* const*current = &root;
  typename BinaryTreeLnk<Data>::NodeLnk* const*estimate = nullptr;
  // standard update estimate
  while (*current != nullptr && (*current)->info != dat) {
    if ((*current)->info < dat) {
      current = &((*current)->right);
    }
    else /* (*current)->info > dat */ {
      estimate = current;
      current = &((*current)->left);
    }
  }
  // update estimate when (*current)->info == dat AND it has right child
  if (*current != nullptr && (*current)->HasRightChild()) {
    estimate = &(FindPointerToMin((*current)->right));
  }
  return *estimate;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerToSuccessor(const Data& dat) noexcept {
  return const_cast<typename BinaryTreeLnk<Data>::NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToSuccessor(dat));
}

/* ************************************************************************** */

}
