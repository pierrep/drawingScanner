#include "ofApp.h"


//--------------------------------------------------------------------
ofApp::~ofApp() {
    scanner.stop();
    ofRemoveListener(scanner.lineEvent,this,&ofApp::lineEvent);
    ofRemoveListener(scanner.scanCompleteEvent,this,&ofApp::scanCompleteEvent);
}

//--------------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);

    scanner.setup();
    ofAddListener(scanner.lineEvent, this, &ofApp::lineEvent);

    offset = 0;
    bReady = false;

    sender.setup(HOST,PORT);
}

//--------------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------------
void ofApp::draw()
{
    if(ofGetFrameNum() % 60 == 0 && ofGetFrameRate() < 59)
        cout << "slow: " << ofGetFrameRate() << "fps" << endl;
}

//--------------------------------------------------------------------
void ofApp::scanImage()
{
    offset = 0;
    scanner.scan();
}

//--------------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if(key == ' ') {
        scanner.stop();
    }
    else if(key == '1'){
        saveImage(0);
    }
    else if(key == '2'){
        saveImage(1);
    }
    else if(key == '3'){
        saveImage(2);
    }
    else if(key == '4'){
        saveImage(3);
    }
}

//--------------------------------------------------------------------
void ofApp::saveImage(int which)
{
    if(which > 3) which = 3;
    if(which < 0) which = 0;

    //if(bReady)
    {
        /*
        pix.setFromPixels(imageData,scanner.getPixelsPerLine(),scanner.getTotalLines(),3);
        img[which].setFromPixels(pix);
        img[which].rotate90(2);
        float w = img[which].getWidth();
        float h = img[which].getHeight();
        float h2 = 1080.0f;
        int w2 = w * h2/h;
        img[which].resize(w2,h2);
        //img[which].save("scan"+ofToString(which)+".jpg");
        */
        bool bLoaded = img[which].load("scan"+ofToString(which)+".png");
        if(bLoaded) {
            ofSaveImage(img[which].getPixels(),imgAsBuffer,OF_IMAGE_FORMAT_JPEG,OF_IMAGE_QUALITY_HIGH);
        }
        //imgAsBuffer = ofBufferFromFile("scan"+ofToString(which)+".jpg", true);
        sendImage(which);
    }
}

//--------------------------------------------------------------------
void ofApp::sendImage(int which)
{

    ofxOscMessage m;
    m.setAddress("/image");
    m.addIntArg(0); // surface id
    m.addIntArg(which);
    m.addBlobArg(imgAsBuffer);
    sender.sendMessage(m);
    cout << "ofApp:: sending scan"+ofToString(which)+".jpg with size: " << imgAsBuffer.size() << endl;
}

//--------------------------------------------------------------------
void ofApp::scanCompleteEvent(bool& bFinished)
{
    ofLogNotice() << "Scan Completed";
    bReady = bFinished;
}

//--------------------------------------------------------------------
void ofApp::lineEvent(lineEventArgs& event)
{
    bReady = false;

    unsigned char* cur = new unsigned char[event.size];
    memcpy(cur, event.line, event.size);
    buffer.push_back(cur);

    for (size_t i = 0; i < event.size; ++i)
    {
       imageData[offset + i] = cur[i];
    }
    offset += event.size;
}
