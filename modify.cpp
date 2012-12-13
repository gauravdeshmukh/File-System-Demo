#include <fstream>
#include <iostream>
#include <ctime>
#include <ios>
#include <sys/stat.h>

using namespace std;

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}

int main(int argc, char *argv[])
{
    if(argc>1)
    {
        ofstream outf("/home/gaurav/Desktop/command.txt",ios::out|ios::app);
        for(int i=1;i<argc;i++)
        {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            outf<<"3\n"<<cwd<<"/"<<argv[i]<<"\n";
            char str;
            str=getchar();
            while(str!=EOF)
            {
                outf<<str;
                str=getchar();
            }
            outf<<"\n@#$%^&*\n";
        }
        outf<<currentDateTime()<<"\n";
        outf.close();
        printf("\nfile modified!\n");
    }
    else
    {
        printf("Filename missing!\n");
    }
    return 0;
}
