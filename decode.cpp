#include <string>
#include "bdict.h"
#include "bstring.h"
#include "decode.h"

namespace bencode
{
	bstring decoder<bstring>::decode(stringstream& ss) {
		int n;
		char del;

		ss >> n >> del;

		string word;
		char ch;

		while (n > 0) {
			ss >> ch;
			word += ch;
			n--;
		}

		return bstring(word);
	}

	bdict decoder<bdict>::decode(stringstream& ss) {
		char d;
		ss >> d;

		decoder<bstring> stringDecoder;
		auto word = stringDecoder.decode(ss);

		return;


	}
}