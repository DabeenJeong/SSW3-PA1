#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class space{
	private:
		string name;
		string S_type;
		int time;
	public:
		string get_type();
		virtual void set_space() = 0;
		virtual int get_floor() = 0;
		virtual int get_num() = 0;
		virtual void rent_space() = 0;
		virtual int back_space() = 0;
};
class study_room:public space{
	private:
		int num;
	public:
		int get_num();
		void rent_space();
};
class seat:public space{
	private:
		int floor;
		int num;
	public:
		void set_space();
		int get_floor();
		int get_num();
		void rent_space();
		int back_space();
};
string space::get_type(){
	return S_type;
}
int study_room::get_num(){
	return num;
}
void study_room::rent_space(int r_num){
	num = r_num;
}
void seat:set_seat(){
	floor = in_floor;
	num = 1;
}
int seat::get_floor(){
	return floor;
}
int seat::get_num(){
	return num;
}
void seat::rent_space(){
	num++;
}
int seat::back_space(){
	num--;
	return num;
}
