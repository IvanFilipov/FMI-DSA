/*
 * A basic benchmarking generic function, for the students to test their own algorithms.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#pragma once

#include <chrono>
#include <iostream>
#include <iomanip>
#include <string>

//marco to create a string
#define fnc_name_to_str(f) #f
namespace dsa {
//format argument
enum class T_FORMAT {
	
	F_MICRO, // 1000 microseconds = 1 millisecond 
	F_MILLI, // 1000 milliseconds = 1 second 
	F_SEC,   // 60 seconds = 1 minute
	F_MIN,
	F_ALL // formated output : m-s-ms-us
};

//a function which receives Functor as a parameter
//runs it and outputs the formatted time that running took

//Functor could be :
// - ordinary function
// - an object from class which implements operator()
// - a lambda function ( we will talk about them throughout the semester ) 


template<typename Functor>
void benchmark_test_fnc(Functor f, T_FORMAT format = T_FORMAT::F_MICRO, 
						const std::string& name = "", std::ostream& os = std::cout) {

//using some dark c++ 11 magic to calculate the time 
//needed from the function in microseconds
//1 second = 1000* 1 millisecond = 1000 * 1000 * 1 microsecond 
//the running time may vary to your machine's current available resources
	
	using namespace std::chrono;
	
	//starting time
	steady_clock::time_point begin = steady_clock::now();

	//run the function
	f();
	
	//end time
	steady_clock::time_point end = steady_clock::now();
	
	//output human readable results
	if (!name.empty()) os << '[' << name << "] ";
	
	os << "running took : ";
	
	switch (format) {
		
	case T_FORMAT::F_MICRO :
	
		os  <<  duration_cast<microseconds>(end - begin).count()
			<< " microseconds" << std::endl;
		break;
		
	case T_FORMAT::F_MILLI : 	
		
		os  <<  duration_cast<milliseconds>(end - begin).count()
			<< " milliseconds" << std::endl;
		break;
	
	case T_FORMAT::F_SEC : 	
		
		os  <<  duration_cast<seconds>(end - begin).count()
			<< " seconds" << std::endl;
		break;
		
	case T_FORMAT::F_MIN : 	
		
		os  <<  duration_cast<minutes>(end - begin).count()
			<< " minutes" << std::endl;
		break;
	
	case T_FORMAT::F_ALL :
		
		microseconds dur = duration_cast<microseconds>(end - begin);
		
		minutes mm = duration_cast<minutes>(dur % hours(1));
		seconds ss = duration_cast<seconds>(dur % minutes(1));
		milliseconds ms = duration_cast<milliseconds>(dur % seconds(1));
		microseconds us = duration_cast<microseconds>(dur % milliseconds(1));
		
		os  << std::setfill('0')
			<< std::setw(2) << mm.count() << "::"
			<< std::setw(2) << ss.count() << "::"
			<< std::setw(3) << ms.count() << "::"
			<< std::setw(3) << us.count() << std::endl; 
	}
}
} // namespace dsa
