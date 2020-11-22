#include <algorithm>
#include <cctype>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <system_error>
#include <vector>
#include <map>
#include <variant>
#include <functional>

#include <boost/lexical_cast.hpp>

#include "error.h"
#include "bdict.h"
#include "bstring.h"
#include "bint.h"
#include "blist.h"
#include "btypes.h"
#include "decode.h"
#include "utils.h"
#include "error.h"

using namespace std;

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
	either<bstring> decode<bstring>(stringstream& ss) {
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
	either<bint> decode<bint>(stringstream& ss) {
		char i;
		ss >> i;

		if (i != 'i') {
			return BErrorF::expected_int_open(i);
		}

		string intstring;
		char ch;
		while (ss.peek() != 'e' && !ss.eof()) {
			ss >> ch;
			intstring += ch;
		}

		if(ss.eof()) {
			return BErrorF::expected_int_end();
		}
		
		ss >> ch;
		try {
			int n = boost::lexical_cast<int>(intstring);
			return bint(n);
		} catch (...) {
			return BErrorF::conversion_to_int(intstring);
		}
	}

	template<>
	either<blist> decode<blist>(stringstream& ss) {
		char l;
		ss >> l;

		if (l != 'l') {
			return BErrorF::expected_list_open(l);
			// return &"decoder: could not parse as list. Expected input 'l', actual " [ l];
		}

		vector<shared_ptr<bdata>> items;

		// decode any additional items
		while (ss.peek() != 'e' && !ss.eof()) {
			auto item = decode<bdata>(ss);
			if (!item) { return item.error(); }
			else { items.push_back(make_shared<bdata>(item.value())); }
		}

		if (ss.eof()) {
			return BErrorF::expected_list_end();
		}
		ss >> l; // drop e

		return blist(items);
	}

	template<>
	either<bdict> decode<bdict>(stringstream& ss) {
		char d;
		ss >> d;

		if (d != 'd') {
			return BErrorF::expected_dict_open(d);
			// return string("decoder: could not parse as dict. Expected input 'd', actual ") + d;
		}

		map<bstring,shared_ptr<bdata>> dict;

		while(ss.peek() != 'e' && !ss.eof()) {
			auto decodedKey = decode<bstring>(ss);
			if(!decodedKey) { return decodedKey.error(); } // abort with error

			auto decodedValue = decode<bdata>(ss);

			if (!decodedValue) { return decodedValue.error(); }
			else { 
				bstring key = decodedKey.value();
				bdata val   = decodedValue.value();
				
				dict.insert({key,make_shared<bdata>(val) }); 
			}
		}

		if (ss.eof()) {
			return BErrorF::expected_dict_end();
		}

		ss >> d; // drop e

		return bdict(dict);
	}

	template<>
	either<bdata> decode<bdata>(stringstream& ss) {

		if(peek_bint(ss)) {
			auto vint = decode<bint>(ss);
			if (!vint) { return vint.error(); }
			else 				   { return vint.value(); }
			
		} else if (peek_bstring(ss)) {

			if (auto vstring = decode<bstring>(ss)) 
				 { return vstring.value(); }
			else { return vstring.error(); }


		} else if (peek_blist(ss)) {
			auto vlist = decode<blist>(ss);
			if (!vlist) { return vlist.error(); }
			else 	   { return vlist.value(); }
		} else {
			auto vdict = decode<bdict>(ss);
			if (!vdict) { return vdict.error(); }
			else 	    { return vdict.value(); }
		}
	}
}