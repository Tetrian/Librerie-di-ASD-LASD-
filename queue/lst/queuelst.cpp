
namespace lasd {

/* ************************************************************************** */

// Specific constructor
template<typename Data>
QueueLst<Data>::QueueLst(const LinearContainer<Data>& con) :
  List<Data>(con) {
}

// Copy constructor
template<typename Data>
QueueLst<Data>::QueueLst(const QueueLst<Data>& qlis) :
  List<Data>(qlis) {
}

// Move constructor
template<typename Data>
QueueLst<Data>::QueueLst(QueueLst<Data>&& qlis) noexcept :
  List<Data>(std::move(qlis)) {
}

// Copy assignment
template<typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& qlis) {
  List<Data>::operator=(qlis);
  return *this;
}

// Move assignment
template<typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& qlis) noexcept {
  List<Data>::operator=(std::move(qlis));
  return *this;
}

// Comparison operators
template<typename Data>
bool QueueLst<Data>::operator==(const QueueLst<Data>& qlis) const noexcept {
  if (size == qlis.size) {
    // sfruttando la lista mi scorro gli elementi
    typename List<Data>::Node *tmp1 = head;
    typename List<Data>::Node *tmp2 = qlis.head;
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
bool QueueLst<Data>::operator!=(const QueueLst<Data>& qlis) const noexcept {
  return !(*this == qlis);
}

// Specific member functions (inherited from Queue)
template<typename Data>
void QueueLst<Data>::Enqueue(const Data& value) {
  List<Data>::InsertAtBack(value);
}

template<typename Data>
void QueueLst<Data>::Enqueue(Data&& value) noexcept {
  List<Data>::InsertAtBack(std::move(value));
}

template<typename Data>
Data& QueueLst<Data>::Head() const {
  if (size != 0) {
    return List<Data>::Front();
  }
  else {
    throw std::length_error("Access to an empty queue.");
  }
}

template<typename Data>
void QueueLst<Data>::Dequeue() {
  if (size != 0) {
    List<Data>::RemoveFromFront();
  }
  else {
    throw std::length_error("Access to an empty queue.");
  }
}

template<typename Data>
Data QueueLst<Data>::HeadNDequeue() {
  if (size != 0) {
    return List<Data>::FrontNRemove();
  }
  else {
    throw std::length_error("Access to an empty queue.");
  }
}

// Specific member functions (inherited from Container)
template<typename Data>
void QueueLst<Data>::Clear() {
  List<Data>::Clear();
}

/* ************************************************************************** */

}
