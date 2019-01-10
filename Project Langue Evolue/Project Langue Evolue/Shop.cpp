#include"Shop.h"
#include<iostream>
#include<iomanip>
#include<fstream>
#include <algorithm>

/**********************************************
*              Useful Functions               *
***********************************************/
bool yes(char x) {
	while (x != 'Y' && x != 'y' && x != 'n' && x != 'n' ) {
		std::cin >> x;
	}
	return (x == 'Y' || x == 'y') ? true : false;
}
void Clear() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template<typename ABC>
void Read(ABC & a) {
	std::cin >> a;
	while (std::cin.fail()) {
		Clear();
		std::cin >> a;
	}
}



/**********************************************
*            Customer Functions               *
***********************************************/
Customer::Customer(bool o) {
	if (o)return;
	setName();
	setMembership();
	setCredit();
	setAddress();
	setEmail();
	setPhone();
}
Customer::Customer(std::string n, membership m, long c, std::string ad, std::string e, int p)
{
	setName(n);
	setMembership(m);
	setCredit(c);
	setAddress(ad);
	setEmail(e);
	setPhone(p);
}

bool Customer::avCredit()const {
	return (credit != 0) ? true : false;
}
bool Customer::avPhone()const {
	return (phone != 0) ? true : false;
}
bool Customer::avEmail()const {
	return (email=="NULL") ? false : true;
}
bool Customer::avAddress()const {
	return (address == "NULL") ? false : true;
}
bool Customer::isEmail(std::string const& address) const{
	size_t at_index = address.find_first_of('@', 0);
	return at_index != std::string::npos
		&& address.find_first_of('.', at_index) != std::string::npos;
}
void Customer::trim(std::string& s)
{
	size_t p = s.find_first_not_of(" \t");
	s.erase(0, p);

	p = s.find_last_not_of(" \t");
	if (std::string::npos != p)
		s.erase(p + 1);
	std::string::iterator new_end =
		std::unique(s.begin(), s.end(),
			[=](char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }
	);
	s.erase(new_end, s.end());
}

void Customer::setPhone(int n) {
		phone = n;
}
void Customer::setPhone() {
	char a;
	std::cout << "Enter Phone number?[Y/N]: ";
	std::cin >> a;
	if (yes(a)) {
		std::cout << "Enter phone Number: ";
		Read<int>(phone);
	}
	else
		phone = 0;
}
void Customer::setCredit(long n) {
		credit = n;
}
void Customer::setCredit() {
	char a;
	Clear();
	std::cout << "Enter credit card?[Y/N]: ";
	std::cin >> a;
	Clear();
	if (yes(a)) {
		std::cout << "Enter Credit card Number: ";
		Read<long>(credit);
		Clear();
	}
	else {
		credit = 0;
	}
}
void Customer::setAddress(std::string s) {
		address = s;
}
void Customer::setAddress() {
	char a;
	std::cout << "Enter Address?[Y/N]: ";
	std::cin >> a;
	if (yes(a)) {
		do {
			std::cout << "Enter Address: ";
			Clear();

			std::getline(std::cin, address);
			trim(address);
		} while (address == "\n");
	}
	else {
		address = "NULL";
	}
		
}
void Customer::setName(std::string s) {
	name = s;
}
void Customer::setName() {
		std::cout << "Enter name: ";
		do {
			std::cin.ignore();
			std::getline(std::cin, name);
		} while (name == "\0");
		trim(name);
}
void Customer::setEmail(std::string s) {
		email = s;
}
void Customer::setEmail() {
	char a;
	std::cout << "Enter Email?[Y/N]: ";
	std::cin >> a;
	if (yes(a)) {
		do {
			std::cout << "Enter Email: ";
			std::cin.ignore();
			std::getline(std::cin, email);
			trim(email);
		} while (!isEmail(email) || email=="\n" );

	}
	else {
		email = "NULL";
	}
		
}
void Customer::setMembership(membership m) {
	membership_type = m;
}
void Customer::setMembership() {
	char t;
	std::cout << "input P(Premium), G(Gold), S(Silver), or N(None): ";
	std::cin >> t;
	switch (t) {
	case 'P':
	case 'p':
		membership_type = Premium;
		break;
	case 'G':
	case 'g':
		membership_type = Gold;
		break;
	case 'S':
	case 's':
		membership_type = Silver;
		break;
	default:
		membership_type = None;
		break;
	}
}

int Customer::getDiscount()const {
	int x = isOnline() * 10;
	switch (membership_type) {
	case Premium:
		return x+20;
	case Gold:
		return x+15;
	case Silver:
		return x+10;
	default:
		return x+0;
	}
}
bool Customer::isOnline()const {
	return false;
}
std::string Customer::getName()const {
	return name;
}
std::string Customer::getEmail()const {
	return email;
}
std::string Customer::getAddress()const {
	return address;
}
long Customer::getCredit()const {
	return credit;
}
int Customer::getPhone()const {
	return phone;
}
membership Customer::getMem()const {
	return membership_type;
}
std::string Customer::strMem() {
	switch (membership_type) {
	case Premium:
		return "Premium";
	case Gold:
		return "Gold";
	case Silver:
		return "Silver";
	default:
		return "None";
	}
}

void Customer::remCredit() {
	setCredit(0);
}
void Customer::remPhone() {
	setPhone(0);
}
void Customer::remAddress() {
	setAddress("NULL");
}
void Customer::remEmail() {
	setEmail("NULL");
}

bool Customer::isValid(bool on){
	if (on) {
		return avAddress() && avCredit() && avEmail() && avPhone();
	}
	else
		return true;
}



/**********************************************
*        Online Customer Functions            *
***********************************************/
OnCustomer::OnCustomer(bool o) {
	setName();
	setMembership();
	setCredit();
	setAddress();
	setEmail();
	setPhone();
}
OnCustomer::OnCustomer(std::string n, membership m, long c, std::string ad, std::string e, int p)
{
	Customer::setName(n);
	Customer::setMembership(m);
	Customer::setCredit(c);
	Customer::setAddress(ad);
	Customer::setEmail(e);
	Customer::setPhone(p);
}

bool OnCustomer::isOnline()const {
	return true;
}

void OnCustomer::setEmail() {
	std::string s;
	std::cout << "Enter Email: ";
	std::cin.ignore();
	std::getline(std::cin, s);
	Customer::setEmail(s);
}
void OnCustomer::setAddress() {
	std::string s;
	std::cout << "Enter Address: ";
	std::cin.ignore();
	std::getline(std::cin, s);
	Customer::setAddress(s);
}
void OnCustomer::setCredit() {
	long c;
	std::cout << "Enter Credit card Number: ";
	std::cin >> c;
	Customer::setCredit(c);
}
void OnCustomer::setPhone() {
	int p;
	std::cout << "Enter phone Number: ";
	std::cin >> p;
	Customer::setPhone(p);
}





/**********************************************
*               Item Functions                *
***********************************************/
Item::Item(std::string s, double p, int c) {
	name = s;
	price = p;
	count = c;
}

void Item::setName(std::string a) {
	name = a;
}
void Item::setPrice(double p) {
	price = p;
}
void Item::setCount(int c) {
	count = c;
}

int Item::getCount()const {
	return count;
}
double Item::getPrice()const {
	return price;
}
std::string Item::getName()const {
	return name;
}

void Item::buy(int c) {
	Item::setCount(Item::getCount() - c);
	//count-=c;
}






/**********************************************
*        purchase operation Functions         *
***********************************************/
purchase_operation::purchase_operation(Customer *c) {
	if (c == NULL) {
		return;
	}
	customer = c;
	items.clear();
	discount = customer->getDiscount();
	price = 0;
}

Customer* purchase_operation::getCustomer() {
	return customer;
}
std::vector<std::pair<Item*, int>>* purchase_operation:: getList() {
	return &items;
}
int purchase_operation::getPos(Item *it) {
	for (int i = 0; i < items.size(); i++) {
		if (items[i].first == it)
			return i;
	}
	return -1;
}
double purchase_operation::getPrice() {
	return price;
}
int purchase_operation::getDiscount() {
	return discount;
}

void purchase_operation::addItem(Item* i, int c) {
	if (i->getCount() == 0)
		return;
	if (c < 0)
		return;
	if(getPos(i )!=-1){
		incrementCount(i);
		return;
	}
	if (c > i->getCount()) {
		c = i->getCount();
		std::cout << "\nRequested quantity of " << i->getName()<<" is not available\n";
	}
	items.push_back(std::make_pair(i, c));
	updatePrice();
}
void purchase_operation::removeItem(Item *it) {
	int i = getPos(it);
	if (i == items.size())
		return;
	items.erase(items.begin() + i);
	updatePrice();
}
void purchase_operation::incrementCount(Item*it) {
	int i = getPos(it);
	if (items[i].second == it->getCount())
		return;
	items[i].second++;
	updatePrice();
}
void purchase_operation::decrementCount(Item*it) {
	int i = getPos(it);
	if (items[i].second>1)
		items[i].second--;
	else if (items[i].second == 1) {
		removeItem(it);
	}
	updatePrice();
}
void purchase_operation::setCount(Item * I, int c) {
	if (c == 0) {
		removeItem(I);
	}
	else if (c < 0) {
		return;
	}

	else {
		int i = getPos(I);
		if (c > I->getCount())
			c = I->getCount();
		items[i].second = c;
	}
	updatePrice();
}
void purchase_operation::updatePrice() {
	price = 0;
	for (int i = 0; i < items.size(); i++) {
		price += (items[i].first)->getPrice()*items[i].second;
	}
}
void purchase_operation::clear() {
	items.clear();
	price = 0;
}
void purchase_operation::display(bool header) {
	if(header)
		std::cout << "----------CART----------------------------------------------------------------------" << std::endl;
	std::cout <<std::setw(4)<<" "<< std::setw(27) << std::left << "Item Name" << std::setw(15) << "Unit Price" << std::setw(15) << "Quantity" << std::setw(15) << "Price" << std::endl;
	for (int i = 0; i < items.size(); i++) {
		std::cout <<std::setw(3)<<std::right<<i+1<<std::left<<"-"<< std::setw(27) << items[i].first->getName() <<"$"<< std::setw(14) << items[i].first->getPrice()<< std::setw(15) << items[i].second <<"$"<< std::setw(14) << (items[i].first)->getPrice()*items[i].second <<std::endl;
	}
	std::cout << std::left<<std::endl << std::setw(55) << " " << std::setw(10) << "Total: " << std::setw(5)<< std::right<< "$"<<price;
	std::cout << std::left << std::endl<< std::setw(55) << " " << std::setw(10) << "Discount: " << std::setw(6)<<std::right<< discount<<"%";
	std::cout << std::left << std::endl << std::setw(55) << " " << std::setw(10) << "Final: " << std::setw(5) <<std::right<< "$"<<price-price*discount/100;

	std::cout << std::left<<std::endl<< "------------------------------------------------------------------------------------" << std::endl;

}






/**********************************************
*         accounting system Functions         *
***********************************************/
void accounting_system::newOperation(purchase_operation p) {
	std::ofstream fout;
	fout.open("accounting_system.txt",std::ios_base::app);
	std::vector<std::pair<Item*, int>>* list = p.getList();
	fout << std::left<<std::setw(10) << ((p.getCustomer()->isOnline()) ? "Online" : "On-Market") << std::endl;
	fout << std::setw(50) << p.getCustomer()->getName() << std::endl;
	fout << std::setw(4) << " " << std::setw(27) << std::left << "Item Name" << std::setw(15) << "Unit Price" << std::setw(15) << "Quantity" << std::setw(15) << "Price" << std::endl;
	for (int i = 0; i < list->size(); i++) {
		fout << std::setw(3) << std::right << i + 1 << std::left << "-" << std::setw(27) << list->at(i).first->getName() << "$" << std::setw(14) << list->at(i).first->getPrice() << std::setw(15) << list->at(i).second << "$" << std::setw(14) << list->at(i).first->getPrice()*list->at(i).second << std::endl;
	}

	fout << std::endl << std::setw(55) << " " << std::setw(10) << "Total: " << std::setw(5) << p.getPrice();
	fout << std::endl << std::setw(55) << " " << std::setw(10) << "Discount: " << std::setw(5) << p.getDiscount();
	fout << std::endl << std::setw(55) << " " << std::setw(10) << "Final: " << std::setw(5) << p.getPrice() - p.getPrice() * p.getDiscount() / 100 << std::endl;
	fout << "------------------------------------------------------------------------------------" << std::endl;
}

