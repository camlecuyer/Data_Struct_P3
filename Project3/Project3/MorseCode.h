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

	/** decode a message that was input using Morse code
	@param message holds the data from the caller function, in the correct format
	*/
	string decode(string message)
	{
		//find();
	} // end decode

	/** encodes a message into Morse code
	@param input holds the data from the caller function that is to be converted
	*/
	string encode(string input)
	{
		//traverse();
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
	} // end buildTree

	/** parses input data for use in the tree
	@param input is the input data from the buildTree function that holds the letter and code
	*/
	void populateTree(string input)
	{
		// holds letter from file
		char letter = input[0];
		// holds path to place letter
		string path = "";
		// holder for error
		bool errorNotFound = true;

		// transforms symobls to 1 or 0 for easier parsing
		for(size_t i = 1; i < input.length(); i++)
		{
			if(input[i] == '.')
			{
				path += '0';
			}
			else
			{
				path += '1';
			} // end if
		} // end loop

		errorNotFound = insert(root, letter, path, 0);

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
	bool insert(BTNode<char>*& local_root,const char& item, const string& path, const int& pos)
	{
		if (local_root == NULL)
		{
			local_root = new BTNode<char>(item);
			return true;
		}
		else
		{
			if (path[pos] == '0')
				return insert(local_root->left, item, path, pos + 1);
			else if (path[pos] == '1')
				return insert(local_root->right, item, path, pos + 1);
			else
				return false;
		} // end if
	} // end insert
}; // end class MorseCode