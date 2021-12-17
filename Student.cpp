#include <string>
#include <iostream>
#include <math.h>
#include "pch.h"
#include "Student.h"
namespace Students{
	std::ostream& operator <<(std::ostream &os, const PI &p)
	{
		return os <<" Student: "<< p.surname << "\n groups:" << p.index<<"\n department: "<<p.chair<<std::endl;
	}
	std::istream& operator >>(std::istream &is, PI &p)
	{
		std::cout << "Enter surname-> " << std::endl;
		std::cin.ignore(80, '\n');
		std::getline(is, p.surname);
		std::cout << "Enter index-> " << std::endl;
		std::getline(is,p.index);
		std::cout << "Enter chair-> " << std::endl;
		return is >> p.chair;
	}
	std::ostream& Junior::show(std::ostream& os)const
	{
		return os << inform << " Estimates:"<< app[0]<<" "<< app[1] << " " << app[2] << " " << app[3] << " " << app[4] << std::endl;
	}
	std::ostream& Senior::show(std::ostream& os)const
	{
		return os << inform << "Estimates:" << app[0] << " " << app[1] << " " << app[2] << " " << app[3] <<"\n direction of the topic of the UIR:"<< 
			direction<<"\n place of execution:"<< place<<"\n evaluations of the manager and the commission:"<< commisiaon[0]<<" "<< commisiaon[1] << std::endl;
	}
	std::ostream& Graduete::show(std::ostream& os)const
	{
		return os << inform << "direction of the DP topic:" <<direction << "\n place of execution:" << 
			place << "\n evaluations of the supervisor, reviewer and the GEC:" << commisiaon[0] << " " << commisiaon[1] << " " << commisiaon[2] << std::endl;
	}
	std::ostream& operator <<(std::ostream &os, const Student &p)
	{
		return p.show(os);
	}
	std::istream& Junior::get(std::istream& is)
	{
		is >> inform;
		std::cout << "Enter Estimates: " << std::endl;
		return is  >> app[0]>> app[1] >> app[2] >> app[3] >> app[4];
	}
	std::istream& Senior::get(std::istream& is)
	{
		is >> inform;
		std::cout << "Enter Estimates: " << std::endl;
		is >> app[0] >> app[1] >> app[2] >> app[3];
		std::cout << "Enter direction of the topic of the UIR: " << std::endl;
		is >> direction;
		std::cout << "Enter place of execution: " << std::endl;
		is >> place;
		std::cout << "Enter evaluations of the manager and the commission: " << std::endl;
		return is >> commisiaon[0]>> commisiaon[1];
	}
	std::istream& Graduete::get(std::istream& is)
	{
		is >> inform;
		std::cout << "Enter direction of the DP topic: " << std::endl;
		is >> direction;
		std::cout << "Enter place of execution: " << std::endl;
		is >> place;
		std::cout << "Enter evaluations of the supervisor, reviewer and the GEC: " << std::endl;
		return is >> commisiaon[0] >> commisiaon[1] >> commisiaon[2];
	}
	std::istream& operator >>(std::istream &is, Student &p)
	{
		return p.get(is);
	}
	
};
