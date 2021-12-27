#pragma once
#include "pch.h"
#include <iostream>
#include <map>
#include <string>
#include <exception>
#include "..\StaticLib1\Student.h"
namespace Prog7b {
	class ConstTableIt;
	template <typename IND, typename INF>
	struct Pair {
		IND first;
		INF second;
		Pair() :first(IND()), second(0) { }
		Pair(const IND &code) :first(code), second(0) { }
		Pair(const IND& ind, const INF& inf) : first(ind), second(inf) { }
	};

	template <typename IND, typename INF>
	Pair <IND, INF> make_pair(const IND& ind, const INF& inf)
	{
		return Pair<IND, INF>(ind, inf);
	}

	template <typename IND, typename INF>
	class Map {
	private:
		Pair <IND, INF>* arr;
		int size;
	public:
		Pair< int, Students::Student*>* find(const int key) const;
		Pair< int, Students::Student*>* begin() const;
		Pair< int, Students::Student*>* end() const;
		Pair< int, Students::Student*>* insert(Pair<IND, INF> key_value);
		Pair< int, Students::Student*>* clear();
		Pair< int, Students::Student*>* erase(const Pair< int, Students::Student*>*);
	};

	class ConstTableIt {
	private:
		const Pair< int, Students::Student*>* cur;
	public:
		ConstTableIt() {}
		ConstTableIt(const Pair< int, Students::Student*>* it) :cur(it) {}
		int operator !=(const ConstTableIt &) const;
		int operator ==(const ConstTableIt &) const;
		const Pair< int, Students::Student *> & operator *();
		const Pair< int, Students::Student *> * operator ->();
		ConstTableIt & operator ++();
		ConstTableIt operator ++(int);
	};
	std::ostream & operator <<(std::ostream &, const Pair< int, Students::Student *> &);

	class Table {
	private:
		Map< int, Students::Student *> arr;
	public:
		Table() {}
		Table(const Table &);
		~Table();
		Table& operator = (const Table &);
		friend class ConstTableIt;
		typedef ConstTableIt Const_Iterator;
		Const_Iterator find(const int &)const;
		bool insert(const int &, const Students::Student *);
		bool replace(const int &, const Students::Student *);
		bool remove(const int&);
		Const_Iterator begin() const
		{
			return ConstTableIt(arr.begin());
		}
		Const_Iterator end() const;
	};
	
};