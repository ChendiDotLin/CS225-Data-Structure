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
	if (wordsFile.is_open()){
		while (getline(wordsFile,word)){
			string bla = word;
			std::sort(bla.begin(),bla.end());
			auto lookup = dict.find(bla);			
			if (lookup!= dict.end()){
				lookup->second.push_back(word);
			}
			else {
				dict[bla].push_back(word);
			}
		}
	}
}

/** 
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */ 
AnagramDict::AnagramDict(const vector< string >& words)
{
    /* Your code goes here! */
	for (unsigned int i = 0; i <words.size(); i++){
		string bla = words[i];
		std::sort(bla.begin(),bla.end());
		auto lookup = dict.find(bla);
		if (lookup!= dict.end()){
			lookup->second.push_back(words[i]);
			}
		else {
			dict[bla].push_back(words[i]);
		}
}
}
/**
 * @param word The word to find anagrams of. 
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the 
 * word list.
 */
vector< string > AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
 
    vector< string > a ;
	string bla = word;
	std::sort(bla.begin(),bla.end());
	auto lookup = dict.find(bla);
	if (lookup!= dict.end()){
	//	for (unsigned long i = 0; i < lookup->second.size(); i++){
			//if (lookup->second[i]!=word)
	//			a.push_back(lookup->second[i]);
	a= lookup->second;	
	}
	
	return a;
}       

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector< vector< string > > AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
     vector< vector < string > > a ;
	for (auto lookup = dict.begin(); lookup != dict.end(); lookup++){
		if (lookup->second.size()>=2) 
			a.push_back(lookup->second);
	}
 
	return a ;
}


