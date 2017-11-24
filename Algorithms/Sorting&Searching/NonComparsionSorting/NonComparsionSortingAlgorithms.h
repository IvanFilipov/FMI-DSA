#pragma once

#include<string> //std::string
#include<vector> //std::vector
#include<queue>

///Counting sort
///good sides : O(n)
///bad sides : O((maxElem - minElem)) additional memory

//unsigned chars have values in [0 , 255]  
int const MAX_VAL = 255;
void countingSort(unsigned char* arr, int size) {

	//here we will count each number's frequency
	int freq[MAX_VAL + 1] = { 0 , };

	//counting step
	for (int i = 0; i < size; i++)
		freq[arr[i]]++;

	//pushing numbers back into the input array
	int j = 0;
	for (unsigned char i = 0; i < MAX_VAL; i++)
		while (freq[i]--)
			arr[j++] = i;


}


//alphabet + '\0' 
int const alphaCount = 27;

//building kind of radix tree...
//to sort the names

//going from the most significant 'digit'/char in our case/ (MSD)
//because we have a lexicographic sort
//args : the vector of names, low border, up border,current position in the strings 
void MSD_RadixSort(std::vector<std::string>& names, int low, int high, int pos){

	if (high <= low)
		return;

	//a queue for each letter and '\0' symbol
	std::queue <std::string> buckets[alphaCount];


	int bucketIndex;
	for (int j = low; j < high; ++j) {

		//index of the queue where we should add the current name
		bucketIndex = names[j][pos] ? names[j][pos] - 'a' + 1 : 0;
		buckets[bucketIndex].push(names[j]);
	}

	int start = low;
	int finish = low;

	for (int j = 0; j < alphaCount; ++j) {

		//making a new array of names from each queue
		while (!buckets[j].empty()) {

			names[finish++] = buckets[j].front();
			buckets[j].pop();
		}

		//sorting the new array
		if (finish > low + 1)
			MSD_RadixSort(names, start, finish, pos + 1);

		start = finish;
	}

}
