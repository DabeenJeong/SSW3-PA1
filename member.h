#include <iostream>
#include <string>
#include <vector>
using namespace std;

class member{
	private:
		string mem_name;
		string mem_type;
		int borrow;
		int restricted;
		int date[3];
	public:
		void set_name(string in_name, string in_type);
		string get_name();
		int get_borrow();
		int get_restrict(int yy, int mm, int dd);
		string get_freedate();
		string get_bdate();
		void lets_borrow(int yy, int mm, int dd);
		int lets_back(int yy, int mm, int dd, int rest);
		int com_date(int yy, int mm, int dd);
};
class Undergraduate:public member{
};
void member::set_name(string in_name, string in_type){
	mem_name = in_name;
	mem_type = in_type;
	borrow = 0;
	restricted = 0;
	date[0] = 0;
	date[1] = 0;
	date[2] = 0;
}
string member::get_name(){
	return mem_name;
}
int member::get_borrow(){
	return borrow;
}
int member::get_restrict(int yy, int mm, int dd){
	int rdate;
	int indate;
	if(restricted > 0){
		rdate = date[0]*360 + (date[1]-1)*30 + (date[2]-1) + restricted;
		indate = yy*360 + (mm-1)*30 + dd-1;
		if((indate-rdate) > 0) restricted = 0;
	}
	return restricted;
}
string member::get_freedate(){
	string ret;
	int days;
	int rdate[3];
	days = date[0]*360 + (date[1]-1)*30 + (date[2]-1) + restricted;
	rdate[0] = days/360;
	rdate[1] = (days%360)/30 + 1;
	rdate[2] = (days%360)%30 + 1;
	if(rdate[0] < 10) ret = "0" + to_string(rdate[0]) + "/";
	else ret = to_string(rdate[0]) + "/";
	if(rdate[1] < 10) ret = ret + "0" + to_string(rdate[1]) + "/";
	else ret = ret + to_string(rdate[1]) + "/";
	if(rdate[2] < 10) ret = ret + "0" + to_string(rdate[2]);
	else ret = ret + to_string(rdate[2]);
	return ret;
}
string member::get_bdate(){
	string ret;
	if(date[0] < 10) ret = "0" + to_string(date[0]) + "/";
	else ret = to_string(date[0]) + "/";
	if(date[1] < 10) ret = ret + "0" + to_string(date[1]) + "/";
	else ret = ret + to_string(date[1]) + "/";
	if(date[2] < 10) ret = ret + "0" + to_string(date[2]);
	else ret = ret + to_string(date[2]);
	return ret;
}
void member::lets_borrow(int yy, int mm, int dd){
	borrow++;
	date[0] = yy;
	date[1] = mm;
	date[2] = dd;
}
int member::lets_back(int yy, int mm, int dd, int rest){
	borrow--;
	date[0] = yy;
	date[1] = mm;
	date[2] = dd;
	if(rest < 14) restricted = 0;
	restricted = rest-13;
	return restricted;
}
int member::com_date(int yy, int mm, int dd){
	int m_date;
	int b_date;
	m_date = date[0]*360 + (date[1]-1)*30 + (date[2]-1);
	b_date = yy*360 + (mm-1)*30 + (dd-1);
	return (b_date - m_date);
}
