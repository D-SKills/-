#ifndef H_ERR
#define H_ERR
#include<iostream>
#include<string>
using namespace std;
class Error
{
	int place;
	std::string type;
public:
	Error(){}
	Error(int i,std::string t)
	{
		place = i;
		type = t;
	}
	void set(int i,std::string t)
	{
		place = i;
		type = t;
	}
	void proceed()
	{
		throw *this;
	}
	std::string getType()
	{
		return type;
	}
	friend ostream& operator<<(ostream& out, Error& error)
	{
		out <<error.place << " " << error.type;
		return out;
	}

};
#endif H_ERR