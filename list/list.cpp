
namespace lasd {

/* ************************************************************************** */

// Specific constructors
template<typename Data>
List<Data>::List(const LinearContainer<Data>& con) {
  for (ulong index = 0; index < con.Size(); ++index) {
    InsertAtBack(con[index]);
  }
}

// Copy constructor
template<typename Data>
List<Data>::List(const List<Data>& lis) {
  size = 0; // necessario visto che gestisco la size direttamente nella insert
  for (ulong index = 0; index < lis.size; ++index) {
    InsertAtBack(lis[index]);
  }
}

// Move constructor
template<typename Data>
List<Data>::List(List<Data>&& lis) noexcept {
  std::swap(size, lis.size);
  if (size == 0) {
    head = nullptr;
    tail = nullptr;
  }
  else if (size == 1) {
    std::swap(head, lis.head);
    tail = head;
  }
  else {
    std::swap(head, lis.head);
    std::swap(tail, lis.tail);
  }
}

// Destructor
template<typename Data>
List<Data>::~List() {
  while (head) {        // finché ho una testa
    Node *temp = head;  // salvo il nodo poi
    head = head->next;  // sposto la testa e
    delete temp;        // cancello il nodo
  }
}

// Copy assignment
template<typename Data>
List<Data>& List<Data>::operator=(const List<Data>& lis) {
  List<Data> *tmp = new List<Data>(lis);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

// Move assignment
template<typename Data>
List<Data>& List<Data>::operator=(List<Data>&& lis) noexcept {
  std::swap(size, lis.size);
  if (size == 0) {
    Clear();
  }
  else if (size == 1) {
    std::swap(head, lis.head);
    tail = head;
  }
  else {
    std::swap(head, lis.head);
    std::swap(tail, lis.tail);
  }
  return *this;
}

//Comparison operators
template<typename Data>
bool List<Data>::operator==(const List<Data>& lis) const noexcept {
  if (size == lis.size) {
    Node *tmp1 = head;
    Node *tmp2 = lis.head;
    // scorro entrambe le liste e faccio il confronto degli elementi
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
bool List<Data>::operator!=(const List<Data>& lis) const noexcept {
  return !(*this == lis);
}

// Specific member functions
template<typename Data>
void List<Data>::InsertAtFront(const Data& value) {
  if (size == 0) {
    head = new Node(value);
    tail = head;
    size = 1;
  }
  else {
    Node* newNode = new Node(value);
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
    size++;
  }
}

template<typename Data>
void List<Data>::InsertAtFront(Data&& value) noexcept {
  if (size == 0) {
    head = new Node(std::move(value));
    tail = head;
    size = 1;
  }
  else {
    Node* newNode = new Node(std::move(value));
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
    size++;
  }
}

template<typename Data>
void List<Data>::RemoveFromFront() {
  if (size != 0) {
    if (size == 1) {
      // se ho solo un elemento pulisco la lista
      Clear();
    }
    else {
      head = head->next;
      delete head->prev;
      head->prev = nullptr;
      size--;
    }
  }
  else {
    throw std::length_error("Access to an empty list.");
  }
}

template<typename Data>
Data List<Data>::FrontNRemove() {
  if (size != 0) {
    Data value;
    value = head->info;
    if (size == 1) {
      Clear();
    }
    else {
      head = head->next;
      delete head->prev;
      head->prev = nullptr;
      size--;
    }
    return value;
  }
  else {
    throw std::length_error("Access to an empty list.");
  }
}

template<typename Data>
void List<Data>::InsertAtBack(const Data& value) {
  if (size == 0) {
    head = new Node(value);
    tail = head;
    size = 1;
  }
  else {
    Node* newNode = new Node(value);
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
    size++;
  }
}

template<typename Data>
void List<Data>::InsertAtBack(Data&& value) noexcept {
  if (size == 0) {
    head = new Node(std::move(value));
    tail = head;
    size = 1;
  }
  else {
    Node* newNode = new Node(std::move(value));
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
    size++;
  }
}

// Specific member functions (inherited from Container)
template<typename Data>
void List<Data>::Clear() {
  while (head) {
    Node *temp = head;
    head = head->next;
    delete temp;
  }
  head = nullptr;
  tail = nullptr;
  size = 0;
}

// Specific member functions (inherited from LinearContainer)
template<typename Data>
Data& List<Data>::Front() const {
  if (size != 0) {
    return head->info;
  }
  else {
    throw std::length_error("Access to an empty list.");
  }
}

template<typename Data>
Data& List<Data>::Back() const {
  if (size != 0) {
    return tail->info;
  }
  else {
    throw std::length_error("Access to an empty list.");
  }
}

template<typename Data>
Data& List<Data>::operator[](const ulong index) const {
  if (index < size) {
    if (index == 0) {
      return head->info;
    }
    if (index == size - 1) {
      return tail->info;
    }
    Node *slide = head;
    for (ulong i = 0; i < index; ++i) {
      slide = slide->next;
    }
    return slide->info;
  }
  else if (size == 0) {
    throw std::length_error("Access to an empty list.");
  }
  else {
    throw std::out_of_range("Access at index " + std::to_string(index) + "; list size " + std::to_string(size) + ".");
  }
}

// Specific member functions (inherited from MappableContainer)
template<typename Data>
void List<Data>::MapPreOrder(const MapFunctor fun, void* par) {
  Node *slide = head;
  for (ulong index = 0; index < size; ++index) {
    fun(slide->info, par);
    slide = slide->next;
  }
}

template<typename Data>
void List<Data>::MapPostOrder(const MapFunctor fun, void* par) {
  Node *slide = tail;
  for (ulong index = 0; index < size; ++index) {
    fun(slide->info, par);
    slide = slide->prev;
  }
}

// Specific member functions (inherited from FoldableContainer)
template<typename Data>
void List<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const {
  Node *slide = head;
  for (ulong index = 0; index < size; ++index) {
    fun(slide->info, par, acc);
    slide = slide->next;
  }
}

template<typename Data>
void List<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const {
  Node *slide = tail;
  for (ulong index = 0; index < size; ++index) {
    fun(slide->info, par, acc);
    slide = slide->prev;
  }
}

/* ************************************************************************** */

}
