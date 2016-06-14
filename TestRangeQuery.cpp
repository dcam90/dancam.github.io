/******************************************************************************
Title       : AvlTree.h
Author      : Dan Cambitsis
Created on  : 3/8/2016
Description : TestRangeQuery implementation.
******************************************************************************/

#include "AvlTree.h"
#include "SequenceMap.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string getAnEzAcro(const string db_line) {
  string theAcro;

  for (unsigned int i = 0; i < db_line.length(); i++) {
    if (db_line[i] == '/') {
      break; //break if a '/' is detected
    }

    theAcro += db_line[i]; //append all characters to theAcro until a '/' is reached
  }

  return theAcro;
}

void getARecoSeq(const string db_line, vector<string> & temp) {
  size_t pos = db_line.find('/');
  string seq;

  for (unsigned int i = pos + 1; i < db_line.length(); i++) {
    if (db_line[i] == '/' && db_line[i + 1] == '/') {
      temp.push_back(seq);
      break; //if a "//" is reached, push back the seq to a temp vector and break
    }
    if (db_line[i] == '/') { //this accounts for all sequences within a line
      temp.push_back(seq); //add the seq to the temp vector
      seq.clear(); //clear the string
      continue; //ignore the line below
    }

    seq += db_line[i]; //append characters of the line to the seq
  }
}

int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <string> <string2>" << endl;
    return 0;
  }
  string db_filename(argv[1]);
  string str1(argv[2]);
  string str2(argv[3]);
  cout << "Input file is " << db_filename << " ";
  cout << "String 1 is " << str1 << " and string 2 is " << str2 << endl;

  ifstream file(db_filename);
  string db_line;

  if (!file) {
    cout << "Unable to open file, program will now terminate." << endl;
    exit(1);
  }

  for (int i = 0; i < 8; i++) {
    file.ignore(256, '\n'); //ignore the first 9 lines
  }

  AvlTree<SequenceMap> a_tree;
  while (getline(file, db_line)) {
    string an_enz_acro = getAnEzAcro(db_line);
    vector<string> temp;
    getARecoSeq(db_line, temp);

    for (unsigned int i = 0; i < temp.size(); i++) {
      string a_reco_seq = temp[i];
      SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
      a_tree.insert(new_sequence_map);
    } 
  }

  if (a_tree.contains(str1) && a_tree.contains(str2) && str1 < str2) {
    cout << "Printing inquired sequences (and enzyme acronyms) and all sequences (and enzyme acronyms) between them ..." << endl;
    a_tree.printBetweenSequences(str1, str2); 
  }

  else {
    cout << "Sorry, the sequence(s) inquired is/are not in the tree OR str1 is greater than str2." << endl;
  }

  file.close();

  return 0;
}
