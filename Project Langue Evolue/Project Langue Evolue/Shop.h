#include<string>
#include<vector>
enum membership  { Premium,Gold,Silver,None};	



/**********************************************
*                 Customer                    *
***********************************************/
class Customer {
private:
	std::string name;
	membership membership_type;
	long credit;
	std::string email;
	int phone;
	std::string address;

	void trim(std::string& s);				//trims string to remove leading, trailing and double spaces
	bool isEmail(std::string const& address)const;		//checks if string has email format

	

public:
	Customer(std::string, membership, long, std::string, std::string, int);
	Customer(bool = true);	//bool used to avoid on customer trigerring this constructor
	
	bool avCredit()const;		//		
	bool avEmail()const;		// check for availability of data
	bool avPhone()const;		//
	bool avAddress()const;		//

	virtual bool isOnline()const;	//check to see if online customer
	
	void setPhone(int);																
	virtual void setPhone();
	void setCredit(long);
	virtual void setCredit();			//setters
	void setAddress(std::string);
	virtual void setAddress();
	virtual void setEmail();
	void setEmail(std::string); 
	void setName(std::string);
	void setName();
	void setMembership(membership);
	virtual void setMembership();

	long getCredit()const;
	std::string getName()const;
	int getPhone()const;				//getters
	std::string getEmail()const;
	std::string getAddress()const;
	membership getMem()const;
	std::string strMem();//return membership in string form

	
	int getDiscount()const;				//calculates discount
	
	void remCredit();		//
	void remPhone();		//		remove data
	void remAddress();		//	
	void remEmail();		//

	bool isValid(bool = false);
};






/**********************************************
*               Online Customer               *
***********************************************/
class OnCustomer :public Customer {
public:
	OnCustomer(bool =true);	
	OnCustomer(std::string n, membership m, long c, std::string ad, std::string e, int p);

	bool isOnline()const;			//check to see if online customer

	void setEmail();
	void setAddress();					//setters
	void setCredit();
	void setPhone();
};






/**********************************************
*                     Item                    *
***********************************************/
class Item {
private:
	std::string name;
	int count;
	double price;

public:
	Item(std::string = "", double = 1000000, int = 1);

	void setName(std::string);			//
	void setPrice(double );				//	setters
	void setCount(int );				//

	int getCount()const;				//
	double getPrice()const;				//	getters
	std::string getName()const;			//

	void buy(int );						//decrease quantity in stock
};






/**********************************************
*            Purchase operation               *
***********************************************/
class purchase_operation {
	Customer *customer;
	std::vector<std::pair<Item*, int>> items;

	int discount;
	double price;
	void updatePrice();
	int getPos(Item *);

public:
	purchase_operation(Customer *);

	std::vector<std::pair<Item*, int>>* getList();	//
	Customer * getCustomer();						//		getters
	double getPrice();								//
	int getDiscount();								//

	void setCount(Item*, int);				//setters
	
	void removeItem(Item *);
	void incrementCount(Item *);
	void decrementCount(Item *);
	void addItem(Item *, int = 1);
	void display(bool=true);
	void clear();
	
};






/**********************************************
*             accounting system               *
***********************************************/
class accounting_system {
public:		
	void newOperation(purchase_operation);					//don't know why it needs to be a class but that's what was required

};
