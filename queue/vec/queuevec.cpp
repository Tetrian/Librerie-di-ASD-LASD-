
namespace lasd {

/* ************************************************************************** */

template<typename Data>
QueueVec<Data>::QueueVec() :
  Vector<Data>(4) { // la size iniziale è arbitraria, l'importante è che non
                    // si lascia il vettore vuoto per evitare di dover gestire
                    // diversamente i casi limite di inserimento e rimozione
  head = 0;
  tail = 0;
  sentry = 3; // size - 1
}

// Specific constructor
template<typename Data>
QueueVec<Data>::QueueVec(const LinearContainer<Data>& con) {
  size = con.Size() * 2;
  tail = con.Size();
  head = 0;
  sentry = size - 1;
  Elements = new Data[size] {};
  for (ulong index = 0; index < tail; ++index) {
    Elements[index] = con[index];
  }
}

// Copy constructor
template<typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data>& qvec) :
  Vector<Data>(qvec) {
  head = qvec.head;
  tail = qvec.tail;
  sentry = qvec.sentry;
} // copio il vettore ed aggiungo i campi in più

// Move constructor
template<typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data>&& qvec) noexcept :
  Vector<Data>(std::move(qvec)) {
  std::swap(head, qvec.head);
  std::swap(tail, qvec.tail);
  std::swap(sentry, qvec.sentry);
}

// Copy assignment
template<typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& qvec) {
  QueueVec<Data> *tmp = new QueueVec<Data>(qvec);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

// Move assignment
template<typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& qvec) noexcept {
  std::swap(Elements, qvec.Elements);
  std::swap(size, qvec.size);
  std::swap(head, qvec.head);
  std::swap(tail, qvec.tail);
  std::swap(sentry, qvec.sentry);
  return *this;
}

// Comparison operators
template<typename Data>
bool QueueVec<Data>::operator==(const QueueVec<Data>& qvec) const noexcept {
  if (Size() == qvec.Size()) {
    if (Size() == 0) {
      return true;
    }
    else if (head < tail && qvec.head < qvec.tail) {
      for (ulong ithis = head, iqvec = qvec.head; ithis < tail; ++ithis, ++iqvec) {
        if (Elements[ithis] != qvec.Elements[iqvec]) {
          return false;
        }
      }
      return true;
    }
    else /* other case */ { // ho preferito usare questo metodo poiché scrivere
                            // tutti gli altri casi in maniera efficiente era
                            // abbastanza complesso e richiedeva molte linee in più
                            // quindi per evitare errori ho preferito fare come segue
      QueueVec<Data> *tmp1 = new QueueVec<Data>(*this);
      QueueVec<Data> *tmp2 = new QueueVec<Data>(qvec);
      for (ulong index = 0; index < Size(); ++index) {
        if (tmp1->HeadNDequeue() != tmp2->HeadNDequeue()) {
          delete tmp1;
          delete tmp2;
          return false;
        }
      }
      delete tmp1;
      delete tmp2;
      return true;
    }
  }
  else {
    return false;
  }
}

template<typename Data>
bool QueueVec<Data>::operator!=(const QueueVec<Data>& qvec) const noexcept {
  return !(*this == qvec);
}

// Specific member functions (inherited from Queue)
template<typename Data>
void QueueVec<Data>::Enqueue(const Data& value) {
  if (tail == sentry) {
    Expand();
  }
  Elements[tail++] = value;
  if (tail == size) { // serve ad evitare, visto come ho implementato il codice
    tail = 0;         // di far superare agli indici il valore della size, quindi
  }                   // si immagina la coda circolare e si ragiona di conseguenza
}

template<typename Data>
void QueueVec<Data>::Enqueue(Data&& value) noexcept {
  if (tail == sentry) {
    Expand();
  }
  Elements[tail++] = std::move(value);
  if (tail == size) {
    tail = 0;
  }
}

template<typename Data>
Data& QueueVec<Data>::Head() const {
  if (Size() != 0) {
    return Elements[head];
  }
  else {
    throw std::length_error("Access to an empty queue.");
  }
}

template<typename Data>
void QueueVec<Data>::Dequeue() {
  if (Size() != 0) {
    if (Size() < size/4) {
      Reduce();
    }
    sentry = head++;
    if (head == size) {
      head = 0;
    }
  }
  else {
    throw std::length_error("Access to an empty queue.");
  }
}

template<typename Data>
Data QueueVec<Data>::HeadNDequeue() {
  if (Size() != 0) {
    if (Size() < size/4) {
      Reduce();
    }
    sentry = head++;
    if (head == size) {
      head = 0;
    }
    return Elements[sentry];
  }
  else {
    throw std::length_error("Access to an empty queue.");
  }
}

// Specific member functions (inherited from Container)
template<typename Data>
ulong QueueVec<Data>::Size() const noexcept {
  if (head <= tail) {
    return (tail - head);
  }
  else { // head > tail
    return ((size - head) + tail);
  }
}

template<typename Data>
void QueueVec<Data>::Clear() {
  Vector<Data>::Clear();
  size = 4;
  Elements = new Data[size] {};
  head = 0;
  tail = 0;
  sentry = 3; // size - 1
}

// Auxiliary member functions
template<typename Data>
void QueueVec<Data>::Expand() {
  if (tail < head) { // in questo caso non funziona la resize di vector, poiché si potrebbe
                     // rischiare di lasciare in mezzo al nuovo vettore degli elementi vuoti
    Data *TmpElements = new Data[2*size] {};
    ulong tmpindex = 0; // indice attuale del nuovo vettore
    for (ulong index = head; index < size; ++index) {
      std::swap(Elements[index], TmpElements[tmpindex++]);
    } // questo for scambia la parte iniziale del vecchio vettore con il nuovo
    for (ulong index = 0; index < tail; ++index) {
      std::swap(Elements[index], TmpElements[tmpindex++]);
    } // questo scambia invece la parte finale del vecchio vettore
    std::swap(Elements, TmpElements);
    // adesso devo aggiornare gli indici
    head = 0;
    tail = tmpindex;
    size *= 2;
    sentry = size - 1;
    delete[] TmpElements;
  }
  else { // head < tail
    // in questo caso posso sfruttare la resize di vector
    Vector<Data>::Resize(2*size);
    sentry = size - 1;
  }
}

template<typename Data>
void QueueVec<Data>::Reduce() {
  // procedimento analogo all'expand
  if (tail < head) {
    Data *TmpElements = new Data[size/2] {};
    ulong tmpindex = 0;
    for (ulong index = head; index < size; ++index) {
      std::swap(Elements[index], TmpElements[tmpindex++]);
    }
    for (ulong index = 0; index < tail; ++index) {
      std::swap(Elements[index], TmpElements[tmpindex++]);
    }
    std::swap(Elements, TmpElements);
    head = 0;
    tail = tmpindex;
    size /= 2;
    sentry = size - 1;
    delete[] TmpElements;
  }
  else { // head < tail
    // non posso usare la resize poiché potrei non avere gli elementi
    // all'inizio del vettore e quindi rischierei di perdere dei dati
    Data *TmpElements = new Data[size/2] {};
    ulong tmpindex = 0;
    for (ulong index = head; index < tail; ++index) {
      std::swap(Elements[index], TmpElements[tmpindex++]);
    }
    std::swap(Elements, TmpElements);
    head = 0;
    tail = tmpindex;
    size /= 2;
    sentry = size - 1;
    delete[] TmpElements;
  }
}

/* ************************************************************************** */

}
