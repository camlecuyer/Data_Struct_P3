// Cameron L'Ecuyer
#include "MorseCode.h"
using namespace::std;

void main()
{
	// holds MorseCode data
	MorseCode code;

	// try block to catch errors thrown by program
	try
	{
		code.build();

		cout << code.decode(". ._ _") << endl;
		cout << code.decode("._.. ___ .__") << endl;
		cout << code.decode("..._ __.. _.._") << endl;
		cout << code.decode(".... ._ _..") << endl;
		cout << code.decode(".... ._ ..._ . _. _") << endl;
	}
	catch(exception e)
	{
		cout << e.what() << endl;
	} // end try/catch
} // end main