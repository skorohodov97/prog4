#include <iostream>
#include "pch.h"
#include "Table.h"
namespace Prog7b {

	Pair< int, Students::Student*>* Map< int, Students::Student*>::find(const int key) const
	{
		for (int i = 0; i < size; ++i)
		{
			if (arr[i].first == key)
			{
				return &arr[i];
			}
		}
		return arr + size;
	}

	template<>
	Pair<int, Students::Student*>* Map< int, Students::Student*>::begin() const
	{
		return &arr[0];
	}
	Pair< int, Students::Student*>* Map< int, Students::Student*>::end() const
	{
		
		return &arr[size];
	}

	Pair< int, Students::Student*>* Map<int, Students::Student*>::insert(Pair<int, Students::Student*> key_value)
	{
		Pair<int, Students::Student*>* new_arr = new Pair<int, Students::Student*>[size + 1];
		for (int i = 0; i < size; ++i)
		{
			new_arr[i].first = arr[i].first;

			int whoAmI = arr[i].second->iAm();

			switch (whoAmI)
			{
			case 1:
				new_arr[i].second = new Students::Junior(*(static_cast<Students::Junior*>(arr[i].second)));
				break;

			case 2:
				new_arr[i].second = new Students::Senior(*(static_cast<Students::Senior*>(arr[i].second)));
				break;
			case 3:
				new_arr[i].second = new Students::Graduete(*(static_cast<Students::Graduete*>(arr[i].second)));
				break;

			default:
				break;
			}

		}

		new_arr[size].first = key_value.first;
		int whoAmI = key_value.second->iAm();
		switch (whoAmI)
		{
		case 1:
			new_arr[size].second = new Students::Junior(*(static_cast<Students::Junior*>(key_value.second)));
			break;

		case 2:
			new_arr[size].second = new Students::Senior(*(static_cast<Students::Senior*>(key_value.second)));
			break;
		case 3:
			new_arr[size].second = new Students::Graduete(*(static_cast<Students::Graduete*>(key_value.second)));
			break;

		default:
			break;
		}
		
		for (int i = 0; i < size; ++i)
		{
			delete arr[i].second;
		}
		delete arr;

		arr = new_arr;

		++size;
		return  &arr[size - 1];
	}

	Pair< int, Students::Student*>* Map<int, Students::Student*>::clear()
	{
		delete arr;
		size = 0;
		arr = nullptr;
		return &arr[0];
	}

	Pair< int, Students::Student*>* Map< int, Students::Student*>::erase(const Pair< int, Students::Student*>* p)
	{
		int l = 0;
		for (int i = 0; i < size; ++i)
		{
			if (arr[i].first == p->first)
			{
				++l;
			}
			if (l > 0) {
				arr[i].first = arr[i+1].first;
				arr[i].second = arr[i + 1].second;
			}
		}
		--size;
		return &arr[0];
	}

	

	std::ostream & operator <<(std::ostream &os, const Pair< int, Students::Student *> &p) {
		return os << '"' << p.first << '"' << " - " << (*p.second);
	}
	Table::Table(const Table &a)
	{
		const Pair< int, Students::Student*>* p;
		for (p = a.arr.begin(); p != a.arr.end(); ++p)
			arr.insert(make_pair(p->first, p->second->clone()));
	}
	Table::~Table()
	{

		 Pair< int, Students::Student*>* p;
		for (p = arr.begin(); p != arr.end(); ++p) {
			if (p != nullptr)
			{
				delete p->second;
				p->second = nullptr;
			}
		}
	}
	Table& Table::operator = (const Table &a)
	{

		 Pair< int, Students::Student*>* p;
		if (this != &a) {
			for (p = arr.begin(); p != arr.end(); ++p)
				delete p->second;
			arr.clear();
			const Pair< int, Students::Student*>*  pp;
			for (pp = a.arr.begin(); pp != a.arr.end(); ++pp)
				arr.insert(make_pair(pp->first, pp->second->clone()));
		}
		return *this;
	}
	bool Table::insert(const int &s, const Students::Student *f)
	{
		bool res = false;
		const Pair< int, Students::Student*>* p = arr.find(s);
		if (p == arr.end()) {
			auto pp = arr.insert(make_pair(s, f->clone()));
			if (!pp->second)
				throw std::exception("can't insert new item into map");
			res = true;
		}
		return res;
	}
	bool Table::remove(const int &s)
	{
		bool res = false;

		 Pair< int, Students::Student*>* p = arr.find(s);
		if (p != arr.end()) { 
			delete p->second;
			p->second = nullptr;
			arr.erase(p); 
			res = true;
		}
		return res;
	}
	bool Table::replace(const int &s, const Students::Student *f)
	{
		bool res = false;

		 Pair< int, Students::Student*>* p = arr.find(s);

			if (p != arr.end()) { 
				delete p->second;
				p->second = f->clone();
				res = true;
			}
		return res;
	}
	Table::Const_Iterator Table::find(const int &s) const
	{
		const Pair< int, Students::Student*>* p = arr.find(s);
		return ConstTableIt(p);
	}
	Table::Const_Iterator Table::end() const
	{
		return ConstTableIt(arr.end());
	}
	int ConstTableIt::operator !=(const ConstTableIt &it) const
	{
		return cur != it.cur;
	}
	int ConstTableIt::operator ==(const ConstTableIt &it) const
	{
		return cur == it.cur;
	}
	const Pair< int, Students::Student *> & ConstTableIt::operator *()
	{
		return *cur;
	}
	const Pair< int, Students::Student *> * ConstTableIt::operator ->()
	{
		return &*cur;
	}
	ConstTableIt & ConstTableIt::operator ++()
	{
		++cur;
		return *this;
	}
	ConstTableIt ConstTableIt::operator ++(int)
	{
		ConstTableIt res(*this);
		++cur;
		return res;
	}
};