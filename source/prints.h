
#ifndef __PRINTS__
#define __PRINTS__

#include "Node.h"
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <map>

template <typename T>
inline std::ostream& operator<<(std::ostream& out, std::vector<T> v){
   out << "[";
   if(v.size() > 0){
      for(unsigned int i = 0; i < v.size()-1; ++i){
         out << v[i] << ", ";
      }
      out << v[v.size()-1];
   }
   return out << "]";
}

template <typename T>
inline std::ostream& ArrayToStream(std::ostream& out, T* v, unsigned int size){
   out << "[";
   if(size > 0){
      for(unsigned int i = 0; i < size-1; ++i){
         out << v[i] << ", ";
      }
      out << v[size-1];
   }
   return out << "]";
}

template <typename T1, typename T2>
inline std::ostream& operator<<(std::ostream& out, const std::unordered_map<T1, T2>& umap){
   std::map<T1, T2> ordered(umap.begin(), umap.end());
   out << "{";
   char comma[3] = {'\0', ' ', '\0'};
   for(auto& x: ordered){
      out << comma;
      out << "{" << x.first << " : " << x.second << "}";
      comma[0] = ',';
   }
   return out << "}";
}

#endif
