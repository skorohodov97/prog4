#include <map>
#include <string>
#include "..\StaticLib1\Student.h"
namespace Prog7b {
	class ConstTableIt;
	std::ostream & operator <<(std::ostream &, const std::pair<const int, Students::Student *> &);
	class Table {
	private:
		std::map<const int, Students::Student *> arr;
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
		Const_Iterator begin() const;
		Const_Iterator end() const;
	};
	class ConstTableIt {
	private:
		std::map<const int, Students::Student *>::const_iterator cur;
	public:
		ConstTableIt() {}
		ConstTableIt(std::map<const int, Students::Student *>::iterator it) :cur(it) {}
		ConstTableIt(std::map<const int, Students::Student *>::const_iterator it) :cur(it) {}
		int operator !=(const ConstTableIt &) const;
		int operator ==(const ConstTableIt &) const;
		const std::pair<const int, Students::Student *> & operator *();
		const std::pair<const int, Students::Student *> * operator ->();
		ConstTableIt & operator ++();
		ConstTableIt operator ++(int);
	};
};
