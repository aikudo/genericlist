// $Id: listmap.tcc,v 1.1 2014-05-25 13:17:09-07 - - $

#include "listmap.h"
#include "trace.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

//ctor node(pair&)
//DONE
template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::node::node (const value_type& pair):
            pair(pair), prev(nullptr), next(nullptr) {
   //cout << "\x1B[0mctor node for header line 21\x1B[0m" << endl;
   TRACE ('l', (void*) this << "->node::node()");
}

//default ctor for list
//how about stuff for node?
//DONE
template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::listmap (): head(nullptr), tail (nullptr) {
   TRACE ('l', (void*) this << "->list()");
}

template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::~listmap () {
   node *curr(head), *prev;
   //clean up link list
   while(curr!=nullptr){
      prev=curr;
      curr=curr->next;
      delete prev;
   }
   TRACE ('l', (void*) this << "->list~");
}

//TODO
//lexicograph inserted by key increasing order
template <typename Key, typename Value, class Less>
void listmap<Key,Value,Less>::insert (const xpair<Key,Value>& pair) {
  // cout << "insert list"  << endl;
   node *node_ = new node(pair);
   node *curr = head;
   Less less;

   while (curr != nullptr 
         and less (curr->pair.second, pair.second) )
      curr = curr->next;
   //curr is either at end or  more than 
   //if( curr == nullptr or less (

   if(head == nullptr){ //empty list
      cout<<"insert head" << endl;
      head = node_;
      tail = node_;
   }else{ //insert at the end
      cout<<"insert tail" << endl;
      tail->next = node_;
      node_->prev = tail;
      tail=node_;
   }
   TRACE ('l', &pair << "->" << pair);
}

template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator  //return type
//listmap<Key,Value,Less>::find (const key_type& that) {
//FIXME TO const
listmap<Key,Value,Less>::find (const key_type& that) const {
   node* curr(head);
   while(curr != nullptr){
      if(curr->pair.first == that) break;
      curr=curr->next;
   }
   TRACE ('l', that);
   return iterator(this, curr);
   //return iterator(this, curr);
}

//member function from listmap->begin()
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator //return type
listmap<Key,Value,Less>::begin () {
   return iterator (this, head); // create a iterator?
}

//member function from listmap->end()
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::end () {
   return iterator (this, nullptr);
}

template <typename Key, typename Value, class Less>
bool listmap<Key,Value,Less>::empty () const {
   return head == nullptr;
}


template <typename Key, typename Value, class Less>
xpair<Key,Value>& listmap<Key,Value,Less>::iterator::operator* () {
   TRACE ('l', where->pair);
   return where->pair;
}

template <typename Key, typename Value, class Less>
xpair<Key,Value> *listmap<Key,Value,Less>::iterator::operator-> () {
   TRACE ('l', where->pair);
   return &(where->pair);
}

template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator++ () {
   TRACE ('l', "First: " << map << ", " << where);
   TRACE ('l', "Second: " << map->head << ", " << map->tail);
   where = where->next;
   return *this;
}

template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator-- () {
   where = where->prev;
   return *this;
}

template <typename Key, typename Value, class Less>
bool listmap<Key,Value,Less>::iterator::operator==
            (const iterator& that) const {
   return this->where == that.where;
}

//iterator ctor
template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::iterator::iterator (listmap *map,
            node *where): map (map), where (where){
}

template <typename Key, typename Value, class Less>
void listmap<Key,Value,Less>::iterator::erase () { //TODO
   TRACE ('l', "map = " << map << ", where = " << where << endl);
}

