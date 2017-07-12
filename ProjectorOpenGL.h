#ifndef PROJECTOROPENGL_H
#define PROJECTOROPENGL_H

#include <iostream>
#include <vector>
#include <sys/types.h>

#include <GL/glew.h>

#include "Projector.h"
#include "OpenGLContext.h"


// ProjectorOpenGL implementations
class ProjectorOpenGL : public Projector {
    public:
        // Interface function
        ProjectorOpenGL(unsigned int _screenNum = 0);
        // Define preset pattern sequence and upload to GPU
        void setPattern(unsigned int patternNumber, const unsigned char *tex, unsigned int texWidth, unsigned int texHeight);
        void displayPattern(unsigned int patternNumber);
        // Upload and display pattern on the fly
        void displayTexture(const unsigned char *tex, unsigned int width, unsigned int height);
        void displayBlack();
        void displayWhite();
        void getScreenRes(unsigned int *nx, unsigned int *ny);
    int setExplosureFramePeriod(unsigned int exposurePeriod, unsigned int framePeriod);
    int setPatternTriggerMode(bool internal);
    int setPatternDisplayMode(bool videoInput);
    int setVideoMode();
    int setSLMode();
    int setStandByMode();
    int playSeq();
    int pauseSeq();
    int stopSeq();
    int getStatus();
    int runPatternTest(unsigned int start, unsigned end,unsigned step);
        ~ProjectorOpenGL();
    private:
        std::vector<GLuint> frameBuffers;
        OpenGLContext *context;
        GLuint shaderProgram;
};

#endif
