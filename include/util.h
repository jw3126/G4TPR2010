//
// Created by jan on 12.04.17.
//

#ifndef G4TPR2010_UTIL_H
#define G4TPR2010_UTIL_H

#include <vector>
#include <map>

using namespace std;

template<typename K, typename V>
inline G4bool HasKey(map<K, V> ma, K k)
{
    return ma.count(k) > 0;
}

template<typename T>
inline G4bool HasElement(vector<T> v, T x) {
    return ( find(v.begin(), v.end(), x) != v.end());
}



#endif //G4TPR2010_UTIL_H