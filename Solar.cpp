#include<iostream>
#import "math.h"

using namespace std;

class PowerGeneratingDevice{
	private:
		double conversion_eff;

	public:
		PowerGeneratingDevice(double c){
			conversion_eff=c;
		}
		virtual double powerOutput(double luminance, double wind_speed)=0;
};

class SolarPanel:public PowerGeneratingDevice{
	private:
		double surface_area;
	public:
		SolarPanel(double c, double s):PowerGeneratingDevice(c){
		surface_area =s;
		}
		double powerOutput(double luminance,double wind_speed){
			return luminance*surface_area;
		}
};

class WindTurbine:public PowerGeneratingDevice{
	private:
		double blade_diameter;
		static double max_speed;
	public:
		WindTurbine(double c, double b):PowerGeneratingDevice(c){
		blade_diameter=b;
		}
		static void set_max_speed(double speed){
		 	max_speed = speed;
		 }
		double powerOutput(double luminance, double wind_speed){
		 	double rotation_speed = wind_speed<max_speed ? wind_speed : max_speed;
		 	return pow(blade_diameter,2)*pow(rotation_speed,3);
		 }
};

class Home{
	private:
		int bedrooms;
		int devices;
		int roofSupport;
		PowerGeneratingDevice* device[3];

	public:
		Home(int _bedrooms, int _roofSupport){
			bedrooms=_bedrooms;
			roofSupport=_roofSupport;
			devices=0;
		}
		bool applyToAdd(PowerGeneratingDevice &newDevice){
			if (devices>=bedrooms){
				return false;
			}
			device[devices]=&newDevice;
			devices++;
			return true;
		}
		double calculatePower(){
			double luminance = 1.0;
			double wind_speed = 4.0;
			double power = 0;
			for (int i=0;i<devices;i++){
				power+=device[i]->powerOutput(luminance,wind_speed);
			}
			return power;
		}
};

double WindTurbine::max_speed=1.0/0.0;

int main(){
	Home home (3, 300);
	SolarPanel solar (0.35,2);
	home.applyToAdd(solar);
	WindTurbine wind (0.5,0.6);
	home.applyToAdd(wind);
	WindTurbine::set_max_speed(10);
	cout<<home.calculatePower();

}