/*
 * A utility class representing a student. Used in some sorting examples.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#pragma once

#include <string>
#include <iostream>

namespace dsa {
struct student {
	
	std::string name;
	int         fn;
	
	student(const std::string& n, int fnum) :
		name(n), fn(fnum) {} 
	
	bool operator<(const student& rhs) {

		return name < rhs.name;
	}
	bool operator>(const student& rhs) {
		
		return name > rhs.name;
	}
	bool operator>=(const student& rhs) {
		
		return name >= rhs.name;
	}
};
}
// can lead to linkage errors if included in more than one cpp
static // means keep copy of this function in each cpp
std::ostream& operator<<(std::ostream& os, const dsa::student& st) {
	
	return os << std::endl
			  << "name : " << st.name 
			  << " fn : "  << st.fn;
 }
