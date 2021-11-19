#include <iostream>
#include <vector> 
#include "setup.hpp"
#include "menu.hpp"
#include "json_reader_writer.hpp"
#include <sstream>



using namespace std;


//Gpio numbers!
const int motor_direction = 10;
const int motor_lift_left = 15;
const int motor_lift_right = 16;
const int motor_lift_middle = 20;
const int motor_gripper = 21;

const int mux_input_signal = 27;
const int mux_S0 = 5;
const int mux_S1 = 6;
const int mux_S2 = 26;
const int mux_S3 = 17;


const float steps_per_rotation = 200;
const float spindle_pitch = 1.25;
const float coin_height = 35;


void error_message(string error_m){
	cout<<error_m<<endl;
}

void console(string text){
	cout<<text<<endl;
}



bool set_mux_entrance(int in){

	int S0 = 0;
	int S1 = 0;
	int S2 = 0;
	int S3 = 0;
	int output = in;

	stringstream ss;
	string str;
	
	ss << in;
	ss >> str;
	
	if(in > 15 || in < 0) return false;
	
	
	if(output>=8){
		S3 = 1;
		output = output-8;
		digitalWrite(mux_S3, HIGH);
	}
	else{
		digitalWrite(mux_S3, LOW);
	}
	if(output>=4){
		S2 = 1;
		output = output-4;
		digitalWrite(mux_S2, HIGH);
	}
	else{
		digitalWrite(mux_S2, LOW);
	}
	if(output>=2){
		S1 = 1;
		output = output-2;
		digitalWrite(mux_S1, HIGH);
	}
	else{
		digitalWrite(mux_S1, LOW);
	}
	if(output>=1){
		S0 = 1;
		output = output-0;
		digitalWrite(mux_S0, HIGH);
	}
	else{
		digitalWrite(mux_S0, LOW);
	}

	
	console("set mux" + str);
	
	
	stringstream ss3;
	string str3;
	ss3 << S3;
	ss3 >> str3;
	console("S3: "+str3);
	
	stringstream ss2;
	string str2;
	ss2 << S2;
	ss2 >> str2;
	console("S2: "+str2);
	
	stringstream ss1;
	string str1;
	ss1 << S1;
	ss1 >> str1;
	console("S1: " + str1);
	
	stringstream ss0;
	string str0;
	ss0 << S0;
	ss0 >> str0;
	console("S0: " + str0);
	
	
	
	return true;
	
}




bool setup_motors(){
	
	//motor left
	/*mux entrance 11 = endschalter left
	 * mux entrance 12 = endschalter right
	 * mux entrance 13 = endschalter middle
	 * mux entrance 14 = endschalter gripper
	 * 
	 * implement error when taking too long
	 */
	 
	 digitalWrite(motor_direction, LOW);
	
	if(set_mux_entrance(11)){
		while(!digitalRead(mux_input_signal)){
			for(int i = 0; i<5; i++){
				digitalWrite(motor_lift_left, HIGH);
				delay(5);
				digitalWrite(motor_lift_left, LOW);
				delay(5);
			}
		}
	}else{
		error_message("could not set_mux_entrance");
		return false;
	}
	if(set_mux_entrance(12)){
		while(!digitalRead(mux_input_signal)){
			for(int i = 0; i<5; i++){
				digitalWrite(motor_lift_right, HIGH);
				delay(5);
				digitalWrite(motor_lift_right, LOW);
				delay(5);
			}
		}
	}else{
		error_message("could not set_mux_entrance");
		return false;
	}
	if(set_mux_entrance(13)){
		while(!digitalRead(mux_input_signal)){
			for(int i = 0; i<5; i++){
				digitalWrite(motor_lift_middle, HIGH);
				delay(5);
				digitalWrite(motor_lift_middle, LOW);
				delay(5);
			}
		}
	}else{
		error_message("could not set_mux_entrance");
		return false;
	}
	if(set_mux_entrance(14)){
		while(!digitalRead(mux_input_signal)){
			for(int i = 0; i<5; i++){
				digitalWrite(motor_gripper, HIGH);
				delay(5);
				digitalWrite(motor_gripper, LOW);
				delay(5);
			}
		}
	}else{
		error_message("could not set_mux_entrance");
		return false;
	}
	
	return true;

}


int main(int argc, char** argv) {
	wiringPiSetupGpio();
	
	pinMode(motor_direction, INPUT);
	pinMode(motor_lift_left, OUTPUT);
	pinMode(motor_lift_right, OUTPUT);
	pinMode(motor_lift_middle, OUTPUT);
	pinMode(motor_gripper, OUTPUT);
	
	pinMode(mux_input_signal, INPUT);
	pinMode(mux_S0, OUTPUT);
	pinMode(mux_S1, OUTPUT);
	pinMode(mux_S2, OUTPUT);
	pinMode(mux_S3, OUTPUT);
	
	
	
	
	//setup_lcd();
	//setup():
	//menu();
	//json_write();
	
	
	return 0;
}

