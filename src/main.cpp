#include <iostream>
#include <vector> 
#include "setup.hpp"
#include "menu.hpp"
#include "json_reader_writer.hpp"
#include <sstream>
#include "connect-four_solver.hpp"



using namespace std;

//Gpio numbers:
const int motor_direction = 10;
const int motor_lift_left = 15;
const int motor_lift_right = 16;
const int motor_lift_middle = 20;
const int motor_gripper = 21;

const int servo_gripper = 18;

const int mux_input_signal = 27;
const int mux_S0 = 5;
const int mux_S1 = 6;
const int mux_S2 = 26;
const int mux_S3 = 17;


const float steps_per_rotation = 200;
const float spindle_pitch = 1.25;
const float coin_height = 35;
const float gear_diameter = 10;
const float pi = 3.1415926;

float gripper_position;

int current_robo_move;

/**
 * game playing function
 * loops between players while they take turns
 */
void playGame() {
	printBoard(board); // print initial board
	while (!gameOver) { // while no game over state
		if (currentPlayer == COMPUTER) { // AI move
			lcd_write("please wait", "AI is thinking");
			int robo_move = aiMove();
			cout<<robo_move<<endl;
			makeMove(board, robo_move, COMPUTER);
			delay(1000);
		}
		else if (currentPlayer == PLAYER) { // player move
			lcd_write("your move", "");
			makeMove(board, userMove(), PLAYER);
		}
		else if (turns == NUM_ROW * NUM_COL) { // if max number of turns reached
			gameOver = true;
		}
		gameOver = winningMove(board, currentPlayer); // check if player won
		currentPlayer = (currentPlayer == 1) ? 2 : 1; // switch player
		turns++; // iterate number of turns
		cout << endl;
		printBoard(board); // print board after successful move
	}
	if (turns == NUM_ROW * NUM_COL) { // if draw condition
		lcd_write("Draw", "");
		delay(6000);
		cout << "Draw!" << endl;
	}
	else { // otherwise, someone won
		cout << ((currentPlayer == PLAYER) ? "AI Wins!" : "Player Wins!") << endl;
		if(currentPlayer == PLAYER){
			lcd_write("AI Wins!", "");
			delay(6000);
		}else{
			lcd_write("Player Wins!", "");
			delay(6000);
		}
	}
}

void error_message(string error_m){
	cout<<error_m<<endl;
}

void console(string text){
	cout<<text<<endl;
}

bool read_mux(){
	return digitalRead(mux_input_signal);
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

void set_motor_direction(bool dir){
	if(dir){
		digitalWrite(motor_direction, HIGH);
	}else{
		digitalWrite(motor_direction, LOW);
	}
}

void move_motor(int motor_pin, int steps, bool direction){
	set_motor_direction(direction);
	for(int i = 0; i< steps; i++){
		digitalWrite(motor_pin, HIGH);
		delay(5);
		digitalWrite(motor_pin, LOW);
		delay(5);
	}
}

bool setup_motors(){
	
	//motor left
	/*mux entrance 11 = endschalter left
	 * mux entrance 12 = endschalter right
	 * mux entrance 13 = endschalter middle
	 * mux entrance 14 = endschalter gripper
	 * implement error when taking too long
	 */

	digitalWrite(motor_direction, LOW);
	
	if(set_mux_entrance(11)){
		while(!digitalRead(mux_input_signal)){
			move_motor(motor_lift_left, 5, 0);
		}
	}else{
		error_message("could not set_mux_entrance");
		return false;
	}
	if(set_mux_entrance(12)){
		while(!digitalRead(mux_input_signal)){
			move_motor(motor_lift_right, 5, 0);
		}
	}else{
		error_message("could not set_mux_entrance");
		return false;
	}
	if(set_mux_entrance(13)){
		while(!digitalRead(mux_input_signal)){
			move_motor(motor_lift_middle, 5, 0);
		}
	}else{
		error_message("could not set_mux_entrance");
		return false;
	}
	if(set_mux_entrance(14)){
		while(!digitalRead(mux_input_signal)){
			move_motor(motor_gripper, 5, 0);
		}
	}else{
		error_message("could not set_mux_entrance");
		return false;
	}
	
	gripper_position = 0;
	return true;

}

void raise_lift(bool left_lift){ //0 or 1 as arguments : 0 = left, 1 = right
	
}



void gripper_move(float to_position){
	bool dir;
	float difference;
	if(to_position > gripper_position){
		 dir = false;
		 difference = to_position - gripper_position;
	}
	else{
		dir = true;
		difference = gripper_position - to_position;
	}
	float steps = difference / (pi*gear_diameter) * steps_per_rotation;	
	move_motor(motor_gripper, (int)steps, dir);

}

void gripper_open(){
	
}

void gripper_close(){
	
}




int get_IR_Position(){
	while(true){
		for(int i = 0; i<11; i++){
			set_mux_entrance(i);
			delay(5);
			if(read_mux()) return 1;
		}
	}
}




int main(int argc, char** argv) {
	wiringPiSetupGpio();
	
	softPwmCreate(servo_gripper, 10, 200);
	
	softPwmWrite(servo_gripper, 10);

	pinMode(motor_direction, OUTPUT);
	pinMode(motor_lift_left, OUTPUT);
	pinMode(motor_lift_right, OUTPUT);
	pinMode(motor_lift_middle, OUTPUT);
	pinMode(motor_gripper, OUTPUT);
	
	pinMode(mux_input_signal, INPUT);
	pinMode(mux_S0, OUTPUT);
	pinMode(mux_S1, OUTPUT);
	pinMode(mux_S2, OUTPUT);
	pinMode(mux_S3, OUTPUT);
	
	
	//setup():
	menu();
	//json_write();
	lcd_write("Game starts!", "");
	
	if(hard) MAX_DEPTH = 5;
	else MAX_DEPTH = 2;
	
	initBoard(); // initial setup
	playGame(); // begin the game
	
	
	return 0;
}








