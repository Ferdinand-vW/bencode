#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include "bdict.h"
#include "bstring.h"
#include "btypes.h"
#include "decode.h"
#include "utils.h"
#include <vector>
#include <map>
#include <variant>
#include <functional>

namespace bencode
{
	bool peek_bint(stringstream& ss) {
		char i = ss.peek();

		return i == 'i';
	}


	bool peek_bstring(stringstream &ss) {
		char s = ss.peek();

		return isdigit(s);
	}

	bool peek_blist(stringstream &ss) {
		char l = ss.peek();

		return l == 'l';
	}

	bool peek_dict(stringstream& ss) {
		char d = ss.peek();

		return d == 'd';
	}

	template<>
	variant<string,bstring> decode<bstring>(stringstream& ss) {
		int n;
		char del;

		ss >> n >> del;

		string word;
		char ch;

		while (n > 0) {
			ss >> ch;
			word.push_back(ch);
			n--;
		}

		return bstring(word);
	}
	
	template<>
	variant<string,bint> decode<bint>(stringstream& ss) {
		char i;
		ss >> i;

		if (i != 'i') { 
			return string("decoder: cannot parse as int. Expected input 'i', actual ") + i; 
		}

		string intstring;
		char ch;
		while (ss >> ch, ch != 'e') {
			cout << string("") + ch << endl;
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
			return &"decoder: could not parse as list. Expected input 'l', actual " [ l];
		}

		vector<bdata> items;
		while (ss.peek() != 'e') {
			auto decodedItem = decode<bdata>(ss);
			if (decodedItem.index() == 0) { 
				return get<string>(decodedItem); }
			else { items.push_back(get<bdata>(decodedItem)); }
		}

		ss >> l; // drop e

		return blist(items);
	}

	template<>
	variant<string,bdict> decode<bdict>(stringstream& ss) {
		char d;
		ss >> d;

		if (d != 'd') {
			return string("decoder: could not parse as dict. Expected input 'd', actual ") + d;
		}

		map<bstring,bdata> dict;

		while(ss.peek() != 'e') {
			auto decodedKey = decode<bstring>(ss);
			if(decodedKey.index() == 0) { return get<string>(decodedKey); } // abort with error
			
			char col;
			ss >> col;

			if (col != ':') { return string("decoder: could not parse as dict. Expected delimiter ':', actual ") + col; }

			auto decodedValue = decode<bdata>(ss);

			if (decodedValue.index() == 0) { return get<string>(decodedValue); }
			else { dict.insert( {get<bstring>(decodedKey),get<bdata>(decodedValue)} ); }
		}

		ss >> d; // drop e

		return variant<string,bdict>(bdict(dict));
	}

	template<>
	variant<string,bdata> decode<bdata>(stringstream& ss) {

		if(peek_bint(ss)) {
			auto vint = decode<bint>(ss);
			if (vint.index() == 0) { return get<string>(vint); }
			else 				   { return get<bint>(vint); }
			
		} else if (peek_bstring(ss)) {

			auto vstring = decode<bstring>(ss);
			if (vstring.index() == 0) { return get<string>(vstring); }
			else	 				  { return get<bstring>(vstring); }


		} else if (peek_blist(ss)) {
			auto vlist = decode<blist>(ss);
			if (vlist.index() == 0) { return get<string>(vlist); }
			else 					{ return get<blist>(vlist); }
		} else {
			auto vdict = decode<bdict>(ss);
			if (vdict.index() == 0) { return get<string>(vdict); }
			else 					{ return get<bdict>(vdict); }
		}
	}
}