#include "ProjectorLC4500.h"

#include <iostream>
#include <unistd.h>
#include "LC4500API/API.h"
#include "LC4500API/usb.h"

void showError(std::string err){
    std::cerr << "Projector4500_Configurator:" << err.c_str() << std::endl;
}


ProjectorLC4500::ProjectorLC4500(unsigned int): nPatterns(0), isRunning(false){

    std::cout << "Connecting to ProjectorLC4500... " << std::endl;

    // Initialize usb connection
    if(USB_Init()){
        showError("Could not init USB!");
    }
    if(USB_Open()){
        showError("Could not connect!");
    }
    if(!USB_IsConnected()){
        showError("Could not connect.");
    }
    std::cout << "Success Connected." << std::endl;
//    unsigned char HWStatus, SysStatus, MainStatus;
//    while(LCR_GetStatus(&HWStatus, &SysStatus, &MainStatus) != 0){
//        std::cout << ".";
//        continue;
//    }

    // Make sure LC is not in standby
    const bool standby = false;
    if(!LCR_SetPowerMode(standby)){
        showError("Error Setting Power Mode");
    }

    // Set LED selection
    const bool SeqCtrl  = false; // manual (false) or automatic (true)
    const bool LEDRed  = false;
    const bool LEDGreen  = false;
    const bool LEDBlue  = true;
    LCR_SetLedEnables(SeqCtrl, LEDRed, LEDGreen,  LEDBlue);

    // Set LED currents
    const unsigned char RedCurrent = 0;
    const unsigned char GreenCurrent = 0;
    const unsigned char BlueCurrent = 100;
    LCR_SetLedCurrents(100, 100, 100);

    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
    LCR_GetLedCurrents(&Red, &Green, &Blue);

//    // Set to pattern sequence mode
//    const bool patternSequenceMode = true;
//    if(!LCR_SetMode(patternSequenceMode)){
//        showError("Error Setting Mode");
//    }
        
//    // Clear pattern LUT
//    LCR_ClearPatLut();
    
//    const int bitDepth = 8;
//    const int ledSelect = 1;
//    bool invertPattern = false;

//    // 2 x 8.333 exposures of the 2x3 psp pattern
//    //int LCR_AddToPatLut(int TrigType, int PatNum,int BitDepth,int LEDSelect,bool InvertPat, bool InsertBlack,bool BufSwap, bool trigOutPrev)
//    LCR_AddToPatLut(0, 1, bitDepth, ledSelect, invertPattern, false, true, false);
//    LCR_AddToPatLut(3, 1, bitDepth, ledSelect, invertPattern, true, false, true);
//    LCR_AddToPatLut(0, 0, bitDepth, ledSelect, invertPattern, false, false, false);
//    LCR_AddToPatLut(3, 0, bitDepth, ledSelect, invertPattern, true, false, true);
//    LCR_AddToPatLut(0, 2, bitDepth, ledSelect, invertPattern, false, false, false);
//    LCR_AddToPatLut(3, 2, bitDepth, ledSelect, invertPattern, true, false, true);

//    LCR_AddToPatLut(0, 1, bitDepth, ledSelect, invertPattern, false, true, false);
//    LCR_AddToPatLut(3, 1, bitDepth, ledSelect, invertPattern, true, false, true);
//    LCR_AddToPatLut(0, 0, bitDepth, ledSelect, invertPattern, false, false, false);
//    LCR_AddToPatLut(3, 0, bitDepth, ledSelect, invertPattern, true, false, true);
//    LCR_AddToPatLut(0, 2, bitDepth, ledSelect, invertPattern, false, false, false);
//    LCR_AddToPatLut(3, 2, bitDepth, ledSelect, invertPattern, true, false, true);

//    // Set to internal flash source
//    const bool patternDisplayMode = false;
//    LCR_SetPatternDisplayMode(patternDisplayMode);

//    LCR_SetPatternConfig(12, true, 12, 2);

//    LCR_SetExpsosure_FramePeriod(16666, 16666);

//    // Internal trigger
//    const bool patternTriggerMode = true;
//    LCR_SetPatternTriggerMode(patternTriggerMode);

//    if(LCR_SendPatLut() < 0)
//        showError("Error Sending Pattern LUT");

//    unsigned char splashLutEntries[] = {3, 4};
//    unsigned int numEntries = 2;
//    LCR_SendSplashLut(splashLutEntries, numEntries);

//    unsigned int status;
//    if(LCR_ValidatePatLutData(&status) < 0)
//        showError("Error validating LUT data");

//    // Set trigger signal configuration
//    LCR_SetTrigOutConfig(1, true, 0, 0);

}

void ProjectorLC4500::setPattern(unsigned int patternNumber, const unsigned char *tex, unsigned int texWidth, unsigned int texHeight){

}

void ProjectorLC4500::displayPattern(unsigned int){

    if(!isRunning){
        // Start pattern sequence
        LCR_PatternDisplay(2);
        isRunning = true;
    }
}

void ProjectorLC4500::displayTexture(const unsigned char *tex, unsigned int texWidth, unsigned int texHeight){

}

void ProjectorLC4500::displayBlack(){

}

void ProjectorLC4500::displayWhite(){

}

void ProjectorLC4500::getScreenRes(unsigned int *nx, unsigned int *ny){
    *nx = 912;
    *ny = 1140;
}

ProjectorLC4500::~ProjectorLC4500(){

    // Stop pattern sequence
    LCR_PatternDisplay(0);

    USB_Close();
    USB_Exit();

}

int ProjectorLC4500::setExplosureFramePeriod(unsigned int exposurePeriod, unsigned int framePeriod) {
    if(LCR_SetExpsosure_FramePeriod(exposurePeriod, framePeriod) < 0){
        showError("Error Sending Exposure period");
        return -1;
    }

}
//true for internal trigger mode,false for external trigger mode.
int ProjectorLC4500::setPatternTriggerMode(bool internal) {
    if(LCR_SetPatternTriggerMode(internal)<0){
        showError("Error set Pattern trigger mode.");
        return -1;
    }
}

int ProjectorLC4500::setVideoMode() {
    LCR_SetPowerMode(0);
    if(LCR_SetMode(0)<0){
        showError("Error switch to Video Mode.");
        return -1;
    }
}

int ProjectorLC4500::setSLMode() {
    if(LCR_SetMode(1)<0){
        showError("Error switch to SL Mode.");
        return -1;
    }
}

int ProjectorLC4500::playSeq() {
    if(LCR_PatternDisplay(2)<0){
        showError("Error play sequence.");
        return -1;
    }
}

int ProjectorLC4500::pauseSeq() {
    if(LCR_PatternDisplay(1)<0){
        showError("Error pause sequence.");
        return -1;
    }
}

int ProjectorLC4500::stopSeq() {
    if(LCR_PatternDisplay(0)<0){
        showError("Error stop sequence.");
        return -1;
    }
}

int ProjectorLC4500::getStatus() {
    bool mode;
    if (LCR_GetMode(&mode)<0){
        showError("Error get mode.");
    } else{
        if(mode){
            std::cout<<"Mode: Pattern Sequence"<<std::endl;
            unsigned resX,resY;
            getScreenRes(&resX,&resY);
            std::cout<<"Screen Resolution: "<<resX<<"*"<<resY<<std::endl;
            unsigned int exposurePeriod,framePeriod;
            LCR_GetExposure_FramePeriod(&exposurePeriod,&framePeriod);
            std::cout<<"Pattern Sequence Period:"<<std::endl;
            std::cout<<"    Exposure:"<<exposurePeriod<<std::endl;
            std::cout<<"    Frame:"<<exposurePeriod<<std::endl;
            bool patternTriggerMode;
            LCR_GetPatternTriggerMode(&patternTriggerMode);
            if(patternTriggerMode) std::cout<<"Pattern Trigger Mode: Internal"<<std::endl;
            else std::cout<<"Pattern Trigger Mode: External"<<std::endl;
            bool patternDisplayMode;
            LCR_GetPatternDisplayMode(&patternDisplayMode);
            if(patternDisplayMode) std::cout<<"Pattern Display Mode: Video"<<std::endl;
            else std::cout<<"Pattern Display Mode: Internal"<<std::endl;
        }
        else {
            std::cout<<"Mode: Video"<<std::endl;
        }
    }

    return 0;
}

int ProjectorLC4500::runPatternTest(unsigned int start, unsigned end,unsigned step) {
    std::cout<<"--- Start Sequence Test ---"<<std::endl;
    for(unsigned int i=start;i<end;i+=step){
        std::cout<<"Period: "<<i<<" Microseconds"<<std::endl;
        setExplosureFramePeriod(i,i);
        playSeq();
        unsigned int sleepTime=1000000;
        stopSeq();
        usleep(sleepTime);
    }
    return 0;
}

int ProjectorLC4500::setPatternDisplayMode(bool videoInput) {
    LCR_SetPatternDisplayMode(videoInput);
    return 0;
}

int ProjectorLC4500::setStandByMode() {
    setVideoMode();
    LCR_SetPowerMode(1);
}




