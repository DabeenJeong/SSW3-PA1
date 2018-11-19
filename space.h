#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class space{
	private:
	public:
		virtual string get_name() = 0;
		virtual int com_ymdt(int tt) = 0;
		virtual int ret_time() = 0;
		virtual void set_space() = 0;
		virtual int get_empty() = 0;
		virtual void rent_space(int yy, int mm, int dd, int tt, string name_in) = 0;
		virtual void back_space() = 0;
};
class study_room:public space{
	private:
		string name;
		int date[3];
		int time;
		int empty;
	public:
		string get_name();
		int com_ymdt(int yy, int mm, int dd, int tt);
		int ret_time();
		void set_space();
		int get_empty();
		void rent_space(int yy, int mm, int dd, int tt, string name_in);
		void back_space();
};
class seat:public space{
	private:
		string name;
		int date[3];
		int time;
		int empty;
	public:
		string get_name();
		int com_ymdt(int yy, int mm, int dd, int tt);
		int ret_time();
		void set_space();
		int get_empty();
		void rent_space(int yy, int mm, int dd, int tt, string name_in);
		void back_space();
};
string study_room::get_name(){
	return name;
}
int study_room::com_ymdt(int yy, int mm, int dd, int tt){
	if(date[0] == yy){
		if(date[1] == mm){
			if(date[2] == dd){
				return tt - time;
			}
		}
	}
	return 24;
}
int study_room::ret_time(){
	return time + 3;
}
void study_room::set_space(){
	empty = 1;
}
int study_room::get_empty(){
	return empty;
}
void study_room::rent_space(int yy, int mm, int dd, int tt, string name_in){
	empty = 0;
	date[0] = yy;
	date[1] = mm;
	date[2] = dd;
	time = tt;
	name = name_in;
}
void study_room::back_space(){
	empty = 1;
}
string seat::get_name(){
	return name;
}
int seat::com_ymdt(int yy, int mm, int dd, int tt){
	if(date[0] == yy){
		if(date[1] == mm){
			if(date[2] == dd){
				return tt - time;
			}
		}
	}
	return 24;
}
int seat::ret_time(){
	return time + 3;
}
void seat::set_space(){
	empty = 50;
}
int seat::get_empty(){
	return empty;
}
void seat::rent_space(int yy, int mm, int dd, int tt, string name_in){
	empty = 0;
	date[0] = yy;
	date[1] = mm;
	date[2] = dd;
	if(tt < time)
	time = tt;
}
void seat::back_space(){
	empty++;
}
