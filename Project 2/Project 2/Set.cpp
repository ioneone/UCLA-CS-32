//
//  Set.cpp
//  Project 2
//
//  Created by Junhong Wang on 1/24/19.
//  Copyright © 2019 ioneone. All rights reserved.
//

#include "Set.h"
#include <iostream>

Set::Set() {
    m_size = 0;
    m_head = nullptr;
    m_tail = nullptr;
}

Set::Set(const Set& other) {
    m_size = other.m_size;
    Node *otherNode = other.m_head;

    if (otherNode == nullptr) {
        m_head = nullptr;
        m_tail = nullptr;
        return;
    }

    m_head = new Node();
    m_head->value = otherNode->value;
    m_head->prev = nullptr;
    m_head->next = nullptr;

    Node *thisNode = m_head;
    while (otherNode->next != nullptr) {
        otherNode = otherNode->next;
        Node *nextNode = new Node();
        nextNode->value = otherNode->value;
        nextNode->prev = thisNode;
        nextNode->next = nullptr;
        thisNode->next = nextNode;
        thisNode = nextNode;
    }

    m_tail = thisNode;
}

Set::~Set() {
    if (m_head == nullptr) return;

    Node *node = m_head;
    Node *nodeNext = m_head->next;

    while (nodeNext != nullptr) {
        delete node;
        node = nodeNext;
        nodeNext = nodeNext->next;

    }

    delete node;
}

bool Set::empty() const {
    return m_size == 0;
}

int Set::size() const {
    return m_size;
}

bool Set::insert(const ItemType& value) {
    // no items in the Set
    if (m_head == nullptr) {
        m_head = new Node();
        m_head->value = value;
        m_head->prev = nullptr;
        m_head->next = nullptr;
        m_tail = m_head;
    }
    // at least one item in the Set
    // insert item at head
    else if (value < m_head->value) {
        Node *oldHead = m_head;
        m_head = new Node();
        m_head->value = value;
        m_head->prev = nullptr;
        m_head->next = oldHead;
        oldHead->prev = m_head;
    }
    // at least one item in the Set
    // insert item at tail
    else if (m_tail->value < value) {
        Node *oldTail = m_tail;
        m_tail = new Node();
        m_tail->value = value;
        m_tail->prev = oldTail;
        m_tail->next = nullptr;
        oldTail->next = m_tail;
    }
    // at least two items in the Set
    // insert item between head and tail
    else {
        Node *node = m_head;
        while (true) {
            if (node->value == value) return false;
            if (node->value < value && value < node->next->value) {
                Node *newNode = new Node();
                newNode->value = value;
                newNode->prev = node;
                newNode->next = node->next;
                node->next->prev = newNode;
                node->next = newNode;
                break;
            }
            node = node->next;
        }
    }

    // insert item successfully
    m_size++;
    return true;
}

bool Set::erase(const ItemType& value) {
    // empty Set
    if (m_head == nullptr) return false;

    Node *node;

    // check head
    if (m_head->value == value) {
        node = m_head->next;
        delete m_head;
        // check if head and tail were the same
        if (node == nullptr) {
            m_head = nullptr;
            m_tail = nullptr;
        } else {
            m_head = node;
            m_head->prev = nullptr;
        }
        m_size--;
        return true;
    }

    // check tail
    if (m_tail->value == value) {
        node = m_tail->prev;
        node->next = nullptr;
        delete m_tail;
        m_tail = node;
        m_size--;
        return true;
    }

    // check nodes between head and tail
    node = m_head->next;
    if (node == nullptr) return false;
    while (node != m_tail) {
        if (node->value > value) return false;
        if (node->value == value) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            delete node;
            m_size--;
            return true;
        }
        node = node->next;
    }

    // item to erase not found
    return false;
}

bool Set::contains(const ItemType& value) const {
    Node *node = m_head;

    while (node != nullptr) {
        if (node->value == value) return true;
        node = node->next;
    }

    return false;
}

bool Set::get(int pos, ItemType& value) const {
    if (pos < 0 || m_size <= pos) return false;

    Node *node = m_head;
    for (int i = 0; i < pos; i++)
        node = node->next;

    value = node->value;

    return true;

}

void Set::swap(Set& other) {
    Node* tmpPtr;

    // swap size
    int tmpSize = m_size;
    m_size = other.m_size;
    other.m_size = tmpSize;

    // swap head
    tmpPtr = m_head;
    m_head = other.m_head;
    other.m_head = tmpPtr;

    // swap tail
    tmpPtr = m_tail;
    m_tail = other.m_tail;
    other.m_tail = tmpPtr;

}

Set& Set::operator=(const Set& other) {
    if (this == &other) return *this;

    Node *otherNode = other.m_head;
    Node *thisNode = m_head;
    Node *thisNodePrev = nullptr;

    while (otherNode != nullptr && thisNode != nullptr) {
        thisNode->value = otherNode->value;
        thisNodePrev = thisNode;
        thisNode = thisNode->next;
        otherNode = otherNode->next;
    }

    // otherNode == nullptr && thisNode == nullptr
    if (m_size == other.m_size) return *this;

    // need to create more nodes
    // thisNode == nullptr
    if (m_size < other.m_size) {

        // m_head is nullptr
        if (thisNodePrev == nullptr) {
            m_head = new Node();
            m_head->value = otherNode->value;
            m_head->prev = nullptr;
            m_head->next = nullptr;
            thisNodePrev = m_head;
            otherNode = otherNode->next;
        }

        while (otherNode != nullptr) {
            Node *newNode = new Node();
            newNode->value = otherNode->value;
            newNode->prev = thisNodePrev;
            newNode->next = nullptr;
            thisNodePrev->next = newNode;

            thisNodePrev = thisNodePrev->next;
            otherNode = otherNode->next;
        }
        m_tail = thisNodePrev;
    }
    // need to delete extra nodes
    // otherNode == nullptr
    else {
        Node *thisNodeNext = thisNode->next;

        // other.m_head is nullptr
        (thisNodePrev == nullptr) ? m_head = nullptr : thisNodePrev->next = nullptr;

        m_tail = thisNodePrev;
        while (thisNodeNext != nullptr) {
            delete thisNode;
            thisNode = thisNodeNext;
            thisNodeNext = thisNodeNext->next;
        }
        delete thisNode;
    }

    m_size = other.m_size;
    return *this;
}

void Set::dump() const {
    Node *node;

    // print from head
    std::cout << "Printing from Head:" << std::endl;
    node = m_head;
    while (node != nullptr) {
        std::cout << node->value << " -> ";
        node = node->next;
    }
    std::cout << '\n';

    // print from tail
    std::cout << "Printing from Tail:" << std::endl;
    node = m_tail;
    while (node != nullptr) {
        std::cout << node->value << " -> ";
        node = node->prev;
    }
    std::cout << '\n';
}

void unite(const Set& s1, const Set& s2, Set& result) {
    Set *set = new Set(s1);
    ItemType value;
    for (int i = 0; i < s2.size(); i++) {
        s2.get(i, value);
        set->insert(value);
    }
    result = *set;
    delete set;
}

void subtract(const Set& s1, const Set& s2, Set& result) {
    Set *set = new Set(s1);
    ItemType value;
    for (int i = 0; i < s2.size(); i++) {
        s2.get(i, value);
        set->erase(value);
    }
    result = *set;
    delete set;
}
