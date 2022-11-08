/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>
#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;
    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open()) {
    /* Reads a line from `wordsFile` into `word` until the file ends. */
    while (getline(wordsFile, word)) {
        string temp=word;
        string idx1word =word.erase(0,1);
        word=temp;
        string idx2word = word.erase(1,1);
        word=temp;
       // std::cout << word << " "<<idx1word<<" "<<idx2word<<std::endl;
        if(d.homophones(word,idx1word)&&d.homophones(word,idx2word)){
            tuple<std::string,std::string,std::string> t={word,idx1word,idx2word};
            ret.push_back(t);
        }
    }
}
    /* Your code goes here! */
    return ret;
}
