#include <iostream>
#include <string>
#include <unistd.h>
#include <ctime>
#include <cmath>
#include <vector>
#include <time.h>
#include <algorithm>
#include <stdlib.h>
#include<sys/wait.h> 


using namespace std;
class Command{
public:
	string history;
	double t;
};

bool compare(const Command & a, const Command & b);
int main(){
	vector <Command> a;
	vector <Command> c;
	Command b;
	string command;
	double start, stop;
	pid_t pid;
	int status;
	while (true){
    	string s = "";
    	cout<<"tinyshell>";
	    getline(cin, command);
	    for(int i = 0; i < command.length(); i++){
    		if (command[i] != ' '){
    			s = s + command[i];
    			if(i != (command.length()-1)){
					if (command[i+1]==' '){
					    s = s + " ";
    				}
    			}
			}
		}
		const char* cmd = s.c_str();
    	if (s.substr(0,4)=="exit"){
    		exit(0);
		
		}else if (s.substr(0,7) == "history"){
		    if ( s.length() == 12 && s.substr(8,4) == "-sbu" ){
		    	start=clock();
		    	sort(c.begin(), c.end(), compare);
		   		vector<Command>::iterator itr;
		   		for(itr = c.end()-1; itr >=c.begin() ; itr--){
		   			cout<< (*itr).history <<"  "<< (*itr).t << "s"<<endl;
		   		}
	    		stop=clock();
			
	    	}else{
		    	start=clock();
		    	vector<Command>::iterator itr;
		   		for(itr = a.end()-1; itr >= a.begin(); itr--){
	   				cout<< (*itr).history <<"  "<< (*itr).t << "s"<<endl;
	   			}
	   			stop=clock();
	    	}
	    }else{
		start=clock();
	        pid = fork();
	        if (pid == 0){
	            
	            system(cmd);
	            
	            pid = 0;
		    exit(0);
		    
	        }else if (pid > 0){
	            waitpid(pid,NULL,0);
	        }else{
	            cout<<"Error";
	        }
		stop=clock();
	    }
	    b.t = (stop - start)/CLOCKS_PER_SEC;
	    b.history = command;
	    a.push_back(b);
    	    c.push_back(b);
    	    if (a.size()>5){
    	    	a.erase(a.begin());
        	c = a;
    		}
	}
}
bool compare(const Command & a, const Command & b){
	return ( a.t < b.t );
}
