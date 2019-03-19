#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>

template<typename ValueType>
class Trie
{
public:
    Trie();
    ~Trie();
    void reset();
    void insert(const std::string& key, const ValueType& value);
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;
    
    // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
private:
    
    struct Node {
        std::vector<ValueType> values;
        std::vector<char> labels;
        std::vector<Node*> children;
    };
    
    int index(const std::vector<char>& vec, const char value) const;
    void clearHelper(Node* node);
    void clear();
    std::vector<ValueType> findHelper(Node* node, const std::string& key, bool exactMatchOnly) const;
    
    Node *m_head;
};

/*
 * Time Complexity: O(1)
 */
template<typename ValueType>
Trie<ValueType>::Trie() {
    m_head = new Node();
}

/*
 * Time Complexity: O(N)
 */
template<typename ValueType>
Trie<ValueType>::~Trie() {
    clear();
}

/*
 * Time Complexity: O(N)
 */
template<typename ValueType>
void Trie<ValueType>::reset() {
    clear();
    m_head = new Node();
}

/*
 * L               : Length of inserted key
 * C               : Average number of children per node
 * Time Complexity : O(LC)
 */
template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value) {
    
    Node *node = m_head;
    
    for (char c : key) {
        
        int i = index(node->labels, c);
        
        if (i == -1) {
            node->labels.push_back(c);
            Node *newNode = new Node();
            node->children.push_back(newNode);
            node = newNode;
        } else {
            node = node->children[i];
        }
        
    }
    //std::cout << value << std::endl;
    node->values.push_back(value);
    
}

template<typename ValueType>
void Trie<ValueType>::clear() {
    clearHelper(m_head);
}

template<typename ValueType>
void Trie<ValueType>::clearHelper(Node* node) {
    
    if (node == nullptr) return;
    
    node->values.clear();
    node->labels.clear();
    
    for (Node *n : node->children) {
        clearHelper(n);
    }
    
    node->children.clear();
    
    delete node;
}

template<typename ValueType>
int Trie<ValueType>::index(const std::vector<char>& vec, const char value) const {
    
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == value) return i;
    }
    
    return -1;
}

/*
 * L               : Length of inserted key
 * C               : Average number of children per node
 * V               : Size of the returned vector.
 * Time Complexity : O(LC) if exactMatchOnly is True
 *                   O(L^2C^2 + V) if exactMatchOnly is False
 */
template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const {
    
    if (key.empty()) return std::vector<ValueType>();
    
    // first letter must match
    int i = index(m_head->labels, key[0]);
    if (i == -1) return std::vector<ValueType>();
        
    return findHelper(m_head->children[i], key.substr(1), exactMatchOnly);
    
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::findHelper(Node* node, const std::string& key, bool exactMatchOnly) const {
    
    if (node == nullptr) return std::vector<ValueType>();
    
    if (key.empty()) return node->values;
    
    int i = index(node->labels, key[0]);
    
    if (exactMatchOnly) return (i == -1) ? std::vector<ValueType>() : findHelper(node->children[i], key.substr(1), true);
    
    std::vector<ValueType> vec;
    for (int j = 0; j < node->children.size(); j++) {
        std::vector<ValueType> v = findHelper(node->children[j], key.substr(1), i != j);
        vec.insert(vec.end(), v.begin(), v.end());
    }
    
    return vec;
}

#endif // TRIE_INCLUDED
