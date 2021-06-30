
namespace lasd {

/* ************************************************************************** */

// Default constructor
template<typename Data>
MatrixCSR<Data>::MatrixCSR() {
  RowVec.Resize(1);
  RowVec[0] = &head;
}

// Specific constructor
template<typename Data>
MatrixCSR<Data>::MatrixCSR(ulong newrow, ulong newclm) {
  row = newrow;
  clm = newclm;
  RowVec.Resize(row + 1);
  for (ulong index = 0; index < row + 1; ++index) {
    RowVec[index] = &head;
  }
}

// Copy constructor
template<typename Data>
MatrixCSR<Data>::MatrixCSR(const MatrixCSR<Data>& csr) :
  MatrixCSR<Data>(csr.row, csr.clm) {
  for (ulong index = 0; index < row; ++index) {
    for (Node* *ptr = csr.RowVec[index]; ptr != csr.RowVec[index + 1]; ptr = &((*ptr)->next)) {
      this->operator()(index, (*ptr)->info.second) = (*ptr)->info.first;
    }
  }
}

// Move constructor
template<typename Data>
MatrixCSR<Data>::MatrixCSR(MatrixCSR<Data>&& csr) noexcept {
  std::swap(row, csr.row);
  std::swap(clm, csr.clm);
  std::swap(size, csr.size);
  std::swap(head, csr.head);
  std::swap(RowVec, csr.RowVec);
  // aggiornare il vettore è necessario poiché
  // spostanto semplicemente il vettore non mi
  // sposta anche l'indirizzo della vecchia head
  UpdateRowVec(0, head);
}

// Copy assignment
template<typename Data>
MatrixCSR<Data>& MatrixCSR<Data>::operator=(const MatrixCSR<Data>& csr) {
  Clear();
  MatrixCSR<Data> *tmp = new MatrixCSR<Data>(csr);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

// Move assignment
template<typename Data>
MatrixCSR<Data>& MatrixCSR<Data>::operator=(MatrixCSR<Data>&& csr) noexcept {
  std::swap(row, csr.row);
  std::swap(clm, csr.clm);
  std::swap(size, csr.size);
  std::swap(head, csr.head);
  std::swap(RowVec, csr.RowVec);
  UpdateRowVec(0, head);
  return *this;
}

// Comparison operators
template<typename Data>
bool MatrixCSR<Data>::operator==(const MatrixCSR<Data>& csr) const noexcept {
  if (row == csr.row && clm == csr.clm) {
    if (size == csr.size) {
      if (size == 0) {
        return true;
      }
      for (ulong index = 0; index < row; ++index) {
        for (Node **ptr_this = RowVec[index], **ptr_csr = csr.RowVec[index]; ptr_csr != csr.RowVec[index + 1];
             /* scorro le colonne con */ ptr_this = &((*ptr_this)->next), ptr_csr = &((*ptr_csr)->next)) {
          if ((*ptr_this)->info != (*ptr_csr)->info) {
            return false;
          }
        }
      }
      return true;
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }
}

template<typename Data>
bool MatrixCSR<Data>::operator!=(const MatrixCSR<Data>& csr) const noexcept {
  return !(*this == csr);
}

// Specific member functions (inherited from Matrix)
template<typename Data>
void MatrixCSR<Data>::RowResize(const ulong newrow) {
  if (newrow == 0) {
    ulong tmp = clm;
    Clear();
    clm = tmp;
  }
  if (newrow > row) {
    RowVec.Resize(newrow + 1);
    for (ulong index = row + 1; index < newrow + 1; ++index) {
      RowVec[index] = RowVec[row];
    }
  }
  if (newrow < row) {
    RowVec.Resize(newrow + 1);
    // funzione ausiliaria necessaria poiché il mio distruttore
    // di nodo implementato in lista non mi cancella tutta la sua
    // sottolista, altrimenti basta fare delete *RowVec[newrow]
    // ma in quel caso bisogna aggiornare la size con un for
    DeleteSubList(*RowVec[newrow]);
    *RowVec[newrow] = nullptr;
  }
  row = newrow; // in qualsiasi condizione dovrò aggiornare il valore delle righe
}

template<typename Data>
void MatrixCSR<Data>::ColumnResize(const ulong newclm) {
  if (newclm == 0) {
    // Pulsico solo la lista delle colonne
    List<std::pair<Data, ulong>>::Clear();
  }
  if (newclm < clm) {
    for (ulong index = 0; index < row; ++index) {
      Node* *ptr = RowVec[index];
      bool exit = false;
      while (ptr != RowVec[index + 1] && !exit) {
        if ((*ptr)->info.second < newclm) {
          ptr = &((*ptr)->next);
        }
        else {
          if (RowVec[index + 1] == &((*ptr)->next)) {
            // se mi trvo di dover cancellare un nodo usato nel
            // vettore delle righe allora ovviamente dovrò anche
            // aggiornare quest'ultimo con il nodo successivo
            UpdateRowVec(index + 1, *ptr);
            exit = true;
          }
          Node *tmp = *ptr;
          *ptr = tmp->next;
          delete tmp;
          --size;
        }
      }
    }
  }
  clm = newclm; // in qualsiasi condizione dovrò aggiornare il valore delle colonne
}

template<typename Data>
bool MatrixCSR<Data>::ExistsCell(const ulong irow, const ulong iclm) const noexcept {
  if (irow < row && iclm < clm) {
    if (RowVec[irow] != RowVec[irow + 1]) {
      for (Node* *ptr = RowVec[irow]; ptr != RowVec[irow + 1]; ptr = &((*ptr)->next)) {
        if ((*ptr)->info.second == iclm) {
          return true;
        }
        if ((*ptr)->info.second > iclm) {
          return false;
        }
      }
      return false;
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }
}

template<typename Data>
Data& MatrixCSR<Data>::operator()(const ulong irow, const ulong iclm) {
  if (irow < row && iclm < clm) {
    Node* *ptr = RowVec[irow];
    while (ptr != RowVec[irow + 1]) {
      // se trovo l'indice di colonna allora ritorno il nodo
      if ((*ptr)->info.second == iclm) {
        return (*ptr)->info.first;
      }
      // se supero l'indice di colonna allora devo aggiungere un nuovo nodo
      else if ((*ptr)->info.second > iclm) {
        Node *newnode = new Node;
        newnode->info.second = iclm;
        newnode->next = *ptr;
        *ptr = newnode;
        ++size;
        return newnode->info.first;
      }
      else {
        // altrimenti vado al nodo successivo
        ptr = &((*ptr)->next);
      }
    } // se esco da questo while significa che devo inserire il dato in una riga
      // ancora tutta vuota, e quindi devo aggiornare anche il vettore delle righe
    Node *newnode = new Node;
    newnode->info.second = iclm;
    if (*ptr != nullptr) {
      newnode->next = *ptr;
    }
    else {
      newnode->next = nullptr;
    }
    *ptr = newnode;
    UpdateRowVec(irow + 1, newnode->next);
    ++size;
    return newnode->info.first;
  }
  else {
    throw std::out_of_range("Access at cell [" + std::to_string(irow) + "," + std::to_string(iclm) + "]; matrix size '" + std::to_string(row) + "x" + std::to_string(clm) + "'.");
  }
}

template<typename Data>
Data const& MatrixCSR<Data>::operator()(const ulong irow, const ulong iclm) const {
  if (irow < row && iclm < clm) {
    for (Node* *ptr = RowVec[irow]; ptr != RowVec[irow + 1]; ptr = &((*ptr)->next)) {
      if ((*ptr)->info.second == iclm) {
        return (*ptr)->info.first;
      }
      else if ((*ptr)->info.second > iclm) {
        throw std::length_error("Access to an empty Cell.");
      }
    }
    throw std::length_error("Access to an empty Cell.");
  }
  else {
    throw std::out_of_range("Access at cell [" + std::to_string(irow) + "," + std::to_string(iclm) + "]; matrix size '" + std::to_string(row) + "x" + std::to_string(clm) + "'.");
  }
}

template<typename Data>
void MatrixCSR<Data>::Clear() {
  List<std::pair<Data, ulong>>::Clear();
  RowVec.Resize(1);
  RowVec[0] = &head;
  row = 0;
  clm = 0;
}

template<typename Data>
void MatrixCSR<Data>::MapPreOrder(MapFunctor fun, void* par) {
  List<std::pair<Data, ulong>>::MapPreOrder (
    [&fun](std::pair<Data, ulong>& dat, void* parx) { fun(dat.first, parx); }
    , par
  );
} // questo è un esempio di espressione lambda, praticamente mi permette di usare
  // la map di lista sul solo parametro first della pair

template<typename Data>
void MatrixCSR<Data>::MapPostOrder(const MapFunctor fun, void* par) {
  MapPostOrder(fun, par, head);
} // ho dovuto reimplementare le post perché in lista usavo la tail ed il puntatore prev

template<typename Data>
void MatrixCSR<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const {
  List<std::pair<Data, ulong>>::FoldPreOrder (
    [&fun](const std::pair<Data, ulong>& dat, const void* parx, void* accx) { fun(dat.first, parx, accx); }
    , par
    , acc
  );
}

template<typename Data>
void MatrixCSR<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const {
  FoldPostOrder(fun, par, acc, head);
}

/* ************************************************************************** */

// Auxiliary member functions
template<typename Data>
void MatrixCSR<Data>::DeleteSubList(Node* curr) {
  while (curr != nullptr) {
    Node *tmp = curr;
    curr = curr->next;
    --size;
    delete tmp;
  }
}

template<typename Data>
void MatrixCSR<Data>::UpdateRowVec(ulong irow, Node*& nod) {
  for (ulong index = irow + 1; index < row + 1; ++index) {
    if (RowVec[index] == RowVec[irow]) {
      RowVec[index] = &nod;
    }
  }
  RowVec[irow] = &nod;
}

template<typename Data>
void MatrixCSR<Data>::MapPostOrder(const MapFunctor fun, void* par, Node* curr) {
  if (curr == nullptr) {
    return;
  }
  MapPostOrder(fun, par, curr->next);
  fun(curr->info.first, par);
}

template<typename Data>
void MatrixCSR<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc, Node* curr) const {
  if (curr == nullptr) {
    return;
  }
  FoldPostOrder(fun, par, acc, curr->next);
  fun(curr->info.first, par, acc);
}

/* ************************************************************************** */

}
