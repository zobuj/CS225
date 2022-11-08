/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()) {
    /* Reads a line from `wordsFile` into `word` until the file ends. */
    while (getline(wordsFile, word)) {
        string temp = word;
      std::sort(word.begin(),word.end());
      dict[word].push_back(temp);
    }

    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for(size_t i = 0;i<words.size();i++){
        string temp=words[i];
        std::sort(temp.begin(),temp.end());
        dict[temp].push_back(words[i]);
    }
    
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    bool flag=true;
    string temp = word;
    std::sort(temp.begin(),temp.end());
    if(!dict.count(temp)){
        //if not found in the dict then return an empty vector
        flag=false;
    }
    if(flag){
        return dict.at(temp);
    }
    return std::vector<string>();
    
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> output;
    bool flag = true;
    for (std::pair<const std::string, std::vector<std::string>>  key_val : dict)
    {   if(key_val.second.size()<=1){
            flag=false;
            continue;
        }
            output.push_back(key_val.second);
            flag=true;
    }
    if(flag==false){
        return vector<vector<string>>();
    }
    return output;
}
