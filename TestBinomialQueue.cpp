/******************************************************************************
Title       : TestBinomialQueue.cpp
Author      : Dan Cambitsis
Created on  : 3/31/2016
Description : Test function for binomial queue.
******************************************************************************/

#include "BinomialQueue.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace chrono;


void TestBinomialQueue(const string input_filename, int flag);
void TestBinomialQueue2(const string input_filename, int flag);
void TestBinomialQueue3(const string input_filename, int flag);

// Sample main for program CreateAndTestHash
int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <input_file_to_create_queue> <flag>" << endl;
    cout << "    flag should be either 0 or 1" << endl;
    return 0;
  }
  
  const string input_filename(argv[1]);
  const int flag = atoi(argv[2]);
  cout << "PART A: " << endl;
  TestBinomialQueue(input_filename, flag);
  cout << "END OF PART A -----------------------" << endl;
  cout << "PART B: " << endl;
  TestBinomialQueue2(input_filename, flag);
  cout << "END OF PART B -----------------------" << endl;
  cout << "PART C: " << endl;
  TestBinomialQueue3(input_filename, flag);
  cout << "END OF PART C -----------------------" << endl;
  return 0;
}

void TestBinomialQueue(const string input_filename, int flag) {
  cout << "Input is " << input_filename << endl;
  cout << "Flag is " << flag << endl;
  BinomialQueue<int> input_queue; //for flag 0
  BinomialQueue<int> bq1; //for flag 1
  BinomialQueue<int> bq2; //for flag 1

  string line, lineCount;
  int intLineCount = 0, quarterCheck = 1, index = 0;
  ifstream myFile(input_filename);

  if (!myFile) { //if the file could not be opened, prompt error and terminate
    cout << "The file could not be opened, terminating program." << endl;
    exit(1);
  }

  while (input_filename[index] != '_') {
    lineCount += input_filename[index];
    ++index; //acquire the amount of elements in the file by using the file name
  }

  intLineCount = stoi(lineCount); //convert the line count to an integer

  cout << "Time for insert: " << endl; //begin time for insert
  const auto begin = high_resolution_clock::now();
  while(getline(myFile, line)) {
    int intLine = stoi(line); //convert the line into an integer
    if (flag == 0) { //if the flag is 0 ...
      input_queue.Insert(intLine); //simply insert the number to the input queue
      //test the time
    }

    else { //the flag is 1 ...
      if (quarterCheck <= intLineCount * .25) { //insert the first quarter of the file into bq1
        bq1.Insert(intLine); //insert into bq1
        ++quarterCheck; //increment quarterCheck 
      }

      else { //quarterCheck has exceeded the first quarter amount of the line count
        bq2.Insert(intLine); //insert into bq2
      }
    }
  }
  const auto end = high_resolution_clock::now(); //stop the time
  cout << duration_cast<nanoseconds>(end-begin).count() << "ns" << endl;
  //display the time in nanoseconds
  if (flag == 0) { //if the flag is 0 ...
    while (!input_queue.IsEmpty()) { //while the input_queue is not empty ...
      cout << "Min to be deleted: " << input_queue.FindMin() << endl;
      input_queue.DeleteMin(); //display and delete the minimum element
    }
  }
  else { //the flag is 1 ...
    cout << "Time for merge: " << endl;
    const auto begin2 = high_resolution_clock::now(); //begin time for merge
    bq1.Merge(bq2); //merge bq2 into bq1
    const auto end2 = high_resolution_clock::now(); //stop the time
    cout << duration_cast<nanoseconds>(end2-begin2).count() << "ns" << endl;
    //display the time in nanoseconds
    int check;
    if (intLineCount < 10) {
      check = intLineCount;
    }
    else {
      check = 10;
    }
    for (int i = 0; i < check; i++) { //display and delete the first 10 elements 
        cout << "Min to be deleted: " << bq1.FindMin() << endl;
        bq1.DeleteMin(); 
    }
  }

  myFile.close();
}

//WITH NEW INSERT
void TestBinomialQueue2(const string input_filename, int flag) {
  BinomialQueue<int> input_queue; //for flag 0
  BinomialQueue<int> bq1; //for flag 1
  BinomialQueue<int> bq2; //for flag 1

  string line, lineCount;
  int intLineCount = 0, quarterCheck = 1, index = 0;
  ifstream myFile(input_filename);

  if (!myFile) { //if the file could not be opened, prompt error and terminate
    cout << "The file could not be opened, terminating program." << endl;
    exit(1);
  }

  while (input_filename[index] != '_') {
    lineCount += input_filename[index];
    ++index; //acquire the amount of elements in the file by using the file name
  }

  intLineCount = stoi(lineCount); //convert the line count to an integer

  cout << "Time for insert: " << endl; //begin time for insert
  const auto begin = high_resolution_clock::now();
  while(getline(myFile, line)) {
    int intLine = stoi(line); //convert the line into an integer
    if (flag == 0) { //if the flag is 0 ...
      input_queue.NewInsert(intLine); //simply insert the number to the input queue
      //test the time
    }

    else { //the flag is 1 ...
      if (quarterCheck <= intLineCount * .25) { //insert the first quarter of the file into bq1
        bq1.NewInsert(intLine); //insert into bq1
        ++quarterCheck; //increment quarterCheck 
      }

      else { //quarterCheck has exceeded the first quarter amount of the line count
        bq2.NewInsert(intLine); //insert into bq2
      }
    }
  }
  const auto end = high_resolution_clock::now(); //stop the time
  cout << duration_cast<nanoseconds>(end-begin).count() << "ns" << endl;
  //display the time in nanoseconds
  if (flag == 0) { //if the flag is 0 ...
    while (!input_queue.IsEmpty()) { //while the input_queue is not empty ...
      cout << "Min to be deleted: " << input_queue.FindMin() << endl;
      input_queue.DeleteMin(); //display and delete the minimum element
    }
  }
  else { //the flag is 1 ...
    cout << "Time for merge: " << endl;
    const auto begin2 = high_resolution_clock::now(); //begin time for merge
    bq1.Merge(bq2); //merge bq2 into bq1
    const auto end2 = high_resolution_clock::now(); //stop the time
    cout << duration_cast<nanoseconds>(end2-begin2).count() << "ns" << endl;
    //display the time in nanoseconds
    int check;
    if (intLineCount < 10) {
      check = intLineCount;
    }
    else {
      check = 10;
    }
    for (int i = 0; i < check; i++) { //display and delete the first 10 elements 
        cout << "Min to be deleted: " << bq1.FindMin() << endl;
        bq1.DeleteMin(); 
    }
  }

  myFile.close();
}

//WITH NEW INSERT AND MERGE
void TestBinomialQueue3(const string input_filename, int flag) {
  BinomialQueue<int> input_queue; //for flag 0
  BinomialQueue<int> bq1; //for flag 1
  BinomialQueue<int> bq2; //for flag 1

  string line, lineCount;
  int intLineCount = 0, quarterCheck = 1, index = 0;
  ifstream myFile(input_filename);

  if (!myFile) { //if the file could not be opened, prompt error and terminate
    cout << "The file could not be opened, terminating program." << endl;
    exit(1);
  }

  while (input_filename[index] != '_') {
    lineCount += input_filename[index];
    ++index; //acquire the amount of elements in the file by using the file name
  }

  intLineCount = stoi(lineCount); //convert the line count to an integer

  cout << "Time for insert: " << endl; //begin time for insert
  const auto begin = high_resolution_clock::now();
  while(getline(myFile, line)) {
    int intLine = stoi(line); //convert the line into an integer
    if (flag == 0) { //if the flag is 0 ...
      input_queue.NewInsert(intLine); //simply insert the number to the input queue
      //test the time
    }

    else { //the flag is 1 ...
      if (quarterCheck <= intLineCount * .25) { //insert the first quarter of the file into bq1
        bq1.NewInsert(intLine); //insert into bq1
        ++quarterCheck; //increment quarterCheck 
      }

      else { //quarterCheck has exceeded the first quarter amount of the line count
        bq2.NewInsert(intLine); //insert into bq2
      }
    }
  }
  const auto end = high_resolution_clock::now(); //stop the time
  cout << duration_cast<nanoseconds>(end-begin).count() << "ns" << endl;
  //display the time in nanoseconds
  if (flag == 0) { //if the flag is 0 ...
    while (!input_queue.IsEmpty()) { //while the input_queue is not empty ...
      cout << "Min to be deleted: " << input_queue.FindMin() << endl;
      input_queue.DeleteMin(); //display and delete the minimum element
    }
  }
  else { //the flag is 1 ...
    cout << "Time for merge: " << endl;
    const auto begin2 = high_resolution_clock::now(); //begin time for merge
    bq1.NewMerge(bq2); //merge bq2 into bq1
    const auto end2 = high_resolution_clock::now(); //stop the time
    cout << duration_cast<nanoseconds>(end2-begin2).count() << "ns" << endl;
    //display the time in nanoseconds
    int check;
    if (intLineCount < 10) {
      check = intLineCount;
    }
    else {
      check = 10;
    }
    for (int i = 0; i < check; i++) { //display and delete the first 10 elements 
        cout << "Min to be deleted: " << bq1.FindMin() << endl;
        bq1.DeleteMin(); 
    }
  }

  myFile.close();
}
