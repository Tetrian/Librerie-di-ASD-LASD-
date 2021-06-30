
namespace lasd {

/* ************************************************************************** */

// Default constructor
template<typename Data>
MatrixVec<Data>::MatrixVec() :
  Vector<Data>() {
  row = 0;
  clm = 0;
}

// Specific constructors
template<typename Data>
MatrixVec<Data>::MatrixVec(const ulong newrow, const ulong newclm) :
  Vector<Data>(newrow * newclm) {
  row = newrow;
  clm = newclm;
}

// Copy constructor
template<typename Data>
MatrixVec<Data>::MatrixVec(const MatrixVec<Data>& mvec) :
  Vector<Data>(mvec) {
  row = mvec.row;
  clm = mvec.clm;
}

// Move constructor
template<typename Data>
MatrixVec<Data>::MatrixVec(MatrixVec<Data>&& mvec) noexcept :
  Vector<Data>(std::move(mvec)) {
  std::swap(row, mvec.row);
  std::swap(clm, mvec.clm);
}

// Copy assignment
template<typename Data>
MatrixVec<Data>& MatrixVec<Data>::operator=(const MatrixVec<Data>& mvec) {
  MatrixVec<Data> *tmp = new MatrixVec<Data>(mvec);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

// Move assignment
template<typename Data>
MatrixVec<Data>& MatrixVec<Data>::operator=(MatrixVec<Data>&& mvec) noexcept {
  std::swap(Elements, mvec.Elements);
  std::swap(size, mvec.size);
  std::swap(row, mvec.row);
  std::swap(clm, mvec.clm);
  return *this;
}

// Comparison operators
template<typename Data>
bool MatrixVec<Data>::operator==(const MatrixVec<Data>& mvec) const noexcept {
  if (row == mvec.row && clm == mvec.clm) {
    for (ulong index = 0; index < size; ++index) {
      if (Elements[index] != mvec.Elements[index]) {
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
bool MatrixVec<Data>::operator!=(const MatrixVec<Data>& mvec) const noexcept {
  return !(*this == mvec);
}

// Specific member functions (inherited from Matrix)
template<typename Data>
void MatrixVec<Data>::RowResize(const ulong newrow) {
  if (newrow == 0) {
    // ha senso mantentere il numero di colonne totali
    ulong tmp = clm;
    Clear();
    clm = tmp;
  }
  else if (row != newrow) {
    // se cambio li numero di righe posso usare la resize
    // di vector perchè mantiene intatta la mia matrice
    Vector<Data>::Resize(newrow * clm);
    row = newrow;
  }
}

template<typename Data>
void MatrixVec<Data>::ColumnResize(const ulong newclm) {
  if (newclm == 0) {
    // ha senso mantentere il numero di righe totali
    ulong tmp = row;
    Clear();
    row = tmp;
  }
  else if (clm != newclm) {
    // devo copiare gli elementi del vecchio vettore 
    // nel nuovo ma nelle giuste posizioni, quindi non
    // posso usare banalmente la resize di vector
    ulong column = (clm < newclm) ? clm : newclm;
    Data *TmpElements = new Data[row * newclm] {};
    for (ulong irow = 0; irow < row; ++irow) {
      for (ulong iclm = 0; iclm < column; ++iclm) {
        std::swap(Elements[(irow * clm) + iclm], TmpElements[(irow * newclm) + iclm]);
      }
    }
    std::swap(Elements, TmpElements);
    clm = newclm;
    size = row * clm;
    delete[] TmpElements;
  }
}

template<typename Data>
Data& MatrixVec<Data>::operator()(const ulong irow, const ulong iclm) {
  return const_cast<Data&>(static_cast<const MatrixVec<Data>*>(this)->operator()(irow, iclm));
}

template<typename Data>
Data const& MatrixVec<Data>::operator()(const ulong irow, const ulong iclm) const {
  if (ExistsCell(irow, iclm)) {
    return Elements[(irow * clm) + iclm];
  }
  else {
    throw std::out_of_range("Access at cell [" + std::to_string(irow) + "," + std::to_string(iclm) + "]; matrix size '" + std::to_string(row) + "x" + std::to_string(clm) + "'.");
  }
}

// Specific member functions (inherited from Container)
template<typename Data>
void MatrixVec<Data>::Clear() {
  Vector<Data>::Clear();
  row = 0;
  clm = 0;
}

/* ************************************************************************** */

}
