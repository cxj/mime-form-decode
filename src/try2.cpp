#include <cstdlib>
#include <iostream>
#include "StringDecoder.h"

using namespace std;

/**
 * Test driver for the StringDecoder API class.
 *
 * Reads stdin until EOF, passes resulting string to API.
 *
 * @author Chris Johnson
 */

int
main(int argc, char **argv)
{
	try {
		mime::StringDecoder d;

		while (cin.good()) {
			string line;
			getline(cin, line, '\0');	// assumes no \0 in text files
			d.processString(line);
		}
		cout << " processString() done\n";

		cout << " Closing decoder object\n";
		d.close();
		cout << " Post Close\n";

		cout << "Sample results contains: \n";

		cout << "  TimeStamp: " << d.getFormValue("TimeStamp") << '\n';
		cout << "  Payload:   " << d.getFormValue("Payload") << '\n';

		cout << '\n';

		string output = d.dump();
		cout << output;

	}
	catch (exception &e) {
		cout << "Exception: " << e.what() << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

