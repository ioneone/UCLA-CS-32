//
//  main.cpp
//  WorkSheet
//
//  Created by Junhong Wang on 2/26/19.
//  Copyright © 2019 ioneone. All rights reserved.
//

#include <iostream>
using namespace std;

//int LA_power(int a, int b) {
//    if (b == 0) return 0;
//    if (b % 2 == 0)
//        return LA_power(a+a, b/2);
//    return LA_power(a+a, b/2) + a;
//
//}
//
//int main() {
//    cout << LA_power(3, 4) << endl;
//
//}
//
//struct Node {
//    int val;
//    Node *left;
//    Node *right;
//};
//
//bool treeContains(const Node *head, int n) {
//
//    if (head == nullptr) return false;
//
//    if (head->val == n) return true;
//
//    if (treeContains(head->left, n)) return true;
//    if (treeContains(head->right, n)) return true;
//
//    return false;
//
//}
//
//
//

class LL {
    
public:
    
    
    void insert(int value) {
        m_head = insert(m_head, value);
    }
    
private:
    
    struct Node {
        int value;
        Node *left;
        Node *right;
        Node *parent;
    };
    
    
    
    Node* insert(Node* node, int value) {
        
        if (node == nullptr) {
            Node *newNode = new Node();
            newNode->value = value;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->parent = nullptr;
            return newNode;
        }
        
        if (value < node->value) {
            
            node->right = insert(node->right, value);
            node->right->parent = node;
            
        } else if (node->value < value) {
            
            node->left = insert(node->left, value);
            node->left->parent = node;
            
        }
        
        return node;
        
    }
    
    Node *m_head = nullptr;
};


int main() {
    LL ll;
    
    ll.insert(30);
    ll.insert(20);
    ll.insert(40);
    ll.insert(70);
    ll.insert(60);
    ll.insert(80);
    
    return 0;
}
