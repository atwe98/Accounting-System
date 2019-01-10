#include<iostream>
#include"Functions.h"
#include<iomanip>
#include<fstream>
#include<Windows.h>
using namespace std;

int main(){
	accounting_system System;
	st state = start;
	Customer* current=NULL;
	OnCustomer* Oncurrent;
	bool On, cash = true;
	int n, m, l, i;
	string name, s;
	char a;
	double d;

	vector<Customer>cust;
	cust.clear();
	vector<OnCustomer> oncust;
	oncust.clear();
	loadcust(cust, oncust);

	vector<Item>items;
	items.clear();
	items= load();

	
	purchase_operation op(NULL);
	while (true) {

		switch (state) {
		case start:
			system("cls");
			title();
			cout << endl;
			cout << "1-Register as new customer" << endl << "2-Login as old customer" << endl << "3-Enter as admin" << endl;
			read<int>(n);
			switch (n) {
			case 1:
				state = regist;

				break;
			case 2:
				state = login;
				break;
			case 3:
				state = admin;
			default:
				Invalid();
				break;
			} break;
		case regist:
			cout << "1-Online\n2-In-Market\n";
			read<int>(n);
			switch (n) {
			case 1:
				On = true;
				state = OnProfile;
				break;
			case 2:
				On = false;
				state = Profile;
				break;
			default:
				Invalid();
				break;
			} break;
		case OnProfile:
			Oncurrent = new OnCustomer(true);
			current = Oncurrent;
			oncust.push_back(*Oncurrent);
			current = &oncust[oncust.size() - 1];
			cout << "Welcome, " << current->getName() << endl;
			Sleep(1000);
			savecust(cust, oncust);
			state = shop;
			break;
		case Profile:
			current = new Customer(false);
			cust.push_back(*current);
			cout << "Welcome, " << current->getName() << endl;
			current = &cust[cust.size() - 1];
			savecust(cust, oncust);
			Sleep(1000);
			state = shop;
			break;
		case login:
			cout << "Enter your name: ";
			std::cin.ignore();
			getline(cin, name);
			cout << "Online Customer?[Y/N]: ";
			cin >> a;
			On = Yes(a);
			if (On) {
				for (i = 0; i < oncust.size(); i++) {
					if (_strcmpi((trim(oncust[i].getName())).c_str(), name.c_str()) == 0) {
						cout << "Welcome back, " << name << endl;
						current = &oncust[i];
						Sleep(1000);
						state = shop;
						break;
					}
				}
				if (i == oncust.size()) {
					Invalid();
					state = start;
				}
			}
			else {
				for (i = 0; i < cust.size(); i++) {
					if (_strcmpi((trim(cust[i].getName())).c_str(), name.c_str()) == 0) {
						cout << "Welcome back, " << name << endl;
						current = &cust[i];
						Sleep(1000);
						state = shop;
						break;
					}
				}
				if (i == cust.size()) {
					Invalid();
					state = start;
				}
			}
			break;

		case admin:
			system("cls");
			cout << "Enter Password: ";		//PASSWORD "123456789"
			cin.ignore();
			getline(cin, s);
			if (s == "123456789") {
				state = control;
				break;
			}
			state = start;
			break;

		case shop:
			printList(items);
			if (op.getCustomer() != current) {
				op = purchase_operation(current);
			}
			op.display();
			cout << "Enter Item Number to add to cart(0:cart		-5:profile):\n";
			read<int>(n);
			while (n != 0) {
				if (n > items.size())
					break;
				op.addItem(&(items[n - 1]), 1);
				printList(items);
				op.display();
				cout << "Enter Item Number to add to cart(0:cart		-5:profile):\n";
				cin >> n;

			}

			if (n == 0)
				state = cart;
			if (n == -5) {
				state = info;
				break;
			}
			break;

		case cart:
			system("cls");
			op.display();
			cout << "Enter Item Number to edit item (0:return to store	-1:checkout	  -2:clear cart		-5:Profile):\n";
			read<int>(n);
			switch (n) {
			case 0:
				state = shop;
				break;

			case -1:
				state = checkout;
				break;
			case -2:
				op.clear();
				state = shop;
				break;
			case -3:
				state = info;
				break;
			case -5:
				state = info;
				break;
			default:
				if (n > op.getList()->size()) {
					Invalid();
					break;
				}
				n = n - 1;
				state = edit;
				break;
			}
			break;
		case edit:
			system("cls");
			cout << "----------EDIT----------------------------------------------------------------------" << endl;
			cout << setw(4) << " " << setw(26) << left << "Item Name" << std::setw(15) << "Unit Price" << setw(15) << "Quantity" << setw(15) << "Price" << endl;
			cout << setw(4) << " " << setw(26) << op.getList()->at(n).first->getName() << "$" << setw(14) << op.getList()->at(n).first->getPrice() << setw(15) << op.getList()->at(n).second << "$" << setw(14) << op.getList()->at(n).second * op.getList()->at(n).first->getPrice() << endl;
			cout << endl << "------------------------------------------------------------------------------------" << endl;
			cout << "0: Cart\n1: Increment count\n2: Decrement count\n3: Set Count\n4:remove item\n ";
			read<int>(m);
			switch (m) {
			case 0:
				state = cart;
				break;
			case 1:
				op.incrementCount(op.getList()->at(n).first);
				break;
			case 2:
				if (op.getList()->at(n).second == 1)
					state = cart;
				op.decrementCount(op.getList()->at(n).first);
				break;
			case 3:
				cout << "Enter desired quantity: ";
				cin >> l;
				if (l == 0)
					state = cart;
				op.setCount(op.getList()->at(n).first, l);

				break;
			case 4:
				op.removeItem(op.getList()->at(n).first);
				state = cart;
				break;
			default:
				break;

			}
			break;
		case checkout:
			if (op.getList()->size() == 0 || !current->isValid(On)) {
				state = cart;
				break;
			}
			if (!On) {
			mark:
				if (current->avCredit()) {
					cout << "Credit Card available, choose payment method:\n1-cash\n2-credit card\n" << endl;
					read<int>(n);
					switch (n) {
					case 1:
						cash = true;
						break;
					case 2:
						cash = false;
						break;
					default:
						Invalid();
						cin >> n;
						goto mark;
					}
				}
				else
					cash = true;

			}
			else 
				cash = false;
			system("cls");
			cout << "----------RECEIPT-------------------------------------------------------------------\n";
			op.display(false);
			cout << current->getName() << endl;
			if (cash)
				cout << setw(20) << "Payment method: " << "cash" << endl;
			else
				cout << setw(20) << "Payment method: " << "Credit Card(" << current->getCredit() << ")" << endl;
			if (current->avAddress())
				cout << setw(20) << "Address: " << current->getAddress() << endl;
			if (current->avEmail())
				cout << setw(20) << "Email: " << current->getEmail() << endl;
			if (current->avPhone())
				cout << setw(20) << "Phone Number: " << current->getPhone() << endl;
			System.newOperation(op);
			for (int i = 0; i < op.getList()->size(); i++) {
				op.getList()->at(i).first->buy(op.getList()->at(i).second);
			}
			save(items);
			system("pause");
			state = shop;
			op = purchase_operation(current);
			break;
		case info:
			system("cls");
			printInfo(current);
		prev3:
			cout << "------------------------------------------------------------------------------------";
			cout << endl << "1-Edit a field" << endl << "2-Remove a Field" << endl << "3-Logout" << endl << "4-Shop" << endl << "5-Cart" << endl;

			read<int>(n);
			switch (n) {
			case 1:
			prev:
				cout << "Enter Field Number to edit:(0:back)";
				read<int>(m);
				switch (m) {
				case 0:
					state = info;
					break;
				case 1:
					current->setName();
					break;
				case 2:
					current->setCredit();
					break;
				case 3:
					current->setAddress();
					break;
				case 4:
					current->setEmail();
					break;
				case 5:
					current->setPhone();
					break;
				default:
					Invalid();
					goto prev;
					break;
				}
				savecust(cust, oncust);
				break;
			case 2:
			prev2:
				cout << "Enter Field Number to remove:(0:back)";
				read<int>(m);
				switch (m) {
				case 0:
					state = info;
					break;
				case 2:
					current->remCredit();
					break;
				case 3:
					current->remAddress();
					break;
				case 4:
					current->remEmail();
					break;
				case 5:
					current->remPhone();
					break;
				default:
					Invalid();
					goto prev2;
					break;
				}
				savecust(cust, oncust);
				break;
			case 3:
				current = NULL;
				state = start;
				break;
			case 4:
				state = shop;
				break;
			case 5:
				state = cart;
				break;
			default:
				goto prev3;
			}
			break;

		case control:
			cout << "0-Logout" << endl << "1-Add Item" << endl << "2-Restock" << endl;
			read<int>(n);
			switch (n) {
			case 0:
				state = start;
				break;
			case 1:
				cout << "Enter Item name:\n";
				cin.ignore();
				getline(cin, s);
				trim(s);
				do {
					cout << "Enter Quantity Available:\n";
					read<int>(n);
				} while (n < 1);
				do {
					cout << "Enter Unit Price:\n";
					read<double>(d);
				} while (d < 0);
				items.push_back(Item(s, d, n));
				save(items);
				break;
			case 2:
				cout << "Enter Item name:\n";
				cin.ignore();
				getline(cin, s);
				s = trim(s);
				for (i = 0; i < items.size(); i++) {
					if ((_strcmpi((trim(items[i].getName())).c_str(), s.c_str())) == 0) {
						cout << "Enter quantity to be added:\n";
						do {
							read<int>(m);
						} while (m < 1);
						items[i].setCount(items[i].getCount() + m);
					}
				}
				save(items);
				break;
			default:
				state = shop;
				break;
			}
		}
	}
	system("pause");
	return 0;
}