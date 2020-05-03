#pragma once

#include <iostream>
#include <map>

namespace laen {
	template <class T> class map {
	public:
		std::map<std::string, T*> thisMap;
		map() {};
		void putObject(std::string emplacement, T* ptr) {
			thisMap[emplacement] = ptr;
		}
		T* getByName(std::string emplacement) {
			return thisMap[emplacement];
		}
		int getSize() {
			return thisMap.size();
		}
		typename std::map<std::string, T*>::iterator begin() { return thisMap.begin(); }
		typename std::map<std::string, T*>::iterator end()   { return thisMap.end();   }
		~map() {
			for (typename std::map<std::string, T*>::iterator it = thisMap.begin(); it != thisMap.end(); ++it) 
			{
				delete it->second;
			}
		};
	};
}

