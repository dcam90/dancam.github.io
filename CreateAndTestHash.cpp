/******************************************************************************
Title       : CreateAndTestHash.cpp
Author      : Dan Cambitsis
Created on  : 3/31/2016
Description : Test function for hash implementations.
******************************************************************************/

#include "QuadraticProbing.h"
#include "LinearProbing.h"
#include "DoubleHashProbing.h"
#include "SeparateChaining.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;



template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename);

// Sample main for program CreateAndTestHash
int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }
  
  const string words_filename(argv[1]);
  const string query_filename(argv[2]);
  const string param_flag(argv[3]);
  cout << "Input words file is " << words_filename << ", and query file is " << query_filename << endl;
  if (param_flag == "linear") {
    cout << "I will run the linear hashing code " << endl;
    LinearHashTable<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);  
  } else if (param_flag == "quadratic") {
    cout << "I will run the quadratic hashing code " << endl;
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);    
  } else if (param_flag == "double") {
    cout << "I will run the double hashing code " << endl;
    DoubleHashTable<string> double_hashing_probing_table;
    TestFunctionForHashTable(double_hashing_probing_table, words_filename, query_filename);
  } else if (param_flag == "chaining") {
    cout << "I will run the seperate chaining hashing code " << endl;
    ChainHashTable<string> separate_chain_hashing_table;
    TestFunctionForHashTable(separate_chain_hashing_table, words_filename, query_filename);
  } else {
    cout << "Unknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}

template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  hash_table.MakeEmpty();  

  string line1;
  ifstream myFile1(words_filename);

  if (!myFile1){
    cout << "The file could not be opened, terminating program." << endl;
    exit(1); //if the file could not be found, prompt and terminate
  }
  
  while (getline(myFile1, line1)) {
    hash_table.Insert(line1); //insert each line into the hash
  }

  cout << endl;
  cout << "------- STATS -------" << endl;
  cout << "Elements in table: " << hash_table.ReturnElementCount() << endl;
  cout << "Size of table: " << hash_table.ReturnTableSize() << endl;
  cout << "Load factor: " << static_cast<double>(hash_table.ReturnElementCount()) / hash_table.ReturnTableSize() << endl;
  cout << "Number of collisions: " << hash_table.ReturnCollisions() << endl;
  cout << "Average number of collisions: " << static_cast<double>(hash_table.ReturnCollisions()) / hash_table.ReturnElementCount() << endl;
  cout << "---------------------" << endl;
  cout << endl; //display the stats

  string line2;
  ifstream myFile2(query_filename);
  while (getline(myFile2, line2)) {
    if (hash_table.Contains(line2)) { //if the hash table contains the inquired line ...
      cout << line2 << " --> FOUND, # of probes used: " << hash_table.ReturnProbeCount() << endl;
    } //print FOUND and display the # of probes
    else {
      cout << line2 << " --> NOT FOUND, # of probes used: " << hash_table.ReturnProbeCount() << endl;
    } //... else print NOT FOUND and display the # of probes used 
  }

  myFile1.close();
  myFile2.close();
}

