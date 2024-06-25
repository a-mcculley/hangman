//This came from when my friend, who was teaching an  introductory cs course at the time, challenged me to write a functional hangman code as fast as possible
//as a result, it does not follow best practices; I don't make use of functions or classes, I have global variables, etc
//none of which is like how I would handle writing this properly (both stylistically and in terms of actual implementation)

#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

enum Hang {nothing, head, body, larm, rarm, lleg, rleg};
vector<string> hangmen; //the various text strings representing hangman states
Hang currentState = nothing;
string phrase;
set<char> phraseLetters;
set<char> guessedLetters;

int main()
{
    bool wantsToQuit = false;
  
    while(!wantsToQuit)
    {
      currentState = nothing;
      phrase = "";
      phraseLetters.clear();
      guessedLetters.clear();
    	hangmen = {"   \n   \n   ", " o \n\n   ", " o \n | \n   ", " o \n/| \n   ", " o \n/|\\\n   ", " o \n/|\\\n/  ", " o \n/|\\\n/ \\"};
    	cout << "Enter a word or phrase: ";
    	getline(cin, phrase);
    	
      for(int i = 0; i < 1000; i++)
    	{
    		cout << "\n";
    	}//for i

      //adds both the upper and lower case versions of the strings to the set of characters in the phrase; this is to handle case insensitivity
      //if i were to implement this properly, I would just handle one case since I'm using toupper/tolower anyway
    	for(int i = 0; i < phrase.size(); i++)
    	{
    		if(isalpha(phrase[i]))
    		{
    			phraseLetters.insert(toupper(phrase[i]));
    			phraseLetters.insert(tolower(phrase[i]));
    		}//if
    	}//for i
    	
      char guess;
    	vector<char> set_diff;
    	
      while(true)
    	{
    		cout << "\n";
    		set_difference(phraseLetters.begin(), phraseLetters.end(), guessedLetters.begin(), guessedLetters.end(), back_inserter(set_diff));
    		if(currentState == rleg || set_diff.size() == 0)
    		{
    			break;
    		}//if
    		set_diff.clear();
    		cout << hangmen[currentState];
        
    		for(int i = 0; i < phrase.size(); i++)
    		{
    		  cout << " ";
          //outputs the non-alphabetical characters, correctly guessed characters, and _ in place of non-guessed characters
    			if(!isalpha(phrase[i]) || guessedLetters.find(phrase[i]) != guessedLetters.end())
    			{
    				cout << phrase[i];
    			}//if
    			else
    			{
    				cout << "_";
    			}//else
    		}//for i
        
    		cout << "\n";
    		if(guessedLetters.begin() != guessedLetters.end())
    		{
    		    cout << "Previously Guessed Letters: ";
          
    		    for(auto i = guessedLetters.begin(); i != guessedLetters.end(); i++)
    		    {
    		        if(isupper(*i))
    		        {
    		            cout << *i << " ";
    		        }//if        
    		    }//for i 
          
    		    cout << "\n";
    		}//if
        
    		while(true)
    		{
    			cout << "Enter a Letter: ";
    			cin >> guess;
    			if(!isalpha(guess))
    			{
    				cout << "Please Enter a Letter, Not a Number or Symbol\n";
    			}//if
    			else if(guessedLetters.find(guess) != guessedLetters.end())
    			{
    				cout << "You've Already Guessed that Letter, Please Guess a New One.\n";
    			}//else if
    			else
    			{
    				guessedLetters.insert(toupper(guess));
    				guessedLetters.insert(tolower(guess));
    				if(phraseLetters.find(guess) == phraseLetters.end())
    				{
    					currentState = (Hang) (((int) currentState) + 1);
    				}//if
    				break;
    			}//else
    		}//while
    	}//while
      
    	cout << "\n";
    	if(currentState == rleg)
    	{
    		cout << hangmen[rleg] << "\nYou Lose!\n";
    		cout << "The phrase was \"" << phrase << "\"\n";
    	}//if
    	else
    	{
    		cout << "The phrase was \"" << phrase << "\", you win!\n";
    	}//else
    	cout << "If you wish to quit enter 'q'. Otherwise enter any other character\n";
    	string endInput;
    	getline(cin, endInput);
    	getline(cin, endInput);
    	if(endInput.size() > 0 && (endInput[0] == 'q' || endInput[0] == 'Q'))
    	{
    	    wantsToQuit = true;
    	}//if
    }//while
}//main
