//
//  newSet.cpp
//  Homework 1
//
//  Created by Junhong Wang on 1/18/19.
//  Copyright © 2019 ioneone. All rights reserved.
//

#include <iostream>
#include "newSet.h"

Set::Set() {
    m_size = 0;
    m_maxSize = DEFAULT_MAX_ITEMS;
    m_data = new ItemType[DEFAULT_MAX_ITEMS];
}

Set::Set(int maxSize) {
    if (maxSize < 0) exit(1);
    m_size = 0;
    m_maxSize = maxSize;
    m_data = new ItemType[maxSize];
}

Set::~Set() {
    delete[] m_data;
}

Set::Set(const Set &other) {
    m_size = other.m_size;
    m_maxSize = other.m_maxSize;
    m_data = new ItemType[m_maxSize];

    for (int i = 0; i < m_size; i++)
        m_data[i] = other.m_data[i];

}

bool Set::empty() const {
    return m_size == 0;
}

int Set::size() const {
    return m_size;
}

bool Set::insert(const ItemType& value) {
    // do nothing if the value is already in the Set or the set exceeds maximum capacity
    if (contains(value) || m_size == m_maxSize) return false;

    m_data[m_size++] = value;
    return true;
}

bool Set::erase(const ItemType& value) {
    for (int i = 0; i < m_size; i++) {

        // target found
        if (m_data[i] == value) {

            // delete the target and shift the positions of data afterwards
            for (int j = i; j < m_size - 1; j++)
                m_data[j] = m_data[j + 1];

            m_size--;

            // successfully deleted value from the Set
            return true;

        }
    }

    // value not found in the Set
    return false;
}

bool Set::contains(const ItemType& value) const {
    for (int i = 0; i < m_size; i++)
        if (m_data[i] == value) return true;

    return false;
}

bool Set::get(int i, ItemType& value) const {
    if (i < 0 || i >= m_size) return false;

    for (int j = 0; j < m_size; j++) {
        int counter = 0;
        for (int k = 0; k < m_size; k++) {
            if (j == k) continue;
            if (m_data[j] > m_data[k]) {
                counter++;
            }
        }

        if (counter == i) {
            value = m_data[j];
            return true;
        }

    }

    return false;
}

void Set::swap(Set& other) {
    ItemType *tmpData = m_data;
    int tmpSize = m_size;
    int tmpMaxSize = m_maxSize;

    // swap data
    m_data = other.m_data;
    other.m_data = tmpData;

    // swap size
    m_size = other.m_size;
    other.m_size = tmpSize;

    // swap maxSize
    m_maxSize = other.m_maxSize;
    other.m_maxSize = tmpMaxSize;

}

Set& Set::operator=(const Set &other) {
    if (&other == this) return *this;

    m_size = other.m_size;

    if (m_maxSize != other.m_maxSize) {
        delete[] m_data;
        m_maxSize = other.m_maxSize;
        m_data = new ItemType[m_maxSize];
    }

    for (int i = 0; i < m_size; i++)
        m_data[i] = other.m_data[i];

    return *this;
}
