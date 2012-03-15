#include "ofxLUT.h"

//--------------------------------------------------------------
ofxLUT::ofxLUT(){}
//--------------------------------------------------------------
ofxLUT::~ofxLUT(){}
//--------------------------------------------------------------
void ofxLUT::setup(){}
//--------------------------------------------------------------
void ofxLUT::load(string path){
	loaded=false;
	img.allocate(640, 480, OF_IMAGE_COLOR);
	
	ofBuffer buffer = ofBufferFromFile(path);
	for (int i=0; i<5; i++) {
		cout << "Skipped line: " << buffer.getNextLine()<<endl;
	}
		
	for(int z=0; z<32; z++){
		for(int y=0; y<32; y++){
			for(int x=0; x<32; x++){
				string content = buffer.getNextLine();
				
				vector <string> splitString = ofSplitString(content, " ", true, true);
				if (splitString.size() >=3) {
					lut[x][y][z] = ofVec3f(ofToFloat(splitString[0]),ofToFloat(splitString[1]), ofToFloat(splitString[2]));
				cout << lut[x][y][z] << endl;	
				}
				
				if (buffer.isLastLine()) {
					cout << "ofxLUT load finished" << endl;
					
					return;
				}
			}
		}
	}    
	loaded = true;
}
//--------------------------------------------------------------
void ofxLUT::applyLUT(ofPixelsRef pix){
	if (loaded) {
		
		ofPixelsRef pixels = pix;
		
		for(int y = 0; y < pix.getHeight(); y++){
			for(int x = 0; x < pix.getWidth(); x++){
				
				ofColor color = pix.getColor(x, y);
				
				int lutPos [3];
				for (int m=0; m<3; m++) {
					lutPos [m] = floor(color[m]/8.0f);
					if (lutPos[m]==31) {
						lutPos[m]=30;
					}
				}
				
				ofVec3f temp = lut[lutPos[0]][lutPos[1]][lutPos[2]];
				ofVec3f temp2 =lut[lutPos[0]+1][lutPos[1]+1][lutPos[2]+1]; 
				
				for (int k=0; k<3; k++) {
					color[k]= ( temp[k] + ((color[k]%8)/8.0f)* (temp2[k] - temp[k]))*255 ;
				}
				
				pixels.setColor(x, y, color);
				
			}
			img.setFromPixels(pixels);
			
		}
	}
}

//--------------------------------------------------------------
void ofxLUT::draw(int x, int y){

	img.draw(x, y);

}







