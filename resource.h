#include <iostream>
#include <string>
#include <vector>
using namespace std;

class resource{
	private:
		string re_name;
		string re_type;
		string person;
		int date[3];
		int empty;
	public:
		void set(string title, string type);
		string get_title();
		string get_name();
		int get_empty();
		string get_retdate();
		void lets_borrow(string name, int yy, int mm, int dd);
		void lets_back();
};
class Book:public resource{
};
void resource::set(string title, string type){
	re_name = title;
	re_type = type;
	date[0] = 0;
	date[1] = 0;
	date[2] = 0;
	empty = 1;
}

string resource::get_title(){
	return re_name;
}
string resource::get_name(){
	return person;
}
int resource::get_empty(){
	return empty;
}
string resource::get_retdate(){
	int d;
	int rdate[3];
	string buf;
	string ret;
	d = date[0]*360 + (date[1]-1)*30 + (date[2]-1) + 13;
	rdate[0] = d/360;
	rdate[1] = (d%360)/30+1;
	rdate[2] = (d%360)%30+1;
	if(rdate[0] < 10) ret = "0" + to_string(rdate[0]) + "/";
	else ret = to_string(rdate[0]) + "/";
	if(rdate[1] < 10) ret = ret + "0" + to_string(rdate[1]) + "/";
	else ret = ret + to_string(rdate[1]) + "/";
	if(rdate[2] < 10) ret = ret + "0" + to_string(rdate[2]);
	else ret = ret + to_string(rdate[2]);
	return ret;
}

void resource::lets_borrow(string name, int yy, int mm, int dd){
	person = name;
	date[0] = yy;
	date[1] = mm;
	date[2] = dd;
	empty = 0;
}

void resource::lets_back(){
	empty = 1;
}

