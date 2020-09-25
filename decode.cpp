#include <cctype>
#include <sstream>
#include <string>
#include "bdict.h"
#include "bstring.h"
#include "btypes.h"
#include "decode.h"
#include "utils.h"
#include <vector>
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
		cout << to_string(ss.peek()) << endl;
		vector<bdata> items;
		while (ss.peek() != 'e') {
			auto decodedItem = decode<bdata>(ss);
			if (decodedItem.index() == 0) { 
				cout << "index is 0" << get<string>(decodedItem) << endl;
				return get<string>(decodedItem); }
			else { items.push_back(get<bdata>(decodedItem)); }

			if (ss.peek() == ':') { ss >> l;}		
		}

		return blist(items);
	}

	// template<>
	// variant<string,bdict> decode<bdict>(stringstream& ss) {
	// 	char d;
	// 	ss >> d;

		

	// 	return "";


	// }

	template<>
	variant<string,bdata> decode<bdata>(stringstream& ss) {

		if(peek_bint(ss)) {
			auto vint = decode<bint>(ss);
			return map(vint,function<bdata(bint)>([](auto a) { return a; }));
		
		} else if (peek_bstring(ss)) {
			auto vstring = decode<bstring>(ss);
			return map(vstring,function<bdata(bstring)>([](auto a) { return a; }));

		} else if (peek_blist(ss)) {
			auto vlist = decode<blist>(ss);
			return map(vlist,function<bdata(blist)>([](auto a) { return a;}));
		} else {
			return string("dict");
			// auto vdict = decode<bdict>(ss);
			// return map(vdict,function<bdata(bdict)>([](auto a) { return a; }));
		}
	}
}