// Cameron L'Ecuyer
#include <iostream>
#include <fstream>
#include "Binary_Tree.h"
using namespace::std;

class MorseCode : public Binary_Tree<char>
{
public:
	// Default Constructor
	/**sets the root to space char to represent empty node
	*/
	MorseCode()
	{
		this->root = new BTNode<char>(' ');
	} // end Default Constructor

	/** Calls the build tree function
	*/
	void build()
	{
		buildTree();
	} // end build

	/** Removes leading and trailing whitespace and extra white spaces
	@param input is the input string passed from caller
	*/
	string removeWhiteSpace(string input)
	{
		// temp variable for whitespace adjustment
		string temp = "";
		// removes leading whitespace
		input = input.erase(0, input.find_first_not_of(" "));
		// removes trailing whitespace
		input = input.erase(input.find_last_not_of(" ") + 1);

		// control flag for loop
		size_t i = 0;
		// bool determines if a space is already found
		// so that additional spaces can be removed
		bool spaceFound = false;

		// loops through input to removes unneccessary spaces
		while(i < input.length())
		{
			// if a space is found enter inner if
			// else add to temp
			if(input[i] == ' ')
			{
				// if no space found add the space to temp and 
				//set spaceFound to true to remove additional spaces
				if(!spaceFound)
				{
					temp += input[i];
					spaceFound = true;
				} // end if
			}
			else
			{
				// if a non-space is found set spaceFound to false and
				// add char to temp
				spaceFound = false;
				temp += input[i];
			} // end if

			i++; // increment control flag
		} // end loop
	
		// return the reduced string
		return temp;
	} // end removeWhiteSpace

	/** traverses the tree by following the path from input
	@param path passed from caller defines the path to the letter
	@param pos is the position in the path
	returns the letter at the end of the path
	*/
	char traverseTree(BTNode<char>*& local_root, string& path, const int& pos)
	{
		// if a null is found throw error
		if (local_root == NULL)
		{
			throw exception("Code is too long for this representation of Morse Code");
		} // end if

		// if found end of path return data
		if(pos == path.length())
		{
			return local_root->data;
		} // end if

		// go left if '.' right if '_'
		if(path[pos] == '.')
		{
			return traverseTree(local_root->left, path, pos + 1);
		}
		else
		{
			return traverseTree(local_root->right, path, pos + 1);
		} // end if
	} // end traverseTree

	/** calls traversTree
	@param path passed from caller defines the path to the letter
	returns the letter at the end of the path
	*/
	char traverse(string path)
	{
		return traverseTree(this->root, path, 0);

	} // end traverse

	/** decode a message that was input using Morse code
	@param message holds the data from the caller function, in the correct format
	returns decoded string message
	*/
	string decode(string message)
	{
		// removes unnecessary white space
		message = removeWhiteSpace(message);

		// holds location of a space
		size_t spaceLocation = 0;
		// used to parse substring data
		size_t i = 0;
		// holds result
		string result = "";

		// loops through the message to parse the data by finding all the spaces
		while(spaceLocation <= message.find_last_of(' '))
		{
			// finds a space's location
			spaceLocation = message.find(' ', spaceLocation + 1);
			// passes a substring from first nonspace to just before space, into traverse and gets result
			result += traverse(message.substr(i, spaceLocation - i));
			// moves i to spaceLocation
			i = spaceLocation;
			i++;		
		} // end loop

		return result;
	} // end decode

	/** finds a letter in the Morse code tree
	@param input is the character to be found
	@param morse is Morse code string
	returns Morse code string representation
	*/
	void findChar(BTNode<char>*& local_root, char input, string morse, string& answer)
	{
		// if a null is found return;
		if (local_root == NULL)
		{
			return;
		} // end if

		// returns if an answer has been found
		if(answer != "")
		{
			return;
		} // end if

		// sets the answer and returns
		if(input == local_root->data)
		{
			answer = morse;
			return;
		} // end if

		// adds a dot to the string and passes it to the left subtree
		string temp = morse + '.';
		findChar(local_root->left, input, temp, answer);

		// resets temp
		temp = "";

		// adds a dash to the string and passes it to the right subtree
		temp = morse + '_';
		findChar(local_root->right, input, temp, answer);
	} // end find

	/** calls findChar
	@param input is the character to be found
	returns Morse code string representation
	*/
	string find(char input)
	{
		// holder for answer
		string answer = "";

		// passes character into findChar
		findChar(root, input, "", answer);

		// if answer not found throw error
		if(answer == "")
		{
			throw exception("Letter not in the tree");
		} // end if

		return answer;
	} // end find

	/** encodes a message into Morse code
	@param input holds the data from the caller function that is to be converted
	returns final Morse code string
	*/
	string encode(string input)
	{
		// removes unnecessary white space
		input = removeWhiteSpace(input);

		// changes word to all lowercase
		for(size_t i = 0; i < input.length(); i++)
		{
			input[i] = tolower(input[i]);
		} // end loop

		// holder for the result
		string result = "";

		// loops through the input passing each character to get
		// Morse code representation
		for(size_t i = 0; i < input.length(); i++)
		{
			// finds Morse code represntation and adds it to the string
			result += find(input[i]);

			// places a space between each character of Morse code
			if(i != input.length() - 1)
			{
				result += ' ';
			} // end if
		} // end loop

		return result;
	} // end encode
private:
	/** Builds the tree from a predetermined file
	*/
	void buildTree()
	{
		// count used to determine if there is too little or too much input
		int count = 0;
		// holder for input
		string line = "";

		// holds input file
		ifstream morseFile;
		morseFile.open("morseMod.txt");

		// tests to see if file exists, if not it throws an error
		if(morseFile.is_open())
		{
			// loops through file to get all input
			while(getline(morseFile, line))
			{
				// calls populateTree and increments a counter 
				populateTree(line);
				count++;
			} // end loop

			// tests if correct number of letters or not
			if(count != 26)
			{
				// if too few or too many letters throws error
				if(count < 26)
				{
					throw exception("Too few entries in file");
				}
				else
				{
					throw exception("Too many entries in file");
				} // end if
			} // end if
		}
		else
		{
			throw exception("Unable to open file");
		} // end if

		morseFile.close();
	} // end buildTree

	/** parses input data for use in the tree
	@param input is the input data from the buildTree function that holds the letter and code
	*/
	void populateTree(string input)
	{
		// holds letter from file
		char letter = input[0];
		// holds path to place letter
		string path = input.erase(0,1);
		// holder for error
		bool errorNotFound = true;

		// inserts letter, if successful no error thrown
		errorNotFound = insert(root, letter, path, 0);

		// if unsuccessful insertion throw error
		if(!errorNotFound)
		{
			throw exception("Error building tree from file");
		} // end if
	} // end populateTree

	/** inserts the data into the morse code tree
	@param local_root is the current node
	@param item is the data to be inserted
	@param path is the code for finding the place to insert the data
	@param pos is where on the path the program currently is
	returns if successfully placed the data or not
	*/
	bool insert(BTNode<char>*& local_root, const char& item, const string& path, const int& pos)
	{
		// if local_root is null isert node, else traverse tree
		if (local_root == NULL)
		{
			local_root = new BTNode<char>(item);
			return true;
		}
		else
		{
			// if '.' go left, if '_' go right, else return fail status
			if (path[pos] == '.')
			{
				return insert(local_root->left, item, path, pos + 1);
			}
			else if (path[pos] == '_')
			{
				return insert(local_root->right, item, path, pos + 1);
			}
			else
			{
				return false;
			} // end if
		} // end if
	} // end insert
}; // end class MorseCode