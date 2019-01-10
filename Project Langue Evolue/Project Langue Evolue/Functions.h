#include<iostream>
#include<iomanip>
#include<algorithm>
#include<string>
#include<vector>
#include"shop.h"


#include<fstream>
using namespace std;
enum st { start, regist, login, OnProfile, Profile, shop, admin, cart, edit, checkout ,info,control};
void title() {
	ifstream i("title.txt");
	char a;
	while (!i.eof()) {
		a = i.get();
		cout << a;
	}
	i.close();
	cout << endl;
}
void clear() {
	std::cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
template<typename ABC>
void read(ABC & a) {
	cin >> a;
	while (cin.fail()) {
		clear();	
		cin >> a;
	}
}
string  trim(std::string s)
{
	size_t p = s.find_first_not_of(" \t");
	s.erase(0, p);

	p = s.find_last_not_of(" \t");
	if (string::npos != p)
		s.erase(p + 1);
	string::iterator new_end =
		unique(s.begin(), s.end(),
			[=](char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }
	);
	s.erase(new_end, s.end());
	return s;
}

bool Yes(char x) {
	while (x != 'Y' && x != 'y' && x != 'n' && x != 'n') {
		std::cin >> x;
	}
	return (x == 'Y' || x == 'y') ? true : false;
}

void Invalid() {
	cout << "Invalid!" << endl;
}
void printList(vector<Item> &items) {
	system("cls");
	cout << "----------Shop----------------------------------------------------------------------" << endl;
	for (int i = 0; i < items.size(); i++) {
		cout << right << setw(3) << i + 1 << "-" << setw(25) << left << items[i].getName() << setw(1) << right << "$" << setw(5) << left << items[i].getPrice() << setw(10) << "quantity" << items[i].getCount() << endl;
	}
}

vector<Item> load() {
	vector<Item> a;
	Item b;
	int x;
	ifstream inf;
	inf.open("Items.txt");
	string name;
	double p;
	getline(inf, name);
	b.setName(name);
	inf >> p;
	b.setPrice(p);
	inf >> x;
	b.setCount(x);
	a.push_back(b);
	while (!inf.eof()) {
		inf.ignore();
		getline(inf, name);
		b.setName(name);
		inf >> p;
		b.setPrice(p);
		inf >> x;
		b.setCount(x);
		a.push_back(b);
	}
	return a;

}

void loadcust(vector<Customer>& a, vector<OnCustomer>&b)
{
	ifstream inf;
	inf.open("customers.txt");
	inf.ignore(100, '\n');
	bool on;
	string n, ad, e;
	int m;
	long c;
	int p;
	while (!inf.eof()) {
		inf >> on;
		inf.ignore();
		getline(inf, n);
		inf >> m;
		inf >> c;
		inf.ignore();
		getline(inf, ad);
		getline(inf, e);
		inf >> p;
		if (on) {
			OnCustomer B(n, static_cast<membership>(m), c, ad, e, p);
			b.push_back(B);
		}
		else {
			Customer A(n, static_cast<membership>(m), c, ad, e, p);
			a.push_back(A);
		}
	}
}

void savecust(vector<Customer>&a, vector<OnCustomer>&b) {
	ofstream outf;
	outf.open("customers.txt");

	for (int i = 0; i < a.size(); i++)
		outf << endl << 0 << endl << a[i].getName() << endl << a[i].getMem() << endl << a[i].getCredit() << endl << a[i].getAddress() << endl << a[i].getEmail() << endl << a[i].getPhone();
	for (int i = 0; i < b.size(); i++)
		outf << endl << 1 << endl << b[i].getName() << endl << b[i].getMem() << endl << b[i].getCredit() << endl << b[i].getAddress() << endl << b[i].getEmail() << endl << b[i].getPhone();
	outf.close();
}
void save(vector<Item>& a)
{
	ofstream outf("Items.txt");
	outf << a[0].getName() << endl << a[0].getPrice() << "\t" << a[0].getCount();
	for (int i = 1; i < a.size(); i++)
		outf << endl << a[i].getName() << endl << a[i].getPrice() << "\t" << a[i].getCount();
	outf.close();
}
void printInfo(Customer *c) {
	cout <<setw(20)<<"1-Name: "<< c->getName() <<"{"<<c->strMem()<<"}"<< endl;
	cout << setw(20) << "2-Credit card: ";
	if (c->avCredit())
		cout << c->getCredit();
	cout << endl;
	cout << setw(20) << "3-Address: ";
	if (c->avAddress())
		cout << c->getAddress();
	cout << endl;
	cout << setw(20) << "4-Email: ";
	if (c->avEmail())
		cout << c->getEmail();
	cout << endl;
	cout << setw(20) << "5-Phone Number: ";
	if (c->avPhone())
		cout << c->getPhone();
	cout << endl;
}
