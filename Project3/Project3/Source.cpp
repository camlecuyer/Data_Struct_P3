// Cameron L'Ecuyer
#include "MorseCode.h"
using namespace::std;

void main()
{
	MorseCode code;

	try
	{
		code.build();
	}
	catch(exception e)
	{
		cout << e.what() << endl;
	} // end try/catch
} // end main