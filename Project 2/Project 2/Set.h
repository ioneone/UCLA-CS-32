//
//  Set.h
//  Project 2
//
//  Created by Junhong Wang on 1/24/19.
//  Copyright © 2019 ioneone. All rights reserved.
//

#ifndef Set_h
#define Set_h

#include <string>
using ItemType = long;
//using ItemType = unsigned long;

class Set
{
public:
    Set();
    Set(const Set& other);
    ~Set();
    
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);
    Set& operator=(const Set& other);
    void dump() const;
    
private:
    struct Node {
        ItemType value;
        Node *prev, *next;
    };
    
    int m_size;
    Node *m_head, *m_tail;
    
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif /* Set_h */
