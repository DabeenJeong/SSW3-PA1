# System Software experiment3 PA1

This program is Library management program.
The structure of code has 3 classes(Library, Resource, Member).

## Library class

- Library class manage other 2 classes(Resource, Member)
- Library class get inputs and use them by using functions in other classes.

```
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
```

- In library class there are vector of member&resource and number of members&resource.

### set resource

```
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
```

- set resource fuction reads "resource.dat" and sets values of resources in vector of resource

### lets party

```
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
```

- lets party function get inputs by the console and store them in different variables to call hustler fuction.

### hustler

```
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
		if(mem.at(i).cmp_name(m_name) == 0) break;
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
```

- hustler function is main opertion fuction in Library class.
- hustler has two part of operation.
	- If resource is not exist it will print return code 1 return immidiately.
	- If op code is B, hustler check cases that borrow book(return code : 2, 4, 5, 6). If input don't have any other limitations, it calls lets borrow function of member&resource and return.
	- If op code is R, hustler check cases that return book(return code : 3, 7). In this case input don't have limitaion in 3, it calls lets borrow function of member&resource and return.(in 7 hustler also calls lets back function, but it will return immidiately) 

## Resource class

- Resource class manages resources.(In this project only book)
- Resource class returns values to identify that operation is wrong or not and commits values in borrow and return operation.

```
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
```

- In resource class there are name&type of resource, name of member who borrow it, date that resource had been borrowed and value to identify it is empty or not.

### set

```
void resource::set(string title, string type){
	re_name = title;
	re_type = type;
	date[0] = 0;
	date[1] = 0;
	date[2] = 0;
	empty = 1;
}
```

- set function sets name and type of resource and initial of other values in this class.

### get title, get name, get empty

```
string resource::get_title(){
	return re_name;
}
string resource::get_name(){
	return person;
}
int resource::get_empty(){
	return empty;
}
```

- These three functions return values of resource class.


### get retdate

```
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
```

- get retdate function return expected return date of resource in string.

### lets borrow, lets back

```
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
```

- These two function change values when that resource is borrowed or returned.

## Member class

- Member class manages members.(in this project Undergraduate only)
- Member class returns values to identify that operation is wrong or not and commits values in borrow and return operation.

```
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
```

- In member class there are name&type of member, date that member borrowed and value to identify he or she borrow resource or not.

### set name

```
void member::set_name(string in_name, string in_type){
	mem_name = in_name;
	mem_type = in_type;
	borrow = 0;
	restricted = 0;
	date[0] = 0;
	date[1] = 0;
	date[2] = 0;
}
```

- set name function sets name&type of member and initial values of that class.

### get name, get borrow, get restrict

```
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
```

- These three function return value of member.
- In get restrict function there is a process of indentification that member is restricted or not.

### get freedate

```
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
```

- get freedate function return end date of member's restriction.

### get bdate 

```
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
```

- get bdate function return date that member borrowed resource.

### lets borrow, lets back

```
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
```

- These two function change values of member in cases borrow and return operation.

### com date

```
int member::com_date(int yy, int mm, int dd){
	int m_date;
	int b_date;
	m_date = date[0]*360 + (date[1]-1)*30 + (date[2]-1);
	b_date = yy*360 + (mm-1)*30 + (dd-1);
	return (b_date - m_date);
}
```

- com date function calculate difference between borrowed date and access date.



