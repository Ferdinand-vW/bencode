#include <string>
#include "bdict.h"
#include "bstring.h"
#include "decode.h"
#include <vector>
#include <variant>

namespace bencode
{

	template<>
	variant<string,bstring> decode<bstring>(stringstream& ss) {
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
	
	template<>
	variant<string,bint> decode<bint>(stringstream& ss) {
		char i;
		ss >> i;

		if (i != 'i') { 
			throw &"decoder: cannot parse as int. Expected input 'i', actual " [ i]; 
		}

		string intstring;
		char ch;
		while (ss >> ch, ch != 'e') {
			intstring += ch;
		}

		int n = stoi(intstring);

		return bint(n);
	}

	template<>
	variant<string,blist> decode<blist>(stringstream& ss) {
		char l;
		ss >> l;

		if (l != 'l') {
			throw "decoder: could not parse as list. Expected input 'l', actual " + l;
		}

		vector<string> items;
		while (ss.peek() != 'e') {
			

			//items.push_back(item);
		}

		return "";
	}

	template<>
	variant<string,bdict> decode<bdict>(stringstream& ss) {
		char d;
		ss >> d;

		

		return "";


	}
}