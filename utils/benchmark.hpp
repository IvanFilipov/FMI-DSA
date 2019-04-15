/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   benchmarking.hpp
 * @author Ivan Filipov
 * @brief  A basic benchmarking generic function, 
 *         for the students to test their own algorithms.
 * @date   10.2018
 */

#pragma once

#include <chrono>
#include <iostream>
#include <iomanip>
#include <string>

/// marco to create a string
#define fnc_name_to_str(f) #f

namespace dsa {
/// time formatting argument
enum class T_FORMAT {
	F_MICRO, //!< format the time in microseconds => 1000 microseconds = 1 millisecond 
	F_MILLI, //!< format the time in milliseconds => 1000 milliseconds = 1 second 
	F_SEC,   //!< format the time in seconds      => 60 seconds = 1 minute
	F_MIN,   //!< format the time in minutes
	F_ALL    //!< format the time as: m-s-ms-us
};

// Functor could be :
// - ordinary function
// - an object from class which implements operator()
// - a lambda function ( we will talk about them throughout the semester ) 

template<typename Functor>
/**
 * @brief a function which receives Functor as a parameter
 *         runs it and outputs the formatted time that running took
 * @tparam Functor -> function like object
 * @param[in] format: time formatting, @see T_FORMAT
 * @param[in] name: name of the tested function, to be printed into the output
 * @param[in] os: output stream, in which to write
 */
void benchmark_test_fnc(Functor f, T_FORMAT format = T_FORMAT::F_MICRO, 
						const std::string& name = "", std::ostream& os = std::cout) {
// using some dark c++ 11 magic to calculate the time 
// needed from the function in microseconds
// 1 second = 1000* 1 millisecond = 1000 * 1000 * 1 microsecond 
// the running time may vary to your machine's current available resources	
	using namespace std::chrono;
	
	// starting time
	steady_clock::time_point begin = steady_clock::now();
	//
	
	// run the function
	f();
	//
	
	//end time
	steady_clock::time_point end = steady_clock::now();
	//
	
	// output human readable results
	if (!name.empty()) os << '[' << name << "] ";
	os << "running took : ";
	
	switch (format) {
	case T_FORMAT::F_MICRO:
		os  <<  duration_cast<microseconds>(end - begin).count()
			<< " microseconds" << std::endl;
		break;
		
	case T_FORMAT::F_MILLI: 	
		os  <<  duration_cast<milliseconds>(end - begin).count()
			<< " milliseconds" << std::endl;
		break;
	
	case T_FORMAT::F_SEC: 	
		os  <<  duration_cast<seconds>(end - begin).count()
			<< " seconds" << std::endl;
		break;
		
	case T_FORMAT::F_MIN: 	
		os  <<  duration_cast<minutes>(end - begin).count()
			<< " minutes" << std::endl;
		break;
		
	case T_FORMAT::F_ALL:
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
	//
}
} // namespace dsa
