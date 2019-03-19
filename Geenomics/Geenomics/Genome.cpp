#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <algorithm>
#include "Trie.h"
using namespace std;

class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    static bool isNameLine(string& s);
    static bool isOnlyContainBases(string& s);
    string m_name;
    string m_sequence;
};

/*
 * S               : length of sequence
 * Time Complexity : O(S)
 */
GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
    m_name = nm;
    m_sequence = sequence;
}

/*
 * N               : number of characters in the loaded genome file
 * Time Complexity : O(N)
 */
bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes) 
{
    string s;
    string sequence = "";
    string name = "";
    
    while (getline(genomeSource, s)) {
        
        if (isNameLine(s)) {
            
            if (sequence != "") genomes.push_back(Genome(name, sequence));
            
            // a line starting with a greater-than character but containing no other characters.
            if (s.substr(1) == "") return false;
            
            name = s.substr(1);
            sequence = "";
            
        } else {
            
            // not starting with a name line
            if (name == "") return false;
            
            transform(s.begin(), s.end(), s.begin(), ::toupper);
            
            // non-name lines containing any characters other than upper or lower case A C T G N
            if (!isOnlyContainBases(s)) return false;
            
            // empty line
            if (s == "") return false;
            
            sequence += s;
        }
    }
    
    // empty lines, no base lines after a name line
    if (name == "" || sequence == "") return false;
    
    genomes.push_back(Genome(name, sequence));
    
    return true;
}

bool GenomeImpl::isNameLine(string& s) {
    if (s.empty()) return false;
    return s[0] == '>';
}

bool GenomeImpl::isOnlyContainBases(string& s) {
    char bases[] = { 'A', 'C', 'T', 'G', 'N' };
    for (char c : s) {
        bool isFound = false;
        for (char base : bases) {
            if (c == base) {
                isFound = true;
                break;
            }
        }
        if (!isFound) return false;
    }
    
    return true;
}

/*
 * Time Complexity : O(1)
 */
int GenomeImpl::length() const
{
    return (int) m_sequence.length();
}

string GenomeImpl::name() const
{
    return m_name;
}

/*
 * S               : length of the extracted sequence
 * Time Complexity : O(S)
 */
bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    if (position < 0 || m_sequence.length() < position) return false;
    if (length < 0) return false;
    if (m_sequence.length() < position + length) return false;
    
    fragment = m_sequence.substr(position, length);
    
    return true;
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes) 
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}
