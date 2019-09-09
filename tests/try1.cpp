#include <cstdlib>
#include <iostream>
#include <map>
#include "Decoder.h"

using namespace std;

/**
 * Test driver for the low-level event-driven Decoder API class.
 *
 * Reads stdin until EOF, calling API for each character read.
 */


/**
 * Implements the Decoder event methods are where something useful would be done.
 */
class TestDecoder : public mime::Decoder
{
public:
	TestDecoder() {}
	~TestDecoder() {}

	virtual void object_created(mime::Object *object);
	virtual void data_start(mime::Object *obj);
	virtual void data(mime::Object *obj, unsigned char *data, int len);
	virtual void data_end(mime::Object *obj);
};

void TestDecoder::object_created(mime::Object *object)
{
	cout << "  New object type " << object->type << "/" << object->subtype << endl;

	map<string, mime::HeaderField>::iterator i;
	for (i = object->fields.begin(); i != object->fields.end(); i++) {
		cout << "  " << i->first << ":" << i->second.value << endl;

		map<string, string>::iterator j;
		for (j = i->second.attributes.begin(); j != i->second.attributes.end(); j++) {
			cout << "    " << j->first << ":" << j->second << endl;
		}
	}
}

void TestDecoder::data_start(mime::Object *object)
{
	cout << "  Data start " << object->type << "/" << object->subtype << endl;
}

void TestDecoder::data(mime::Object *object, unsigned char *data, int len)
{
//    cout << "*** Data (" << len << ")" << endl;
	for (int i = 0; i < len; i++)
		cout << data[i];
}

void TestDecoder::data_end(mime::Object *object)
{
	cout << "  Data end " << object->type << "/" << object->subtype << endl;
}

int main(int argc, char **argv)
{
	try {
		TestDecoder d;

		while (cin.good()) {
			unsigned char c = cin.get();
			if (cin.good())
				d.decode(c);
		}
		d.close();
	}
	catch (exception &e) {
		cout << "Exception: " << e.what() << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

