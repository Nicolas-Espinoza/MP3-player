#ifndef LIST_H
#define LIST_H

#include <iostream>

template<typename T>
struct nodo
{
  T dato;
  nodo<T>* next;
};

template<typename T>
class List
{
private:
  nodo<T> *header;
  int size;
public:
  List();
  List(List& L);
  ~List();

  void append(T data);
  void insert(T data,int pos);
  void remove(int pos);
  T& operator[](int pos);
  List<T>& operator=(List<T>& L);
  int length(){ return size; }
protected:
  nodo<T>* get_address(int pos);
};

template<typename T>
List<T>::List()
{
  header = new nodo<T>;
  header->next = nullptr;
  size = 0;
}

template<typename T>
List<T>::List(List<T>& L)
{
  header = new nodo<T>;
  header->next = nullptr;
  size = 0;
  (*this) = L;
}

template<typename T>
List<T>::~List()
{
  while( size )
    remove(0);
  delete header;
}

template<typename T>
void List<T>::append(T data)
{
  nodo<T> *prev = get_address(size-1);

  nodo<T> *_new = new nodo<T>;
  _new->dato = data;
  _new->next = nullptr;

  prev->next = _new;
  size++;
}

template<typename T>
void List<T>::insert(T data,int pos)
{
  if( pos < 0 || pos > size )
    throw("Index out of range");

  nodo<T> *prev = get_address(pos-1);
  nodo<T> *curr = prev->next;
  nodo<T> *_new = new nodo<T>;
  _new->dato = data;
  _new->next = curr;
  prev->next = _new;
  size++;
}

template<typename T>
void List<T>::remove(int pos)
{
  if( pos < 0 || pos >= size )
    throw("Index out of range");

  nodo<T> *prev  = get_address(pos-1);
  nodo<T> *next = get_address(pos+1);
  delete prev->next;
  prev->next = next;
  size--;
}

template<typename T>
T& List<T>::operator[](int pos)
{
  if( pos < 0 || pos >= size )
    throw("index out of range");

  return get_address(pos)->dato;
}

template<typename T>
List<T>& List<T>::operator=(List<T>& L)
{
  while( size > L.size )
    remove(0);
  for( int i=0 ; i<L.size ; i++ )
  {
    if( size <= i )
      append(L[i]);
    else
      (*this)[i] = L[i];
  }
  return *this;
}

template<typename T>
nodo<T>* List<T>::get_address(int pos)
{
  if( pos == -1 )
    return header;
  if( pos < -1 || pos >= size )
    return nullptr;

  nodo<T> *aux = header->next;
  while( pos-- )
    aux = aux->next;
  return aux;
}

#endif // LIST_H
