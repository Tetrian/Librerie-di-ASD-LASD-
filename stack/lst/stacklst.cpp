
namespace lasd {

/* ************************************************************************** */

// Specific constructor
template<typename Data>
StackLst<Data>::StackLst(const LinearContainer<Data>& con) :
  List<Data>(con) {
}

// Copy constructor
template<typename Data>
StackLst<Data>::StackLst(const StackLst<Data>& slis) :
  List<Data>(slis) {
}

// Move constructor
template<typename Data>
StackLst<Data>::StackLst(StackLst<Data>&& slis) noexcept :
  List<Data>(std::move(slis)) {
}

// Copy assignment
template<typename Data>
StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& slis) {
  List<Data>::operator=(slis);
  return *this;
}

// Move assignment
template<typename Data>
StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& slis) noexcept {
  List<Data>::operator=(std::move(slis));
  return *this;
}

// Comparison operators
template<typename Data>
bool StackLst<Data>::operator==(const StackLst<Data>& slis) const noexcept {
  if (size == slis.size) {
    // sfruttando la lsita mi scorro gli elementi
    typename List<Data>::Node *tmp1 = head;
    typename List<Data>::Node *tmp2 = slis.head;
    for (ulong index = 0; index < size; ++index) {
      if (tmp1->info != tmp2->info) {
        return false;
      }
      tmp1 = tmp1->next;
      tmp2 = tmp2->next;
    }
    return true;
  }
  else {
    return false;
  }
}


template<typename Data>
bool StackLst<Data>::operator!=(const StackLst<Data>& slis) const noexcept {
  return !(*this == slis);
}

// Specific member functions (inherited from Stack)
template <typename Data>
void StackLst<Data>::Push(const Data& value) {
  List<Data>::InsertAtFront(value);
}

template <typename Data>
void StackLst<Data>::Push(Data&& value) noexcept {
  List<Data>::InsertAtFront(std::move(value));
}

template <typename Data>
Data& StackLst<Data>::Top() const {
  if (size != 0) {
    return List<Data>::Front();
  }
  else {
    throw std::length_error("Access to an empty stack.");
  }
}

template<typename Data>
void StackLst<Data>::Pop() {
  if (size != 0) {
    List<Data>::RemoveFromFront();
  }
  else {
    throw std::length_error("Access to an empty stack.");
  }
}

template<typename Data>
Data StackLst<Data>::TopNPop() {
  if (size != 0) {
    return List<Data>::FrontNRemove();
  }
  else {
    throw std::length_error("Access to an empty stack.");
  }
}

// Specific member functions (inherited from Container)
template<typename Data>
void StackLst<Data>::Clear() {
  List<Data>::Clear();
}

/* ************************************************************************** */

}
