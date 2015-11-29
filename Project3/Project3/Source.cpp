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
		// builds tree
		code.build();

		// test for decode
		cout << code.decode(". ._ _") << endl;
		cout << code.decode("._.. ___ .__") << endl;
		cout << code.decode("..._ __.. _.._") << endl;
		cout << code.decode(".... ._ _..") << endl;
		cout << code.decode(".... ._ ..._ . _. _") << endl;

		// test for encode
		cout << code.encode("eat") << endl;
		cout << code.encode("fish") << endl;
		cout << code.encode("towel") << endl;
		cout << code.encode("blue") << endl;

		// test for both functions accurracy
		cout << code.encode(code.decode(".. .__ __")) << endl;
		cout << code.decode(code.encode("waffle")) << endl;
	}
	catch(exception e)
	{
		cout << e.what() << endl;
	} // end try/catch
} // end main