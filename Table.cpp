#include <iostream>
#include "pch.h"
#include "Table.h"
namespace Prog7b {

	std::ostream & operator <<(std::ostream &os,const std::pair<const int, Students::Student *> &p) {
		return os << '"' << p.first << '"' << " - " << (*p.second);
	}
	Table::Table(const Table &a)
	{
		std::map<const int, Students::Student *>::const_iterator p;
		for (p = a.arr.begin(); p != a.arr.end(); ++p)
			arr.insert(std::make_pair(p->first, p->second->clone()));
	}
	Table::~Table()
	{
		std::map<const int, Students::Student *>::iterator p;
		for (p = arr.begin(); p != arr.end(); ++p) {
			delete p->second;
			p->second = nullptr;
		}
	}
	Table& Table::operator = (const Table &a)
	{
		std::map<const int, Students::Student *>::iterator p;
		if (this != &a) {
			for (p = arr.begin(); p != arr.end(); ++p)
				delete p->second;
			arr.clear();
			std::map<const int, Students::Student *>::const_iterator pp;
			for (pp = a.arr.begin(); pp != a.arr.end(); ++pp)
				arr.insert(std::make_pair(pp->first, pp->second->clone()));
		}
		return *this;
	}
	bool Table::insert(const int &s, const Students::Student *f)
	{
		bool res = false;
		std::map<const int, Students::Student *>::iterator p = arr.find(s);
		if (p == arr.end()) {
			std::pair<std::map<const int, Students::Student *>::iterator, bool> pp =arr.insert(std::make_pair(s, f->clone()));
			if (!pp.second)
				throw std::exception("can't insert new item into map");
			res = true;
		}
		return res;
	}
	bool Table::remove(const int &s)
	{
		bool res = false;
		std::map<const int , Students::Student *>::iterator p = arr.find(s);
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
		std::map<const int, Students::Student *>::iterator p = arr.find(s);

			if (p != arr.end()) { 
				delete p->second;
				p->second = f->clone();
				res = true;
			}
		return res;
	}
	Table::Const_Iterator Table::find(const int &s) const
	{
		std::map<const int, Students::Student *>::const_iterator p = arr.find(s);
		return ConstTableIt(p);
	}
	Table::Const_Iterator Table::begin() const
	{
		return ConstTableIt(arr.begin());
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
	const std::pair<const int, Students::Student *> & ConstTableIt::operator *()
	{
		return *cur;
	}
	const std::pair<const int, Students::Student *> * ConstTableIt::operator ->()
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
