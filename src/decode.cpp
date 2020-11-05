#include <algorithm>
#include <boost/outcome/outcome.hpp>
#include <boost/system/error_code.hpp>
#include <cctype>
#include <memory>
#include <sstream>
#include <string>
#include "bdict.h"
#include "bstring.h"
#include "bint.h"
#include "blist.h"
#include "btypes.h"
#include "decode.h"
#include "utils.h"
#include <system_error>
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
	outcome<bstring> decode<bstring>(stringstream& ss) {
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
	outcome<bint> decode<bint>(stringstream& ss) {
		char i;
		ss >> i;

		if (i != 'i') {
			return boost::system::errc::address_in_use; 
			// return throw("decoder: cannot parse as int. Expected input 'i', actual ") + i; 
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
	outcome<blist> decode<blist>(stringstream& ss) {
		char l;
		ss >> l;

		if (l != 'l') {
			return boost::system::errc::address_in_use;
			// return &"decoder: could not parse as list. Expected input 'l', actual " [ l];
		}

		vector<shared_ptr<bdata>> items;

		// decode any additional items
		while (ss.peek() != 'e') {
			auto item = decode<bdata>(ss);
			if (!item) { return item.error(); }
			else { items.push_back(make_shared<bdata>(item.value())); }
		}

		ss >> l; // drop e

		return blist(items);
	}

	template<>
	outcome<bdict> decode<bdict>(stringstream& ss) {
		char d;
		ss >> d;

		if (d != 'd') {
			return boost::system::errc::address_in_use;
			// return string("decoder: could not parse as dict. Expected input 'd', actual ") + d;
		}

		map<bstring,shared_ptr<bdata>> dict;

		while(ss.peek() != 'e') {
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

		ss >> d; // drop e

		return bdict(dict);
	}

	template<>
	outcome<bdata> decode<bdata>(stringstream& ss) {

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