#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "resource.h"
#include "member.h"
#include "space.h"
using namespace std;

class library{
	private:
		vector<member> mem;
		vector<resource> res;
		seat* sea[3][50];
		study_room* room[10];
		int res_num;
		int mem_num;
	public:
		void set_resource();
		void lets_party();
		void hustler(int yy, int mm, int dd, string r_type, string r_name, string in_op, string m_type, string m_name);
		void hustler2(int yy, int mm, int dd, int tt, string s_type, int s_num, string in_op, string m_type, string m_name, int num_of_m, int time_p);
};
void library::set_resource(){
	int i = 0;
	Book temp;
	ifstream rin("resource.dat");
	string in_type;
	string in_name;
	rin.is_open();
	rin >> in_type;
	rin >> in_name;
	while(!rin.eof()){
		rin >> in_type;
		rin >> in_name;
		if(rin.eof()) break;
		if(in_type.compare("Book") == 0) res.push_back(temp);
		res.at(i++).set(in_name, in_type);
	}
	res_num = i;
	mem_num = 0;
}
void library::lets_party(){
	string ymd;
	string rtype;
	string rname;
	string op;
	string mtype;
	string mname;
	string ybuf;
	string mbuf;
	string dbuf;
	string ymdt;
	string stype;
	int snum = 0;
	string s_op;
	string s_mtype;
	string s_mname;
	int num_of_m;
	int time_p = 0;
	int yy = 0;
	int mm = 0;
	int dd = 0;
	int tt = 0;
	int i = 0;
	int j = 0;
	ifstream min("input.dat");
	ifstream sin("space.dat");
	min >> ymd;
	min >> rtype;
	min >> rname;
	min >> op;
	min >> mtype;
	min >> mname;
	cout << "Op_#\tReturn_code\tDescription" << endl;
	while(!min.eof()){
		min >> ymd;
		min >> rtype;
		min >> rname;
		min >> op;
		min >> mtype;
		min >> mname;
		if(min.eof()) break;
		i++;
		ybuf = ymd.substr(0, 2);
		yy = stoi(ybuf);
		mbuf = ymd.substr(3, 2);
		mm = stoi(mbuf);
		dbuf = ymd.substr(6, 2);
		dd = stoi(dbuf);
		cout << i << "\t";
		hustler(yy, mm, dd, rtype, rname, op, mtype, mname);
	}
	sin >> ymdt;
	sin >> stype;
	sin >> snum;
	sin >> s_op;
	sin >> s_mtype;
	sin >> s_mname;
	sin >> num_of_m;
	sin >> time_p;
	while(!sin.eof()){
		sin >> ymdt;
		sin >> stype;
		sin >> snum;
		sin >> s_op;
		sin >> s_mtype;
		sin >> s_mname;
		if(s_op.compare("B") == 0){
			sin >> num_of_m;
			sin >> time_p;
		}
		if(sin.eof()) break;
		j++;
		ybuf = ymdt.substr(0, 4);
		cout  << endl << ybuf << endl;
		yy = stoi(ybuf);
		mbuf = ymdt.substr(5, 2);
		mm = stoi(mbuf);
		dbuf = ymdt.substr(8, 2);
		dd = stoi(dbuf);
		ybuf = ymdt.substr(11, 2);
		tt = stoi(ybuf);
		hustler2(yy, mm, dd, tt, stype, snum, s_op, s_mtype, s_mname, num_of_m, time_p);
	}
}
void library::hustler(int yy, int mm, int dd, string r_type, string r_name, string in_op, string m_type, string m_name){
	Undergraduate temp;
	int r_index;
	int m_index;
	int rest;
	int i;
	for(i = 0; i < res_num; i++){
		if(r_name.compare(res.at(i).get_title()) == 0) break;
	}
	if(i == res_num){
		cout << "1\t" << "Non exist resource." << endl;
		return;
	}
	else r_index = i;
	for(i = 0; i < mem_num; i++){
		if(m_name.compare(mem.at(i).get_name()) == 0) break;
	}
	if(i == mem_num){
		if(m_type.compare("Undergraduate") == 0) mem.push_back(temp);
		mem.at(mem_num).set_name(m_name, m_type);
		m_index = mem_num++;
	}
	else m_index = i;
	if(in_op.compare("B") == 0){
		if(m_type.compare("Undergraduate") == 0){
			if(mem.at(m_index).get_borrow()){
				cout << "2\t" << "Exceeds your possible number of borrow. Possible # of borrows: " << mem.at(m_index).get_borrow() << endl;
				return;
			}
		}
		if((res.at(r_index).get_name()).compare(m_name) == 0){
			cout << "4\t" << "You already borrowed this book at " << mem.at(m_index).get_bdate() << endl;
			return;
		}
		if(!res.at(r_index).get_empty()){
			cout << "5\t" << "Other member already borrowed this book. This book will be returned at " << res.at(r_index).get_retdate() << endl;
			return;
		}
		if(m_type.compare("Undergraduate") == 0){
			if(mem.at(m_index).get_restrict(yy, mm, dd) > 0){
				cout << "6\t" << "Restricted member until " << mem.at(m_index).get_freedate() << endl;
				return;
			}
		}
		mem.at(m_index).lets_borrow(yy, mm, dd);
		res.at(r_index).lets_borrow(m_name, yy, mm, dd);
	}
	else{
		if((res.at(r_index).get_name()).compare(m_name) != 0){
			cout << "3\t" << "You did not borrow this book." << endl;
			return;
		}
		if((rest = mem.at(m_index).com_date(yy, mm, dd)) > 0){
			mem.at(m_index).lets_back(yy, mm, dd, rest);
			res.at(r_index).lets_back();
			if(rest >= 14){
				cout << "7\t" << "Delayed return. You'll be restricted until ";
				cout << mem.at(m_index).get_freedate() << endl;
				return;
			}
			else{
				cout << "0\tSuccess." << endl;
				return;
			}
		}
	}
	cout << "0\tSuccess." << endl;
}
void library::hustler2(int yy, int mm, int dd, int tt, string s_type, int s_num, string in_op, string m_name, string m_type, int num_of_m, int time_p){
	Undergraduate temp;
	int i,j;
	int m_index;
	for(i = 0; i < mem_num; i++){
		if(m_name.compare(mem.at(i).get_name()) == 0) break;
	}
	if(i == mem_num){
		if(m_type.compare("Undergraduate") == 0) mem.push_back(temp);
		mem.at(mem_num).set_name(m_name, m_type);
		m_index = mem_num++;
	}
	else m_index = i;
	if(in_op.compare("B") == 0){
		if(s_type.compare("StudyRoom") == 0){
			if(s_num > 10 || s_num < 1){
				cout << "8\t" << "Invalid space id.\n";
				return;
			}
			if(tt < 9 || tt > 18){
				cout << "9\t" << "This space is not available now. Available from 09 to 18\n";
				return;
			}
			if(num_of_m > 6){
				cout << "12\t" << "Exceed available number.\n";
				return;
			}
			if(time_p > 3){
				cout << "13\t" << "Exceed available time.\n";
				return;
			}
			if(room[s_num]->get_empty() == 0){
				if(room[s_num]->com_ymdt(yy, mm, dd, tt) < 3){
					cout << "14\t" << "There is no remain space. This space is available after " << room[s_num]->ret_time() << ".\n";
				}
			}
			room[s_num]->rent_space(yy, mm, dd, tt, m_name);
			cout << "0\t Success.\n";
			return;
		}
		else{
			if(s_num > 3 || s_num < 1){
				cout << "8\t" << "Invalid space id.\n";
				return;
			}
			if((tt < 9 || tt > 18) && s_num == 3){
				cout << "9\t" << "This space is not available now. Available from 09 to 18\n";
				return;
			}
			if((tt < 9 || tt > 21) && s_num == 2){
				cout << "9\t" << "This space is not available now. Available from 09 to 21\n";
				return;
			}
			if(num_of_m > 1){
				cout << "12\t" << "Exceed available number.\n";
				return;
			}
			if(time_p > 3){
				cout << "13\t" << "Exceed available time.\n";
				return;
			}
			for(j = 0; j < 50; j++){
				if(sea[s_num][j]->get_empty() == 0){
					if(sea[s_num][j]->com_ymdt(yy, mm, dd, tt) < 3){
						cout << "14\t" << "There is no remain space. This space is available after " << sea[s_num][j]->ret_time() << ".\n";
					}
				}
				else break;
			}
			sea[s_num][j]->rent_space(yy, mm, dd, tt, m_name);
			cout << "0\t Success.\n";
			return;
		}
		if(mem.at(m_index).get_stype() != 0){
			if(mem.at(m_index).com_ymdt(yy, mm, dd, tt) < 3){
				cout << "11\t" << "You already borrowed this kind of space.\n";
				return;
			}
		}
	}
	else if(in_op.compare("R")){
		if(s_type.compare("StudyRoom") == 0){
			if(mem.at(m_index).get_stype() == 1){
				if(mem.at(m_index).com_ymdt(yy, mm, dd, tt) > 3){
					cout << "10\t" << "You did not borrow this place.\n";
					return;
				}
			}
			else{
				cout << "10\t" << "You did not borrow this place.\n";
				return;
			}
			room[s_num]->back_space();
			cout << "0\t Success.\n";
			return;

		}
		else{
			if(mem.at(m_index).get_stype() == 2){
				if(mem.at(m_index).com_ymdt(yy, mm, dd, tt) > 3){
					cout << "10\t" << "You did not borrow this place.\n";
					return;
				}
			}
			else{
				cout << "10\t" << "You did not borrow this place.\n";
				return;
			}
			for(j = 0; j < 50; j++){
				if(m_name.compare(sea[s_num][j]->get_name()) == 0){
					break;
				}
			}
			sea[s_num][j]->back_space();
			cout << "0\t Success.\n";
			return;
		}
	}
}
