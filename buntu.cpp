#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <syslog.h>

using namespace std;

#define DAEMON_NAME "vdaemon"

void process(){
        ifstream fin("/home/gaurav/command.txt",ios::in);
	    if(fin!=NULL)
            {
	        printf("\n File opened successfully through fopen()\n");
	        string command="0";
	        string str=" ";
	        FILE *fil;
	        fstream modify;
	        char *fn;
	        bool t=getline(fin,command);
	        char c=command[0];
	        while(t)
	        {	        
	        switch(c)
	        {
	            case '1':  
							{
                            getline(fin,str,'\n');
                            fn=new char[str.length()];
                            for(int i=0;i<str.length();i++)
                             fn[i]=str[i];
                            fil=fopen(fn,"w");
                            getline(fin,str,'\n');
                            break;
							}
                case '2':
							{                            
                            getline(fin,str,'\n');
                            fn=new char[str.length()];
                            for(int i=0;i<str.length();i++)
                             fn[i]=str[i];
                            remove(fn);
                            getline(fin,str,'\n');
							}
                case '3':
							{                            
                            getline(fin,str,'\n');
                            fn=new char[str.length()];
                            for(int i=0;i<str.length();i++)
                             fn[i]=str[i];
                            modify.open(fn,ios::out|ios::app);
                            getline(fin,str,'\n');
                            while(str.compare("@#$%^&*") != 0)
                            {
                                cout<<str<<endl;
                                modify<<str<<"\n";
                                getline(fin,str,'\n');
                            }
                            modify.close();
                            getline(fin,str,'\n');
                            break;
							}                
	            default:    break;
	        }
	        t=getline(fin,command);
	        c=command[0];
	        printf("%c\n",c);
            }
	    remove("/home/gaurav/command.txt");
            }
	    else
	    {
	        printf("\nError\n");
	    }
}

int main(int argc, char *argv[]) {

    //Set our Logging Mask and open the Log
    setlogmask(LOG_UPTO(LOG_NOTICE));
    openlog(DAEMON_NAME, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);

    syslog(LOG_INFO, "Entering Daemon");

    pid_t pid, sid;

   //Fork the Parent Process
    pid = fork();

    if (pid < 0) { exit(EXIT_FAILURE); }

    //We got a good pid, Close the Parent Process
    if (pid > 0) { exit(EXIT_SUCCESS); }

    //Change File Mask
    umask(0);

    //Create a new Signature Id for our child
    sid = setsid();
    if (sid < 0) { exit(EXIT_FAILURE); }

    //Change Directory
    //If we cant find the directory we exit with failure.
    if ((chdir("/")) < 0) { exit(EXIT_FAILURE); }

    //Close Standard File Descriptors
    close(STDIN_FILENO);
    //close(STDOUT_FILENO);
    close(STDERR_FILENO);

    //----------------
    //Main Process
    //----------------
    int i=4;
    while(i--){
        process();    //Run our Process
        sleep(1);    //Sleep for 1 seconds
    }

    //Close the log
    closelog ();
}

