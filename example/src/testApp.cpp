#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	dir.allowExt("cube");
	dir.listDir("LUTs/");
	dir.sort();
	if (dir.size()>0) {
		dirLoadIndex=0;
		myLUT.load(dir.getPath(dirLoadIndex));
		doLUT = true;
	}else{
		doLUT = false;
	}
	
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(640,480);

//	myLUT.img.setAnchorPoint(0.5f, 0.5f);
	
	thumbPos.set(myLUT.img.getWidth()*0.5f-80, -myLUT.img.getHeight()*0.5f - 60, 0);
	lutPos.set(-myLUT.img.getWidth()*0.5f, -myLUT.img.getHeight()*0.5f, 0);
	ofBackground(0);
	ofSetColor(255);
}

//--------------------------------------------------------------
void testApp::update(){
	vidGrabber.grabFrame();
	
	if (doLUT) {
		if (vidGrabber.isFrameNew()){
			myLUT.applyLUT(vidGrabber.getPixelsRef());
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
		ofPushMatrix();
		ofTranslate(ofGetWidth()*0.5f, ofGetHeight()*0.5f, 0);	
	if(doLUT){
		myLUT.draw(lutPos.x, lutPos.y);
	}else {
		vidGrabber.draw(lutPos.x, lutPos.y);
	}
		ofRect(thumbPos.x-3, thumbPos.y-3, 166, 126);
		vidGrabber.draw(thumbPos.x, thumbPos.y, 160, 120);
		
		ofDrawBitmapString(dir.getName(dirLoadIndex), lutPos.x, -lutPos.y+50);
		ofPopMatrix();
	
	ofDrawBitmapString("Use UP/DOWN arrow keys to change to a different LUT.\nPress spacebar to enable/disable the LUT", 50, ofGetHeight()-20);
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	switch (key) {
		case ' ':
			doLUT^=true;
			break;
		case OF_KEY_UP:
			dirLoadIndex++;
			if (dirLoadIndex>=dir.size()) {
				dirLoadIndex=0;
			}
			myLUT.load(dir.getPath(dirLoadIndex));
			
			break;
		case OF_KEY_DOWN:
			dirLoadIndex--;
			if (dirLoadIndex<0) {
				dirLoadIndex=dir.size()-1;
			}
			myLUT.load(dir.getPath(dirLoadIndex));
			break;
		default:
			break;
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}