#include <iostream>
#include <vector> 
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
extern "C" {
#include "../WiringPi/wiringPi/wiringPi.h"
#include "../WiringPi/devLib/lcd.h"
#include "../WiringPi/devLib/lcd.c"
#include "../WiringPi/wiringPi/softPwm.h"
}
	using namespace std;
	
	int navigator, depth;
	
	vector<string> menu_1 = {"Spielstart", "Einstellungen"};					//depth = 0
	vector<string> menu_2 = {"Schwierigkeit", "Farbe", "Beginner", "zurueck"};	//depth = 1	
	vector<string> menu_schwierigkeit = {"einfach", "schwer"};					//depth = 2
	vector<string> menu_farbe = {"Gelb", "Rot"};								//depth = 3
	vector<string> menu_beginner = {"Spieler", "Roboter"};						//depth = 4
	vector<string> actual_menu;									//menu to display currently
	
	
	int rs = 7;
	int strb = 8;
	int pin1 = 25;
	int pin2 = 24;
	int pin3 = 23;
	int pin4 = 18;
	
	int lcd;
	
	void setup_lcd(){
		wiringPiSetupGpio();
		lcd = lcdInit(2, 16, 4, rs, strb, pin1, pin2, pin3, pin4, 0, 0, 0, 0);
		delay(500);
		lcdPuts(lcd, "ABCDE");
		delay(500);
	}
	
	void display(){
		int size = actual_menu.size();
		lcdClear(lcd);
		if(navigator < size-1){
			stringstream ss;
			string str;			
			stringstream ss2;
			string str2;
			ss << actual_menu[navigator];
			ss >> str;
			ss2 << actual_menu[navigator+1];
			ss2 >> str2;
			lcdPuts(lcd,(">"+str).c_str());
			lcdPosition(lcd, 0, 1);
			lcdPuts(lcd, str2.c_str());
		}
		else{
			stringstream ss;			
			stringstream ss2;
			string str;
			string str2;
			ss << actual_menu[navigator-1];
			ss >> str;
			ss2 << actual_menu[navigator];
			ss2 >> str2;
			lcdPuts(lcd, str.c_str());
			lcdPosition(lcd, 0, 1);
			lcdPuts(lcd,(">" + str2).c_str());
		}
	}
	
	void get_action(){
		
		// 8 = hoch			789
		// 6 = enter		456	
		// 2 = runter		123
		
		
		int input;
		cin >> input;
		
		int menu_size = actual_menu.size();
		switch (input){
			case 2:
				if(navigator < menu_size-1){
					navigator++;
				}
				else{
					navigator = navigator;
				}
				break;
				
			case 8:
				if(navigator > 0){
					navigator--;
				}
				else{
					navigator = 0;
				}
				break;
				
			case 6:
				if(depth == 0 && navigator == 1 ){
					depth = 1;
					actual_menu = menu_2;
				}
				else if(depth == 1 && navigator == 0){
					depth = 2;
					actual_menu = menu_schwierigkeit;
				}
				else if(depth == 1 && navigator ==	1){
					depth = 3;
					actual_menu = menu_farbe;
				}
				else if(depth == 1 && navigator == 2){
					depth = 4;
					actual_menu = menu_beginner;
				}
				else if(depth == 1 && navigator == 3){
					depth = 0;
					actual_menu = menu_1;
				}
				else{
					depth = 0;
					actual_menu = menu_1;
				}
				navigator = 0;
				break;
				
			default:
				navigator = 0;
				break;
		}
	}
	
	int menu(){
		setup_lcd();
		navigator = 0;
		depth = 0;
		actual_menu = menu_1;
		
		
		while(true){
			display();
			get_action();
			
		}
		
		
		
		
		return 0;
	}
	
