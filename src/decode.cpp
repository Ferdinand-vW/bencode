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

namespace bencode
{
	bool peek_bint(std::istream& is) {
		char i = is.peek();

		return i == 'i';
	}


	bool peek_bstring(std::istream &is) {
		char s = is.peek();

		return isdigit(s);
	}

	bool peek_blist(std::istream &is) {
		char l = is.peek();

		return l == 'l';
	}

	bool peek_bdict(std::istream& is) {
		char d = is.peek();

		return d == 'd';
	}

	template<>
	either<bstring> decode<bstring>(std::istream& is) {
		std::string snum;
		char d;

		while(isdigit(is.peek()) && !is.eof()) { // build the int string
			is >> d;
			snum+=d; 
		}

		int64_t n = 0;
		if (snum.length() > 0) { n = boost::lexical_cast<int64_t>(snum); }
		else if (is.eof()) { return BErrorF::expected_string_open(""); }
		else 		  	   { return BErrorF::expected_string_open(std::string(1,is.peek())); }

		char del = is.peek();
		if (del == ':') { is >> del; } // parse and throw away the delimiter
		else if (is.eof()) { return BErrorF::expected_string_delimiter(""); }
		else 		  	   { return BErrorF::expected_string_delimiter(std::string(1,del)); }
		
		std::vector<char> buff(n); //create buffer of size n
		is.read(&buff[0], n); // try to read n bytes
		auto num = is.gcount(); // actual number of bytes read
		std::string word (buff.begin(),buff.begin()+num); // copy the bytes into string

		//if end of stream reached but expecting more symbols
		if (num < n) {
			return BErrorF::expected_string_symbols(word,n - num);
		}

		return bstring(buff);
	}
	
	template<>
	either<bint> decode<bint>(std::istream& is) {
		char i;
		is >> i;

		if (i != 'i') {
			return BErrorF::expected_int_open(i);
		}

		std::string intstring;
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
			int64_t n = boost::lexical_cast<int64_t>(intstring);
			return bint(n);
		} catch (...) {
			return BErrorF::conversion_to_int(intstring);
		}
	}

	template<>
	either<blist> decode<blist>(std::istream& is) {
		char l;
		is >> l;

		if (l != 'l') {
			return BErrorF::expected_list_open(l);
		}

		std::vector<std::shared_ptr<bdata>> items;

		// decode any additional items
		while (is.peek() != 'e' && !is.eof()) {
			auto item = decode<bdata>(is);
			if (!item) { return item.error(); }
			else { 
				items.emplace_back(std::make_shared<bdata>(item.value()));
			}
		}

		if (is.eof()) {
			return BErrorF::expected_list_end();
		}
		is >> l; // drop e

		return blist(items);
	}

	template<>
	either<bdict> decode<bdict>(std::istream& is) {
		char d;
		is >> d;

		if (d != 'd') {
			return BErrorF::expected_dict_open(d);
		}

		std::map<bstring,std::shared_ptr<bdata>> dict;

		while(is.peek() != 'e' && !is.eof()) {
			auto decodedKey = decode<bstring>(is);
			if(!decodedKey) { return decodedKey.error(); } // abort with error

			auto decodedValue = decode<bdata>(is);

			if (!decodedValue) { return decodedValue.error(); }
			else { 
				bstring key = decodedKey.value();
				bdata val   = decodedValue.value();
				
				dict.insert({key,std::make_shared<bdata>(val)}); 
			}
		}

		if (is.eof()) {
			return BErrorF::expected_dict_end();
		}

		is >> d; // drop e

		return bdict(dict);
	}

	template<>
	either<bdata> decode(std::istream& is) {


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
			if (is.eof()) { s = ""; } else { s = std::to_string(c); }
			return BErrorF::invalid_input(s);
		}
	}
}