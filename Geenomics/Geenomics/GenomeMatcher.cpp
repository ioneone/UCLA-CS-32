#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include "Trie.h"
using namespace std;

class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
    struct GenomePointer {
        int index;
        int position;
    };
    
    bool findGenomeWithThisDNACandidates(const string& fragment, int minimumLength, bool exactMatchOnly, vector<GenomePointer>& values, vector<DNAMatch>& candidates) const;
    
    void findBestCandidates(vector<DNAMatch>& candidates, vector<DNAMatch>& matches) const;
    
    int m_minSearchLength;
    vector<Genome> m_genomes;
    
    Trie<GenomePointer> m_genomeTrie;
};

bool compareGenomeMatch(const GenomeMatch& match1, const GenomeMatch& match2) {
    if (match1.percentMatch == match2.percentMatch) return match1.genomeName < match2.genomeName;
    return match1.percentMatch > match2.percentMatch;
}

bool compareDNAMatch(const DNAMatch& match1, const DNAMatch& match2) {
    if (match1.length == match2.length) return match1.genomeName < match2.genomeName;
    return match1.length > match2.length;
}

/*
 * Time Complexity : O(1)
 */
GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    m_minSearchLength = minSearchLength;
}

/*
 * L               : GenomeMatcher's minSearchLength
 * N               : length of the added Genome's DNA sequence
 * Time Complexity : O(L*N)
 */
void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    m_genomes.push_back(genome);
    
    for (int i = 0; i < genome.length() - m_minSearchLength; i++) {
        string fragment, value;
        genome.extract(i, m_minSearchLength, fragment);

        GenomePointer pointer;
        pointer.index = (int) m_genomes.size() - 1;
        pointer.position = i;
        m_genomeTrie.insert(fragment, pointer);
        
        
    }
    
}

/*
 * Time Complexity : O(1)
 */
int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_minSearchLength;
}

/*
 * F               : length of fragment
 * H               : number of distinct hits across all genomes where the prefix of length minSearchLength of fragment was found
 * Time Complexity : O(H*F)
 */
bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    if (fragment.length() < minimumLength) return false;
    
    if (minimumLength < m_minSearchLength) return false;
    
    vector<GenomePointer> values = m_genomeTrie.find(fragment.substr(0, m_minSearchLength), exactMatchOnly);
    
    vector<DNAMatch> candidates;
    if (!findGenomeWithThisDNACandidates(fragment, minimumLength, exactMatchOnly, values, candidates)) return false;
    
    findBestCandidates(candidates, matches);
    
    return true;
}

bool GenomeMatcherImpl::findGenomeWithThisDNACandidates(const string& fragment, int minimumLength, bool exactMatchOnly, vector<GenomePointer>& values, vector<DNAMatch>& candidates) const {
    
    candidates.clear();
    
    for (GenomePointer value : values) {
        
        int index = value.index;
        int position = value.position;
        
        int length = m_minSearchLength;
        int positionPtr = position + m_minSearchLength;
        
        string searchString;
        m_genomes[index].extract(position, m_minSearchLength, searchString);
        bool isMismatchAllowed = !exactMatchOnly && searchString == fragment.substr(0, m_minSearchLength);
        
        for (int i = m_minSearchLength; i < fragment.length(); i++) {
            string temp;
            
            // reaches the end of Genome sequence
            if (!m_genomes[index].extract(positionPtr++, 1, temp)) break;
            
            if (fragment[i] == temp[0]) {
                length++;
            } else {
                if (isMismatchAllowed) {
                    length++;
                    isMismatchAllowed = false;
                } else {
                    break;
                }
            }
        }
        
        DNAMatch candidate;
        candidate.genomeName = m_genomes[index].name();
        candidate.position = position;
        candidate.length = length;
        
        if (length < minimumLength) continue;
        
        candidates.push_back(candidate);
        
    }
    
    return !candidates.empty();
}

void GenomeMatcherImpl::findBestCandidates(vector<DNAMatch>& candidates, vector<DNAMatch>& matches) const {
    
    unordered_map<string, DNAMatch> map;
    for (int i = 0; i < candidates.size(); i++) {
        auto it = map.find(candidates[i].genomeName);
        if (it == map.end()) {
            map[candidates[i].genomeName] = candidates[i];
        } else {
            if (it->second.length < candidates[i].length) {
                it->second = candidates[i];
                continue;
            }
            
            if (it->second.length == candidates[i].length && it->second.position > candidates[i].position) {
                it->second = candidates[i];
                continue;
            }
        }
    }
    
    matches.clear();
    for (auto it = map.begin(); it != map.end(); it++) {
        matches.push_back(it->second);
    }
    
    sort(matches.begin(), matches.end(), compareDNAMatch);
}

/*
 * Q               : length in DNA bases of the query sequence
 * X               : function in the big-O of your findGenomesWithThisDNA() method
 * Time Complexity : O(Q*X)
 */
bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    
    int S = query.length() / fragmentMatchLength;
    unordered_map<string, int> count;
    for (int i = 0; i < S; i++) {
        string fragment;
        query.extract(i * fragmentMatchLength, fragmentMatchLength, fragment);
        vector<DNAMatch> matches;
        findGenomesWithThisDNA(fragment, fragmentMatchLength, exactMatchOnly, matches);
        for (DNAMatch match : matches) {
            auto it = count.find(match.genomeName);
            if (it == count.end()) {
                count[match.genomeName] = 1;
            } else {
                it->second++;
            }
        }
    }
    
    bool isCloseMatchFound = false;
    results.clear();
    
    for (auto it = count.begin(); it != count.end(); it++) {
        
        double percent = 100 * it->second / (double) S;
        
        if (percent < matchPercentThreshold) continue;
        
        isCloseMatchFound = true;
        GenomeMatch match;
        match.genomeName = it->first;
        match.percentMatch = percent;
        results.push_back(match);
        
    }
    sort(results.begin(), results.end(), compareGenomeMatch);
    
    return isCloseMatchFound;
    
}

//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
