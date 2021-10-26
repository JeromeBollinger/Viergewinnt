#include <iostream>
using namespace std;




int getlength(string array[]){
	return sizeof(array)/sizeof(array[0]);
}

void display(int navigator, string array[]){
	
	if(getlength(array) >= navigator+1){
		cout<<">" + array[navigator]<<endl;
		cout<<array[navigator+1]<<endl;
	}
	else{
		cout<<array[navigator-1]<<endl;
		cout<<">" + array[navigator]<<endl;
	}
	
}

int get_action(){
	int input;
	cin>>input;
	return input;
}

int menu(){
	
	string menu_1[2] = {"Spielstart", "Einstellungen"};
	
	string menu_2[4] = {"Schwierigkeit", "Farbe", "Beginner", "zurueck"};
	
	string menu_schwierigkteit[2] = {"einfach", "schwer"};
	string menu_farbe[2] = {"Gelb", "Rot"};
	string menu_beginner[2] = {"Spieler", "Roboter"};
	
	int navigator = 0;
	int depth = 0;
	// 8 = hoch			789
	// 6 = enter		456	
	// 2 = runter		123
	
	while(true){
		switch(depth){
			case 0:
				display(navigator, menu_1);
				break;
				
			
			case 1:
				display(navigator, menu_2);
				break;
						
		}
	
		navigator = get_action();
	
	}
	
	
	
	
	return 0;
}
