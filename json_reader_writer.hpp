#include <iostream>
#include <vector> 
#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/reader.h"
#include "rapidjson/include/rapidjson/writer.h"
#include "rapidjson/include/rapidjson/stringbuffer.h"
#include "rapidjson/include/rapidjson/filereadstream.h"
#include <cstdio>

#include <sstream>
#include <fstream>

using namespace std;
using namespace rapidjson;

string difficulty, color, beginner;


void json_read(){
	
	FILE* fp = fopen("Settings.json", "rb");
	
	char readBuffer[255];
	FileReadStream fileReadStream(fp, readBuffer, sizeof(readBuffer));
	
	Document document;
	document.ParseStream(fileReadStream);
	
	difficulty = document["Difficulty"].GetString();
	color = document["Color"].GetString();
	beginner = document["Beginner"].GetString();
	
	fclose(fp);
}
