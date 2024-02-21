#include "lecture.h"



void lecture()
{
    std::ifstream ifs{"SimpleRobot.rom"};
    std::string test;
    if(!ifs)
    {
        std::cerr<<"Ma vie c de la merde"<<std::endl;
    }
    else
    {
      while(getline(ifs,test))
        {
            traitement(test);
        }
        ifs.close();

    }
}


void traitement(std::string test)
{
    std::istringstream iss(test);

  while(test=="");
    {
        iss>>test;
        if(test=="id")
        {
            iss>>test;
            std::cout<<test;
            iss.ignore();
        }
        if(test=="refpos")
        {
           iss>>test;
           std::cout<<test;
        }
        if(test=="basepos")
        {
           iss>>test;
           std::cout<<test;
        }
         if(test=="width")
        {
           iss>>test;
           std::cout<<test;
        }
        if(test=="color")
          {
           iss>>test;
           std::cout<<test;
        }

    }


}
