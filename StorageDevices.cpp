#include <iostream>
using namespace std;

class StorageDevice{
	protected: 
		double _capacity, _bandwidth;
	public: 
		virtual double latency() =0;
		double capacity(){
			return _capacity;
		}
		double bandwidth(){
			return _bandwidth;
		}
		StorageDevice(double c, double b){
			_capacity = c;
			_bandwidth = b;
		}
};

class HardDisk:public StorageDevice{
	double _rotation_time, _seek_time;
	public:
		HardDisk(double c, double b, double r, double s):StorageDevice(c,b){
			_rotation_time=r;
			_seek_time = s;	
		}
		double latency(){
			return _rotation_time+_seek_time;
		}
};

class SSD:public StorageDevice{
	double _average_access;
	public:
		SSD(double c, double b, double a):StorageDevice(c,b){
			_average_access = a;
		}
		double latency(){
			return _average_access;
		}
};

class StorageArray{
	protected: 
		int devices;
		StorageDevice* device[12];
		double totalCapacity() const{
			double sum = 0;
			for (int i=0;i<devices;i++){
				sum+=device[i]->capacity();
			}
			return sum;
		}
		double totalBandwidth() const{
			double sum = 0;
			for (int i =0; i<devices;i++){
				sum+=device[i]->bandwidth();
			}
			return sum;
		}
		virtual double scaleFactor() const =0;
	public:
		StorageArray(){
			devices = 0;
		}
		bool add(StorageDevice* d){
			if (devices>=12){
				return false;
			}
			devices++;
			device[devices]=d;
			return true;
		}
		double latency(){
			if (devices<1){
				return 0;
			}
			double max = device[0]->latency();
			for (int i=1;i<devices;i++){
				double device_latency = device[i]->latency();
				if (device_latency>max){
					max = device_latency;
				}
			}
			return max;
		}
		double bandwidth() const{
			return totalBandwidth()*scaleFactor();
		}
		double capacity() const{
			return totalCapacity()*scaleFactor();
		}
};

class RAID1:public StorageArray{
	protected:
		double scaleFactor() const{
			return 0.5;
		}
	public:
		RAID1():StorageArray(){}
};

class RAID5:public StorageArray{
	protected:
		double scaleFactor() const{
			return (devices/(devices-1));
		}
	public:
		RAID5():StorageArray(){}
};

int main(){
		RAID1 raid1;
		RAID5 raid5;
		for (int i = 0; i<4; i++){
			raid1.add(new HardDisk(500,100,4,8));
			raid5.add(new SSD(30,300,0.01));
		}
		cout<<"RAID 1"<<raid1.bandwidth()<<" "<<raid1.capacity()<<endl;
		cout<<"RAID 5"<<raid5.latency();

}