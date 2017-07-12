#ifndef PROJECTOR_H
#define PROJECTOR_H

#include <iostream>
#include <vector>

// Abstract Projector base class
class Projector {
public:
    // Interface function
    Projector() {}

    // Define preset pattern sequence
    virtual void
    setPattern(unsigned int patternNumber, const unsigned char *tex, unsigned int texWidth, unsigned int texHeight) = 0;

    virtual void displayPattern(unsigned int patternNumber) = 0;

    // Upload and display pattern on the fly
    virtual void displayTexture(const unsigned char *tex, unsigned int width, unsigned int height) = 0;

    // Monochrome color display
    virtual void displayBlack() = 0;

    virtual void displayWhite() = 0;

    virtual void getScreenRes(unsigned int *nx, unsigned int *ny) = 0;

    virtual int setExplosureFramePeriod(unsigned int exposurePeriod, unsigned int framePeriod)=0;

    virtual int setPatternTriggerMode(bool internal)=0;

    virtual int setPatternDisplayMode(bool videoInput)=0;

    virtual int setVideoMode()=0;

    virtual int setSLMode()=0;

    virtual int setStandByMode()=0;

    virtual int playSeq()=0;

    virtual int pauseSeq()=0;

    virtual int stopSeq()=0;

    virtual int getStatus()=0;

    virtual int runPatternTest(unsigned int start, unsigned end, unsigned step)=0;

    virtual ~Projector() {}
};

#endif
