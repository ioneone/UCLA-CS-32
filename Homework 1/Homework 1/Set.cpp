////
////  Set.cpp
////  Homework 1
////
////  Created by Junhong Wang on 1/15/19.
////  Copyright © 2019 ioneone. All rights reserved.
////
//
//#include <iostream>
//#include "Set.h"
//
//
//Set::Set() {
//    m_size = 0;
//}
//
//bool Set::empty() const {
//    return m_size == 0;
//}
//
//int Set::size() const {
//    return m_size;
//}
//
//bool Set::insert(const ItemType& value) {
//    // do nothing if the value is already in the Set or the set exceeds maximum capacity
//    if (contains(value) || m_size == DEFAULT_MAX_ITEMS) return false;
//
//    m_data[m_size++] = value;
//    return true;
//}
//
//bool Set::erase(const ItemType& value) {
//    for (int i = 0; i < m_size; i++) {
//
//        // target found
//        if (m_data[i] == value) {
//
//            // delete the target and shift the positions of data afterwards
//            for (int j = i; j < m_size - 1; j++)
//                m_data[j] = m_data[j + 1];
//
//            m_size--;
//
//            // successfully deleted value from the Set
//            return true;
//
//        }
//    }
//
//    // value not found in the Set
//    return false;
//}
//
//bool Set::contains(const ItemType& value) const {
//    for (int i = 0; i < m_size; i++)
//        if (m_data[i] == value) return true;
//
//    return false;
//}
//
//bool Set::get(int i, ItemType& value) const {
//    if (i < 0 || i >= m_size) return false;
//
//    for (int j = 0; j < m_size; j++) {
//        int counter = 0;
//        for (int k = 0; k < m_size; k++) {
//            if (j == k) continue;
//            if (m_data[j] > m_data[k]) {
//                counter++;
//            }
//        }
//
//        if (counter == i) {
//            value = m_data[j];
//            return true;
//        }
//
//    }
//
//    return false;
//}
//
//void Set::swap(Set& other) {
//
//    int tmpSize = m_size;
//    Set *smallerSet;
//    Set *biggerSet;
//    smallerSet = (m_size < other.m_size) ? this : &other;
//    biggerSet = (m_size <= other.m_size) ?  &other: this;
//
//    // swap data until smaller set reaches the end
//    for (int i = 0; i < smallerSet->m_size; i++) {
//        ItemType tmpData = m_data[i];
//        m_data[i] = other.m_data[i];
//        other.m_data[i] = tmpData;
//    }
//
//    // move left over data in the bigger set to the smaller set
//    for (int i = smallerSet->m_size; i < biggerSet->m_size; i++)
//        smallerSet->m_data[i] = biggerSet->m_data[i];
//
//    // swap the size
//    m_size = other.m_size;
//    other.m_size = tmpSize;
//
//}
