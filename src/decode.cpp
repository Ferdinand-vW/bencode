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

#include "bencode/error.h"
#include "bencode/bdict.h"
#include "bencode/bdata.h"
#include "bencode/bstring.h"
#include "bencode/bint.h"
#include "bencode/blist.h"
#include "bencode/btypes.h"
#include "bencode/decode.h"
#include "bencode/utils.h"

using namespace std;

namespace bencode
{
	bool peek_bint(istream& is) {
		char i = is.peek();

		return i == 'i';
	}


	bool peek_bstring(istream &is) {
		char s = is.peek();

		return isdigit(s);
	}

	bool peek_blist(istream &is) {
		char l = is.peek();

		return l == 'l';
	}

	bool peek_bdict(istream& is) {
		char d = is.peek();

		return d == 'd';
	}

	template<>
	either<bstring> decode<bstring>(istream& is) {
		string snum;
		char d;

		while(isdigit(is.peek()) && !is.eof()) { // build the int string
			is >> d;
			snum+=d; 
		}

		long long n = 0;
		if (snum.length() > 0) { n = boost::lexical_cast<long long>(snum); }
		else if (is.eof()) { return BErrorF::expected_string_open(""); }
		else 		  	   { return BErrorF::expected_string_open(string(1,is.peek())); }

		char del = is.peek();
		if (del == ':') { is >> del; } // parse and throw away the delimiter
		else if (is.eof()) { return BErrorF::expected_string_delimiter(""); }
		else 		  	   { return BErrorF::expected_string_delimiter(string(1,del)); }
		
		vector<char> buff(n); //create buffer of size n
		is.read(&buff[0], n); // try to read n bytes
		auto num = is.gcount(); // actual number of bytes read
		string word (buff.begin(),buff.begin()+num); // copy the bytes into string

		//if end of stream reached but expecting more symbols
		if (num < n) {
			return BErrorF::expected_string_symbols(word,n - num);
		}

		return bstring(buff);
	}
	
	template<>
	either<bint> decode<bint>(istream& is) {
		char i;
		is >> i;

		if (i != 'i') {
			return BErrorF::expected_int_open(i);
		}

		string intstring;
		char ch;
		while (is.peek() != 'e' && !is.eof()) {
			is >> ch;
			intstring += ch;
		}

		if(is.eof()) {
			return BErrorF::expected_int_end();
		}
		
		is >> ch; // parse e
		try {
			long long n = boost::lexical_cast<long long>(intstring);
			return bint(n);
		} catch (...) {
			return BErrorF::conversion_to_int(intstring);
		}
	}

	template<>
	either<blist> decode<blist>(istream& is) {
		char l;
		is >> l;

		if (l != 'l') {
			return BErrorF::expected_list_open(l);
		}

		vector<bdata> items;

		// decode any additional items
		while (is.peek() != 'e' && !is.eof()) {
			auto item = decode<bdata>(is);
			if (!item) { return item.error(); }
			else { items.push_back(item.value()); }
		}

		if (is.eof()) {
			return BErrorF::expected_list_end();
		}
		is >> l; // drop e

		return blist(items);
	}

	template<>
	either<bdict> decode<bdict>(istream& is) {
		char d;
		is >> d;

		if (d != 'd') {
			return BErrorF::expected_dict_open(d);
		}

		map<bstring,bdata> dict;

		while(is.peek() != 'e' && !is.eof()) {
			auto decodedKey = decode<bstring>(is);
			if(!decodedKey) { return decodedKey.error(); } // abort with error

			auto decodedValue = decode<bdata>(is);

			if (!decodedValue) { return decodedValue.error(); }
			else { 
				bstring key = decodedKey.value();
				bdata val   = decodedValue.value();
				
				dict.insert({key,val}); 
			}
		}

		if (is.eof()) {
			return BErrorF::expected_dict_end();
		}

		is >> d; // drop e

		return bdict(dict);
	}

	template<>
	either<bdata> decode<bdata>(istream& is) {

		if(peek_bint(is)) {
			auto vint = decode<bint>(is);
			if (!vint) { return vint.error(); }
			else 	   { return bdata(vint.value()); }
			
		} else if (peek_bstring(is)) {
			auto vstring = decode<bstring>(is);
			if (!vstring) { return vstring.error(); }
			else 		  { return bdata(vstring.value()); }

		} else if (peek_blist(is)) {
			auto vlist = decode<blist>(is);
			if (!vlist) { return vlist.error(); }
			else 	    { return bdata(vlist.value()); }
		
		} else if (peek_bdict(is)) {
			auto vdict = decode<bdict>(is);
			if (!vdict) { return vdict.error(); }
			else 	    { return bdata(vdict.value()); }
		
		} else {
			char c = is.peek();
			std::string s;
			if (is.eof()) { s = ""; } else { s = to_string(c); }
			return BErrorF::invalid_input(s);
		}
	}
}