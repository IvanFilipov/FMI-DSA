/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   student.h
 * @author Ivan Filipov
 * @date   10.2018
 */

#pragma once

#include <string>    // std::string
#include <iostream>  // std::ostream

namespace dsa {
/**
 * @struct student
 * @brief  A utility class representing a student - name and faculty number. 
 *		   Used in some examples as test class.	
 */
struct student {
	std::string name;
	int         fn;
	
	student(const std::string& n, int fnum) :
		name(n), fn(fnum) {} 
	
	student()                          = default;
	student(const student&)            = default;
	student& operator=(const student&) = default;
	~student()                         = default;
	
	bool operator<(const student& rhs) const {

		return name < rhs.name;
	}
	bool operator>(const student& rhs) const {
		
		return name > rhs.name;
	}
	bool operator>=(const student& rhs) const {
		
		return name >= rhs.name;
	}
	bool operator==(const student& rhs) const {
		
		return (name == rhs.name) && (fn == rhs.fn);
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
