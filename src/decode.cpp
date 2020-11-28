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
#include "bdata.h"
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

	bool peek_bdict(stringstream& ss) {
		char d = ss.peek();

		return d == 'd';
	}

	template<>
	either<bstring> decode<bstring>(stringstream& ss) {
		string snum;
		char d;

		while(isdigit(ss.peek()) && !ss.eof()) { // build the int string
			ss >> d;
			snum+=d; 
		}

		int n = 0;
		if (snum.length() > 0) { n = boost::lexical_cast<int>(snum); }
		else if (ss.eof()) { return BErrorF::expected_string_open(""); }
		else 		  	   { return BErrorF::expected_string_open(string(1,ss.peek())); }

		char del = ss.peek();
		if (del == ':') { ss >> del; } // parse and throw away the delimiter
		else if (ss.eof()) { return BErrorF::expected_string_delimiter(""); }
		else 		  	   { return BErrorF::expected_string_delimiter(string(1,del)); }
		
		string word;
		char ch;
		while (ss.peek() && n > 0 && !ss.eof()) { // peek is used to trigger eof bit
			ss >> ch;
			word.push_back(ch);
			n--;
		}

		if (n > 0 && ss.eof()) {
			return BErrorF::expected_string_symbols(word,n);
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
			else 	   { return bdata(vint.value()); }
			
		} else if (peek_bstring(ss)) {
			auto vstring = decode<bstring>(ss);
			if (!vstring) { return vstring.error(); }
			else 		  { return bdata(vstring.value()); }

		} else if (peek_blist(ss)) {
			auto vlist = decode<blist>(ss);
			if (!vlist) { return vlist.error(); }
			else 	    { return bdata(vlist.value()); }
		
		} else if (peek_bdict(ss)) {
			auto vdict = decode<bdict>(ss);
			if (!vdict) { return vdict.error(); }
			else 	    { return bdata(vdict.value()); }
		
		} else {
			char c = ss.peek();
			std::string s;
			if (ss.eof()) { s = ""; } else { s = to_string(c); }
			return BErrorF::invalid_input(s);
		}
	}
}