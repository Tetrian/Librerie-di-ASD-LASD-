
namespace lasd {

/* ************************************************************************** */

/* Node member function */

// Specific constructors
template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& value) {
  info = value;
}

template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data&& value) noexcept {
  std::swap(info, value);
}

// Destructor
template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
  if (left != nullptr) {
    delete left;
  }
  if (right != nullptr) {
    delete right;
  }
}

// Copy assignment
template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk& key) {
  NodeLnk *tmp = new NodeLnk(key.info);
  if (key.left != nullptr) {
    left = key.left;
  }
  if (key.right != nullptr) {
    right = key.right;
  }
  return *tmp;
}

//Move assignment
template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk&& key) noexcept {
  std::swap(info, key.info);
  std::swap(left, key.left);
  std::swap(right, key.right);
  return *this;
}

// Comparison operators
template<typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::operator==(const NodeLnk& key) const noexcept {
  bool areEqual = true;
  if (info != key.info) {
    return false;
  }
  if (areEqual) {
    if (HasLeftChild() == key.HasLeftChild()) {
      if (HasLeftChild()) {
        areEqual = (left == key.left);
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
        areEqual = (right == key.right);
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
bool BinaryTreeLnk<Data>::NodeLnk::operator!=(const NodeLnk& key) const noexcept {
  return !(*this == key);
}

// Specific member functions
template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
  if (HasLeftChild()) {
    return *left;
  }
  else {
    throw std::out_of_range("Access to a non-existent left child.");
  }
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
  if (HasRightChild()) {
    return *right;
  }
  else {
    throw std::out_of_range("Access to a non-existent right child.");
  }
}

/* ************************************************************************** */

// Auxiliary member function for the BinaryTreeLnk specific constructor
template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::AuxBTLcon(const LinearContainer<Data>& con, NodeLnk* key, ulong index) {
  if (index < con.Size()) {
    NodeLnk* tmp = new NodeLnk(con[index]);
    key = tmp;
    // insert left sub-tree
    key->left = AuxBTLcon(con, key->left, 2*index + 1);
    // insert right sub-tree
    key->right = AuxBTLcon(con, key->right, 2*index + 2);
  }
  return key;
}

// Specific constructor
template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data>& con) {
  size = con.Size();
  if (size != 0) {
    ulong index = 0;
    root = AuxBTLcon(con, root, index);
  }
}

// Auxiliary member function for the BinaryTreeLnk copy constructor
template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::AuxBTLcopy(const NodeLnk* btkey, NodeLnk* key) {
  NodeLnk* tmp = new NodeLnk(btkey->info);
  key = tmp;
  if (btkey->left != nullptr) {
    // insert left sub-tree
    key->left = AuxBTLcopy(btkey->left, key->left);
  }
  if (btkey->right != nullptr) {
    // insert right sub-tree
    key->right = AuxBTLcopy(btkey->right, key->right);
  }
  return key;
}

// Copy constructor
template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& btl) {
  size = btl.Size();
  root = AuxBTLcopy(btl.root, root);
}

// Move constructor
template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& btl) noexcept {
  std::swap(size, btl.size);
  std::swap(root, btl.root);
}

// Destructor
template<typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk() {
  if (root != nullptr) {
    delete root; // questo chiama il distruttore di nodo, ovvero cancella l'albero
  }              // in post order, chiamando ricorsivamente delete left e right
}

// Copy assignment
template<typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& btl) {
    BinaryTreeLnk<Data> *tmp = new BinaryTreeLnk<Data>(btl);
    std::swap(*tmp, *this);
    delete tmp;
    return *this;
}

// Move assignment
template<typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& btl) noexcept {
  std::swap(size, btl.size);
  std::swap(root, btl.root);
  return *this;
}

// Specific member functions (inherited from BinaryTree)
template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const {
  if (root != nullptr) {
    return *root;
  }
  else {
    throw std::length_error("Access to an empty binary tree.");
  }
}

// Specific member functions (inherited from Container)
template<typename Data>
void BinaryTreeLnk<Data>::Clear() {
  if (root != nullptr) {
    delete root;
    size = 0;
    root = nullptr;
  }
}

/* ************************************************************************** */

}
