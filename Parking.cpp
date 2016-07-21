using namespace std;
#include<iostream>
#include<string>

class ParkingFine{
protected:
	string date;
	string time;
	string registration;
	int code;

public:
	ParkingFine(string d, string t, string r, int c){
		date = d;
		time = d;
		registration = r;
		code = c;
	}
	virtual double amount()=0;
};

class FixedPenalty:public ParkingFine{
private:
	static double fine;
public:
	FixedPenalty(string d, string t, string r, int c):ParkingFine(d, t, r, c){}
	static void set_fine(double amount){
		fine = amount;
	}
	static double get_fine(){
		return fine;
	}
	double amount(){
		return fine;
	}
};

class ExcessCharge:public ParkingFine{
private: 
	int minutes;
public:
	ExcessCharge(string d, string t, string r, int c, int mins):ParkingFine(d,t,r,c){
		minutes = mins;
	}
	double amount(){
		double excess = 20+5*minutes;
		return (excess<FixedPenalty::get_fine())?excess:FixedPenalty::get_fine();
	}
};

class ParkingAttendant{
protected:
	int badge_number;
	double fines_issued;
public:
	ParkingAttendant(int b){
		badge_number = b;
		fines_issued = 0;
	}
	virtual double salary()=0;
	virtual void issueFine(ParkingFine& p){
		fines_issued+=p.amount();
	} 
};

class SeniorPA:public ParkingAttendant{
public:
	SeniorPA(int b):ParkingAttendant(b){}
	double salary(){
		return 1200+fines_issued*0.1;
	}
};

class JuniorPA:public ParkingAttendant{
public:
	JuniorPA(int b):ParkingAttendant(b){}
	double salary(){
		return 900+fines_issued*0.05;
	}
};

double FixedPenalty::fine=100;

int main(){
	SeniorPA charon(666);
	FixedPenalty fp1("16/02/2006","09h50","L052RNA",26);
	charon.issueFine(fp1);
	cout<<charon.salary();
	FixedPenalty::set_fine(120);


}