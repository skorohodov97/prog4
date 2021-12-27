#pragma once
#include <iostream>
namespace Students {
	class PI {
	private:
		std::string surname,index;// ������� � ��������, ������ ������
		double chair;//����� ������������� �������
	public:
		PI(std::string surname0="", std::string index0 = "",double chair0=0) :surname(surname0), index(index0), chair(chair0) {}
		friend std::ostream& operator <<(std::ostream &,const PI &);// ����� ���������� � ��������
		friend std::istream& operator >>(std::istream &, PI &);
		std::string getS() const { return surname; }
		std::string getInd() const { return index; }
		double getCh() const { return chair; }
		PI & setS(std::string a) { surname =a; return *this;}
		PI & setInd(std::string a) { index = a; return *this; }
		PI & setCh(double a) {chair = a; return *this;}

	};
	class Student {
	protected:
		virtual std::ostream& show(std::ostream&)const = 0;
		virtual std::istream& get(std::istream&) = 0;
		PI inform;
	public:
		virtual Student* clone()const = 0;
		Student():inform() {};
		friend std::ostream& operator <<(std::ostream &, const Student &);
		friend std::istream& operator >>(std::istream &, Student &);
		virtual int iAm()const = 0;// ����� ��������� ��������
		//virtual double transfer()const = 0;//��������� ��������  � ������ ������
		//virtual double Egroup()const = 0;//�������� ������ ������� ������; 
		virtual int Estim(int *a)const = 0;
		virtual ~Student() {}
	};
	class Junior :public Student {
	protected:
		//PI inform;//���������� � ��������
		int app[5] = { 0, 0, 0,0,0 };// ������
		 std::ostream& show(std::ostream&)const;//����� ������
		 std::istream& get(std::istream&);
	public:
		Junior() :Student() { for (int i = 0; i < 5; ++i) app[i] = 0; }
		Junior(std::string surname0 , std::string index0, double chair0, int a[5] = { 0 });
		Junior(const PI &p, int a[5] = { 0 });
		virtual Junior* clone() const
		{
			return new Junior(*this);
		}
		virtual int iAm()const { return 1; }
		virtual int Estim(int *a)const { for (int i = 0; i < 5; ++i) a[i]=app[i]; return 5; };
		//virtual double transfer() const;
		//virtual double Egroup() const;
	};
	class Senior :public Student {
	protected:
		//PI inform;//���������� � ��������
		int app[4] = { 0, 0, 0,0 };//������
		std::string direction,place;//����������� ���� ���, ����� ����������
		int commisiaon[2] = { 0, 0 };// ������ ������������ � ������� 
		virtual std::ostream& show(std::ostream&)const;//��������  ���������� � ���� �������������� ������ � � ����� ���������� ������; 
		virtual std::istream& get(std::istream&);//�������� ��� ����������
	public:
		Senior(std::string direction0 = "", std::string place0 = "") :Student(), direction(direction0), place(place0) { for (int i = 0; i < 4; ++i) { app[i] = 0; commisiaon[i / 2] = 0; } }
		Senior(std::string surname0, std::string index0, double chair0, int a[4] = { 0 }, std::string direction0 = "", std::string place0 = "", int *commisiaon0 = { 0 });
		Senior(const PI &p, int a[4] = { 0 }, std::string direction0 = "", std::string place0 = "", int *commisiaon0 = { 0 });
		virtual Senior* clone()const
		{
			return new Senior(*this);
		}
		virtual int iAm()const { return 2; }
		virtual int Estim(int *a)const { for (int i = 0; i < 4; ++i) a[i] = app[i]; for (int i = 4; i < 6; ++i) a[i] = commisiaon[i-4]; return 6; };
		//virtual double transfer()const;
		//virtual double Egroup()const;
	};
	class Graduete :public Student {
	protected:
		//PI inform;//���������� � ��������
		std::string direction, place;//����������� ���� ��, ����� ����������
		int commisiaon[3] = { 0,0,0 };//������ ������������, ���������� � ��� 
		virtual std::ostream& show(std::ostream&)const;//��������  ���������� � ���� �������������� ������ � � ����� ���������� ������; 
		virtual std::istream& get(std::istream&);//�������� ��� ����������
	public:
		Graduete(std::string direction0 = "", std::string place0 = "") :Student(), direction(direction0), place(place0) { for (int i = 0; i < 2; ++i)  commisiaon[i] = 0;  }
		Graduete(std::string surname0, std::string index0, double chair0, std::string direction0 = "", std::string place0 = "", int *commisiaon0 = { 0 });
		Graduete(const PI &p, std::string direction0 = "", std::string place0 = "", int *commisiaon0 = { 0 });
		virtual Graduete* clone()const
		{
			return new Graduete(*this);
		}
		virtual int iAm()const { return 3; }
		virtual int Estim(int *a)const {  for (int i = 0; i < 2; ++i) a[i] = commisiaon[i]; return 3; };
		//virtual double transfer()const;
		//virtual double Egroup()const;
	};

};