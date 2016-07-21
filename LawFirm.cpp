using namespace std;
#include<iostream>
#include<string>

class Client{
	string name;
	int amount_owing;
	public:
		Client(string _name){
			name = _name;
			amount_owing=0;
		}
		void owes(int bill){
			amount_owing+=bill;
		}
		int get_owed_amount(){
			return amount_owing;
		}
};

class Employee{
	string name;
	int billed;
	public:
		Employee(string _name){
			name = _name;
		}
		virtual void works(Client& client, int hours) = 0;
		virtual double get_bonus()=0;
};

class Solicitor:public Employee{
	string name;
	int billed;
	public:
	static int rate;
		Solicitor(string _name):Employee(_name){
			billed =0;
		}
		void works(Client& client, int hours){
			int bill = hours*rate;
			billed+=bill;
			client.owes(bill);
		}
		double get_bonus(){
			return billed*0.1;
		}
		static void set_rate(int _rate){
			rate = _rate;

		}
};

class Barrister:public Employee{
	string name;
	int grade;
	int rate;
	int billed;
	public:
		Barrister(string _name, int _grade):Employee(_name){
			grade = _grade;
			billed = 0;
			if (grade ==1){
				rate = 150;
			}
			if (grade ==2){
				rate =200;
			}
			else {rate = 400;}
		}

		void pass_exam(){
			if (grade==1){
				grade++;
				rate = 200;
			}
			else if (grade==2){
				grade++;
				rate = 400;
			}
		}
		void works(Client& client, int hours){
		int bill = hours*rate;
			billed+=bill;
			client.owes(bill);	
		}
		double get_bonus(){
			return billed*0.1;
		}

};

int Solicitor::rate = 150;



int main(){
	Solicitor fiona("Fiona Shackelton");
	Barrister nicholas("Nicholas Mostyn", 2);
	Client paul("Paul McCartney");
	Client andrew("Prince Andrew");
	fiona.works(paul,10);
	Solicitor::set_rate(175);
	fiona.works(andrew, 5);
	nicholas.works(paul,15);
	nicholas.pass_exam();
	cout<<paul.get_owed_amount()<<endl;
	cout<<fiona.get_bonus()<<endl;
	return 0;
}
