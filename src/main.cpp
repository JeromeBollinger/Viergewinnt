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

const float magazin_left_1 = 68;
const float magazin_left_2 = 68*2;
const float board_0 = 68*3;
const float board_1 = 68*4;
const float board_2 = 68*5;
const float board_3 = 68*6;
const float board_4 = 68*7;
const float board_5 = 68*8;
const float board_6 = 68*9;
const float magazin_right_1 = 68*10;
const float magazin_right_2 = 68*11;

const float board_position_array[7] = {board_0, board_1, board_2, board_3, board_4, board_5, board_6};

float gripper_position;
float magazin_left_position;
float magazin_right_position;
float board_lift_position;

int current_robo_move;

//function declarations
void robo_goes_brr(int robo_move);
void playGame();
void move_motor(int motor_pin, int steps, bool direction);
void gripper_move(float to_position);
void magazin_left_move(float to_position);
bool get_mux_signal(int mux_signal);
void gripper_close();
void gripper_open();
void magazin_left_move(float to_position);
void magazin_right_move(float to_position);

//red left, default robo


 void robo_goes_brr(int robo_move){
	 
	 //gripper gets coin
	 gripper_open();
	 if(red){
		 magazin_left_move(magazin_left_position + 18);
		 if(turns%4 > 1) gripper_move(magazin_left_1);
		 else gripper_move(magazin_left_2);
		gripper_close();
		magazin_left_move(magazin_left_position - 18);
			
	 }else{
		 magazin_right_move(magazin_right_position + 18);
		 if(turns%4 > 1) gripper_move(magazin_right_1);
		 else gripper_move(magazin_right_2);
		 gripper_close();
		magazin_right_move(magazin_right_position - 18);
	 }
	 
	 
	 
	 //gripper goes to placement
	 switch(robo_move){
		 case 0:
			gripper_move(board_0);
			gripper_position = board_0;
			break;
		
		case 1:
			gripper_move(board_1);
			gripper_position = board_1;
			break;
		
		case 2:
			gripper_move(board_2);
			gripper_position = board_2;
			break;
		
		case 3:
			gripper_move(board_3);
			gripper_position = board_3;
			break;
			
		case 4:
			gripper_move(board_4);
			gripper_position = board_4;
			break;
			
		case 5:
			gripper_move(board_5);
			gripper_position = board_5;
			break;
			
		case 6:
			gripper_move(board_6);
			gripper_position = board_6;
			break;
		}
	gripper_open();
	gripper_move(0);
	
	if(red) magazin_left_move(magazin_left_position + 18);
	else magazin_right_move(magazin_right_position +18);	
 }
 
 
 
void playGame() {
	printBoard(board); // print initial board
	while (!gameOver) { // while no game over state
		if (currentPlayer == COMPUTER) { // AI move
			lcd_write("please wait", "AI is thinking");
			int robo_move = aiMove();
			robo_goes_brr(robo_move);
			cout<<robo_move<<endl;
			makeMove(board, robo_move, COMPUTER);
			delay(1000);
		}
		else if (currentPlayer == PLAYER) { // player move
			lcd_write("your move", "");
			if(red)	magazin_right_move(magazin_right_position +18);
			else magazin_left_move(magazin_left_position +18);
			
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
	gameOver = false;
	turns = 0;
}

void sort_board(){
	home_magazin_left();
	home_magazin_right();
	
	for(int i = 0; i<6; i++){
		for(int j 0 =; j<7; j++){
			switch(board[i][j]){
					gripper_open();
					gripper_move(board_position_array[j]);
					gripper_close();
				
				case 1: //players piece
				if(!red){
					
					
				
			if(board[i][j] == 0) continue;
			if(board[i][j] == 
				 
	
	
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
		delay(2);
		digitalWrite(motor_pin, LOW);
		delay(2);
	}
}


void home_gripper(){
	digitalWrite(motor_direction, LOW);
	set_mux_entrance(14);
	delay(20);
	while(!read_mux()){
		move_motor(motor_gripper, 5, 0);
	}
	gripper_position = 0;
}

void home_magazin_left(){
	digitalWrite(motor_direction, LOW);
	set_mux_entrance(11);
	delay(20);
	while(!read_mux()){
		move_motor(motor_lift_left, 5, 0);
	}
	magazin_left_position = 0;
}

void home_magazin_right(){
	digitalWrite(motor_direction, LOW);
	set_mux_entrance(12);
	delay(20);
	while(!read_mux()){
		move_motor(motor_lift_right, 5, 0);
	}
	magazin_right_position = 0;
}

void home_board(){
	digitalWrite(motor_direction, LOW);
	set_mux_entrance(13);
	delay(20);
	while(!read_mux()){
		move_motor(motor_lift_middle, 5, 0);
	}
	board_lift_position = 0;
}

bool setup_motors(){
	home_magazin_left();
	home_gripper();
	home_magazin_right();
	home_board();
	return true;
}


void magazin_left_move(float to_position){
	bool dir;
	float difference;
	if(to_position > magazin_left_position){
		 dir = true;
		 difference = to_position - magazin_left_position;
	}
	else{
		dir = false;
		difference = magazin_left_position - to_position;
	}
	float steps = difference *spindle_pitch / steps_per_rotation;	
	move_motor(motor_lift_left, (int)steps, dir);
	magazin_left_position = to_position;
}
void magazin_right_move(float to_position){
	bool dir;
	float difference;
	if(to_position > magazin_right_position){
		 dir = true;
		 difference = to_position - magazin_right_position;
	}
	else{
		dir = false;
		difference = magazin_right_position - to_position;
	}
	float steps = difference *spindle_pitch / steps_per_rotation;	
	move_motor(motor_lift_right, (int)steps, dir);
	magazin_right_position = to_position;
}

void board_move(float to_position){
	bool dir;
	float difference;
	if(to_position > board_lift_position){
		 dir = true;
		 difference = to_position - board_lift_position;
	}
	else{
		dir = false;
		difference = board_lift_position - to_position;
	}
	float steps = difference *spindle_pitch / steps_per_rotation;	
	move_motor(motor_lift_middle, (int)steps, dir);
	board_lift_position = to_position;
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
	gripper_position = to_position;

}

void gripper_open(){
	softPwmWrite(servo_gripper, 10);
	delay(2000);
}

void gripper_close(){
	softPwmWrite(servo_gripper, 13);
	delay(2000);
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

bool get_mux_signal(int mux_signal){
	set_mux_entrance(mux_signal);
	delay(20);
	return read_mux();
}


int main(int argc, char** argv) {
	
	wiringPiSetupGpio();
	
	softPwmCreate(servo_gripper, 10, 200);
	
	pinMode(motor_direction, OUTPUT);
	pinMode(motor_lift_left, OUTPUT);
	pinMode(motor_lift_right, OUTPUT);
	pinMode(motor_lift_middle, OUTPUT);
	pinMode(motor_gripper, OUTPUT);
	
	pinMode(mux_input_signal, INPUT);
	pullUpDnControl(mux_input_signal, PUD_DOWN);
	pinMode(mux_S0, OUTPUT);
	pinMode(mux_S1, OUTPUT);
	pinMode(mux_S2, OUTPUT);
	pinMode(mux_S3, OUTPUT);
	
	//setup_motors();
	setup_lcd();
	
	
	
	
	while(true){
		menu();
		//json_write();
		lcd_write("Game starts!", "");
		
		if(hard) MAX_DEPTH = 5;
		else MAX_DEPTH = 2;
		cout<<robot_begins<<endl;
		if(robot_begins) currentPlayer = COMPUTER;
		else currentPlayer = PLAYER;
		
		initBoard(); // initial setup
		playGame(); // begin the game
	}
	
	return 0;
}








