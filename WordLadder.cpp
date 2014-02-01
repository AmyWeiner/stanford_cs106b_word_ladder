/*
 * File: WordLadder.cpp
 * --------------------
 * Name: [TODO: Amy R. Weiner]
 * Section: [TODO: Sammy Nguyen]
 * [TODO: This program finds the minimal word ladder from 
 * a start word to a destination word,by implementing the 
 * breadth-first algorithmic method]
 */

#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
using namespace std;

/* Program constants*/
const string alphabet = "abcdefghijklmnopqrstuvwxyz";

/* Funtion prototypes*/
Vector<string> findWordLadder(Queue< Vector<string> > &partialWordLadders, string destination, Lexicon &english, Set<string> &wordsUsed);
void findOneHopWords(Vector<string> currentLadder, Queue< Vector<string> > &partialWordLadders, Lexicon &english, Set<string> &wordsUsed);
bool isEnglishWord(Lexicon &english, string currentWord);
bool hasWordLadder(Vector<string> wordLadder);
string vectorToString(Vector<string> wordLadder);

/* Main program */
int main() {
    Lexicon english("EnglishWords.dat");
    Set<string> wordsUsed;
	while (true) {
        string start = getLine("Enter start word (RETURN to quit) : ");
        if (start == "") break;
        string destination = getLine("Enter destination word : ");
        Vector<string> startWord;
        startWord.add(start);
        wordsUsed.add(start);
        Queue< Vector<string> > partialWordLadders;
        partialWordLadders.enqueue(startWord);
        Vector<string> wordLadder = findWordLadder(partialWordLadders,destination,english,wordsUsed);
        if (hasWordLadder(wordLadder)) {
            string wordLadderToString = vectorToString(wordLadder); 
            cout << "Found ladder: " << wordLadderToString << endl;
        } else {
            cout << "No ladder found." << endl;
        }
    }
	return 0;
}

/* Function: findWordLadder
 * Usage: Vector<string> wordLadder = findWordLadder(partialWordLadders,destination,english,wordsUsed);
 * ----------------------------------------------------------------------------------------------------
 * This function finds the minimal word ladder from a start word to a destination word, as input by the
 * user. The value returned by the function is word ladder for instances in which a word ladder exists,
 * or an empty string Vector for instances in which no word ladder exists between the start and 
 * destination words. 
 */
Vector<string> findWordLadder(Queue< Vector<string> > &partialWordLadders, string destination, Lexicon &english, Set<string> &wordsUsed) {
    Vector<string> empty;
    while (!partialWordLadders.isEmpty()) {
        Vector<string> currentLadder = partialWordLadders.dequeue();
        if (currentLadder.get(currentLadder.size()-1) == destination) {
            return currentLadder;
        } else {
            findOneHopWords(currentLadder,partialWordLadders,english,wordsUsed);
        }
    }
    return empty;
}

/* Function: findOneHopWords
 * Usage: findOneHopWords(Vector<string> currentLadder, Queue< Vector<string> > &partialWordLadders, Lexicon &english, Set<string> &wordsUsed);
 * --------------------------------------------------------------------------------------------------------------------------------------------
 * This function finds all of the words in the English Lexicon that differ from the last word in a partial word ladder by one letter. These one
 * hope words are then appended to the partial word ladder, and entered in a second lexicon, wich keeps track of words that have already been
 * added to a partial word ladder for the given start word. 
 */
void findOneHopWords(Vector<string> currentLadder, Queue< Vector<string> > &partialWordLadders, Lexicon &english, Set<string> &wordsUsed) {
    string currentWord = currentLadder.get(currentLadder.size()-1);
    for (int i = 0; i < currentWord.length(); i++) {
        for (int j = 0; j < alphabet.length(); j++) {
            currentWord[i] = alphabet[j];
            if (isEnglishWord(english,currentWord) && !wordsUsed.contains(currentWord)) {
                Vector<string> copyCurrentLadder = currentLadder;
                copyCurrentLadder.add(currentWord);
                partialWordLadders.enqueue(copyCurrentLadder);
                wordsUsed.add(currentWord);
            }
        }
        currentWord = currentLadder.get(currentLadder.size()-1);
    }
}

/* Function: isEnglishWord
 * Usage: if (isEnglishWord(currentWord)) . . .
 * --------------------------------------------
 * This function returns true if the given word
 * is contained within the English Lexicon. 
 */
bool isEnglishWord(Lexicon &english, string currentWord) {
    return english.contains(currentWord);
}

/* Function: hasWordLadder
 * Usage: if (hasWordLadder(wordLadder)) . . .
 * -------------------------------------------
 * This function returns true if a word ladder
 * exists between a given start and destination
 * word. 
 */
bool hasWordLadder(Vector<string> wordLadder) {
    return !wordLadder.isEmpty();
}

/* Function: vectorToString
 * Usage: string wordLadderToString = vectorToString(wordLadder); 
 * --------------------------------------------------------------
 * This function returns a string consisting of the words
 * contained within a word ladder. 
 */
string vectorToString(Vector<string> wordLadder) {
    string result = "";
    for (int i = 0; i < wordLadder.size(); i ++) {
        result += wordLadder.get(i) + " ";
        
    }
    return result;
}







