#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "resource.h"
#include "member.h"
using namespace std;

class library{
	private:
		vector<member> mem;
		vector<resource> res;
		int res_num;
		int mem_num;
	public:
		void set_resource();
		void lets_party();
		void hustler(int yy, int mm, int dd, string r_type, string r_name, string in_op, string m_type, string m_name);
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
	int yy = 0;
	int mm = 0;
	int dd = 0;
	int i = 0;
	cin >> ymd;
	cin >> rtype;
	cin >> rname;
	cin >> op;
	cin >> mtype;
	cin >> mname;
	cout << "Op_#\tReturn_code\tDescription" << endl;
	while(!cin.eof()){
		cin >> ymd;
		cin >> rtype;
		cin >> rname;
		cin >> op;
		cin >> mtype;
		cin >> mname;
		if(cin.eof()) break;
		i++;
		ybuf = ymd.substr(0, 2);
		yy = stoi(ybuf);
		mbuf = ymd.substr(3, 2);
		mm = stoi(mbuf);
		dbuf = ymd.substr(6, 7);
		dd = stoi(dbuf);
		cout << i << "\t";
		hustler(yy, mm, dd, rtype, rname, op, mtype, mname);
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
