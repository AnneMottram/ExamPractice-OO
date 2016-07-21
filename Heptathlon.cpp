#include <iostream>
#include <string>
using namespace std;

class Competitor{
	private:
		string name;	
		int age;
		double score;
	public:
		Competitor(string  n, int a){
			name = n;
			age=a;
			score = 0;
		}
		double get_score(){
			return score;
		}
		void competesIn(Event &e){
			score+=e.pointsScored();
		}
};

class Event{
protected:
	double result;
public:
	virtual double score()=0;
};

class RunningEvent{
	
}




int main(){
	Competitor jessica("Jessica Ennis",28);
	100M jessica100(12.54);
	jessica.competesIn(jessica100);
	HighJump jessicahj(186);
	jessica.competesIn(jessicahj);

}