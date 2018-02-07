#pragma once

#include "ofMain.h"
#include "ofxSane.h"
#include "ofxOsc.h"
#include <list>

#define HOST1 "192.168.0.51"
#define HOST2 "localhost"
#define HOST3 "192.168.0.61"
#define HOST4 "192.168.0.71"
#define PORT 12345

class ofApp : public ofBaseApp{
public:
    ~ofApp();

    void setup();
    void update();
    void draw();    
    void keyPressed(int key);
    void scanImage();
    void saveImage(int which);
    void sendImage(int which);
    void lineEvent(lineEventArgs& event);
    void scanCompleteEvent(bool& event);

    ofxSane scanner;
    list<unsigned char*> buffer;
    size_t offset;
    int linelength;
    bool bReady;

    unsigned char imageData[2556*3543*3];
    ofPixels pix;
    ofImage img[4];

    ofxOscSender sender1;
    ofxOscSender sender2;
    ofxOscSender sender3;
    ofxOscSender sender4;
    ofBuffer imgAsBuffer;
    int imageId;;
};
