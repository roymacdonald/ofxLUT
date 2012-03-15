#pragma once
#include "ofMain.h"

class ofxLUT{

public:
	ofxLUT();
	~ofxLUT();
	void setup();
	void load(string path);
	void applyLUT(ofPixelsRef pix);
	void draw(int x, int y);
	
	bool loaded;
	ofVec3f lut[32][32][32];
	
	ofImage img;
	
	
};