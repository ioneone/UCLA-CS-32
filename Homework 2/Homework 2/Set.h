//
//  Set.h
//  Homework 2
//
//  Created by Junhong Wang on 2/2/19.
//  Copyright © 2019 ioneone. All rights reserved.
//

#ifndef Set_h
#define Set_h

#include <string>

// Later in the course, we'll see that templates provide a much nicer
// way of enabling us to have Sets of different types.  For now,
// we'll use a type alias.

using ItemType = char;

class Set
{
public:
    Set();               // Create an empty set (i.e., one with no items).
    bool empty() const;  // Return true if the set is empty, otherwise false.
    int size() const;    // Return the number of items in the set.
    
    bool insert(const ItemType& value);
    // Insert value into the set if it is not already present.  Return
    // true if the value was actually inserted.  Leave the set unchanged
    // and return false if the value was not inserted (perhaps because it
    // was already in the set or because the set has a fixed capacity and
    // is full).
    
    bool erase(const ItemType& value);
    // Remove the value from the set if present.  Return true if the
    // value was removed; otherwise, leave the set unchanged and
    // return false.
    
    bool contains(const ItemType& value) const;
    // Return true if the value is in the set, otherwise false.
    
    bool get(int i, ItemType& value) const;
    // If 0 <= i < size(), copy into value the item in the set that is
    // strictly greater than exactly i items in the set and return true.
    // Otherwise, leave value unchanged and return false.
    
    void swap(Set& other);
    // Exchange the contents of this set with the other one.
    
    // Housekeeping functions
    ~Set();
    Set(const Set& other);
    Set& operator=(const Set& rhs);
    
private:
    // Representation:
    //   a circular doubly-linked list with a dummy node.
    //   m_head points to the dummy node.
    //   m_head->m_prev->m_next == m_head and m_head->m_next->m_prev == m_head
    //   m_size == 0  iff  m_head->m_next == m_head->m_prev == m_head
    //   If p and p->m_next point to nodes other than the dummy node,
    //      p->m_value < p->m_next->m_value
    
    struct Node
    {
        ItemType m_value;
        Node*    m_next;
        Node*    m_prev;
    };
    
    Node* m_head;
    int   m_size;
    
    void createEmpty();
    // Create an empty list.  (Will be called only by constructors.)
    
    void insertBefore(Node* p, const ItemType& value);
    // Insert value in a new Node before Node p, incrementing m_size.
    
    void doErase(Node* p);
    // Remove the Node p, decrementing m_size.
    
    Node* findFirstAtLeast(const ItemType& value) const;
    // Return pointer to first Node whose m_value >= value if present,
    // else m_head
};

// Declarations of non-member functions

void unite(const Set& s1, const Set& s2, Set& result);
// result = { x | (x in s1) OR (x in s2) }

void subtract(const Set& s1, const Set& s2, Set& result);
// result = { x | (x in s1) AND NOT (x in s2) }

// Inline implementations

inline
int Set::size() const
{
    return m_size;
}

inline
bool Set::empty() const
{
    return size() == 0;
}

inline
bool Set::contains(const ItemType& value) const
{
    Node* p = findFirstAtLeast(value);
    return p != m_head  &&  p->m_value == value;
}

#endif /* Set_h */
