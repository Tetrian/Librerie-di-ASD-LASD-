
namespace lasd {

/* ************************************************************************** */

// Default constructor
template<typename Data>
StackVec<Data>::StackVec() :
  Vector<Data>(2) { // la size iniziale è arbitraria, l'importante è che non
                    // si lascia il vettore vuoto per evitare di dover gestire
                    // diversamente i casi limite di inserimento e rimozione
  realsize = 0;
}

// Specific constructor
template<typename Data>
StackVec<Data>::StackVec(const LinearContainer<Data>& con) {
  realsize = con.Size();
  size = con.Size() * 2;
  Elements = new Data[size] {};
  for (ulong index = 0; index < realsize; ++index) {
    Elements[index] = con[index];
  }
}

// Copy constructor
template<typename Data>
StackVec<Data>::StackVec(const StackVec<Data>& svec) :
  Vector<Data>(svec) {
  realsize = svec.realsize;
} // copio il vettore ed aggiorno i campi in più

// Move constructor
template<typename Data>
StackVec<Data>::StackVec(StackVec<Data>&& svec) noexcept :
  Vector<Data>(std::move(svec)) {
  std::swap(realsize, svec.realsize);
}

// Copy assignment
template<typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& svec) {
  StackVec<Data> *tmp = new StackVec<Data>(svec);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

// Move assignment
template<typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& svec) noexcept {
  std::swap(Elements, svec.Elements);
  std::swap(size, svec.size);
  std::swap(realsize, svec.realsize);
  return *this;
}

// Comparison operators
template<typename Data>
bool StackVec<Data>::operator==(const StackVec<Data>& svec) const noexcept {
  if (realsize == svec.realsize) {
    for (ulong index = 0; index < realsize; ++ index) {
      if (Elements[index] != svec.Elements[index]) {
        return false;
      }
    }
    return true;
  }
  else {
    return false;
  }
}

template<typename Data>
bool StackVec<Data>::operator!=(const StackVec<Data>& svec) const noexcept {
  return !(*this == svec);
}

// Specific member functions (inherited from Stack)
template<typename Data>
void StackVec<Data>::Push(const Data& value) {
  if (realsize + 1 == size) { // faccio la resize quando ho ancora una cella libera,
    Expand();                 // ma si può fare benissimo con realsize == size
  }
  Elements[realsize++] = value;
}

template<typename Data>
void StackVec<Data>::Push(Data&& value) noexcept {
  if (realsize + 1 == size) {
    Expand();
  }
  Elements[realsize++] = std::move(value);
}

template<typename Data>
Data& StackVec<Data>::Top() const {
  if (realsize != 0) {
    return Elements[realsize - 1];
  }
  else {
    throw std::length_error("Access to an empty stack.");
  }
}

template<typename Data>
void StackVec<Data>::Pop() {
  if (realsize != 0) {
    if (realsize < size/4) { // riduco il vettore quando i miei elementi occupano
      Reduce();              // un quarto della size, ma ovviamente è una mia scelta
    }                        // puoi usare la condizione che preferisci (tipo size/2)
    realsize--;
  }
  else {
    throw std::length_error("Access to an empty stack.");
  }
}

template<typename Data>
Data StackVec<Data>::TopNPop() {
  if (realsize != 0) {
    if (realsize < size/4) {
      Reduce();
    }
    return Elements[--realsize];
  }
  else {
    throw std::length_error("Access to an empty stack.");
  }
}

// Specific member functions (inherited from Container)
template<typename Data>
void StackVec<Data>::Clear() {
  Vector<Data>::Clear();
  size = 2;
  Elements = new Data[size] {};
  realsize = 0;
}

// Auxiliary member functions
// funzionano benissimo le resize di vector
template<typename Data>
void StackVec<Data>::Expand() {
  Vector<Data>::Resize(2*size);
}

template<typename Data>
void StackVec<Data>::Reduce() {
  Vector<Data>::Resize(size/2);
}

/* ************************************************************************** */

}
