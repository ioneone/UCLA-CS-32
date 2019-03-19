//
//  main.cpp
//  Homework 4
//
//  Created by Junhong Wang on 3/1/19.
//  Copyright © 2019 ioneone. All rights reserved.
//

#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

void test()
{
    Set<int> si;
    Set<string> ss;
    assert(si.empty());
    assert(ss.empty());
    assert(si.size() == 0);
    assert(ss.size() == 0);
    assert(si.insert(10));
    assert(ss.insert("hello"));
    assert(si.contains(10));
    assert(ss.contains("hello"));
    int i;
    assert(si.get(0, i)  &&  i == 10);
    string s;
    assert(ss.get(0, s)  &&  s == "hello");
    assert(si.erase(10));
    assert(ss.erase("hello"));
    Set<int> si2(si);
    Set<string> ss2(ss);
    si.swap(si2);
    ss.swap(ss2);
    si = si2;
    ss = ss2;
    unite(si,si2,si);
    unite(ss,ss2,ss);
    subtract(si,si2,si);
    subtract(ss,ss2,ss);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}


#include "Set.h"  // class template from problem 1
using namespace std;

class Coord
{
public:
    Coord(int r, int c) : m_r(r), m_c(c) {}
    Coord() : m_r(0), m_c(0) {}
    double r() const { return m_r; }
    double c() const { return m_c; }
private:
    double m_r;
    double m_c;
};

bool operator<(Coord const &c1, Coord const &c2) {
    return c1.r() < c2.r();
}

bool operator==(Coord const &c1, Coord const &c2) {
    return c1.r() == c2.r();
}

//int main()
//{
//    Set<int> si;
//    si.insert(7);               // OK
//    Set<string> ss;
//    ss.insert("7-Up");         // OK
//    Set<Coord> sc;
//    sc.insert(Coord(7, -7));    // error!
//}


/*
 Explain in a sentence or two why the call to Set<Coord>::insert causes at least one compilation
 error. (Notice that the calls to Set<int>::insert and Set<string>::insert are fine.) Don't just
 transcribe a compiler error message; your answer must indicate you understand the ultimate root cause
 of the problem and why that is connected to the call to Set<Coord>::insert.
 
 Because Set<Coord>::insert internally comparing the Items and inserting the new Item
 at appropriate position. C++ already knows how to compare built-in types like int and double,
 but it doesn't know how to compare a user defined class Coord. In order to fix the error,
 we must tell C++ how to compare Coord object by defining operator < and operator == functions
 for Coord class.
 
 */


/*
 const int N = some value;
 bool hasCommunicatedWith[N][N];
 ...
 int numIntermediaries[N][N];
 for (int i = 0; i < N; i++)
 {
 numIntermediaries[i][i] = -1;  // the concept of intermediary
 // makes no sense in this case
 for (int j = 0; j < N; j++)
 {
 if (i == j)
 continue;
 numIntermediaries[i][j] = 0;
 for (int k = 0; k < N; k++)
 {
 if (k == i  ||  k == j)
 continue;
 if (hasCommunicatedWith[i][k]  &&  hasCommunicatedWith[k][j])
 numIntermediaries[i][j]++;
 }
 }
 }
 
 What is the time complexity of this algorithm, in terms of the number of basic operations (e.g.,
 additions, assignments, comparisons) performed: Is it O(N), O(N log N), or what? Why? (Note: In this
 homework, whenever we ask for the time complexity, we care only about the high order term, so don't
 give us answers like O(N3+4N2).)
 
 
 O(N^3)
 
 Since we only care about the high order term, and we ignore the scaler, we can just consider the
 worst case. The i will loop at most N times. Similarly, j and k will loop at most N times.
 Therefore, N * N * N = O(N^3).
 
 
 const int N = some value;
 bool hasCommunicatedWith[N][N];
 ...
 int numIntermediaries[N][N];
 for (int i = 0; i < N; i++)
 {
 numIntermediaries[i][i] = -1;  // the concept of intermediary
 // makes no sense in this case
 for (int j = 0; j < i; j++)  // loop limit is now i, not N
 {
 numIntermediaries[i][j] = 0;
 for (int k = 0; k < N; k++)
 {
 if (k == i  ||  k == j)
 continue;
 if (hasCommunicatedWith[i][k]  &&  hasCommunicatedWith[k][j])
 numIntermediaries[i][j]++;
 }
 numIntermediaries[j][i] = numIntermediaries[i][j];
 }
 }

 Still O(N^3)
 
 Here again, we only consider the worse case. The i will loop at most N times. The j will
 loop at most N times. (Although technically j will loop 1 + 2 + ... + N times, but we will
 only think of the worst case.) The k will loop at most N times. Therefore,
 N * N * N = N^3
 */


/*
 void unite(const Set& set1, const Set& set2, Set& result)
 {
 const Set* sp = &set2;
 if (&result == &set1)
 {
 if (&result == &set2)
 return;
 }
 else if (&result == &set2)
 sp = &set1;
 else
 {
 result = set1;
 if (&set1 == &set2)
 return;
 }
 for (int k = 0; k < sp->size(); k++)
 {
 ItemType v;
 sp->get(k, v);
 result.insert(v);
 }
 }
 
 Since we only care about worst case, we can only focus on the time complexity of the for loop.
 The for loop will run N times. sp->get(k, v) is doing linear search, so it takes O(N).
 (Technically it is O(N/2) because it will find the element before reaching the middle.)
 result.insert(v) first call findFirstAtLeast() and insert v in front of it. findFirstAtLeast()
 simply loops through the entire set from beginning to the end. The worst case for
 findFistAtLeast() is N. The insertion itself just takes constant time. Therefore,
 result.insert(v) takes O(N). Therefore, the total time it takes is N * (N + N).
 Therefore, the time complexity unite() is O(N^2).
 
 
 void Set::unite(const Set& set1, const Set& set2)
 {
 vector<ItemType> v;
 
 // copy all items into v;
 for (Node* p1 = set1.m_head->m_next; p1 != set1.m_head; p1 = p1->m_next)
 v.push_back(p1->m_value);
 for (Node* p2 = set2.m_head->m_next; p2 != set2.m_head; p2 = p2->m_next)
 v.push_back(p2->m_value);
 
 // sort v using an O(N log N) algorithm
 sort(v.begin(), v.end());
 
 // delete result nodes (other than the dummy node)
 while (m_head->next != m_head)
 doErase(m_head->m_next);
 
 // copy unique items from v into result
 for (size_t k = 0; k < v.size(); k++)
 {
 if (k == 0  ||  v[k] != v[k-1])  // add non-duplicates
 insertBefore(m_head, v[k]);
 }
 
 // v is destroyed when function returns
 }

 To copy all items into v from set1, it takes O(N) to loop through all the elements in set1.
 Similarly, it takes O(N) to copy all items into v. sort() takes O(Nlog(N)). Deleting
 result nodes takes O(N) to loop through all the elements in result. Deleting takes constant time.
 Copying unique items from v into result takes O(N). (Technically it's O(2N)). insertBefore()
 takes constant time. Therefore, it takes N + N + Nlog(N) + N + N = O(Nlog(N)).
 
 O(Nlog(N))
 
 
 
 void Set::unite(const Set& set1, const Set& set2)
 {
 const Set* sp = &set2;
 if (this == &set1)
 {
 if (this == &set2)
 return;
 }
 else if (this == &set2)
 sp = &set1;
 else
 {
 *this = set1;
 if (&set1 == &set2)
 return;
 }
 Node* p1 = m_head->m_next;
 Node* p2 = sp->m_head->m_next;
 while (p1 != m_head  &&  p2 != sp->m_head)
 {
 if (p1->m_value < p2->m_value)
 p1 = p1->m_next;
 else
 {
 if (p1->m_value > p2->m_value)
 insertBefore(p1, p2->m_value);
 else
 p1 = p1->m_next;
 p2 = p2->m_next;
 }
 }
 for ( ; p2 != sp->m_head; p2 = p2->m_next)
 insertBefore(m_head, p2->m_value);
 }
 
 While loop and for loop will loop through all the elements in set1 and set2. It takes
 N + N = O(N).
 
 O(N).
 
 
 */
