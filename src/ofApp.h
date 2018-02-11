#pragma once

#include "ofMain.h"
#include "ofxSane.h"
#include "ofxOsc.h"
#include <list>

#define HOST1 "localhost"
#define HOST2 "192.168.1.4"
#define HOST3 "192.168.1.3"
#define HOST4 "192.168.1.5"
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
    int imageId;
    bool bIsBlack;
};
