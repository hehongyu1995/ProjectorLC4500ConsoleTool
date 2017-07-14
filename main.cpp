#include <iostream>
#include "ProjectorLC4500.h"
#include "ProjectorOpenGL.h"
#include "Projector.h"
#include <unistd.h>
#include <string>
#include <cstring>
void parseCommandLine (int argc, char *argv[]);
void showHelp (char *filename);
int findSwitch(int argc, char *argv[],const char *switchStr);
Projector *projector;
int main(int argc, char *argv[]) {

    parseCommandLine(argc,argv);
    return 0;
}

void
parseCommandLine (int argc, char *argv[])
{

    try{
        if(argc==1){
            throw "Error: None Params";
        }
        //Show help
        if (0==strcmp (argv[1], "-h"))
        {
            showHelp (argv[0]);
            exit (0);
        }
        if(0==strcmp (argv[1], "display")) {

            int screenPara=findSwitch(argc,argv,"-screen")+1;
            unsigned int screenNum;
            screenNum=screenPara>1?(unsigned int) std::stoi(argv[screenPara]):1;
            Projector *projector=new ProjectorOpenGL(screenNum);
            if (strcmp(argv[2], "white") == 0) {
                projector->displayWhite();
            }
            if (strcmp(argv[2], "black") == 0) {
                projector->displayBlack();
            }
        } else{
            projector=new ProjectorLC4500(0);
            if(strcmp (argv[1], "status")==0) {
                projector->getStatus();
                return;
            }else if(strcmp (argv[1], "set")==0){

                if(0==strcmp(argv[2],"period")) {
                    unsigned int explosurePeriod = (unsigned int) std::stoi(argv[3]);
                    unsigned int framePeriod=explosurePeriod;
                    if(argc>=5&&strcmp (argv[4], "-p")!=0) {
                        framePeriod = (unsigned int) std::stoi(argv[4]);
                        projector->setExplosureFramePeriod(explosurePeriod, framePeriod);
                    } else{
                        projector->setExplosureFramePeriod(explosurePeriod, explosurePeriod);
                    }
                    if(findSwitch(argc,argv,"-p")) projector->playSeq();
                }
                if(0==strcmp(argv[2],"fps")) {
                    unsigned int fps = (unsigned int) std::stoi(argv[3]);
                    projector->setPatternFPS(fps);
                    if(findSwitch(argc,argv,"-p")) projector->playSeq();
                }
                if(0==strcmp(argv[2],"trigger")) {
                    if(0==strcmp(argv[3],"internal")) projector->setPatternTriggerMode(true);
                    if(0==strcmp(argv[3],"external")) projector->setPatternTriggerMode(false);
                }
                if(0==strcmp(argv[2],"mode")) {
                    if(0==strcmp(argv[3],"video")) {
                        std::cout<<"Set video mode"<<std::endl;
                        projector->setVideoMode();
                    }
                    if(0==strcmp(argv[3],"pattern")) projector->setSLMode();
                }
                if(0==strcmp(argv[2],"pattern_src")){
                    if(0==strcmp(argv[3],"video")) projector->setPatternDisplayMode(true);
                    if(0==strcmp(argv[3],"internal")) projector->setPatternDisplayMode(false);
                }
            } else if(strcmp (argv[1], "status")==0){
                projector->getStatus();
            } else if(strcmp (argv[1], "seq")==0){
                if(strcmp(argv[2],"play")==0) {
                    projector->playSeq();
                }
                if(strcmp(argv[2],"pause")==0) projector->pauseSeq();
                if(strcmp(argv[2],"stop")==0) projector->stopSeq();

            } else if(strcmp (argv[1], "run")==0) {
                if(strcmp (argv[2], "pattern_test")==0) {
                    unsigned int start = (unsigned int) std::stoi(argv[3]);
                    unsigned int end = (unsigned int) std::stoi(argv[4]);
                    unsigned int step = (unsigned int) std::stoi(argv[5]);
                    projector->runPatternTest(start,end,step);
                }
            } else if(strcmp (argv[1], "export")==0){
                if(strcmp (argv[2], "calibration")==0) {
                    //todo: export calibration.xml
                }
            } else{
                throw "Unknown Command.";
            }
        }


    }catch (const char* msg){
        std::cerr<<msg<<std::endl;
        showHelp(argv[0]);
    }
    catch (std::exception& e){
        std::cerr<<"Exception: "<<e.what()<<std::endl;
        showHelp(argv[0]);
    }



}

void
showHelp (char *filename)
{
    std::cout << std::endl;
    std::cout << "***************************************************************************" << std::endl;
    std::cout << "*                                                                         *" << std::endl;
    std::cout << "*             Correspondence Grouping Tutorial - Usage Guide              *" << std::endl;
    std::cout << "*                                                                         *" << std::endl;
    std::cout << "***************************************************************************" << std::endl << std::endl;
    std::cout << "Usage: " << filename << " model_filename.pcd scene_filename.pcd [Options]" << std::endl << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "     -h:                     Show this help." << std::endl;
    std::cout << "     -k:                     Show used keypoints." << std::endl;
    std::cout << "     -c:                     Show used correspondences." << std::endl;
    std::cout << "     -r:                     Compute the model cloud resolution and multiply" << std::endl;
    std::cout << "                             each radius given by that value." << std::endl;
    std::cout << "     --algorithm (Hough|GC): Clustering algorithm used (default Hough)." << std::endl;
    std::cout << "     --model_ss val:         Model uniform sampling radius (default 0.01)" << std::endl;
    std::cout << "     --scene_ss val:         Scene uniform sampling radius (default 0.03)" << std::endl;
    std::cout << "     --rf_rad val:           Reference frame radius (default 0.015)" << std::endl;
    std::cout << "     --descr_rad val:        Descriptor radius (default 0.02)" << std::endl;
    std::cout << "     --cg_size val:          Cluster size (default 0.01)" << std::endl;
    std::cout << "     --cg_thresh val:        Clustering threshold (default 5)" << std::endl << std::endl;
}

int findSwitch(int argc, char *argv[],const char *switchStr){
    for(unsigned int i=1;i<argc;i++){
        if(strcmp(argv[i],switchStr)==0) return i;
    }
    return 0;
}
