/*
 * Example usage of our custom dsa::hash_map.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream> // std::cout
#include <string>   // std::string
#include <cstdlib>  // std::srand(), rand()
#include <ctime>    // std::time()
#include "hash_map.hpp" // dsa::hash_map

void run_basic_tests() {
	
	std::cout << "#### running basic tests ####\n";
	
	dsa::hash_map<int, std::string> s_map;
	// inserting some students
	s_map[46489] = "Sashko";
	s_map[12345] = "Hacker";
	s_map[46123] = "Clang_master";
	s_map[41234] = "Sbndio";
	s_map[46289] = "Misho";
	s_map[46255] = "Dakomir";
	s_map[47123] = "Kriskchakis";
	s_map[48234] = "Sandio";
	// output the map
	using student_info = std::pair<int, std::string>;
	std::cout << "\ncurrent contain:\n\n";
	std::vector<student_info> vec = s_map.to_vector();
	for (const student_info& s : vec) {
		std::cout << "{ key: " << s.first << ", value: "
				  << s.second << " }" << std::endl;
	}
	
	std::cout << "\nchanging data for key 12345:" << std::endl;;
	s_map[12345] = "Semeshko";
	std::cout << "new data: " << s_map[12345];
	std::cout << std::endl;
		
	try {
		std::cout << "\nsearching for 46230" << std::endl;
		std::string res = s_map.find(46230);
		std::cout << "found: " << res << std::endl;
	} catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	
	try {
		std::cout << "\nsearching for 46255" << std::endl;
		std::string res = s_map.find(46255);
		std::cout << "found: " << res << std::endl;
		std::cout << "removing him...";
		s_map.erase(46255);
		std::cout << "done!" << std::endl;
	} catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	
	try {
		std::cout << "\ntrying to remove 51230..." << std::endl;
		s_map.erase(51230);
		std::cout << "done!" << std::endl;
	} catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	
	try {
		std::cout << "\ntrying to insert { 47123, Java Lover }..." << std::endl;
		s_map.insert(std::make_pair(47123, "Java Lover"));
		std::cout << "done!" << std::endl;
	} catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "Sorry, Java Lover, there is no room for you here!" << std::endl;
	}
		
	std::cout << "\ncurrent contain:\n\n";
	std::vector<student_info> vec_new = s_map.to_vector();
	for (const student_info& s : vec_new) {
		std::cout << "{ key: " << s.first << ", value: "
				  << s.second << " }" << std::endl;
	}
}

void run_advanced_tests() {
	
	std::cout << "\n\n#### running advanced tests ####\n";
	
	dsa::hash_map<int, int> s_map;
	
	std::cout << "current chains count: " 
			  << s_map.chain_count()
			  << std::endl
			  << "maximum length of each chain: "
			  << s_map.chain_max_size()
			  << std::endl;
	
	std::cout << "\n...let's check Dirichlet's principle...\n";
	size_t max_elems_count = s_map.chain_count() * s_map.chain_max_size() + 200;
	
	std::cout << "going to insert "
			  << max_elems_count
			  << " random {key, data} elements into the map"
			  << std::endl
			  << "with total capacity: " << max_elems_count - 200
			  << std::endl;
	
	std::srand(std::time(nullptr));
	size_t cnt = 0;
	for (size_t i = 0; i < max_elems_count; i++)
		try {
			s_map.insert(std::make_pair(std::rand() % 100000, std::rand()));
			++cnt;
		} catch(...) {}
	
	std::cout << "\ntotal inserted: " << cnt << std::endl;
	size_t new_cap = s_map.chain_count() * s_map.chain_max_size();
	if (max_elems_count - 200 < new_cap) {
		std::cout << "\ndefinitely resized!" 
				  << std::endl
				  << "new capacity: " 
				  << new_cap
				  << std::endl;
	} else {
		std::cout << "no resize?!?!?!" << std::endl;
	}
}

int main() {
	
	/* test basic functionality */
	run_basic_tests();
	/* test advanced functionality (rehashing) */
	run_advanced_tests();
	
	return 0;
}
