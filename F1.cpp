#include<iostream>
#include<string>
#include <math.h> 
using namespace std;

class Driver{
	private:
		string name;
		int mass;
	public:
		Driver(string _name, int _mass){
			name = _name;
			mass = _mass;
		}
		int get_mass(){
			return mass;
		}
};

class Chassis{
	private:
		int mass;
	public: 
		Chassis(int _mass){
			mass = _mass;
		}
		int get_mass(){
			return mass;
		}
};

class Engine{
	protected:
		int mass;
		int powerFactor;
		int cylinders;
	public:
		Engine(int _mass, int _powerFactor, int _cylinders){
			mass = _mass;
			powerFactor=_powerFactor;
			cylinders=_cylinders;
		}
		virtual double time(int racing_mass, int distance) = 0;
		double get_mass(){
			return mass;
		}
};

class TurboChargeEngine:public Engine{
	public:
		TurboChargeEngine(int _mass, int _powerFactor, int _cylinders):Engine(_mass,_powerFactor,_cylinders){}
		double time (int racing_mass, int distance){
			double denom = powerFactor*pow(cylinders,2);
			double num = racing_mass*distance;
			return num/denom;
		}
};

class SupermanEngine:public Engine{
	public:
		SupermanEngine(int _mass, int _powerFactor, int _cylinders):Engine(_mass,_powerFactor,_cylinders){}
		double time (int racing_mass, int distance){
			double denom = powerFactor*cylinders;
			double num = 2*racing_mass*distance;
			return sqrt(num/denom);
		}
};


class RacingCar{
	private:
		Chassis* chassis;
		Engine* engine;
		Driver* driver;
		static int minimum_mass;
	public:
		RacingCar(Chassis& _chassis, Engine& _engine){
			chassis = &_chassis;
			engine = &_engine;
			driver = NULL;
		}
		double race(Driver& _driver, int distance){
			driver = &_driver;
			int racing_mass = minimum_mass;
			if(total_mass()>racing_mass){
				racing_mass=total_mass();
			}
			return engine->time(racing_mass,distance);
		}
		int total_mass(){
			return chassis->get_mass()+engine->get_mass()+driver->get_mass();
		}
		static void set_minimum_mass(int minimum){
			minimum_mass=minimum;
		}
};

int RacingCar::minimum_mass=642;

int main(){
	Driver lewis("Lewis Hamilton",67);
	Chassis nrchassis(582);
	TurboChargeEngine turbocharge(91, 250, 5);
	RacingCar nr14(nrchassis,turbocharge);
	Chassis tfdchassis(411);
	SupermanEngine superman(87,175,4);
	RacingCar tfd2(tfdchassis,superman);
	cout<<nr14.race(lewis,1000)<<endl;
	cout<<tfd2.race(lewis,1500)<<endl;
	RacingCar::set_minimum_mass(550);
	cout<<nr14.race(lewis,1000)<<endl;
	cout<<tfd2.race(lewis,1500)<<endl;

}