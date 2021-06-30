
namespace lasd {

/* ************************************************************************** */

/* Node member function */

// Copy assignment
template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(const NodeVec& key) {
  info = key.info;
  current = key.current;
  vecptr = key.vecptr;
  return *this;
}

// Move assignment
template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(NodeVec&& key) noexcept {
  std::swap(info, key.info);
  std::swap(current, key.current);
  std::swap(vecptr, key.vecptr);
  return *this;
}

// Comparison operators
template<typename Data>
bool BinaryTreeVec<Data>::NodeVec::operator==(const NodeVec& key) const noexcept {
  bool areEqual = true;
  if (info != key.info) {
    return false;
  }
  if (areEqual) {
    if (HasLeftChild() == key.HasLeftChild()) {
      if (HasLeftChild()) {
        areEqual = (vecptr->operator[](2*current + 1) == (key.vecptr)->operator[](2*current + 1));
      }
      else {
        areEqual = true;
      }
    }
    else {
      return false;
    }
  }
  if (areEqual) {
    if (HasRightChild() == key.HasRightChild()) {
      if (HasRightChild()) {
        areEqual = (vecptr->operator[](2*current + 2) == (key.vecptr)->operator[](2*current + 2));
      }
      else {
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
bool BinaryTreeVec<Data>::NodeVec::operator!=(const NodeVec& key) const noexcept {
  return !(*this == key);
}

// Specific member functions
template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
  if(HasLeftChild()) {
    return vecptr->operator[](2*current + 1);
  }
  else {
    throw std::out_of_range("Access to a non-existent left child.");
  }
}

template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const {
  if(HasRightChild()) {
    return vecptr->operator[](2*current + 2);
  }
  else {
    throw std::out_of_range("Access to a non-existent right child.");
  }
}

/* ************************************************************************** */

// Specific constructors
template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data>& con) {
  size = con.Size();
  vec = new Vector<NodeVec>(size);
  for (ulong index = 0; index < size; ++index) {
    (vec->operator[](index)).info = con[index];
    (vec->operator[](index)).current = index;
    (vec->operator[](index)).vecptr = vec;
  }
}

// Copy constructor
template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& btv) {
  size = btv.size;
  vec = new Vector<NodeVec>(*(btv.vec));
}

// Move constructor
template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& btv) noexcept {
  std::swap(size, btv.size);
  std::swap(vec, btv.vec);
}

// Destructor
template<typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec() {
  Vector<NodeVec> *tmp = vec;
  vec = nullptr;
  delete tmp;
}

// Copy assignment
template<typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& btv) {
  BinaryTreeVec<Data> *tmp = new BinaryTreeVec<Data>(btv);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

// Move assignment
template<typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& btv) noexcept {
  std::swap(size, btv.size);
  std::swap(vec, btv.vec);
  return *this;
}

// potrei ottimizzare l'operatore di comparazione come segue, ma ovviamente devo
// cambiare anche l'operatore== di NodeVec, altrimenti scorrerei tutti i nodi
// restanti ogni volta che comparo il nodo
// // Comparison operators
// template<typename Data>
// bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& btv) const noexcept {
//   if (size == btv.size) {
//     if (size == 0) {
//       return true;
//     }
//     else {
//       return vec->operator==(*(btv.vec));
//     }
//   }
//   else {
//     return false;
//   }
// }
//
// template<typename Data>
// bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& btv) const noexcept {
//   return !(*this == btv);
// }

template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
  if (size != 0) {
    return vec->operator[](0);
  }
  else {
    throw std::length_error("Access to an empty binary tree.");
  }
}

template<typename Data>
void BinaryTreeVec<Data>::Clear() {
  for (ulong index = 0; index < size; ++index) {
    (vec->operator[](index)).vecptr = nullptr;
  } // metto i vec di tutti i nodi a null per evitare che in successivi
    // utilizzi dell'istanza di questa classe trovi la memoria sporca
  Vector<NodeVec> *tmp = vec;
  vec = nullptr;
  delete tmp;
  size = 0;
}

/* ************************************************************************** */

}
