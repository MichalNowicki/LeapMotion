#include "kinect.h"


int main()
{
    
    Kinect *Program  = new Kinect();

    Program->PrzygotujChmury();
  
    Program->NARF_ICP();
    Program->ICP();
    
    delete Program;

    return 0;
}
