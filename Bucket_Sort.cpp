// Project5.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>
using namespace std;

class bucketsortarray{
public:
	int *bucket_array;
	int minData;
	int maxData;
	int bucketsize;
	int offset;
	bucketsortarray(const char* input_filename,const char* output_filename,const char* debug_filename){
		findMinMax(input_filename);
		bucket_array = new int[bucketsize]();
		buildarray(input_filename, debug_filename);
		printBucketAry(debug_filename);
		printSortedData(output_filename);
	}

	
	void findMinMax(const char* input_filename) {
		int ints_of_input;
		ifstream input_file(input_filename);
        input_file >> maxData >> minData;
		while (input_file >> ints_of_input) {
			if (ints_of_input < minData) {
				minData = ints_of_input;
			}
			else if (ints_of_input >  maxData) {
					  maxData = ints_of_input;
			}
		}
		bucketsize = maxData - minData + 1;
		offset = minData;
		input_file.close();
	}
	
	void buildarray(const char* input_filename,const char* debug_filename) {
		ifstream input_file(input_filename);
		ofstream debug_file(debug_filename);
		int ints_of_inputs;
		while (input_file >> ints_of_inputs) {
			int index = getIndex(ints_of_inputs);
			bucket_array[index]++;
			debug_file << ints_of_inputs << " " << index << endl;
		}
		input_file.close();


	}
	
	int getIndex(int data) {
		int index = data - offset;
		return index;
	}
	
	void printSortedData(const char* output_filename) {
		ofstream output_file(output_filename);
		for (int index = 0; index < bucketsize;index++) {
			while (bucket_array[index] != 0) {
				stringstream file_output;
				file_output << index + offset;
				output_file << file_output.str() << endl;
				bucket_array[index]--;
			}
			
		}
		output_file.close();
	}

	void printBucketAry(const char* debug_filename) {
		ofstream debug_file;
		debug_file.open(debug_filename, fstream::app);
		for (int index = 0; index <= 18; index++) {
			stringstream output_index;
			output_index << index;
			debug_file << output_index.str() << "\t";
		}
		debug_file << endl;
		for (int index = 0; index <= 18; index++) {
			stringstream bucket_index;
			bucket_index << bucket_array[index];
			debug_file << bucket_index.str() << "\t";
		}
		debug_file << endl;
		debug_file.close();
	}
		
	
};

int main(int argc, char* argv[])
{
	char* inputfilename = argv[1];
	char* outputfilename = argv[2];
	char* debugfilename = argv[3];
	bucketsortarray bucket(inputfilename,outputfilename,debugfilename);
	return 0;
}

