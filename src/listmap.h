// $Id: listmap.h,v 1.1 2014-05-25 13:17:09-07 - - $

#ifndef __LISTMAP_H__
#define __LISTMAP_H__

#include "xless.h"
#include "xpair.h"

template <typename Key, typename Value, class Less=xless<Key>>
class listmap {
   public:
      typedef Key key_type;
      typedef Value mapped_type;
      typedef xpair<key_type,mapped_type> value_type;
   private:
      Less less;
      struct node {
         value_type pair;
         node* prev;
         node* next;
         node (const value_type&); //ctor for struct node
      }; //this is not a field, but a type struct
      node* head;
      node* tail;
   public:
      class iterator; //all done?
      listmap();  //default ctor for listmap
      listmap (const listmap&);
      listmap& operator= (const listmap&);
      ~listmap();
      void insert (const value_type&);
      //iterator find (const key_type&) ;
      iterator find (const key_type&) const;
      iterator begin(); //return head?
      iterator end(); //return null?
      bool empty() const;
};


template <typename Key, typename Value, class Less=xless<Key>>
class listmap<Key,Value,Less>::iterator {
      friend class listmap<Key,Value>;
   private:
      iterator (listmap* map, node* where);
      //iterator (listmap* map, node* where) const;
      listmap<Key,Value,Less>* map;
      node* where;
   public:
      iterator(): map(NULL), where(NULL) {}
      value_type& operator*(); //deference return actual value
      value_type* operator->(); //return address?
      iterator& operator++(); //++itor
      iterator& operator--(); //--itor
      void erase(); //remove pointed data; double erase will error
      bool operator== (const iterator&) const;
      inline bool operator!= (const iterator& that) const {
         return not (*this == that);
      }
};

#include "listmap.tcc" //is this needed?
#endif

