
namespace lasd {

/* ************************************************************************** */

// Specific member functions (SearchableContainer)
template<typename Data>
void AuxFoldExist(const Data& dat, const void* val, void* exists) {
  if (dat == *((Data*) val)) {
    *((bool*) exists) = true;
  }
}

template<typename Data>
bool FoldableContainer<Data>::Exists(const Data& dat) const noexcept {
  bool exists = false;
  // chiamo la funzione AuxFoldExist che cambia l'accumulatore exists in true
  // solo se trova il dato dat all'interno del contenitore, altrimenti resta false
  FoldPreOrder(&AuxFoldExist<Data>, &dat, &exists);
  return exists;
}

/* ************************************************************************** */

}
