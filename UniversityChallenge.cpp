#include<iostream>
#include<string>
using namespace std;

class University{
	private:
		string name;
	public: 
		University(string n){
			name=n;
		}
		string getName(){
			return name;
		}	
};

class Contestant{
	private:
		string name;
		int age;
		bool registered;
		bool captain;
		University* uni;

	public:
		Contestant(string n, int a, University &u, bool r, bool c=false){
			name = n;
			age = a;
			uni = &u;
			registered = r;
			captain = c;
		}
		int get_age(){
			return age;
		}
		bool get_captain(){
			return captain;
		}
		bool is_valid(string team_uni){
			return (age>=18 && age<=40 && (registered) && team_uni==uni->getName());
		}
		void graduate(){
			uni = NULL;
			registered = false;
		}
		void change_uni(University& new_uni){
			uni = &new_uni;
		}
};


class Team{
	private:
		int members;
		University* uni;
		Contestant* member[4];
	public:
		Team(University& u){
			uni = &u;
			members=0;
			for (int n=0;n<4;n++){
				member[n]=NULL;
			}
		}
		bool add_member(Contestant& c){
			if(members>=4){
				return false;
			}
			member[members]=&c;
			members++;
		}

		bool average_age(){
			double sum =0;
			for (int i=0;i<members;i++){
				sum+=member[i]->get_age();
			}
			return sum/members; 	
		}
		bool is_valid(){
			if (members!=4){
				return false;
			}
			int captains = 0;
			for (int i=0;i<members;i++){
				if(!member[i]->is_valid(uni->getName())){
					return false;
				}
				if(member[i]->get_captain()){
					captains++;
				}
			}
			return (captains==1)&&average_age()<25.0;
		}
};


int main(){
	University imperial("Imperial");
	Team teamimperial(imperial);
	Contestant ivan("Ivan",20,imperial,true);
	teamimperial.add_member(ivan);
	Contestant prezza("Prezza",18,imperial,true);
	teamimperial.add_member(prezza);
	Contestant ivonna("Ivonna",25,imperial,true,true);
	teamimperial.add_member(ivonna);
	Contestant yuman("Yuman",32,imperial,true);
	teamimperial.add_member(yuman);
	prezza.graduate();
	cout<<"Team is ";
	if (!teamimperial.is_valid()){
		cout<<"not valid";
	}
	cout<<"valid";
	return 0;
}

