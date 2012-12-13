#include <iostream>
#include <fstream>
#include <iostream>
#include <ctime>
#include <ios>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}
//Functions for Daemon
//requires <cstdio>
void readfile()
{
	int choice;
	string filename1;
	//char* filename;
	ifstream inf("Command.txt");
	inf>>choice;
	inf>>filename1;
	char *filename=new char[filename1.size()+1];
	filename[filename1.size()]='0';
	memcpy(filename,filename1.c_str(),filename1.size());
	switch(choice)
	{
		case 1:
		{
			//cout<<"case1"<<endl;
			string tf;
			inf>>tf;
			//cout<<tf;
			string timestamp;
			inf>>timestamp;
			//cout<<timestamp<<endl;
			if (tf.compare("true") == 0)
			{
				string line;
				//inf.ignore(1000, '\n');
				std::getline(inf,line);
				cout<<"File created!";
				ofstream outf(filename);
				outf<<line;
			}
			inf.close();
			break;
		}
		case 2:
		{
			remove(filename);
			cout<<"File deleted!";
			inf.close();
			break;
		}
		case 3:
		{
			cout<<"I am here!"<<endl;
			string timestamp;
			//inf.ignore(1000, '\n');
			std::getline(inf,timestamp);
			cout<<"I am here now!"<<endl<<timestamp<<endl;
			string line;
			//inf.ignore(1000, '\n');
			std::getline(inf,line);
			cout<<line<<endl;
			inf.close();
			ofstream outf(filename,ios::app);
			outf<<line;
			//cout<<"File modified!";
			break;
		}
		default:
		{
			cout<<":(";
		}
	}
}
int main()
{
     int choice;
     string filename;
     cout<<"Select a choice about what do you want to do:";
     cout<<endl<<"1: Create a file\t2: Delete a file\t3: Write to(append) a file\n";
     cin>>choice;
     cout<<"Enter the name of the file which you want to operate on:\n";
     cin>>filename;
     ofstream outf("Command.txt");
     switch(choice)
     {
	  case 1:
	  {
		   int write;
		   cout<<"Do you want to write to file or create a blank file?\nEnter 1 for writing a file, 0 otherwise: ";
		   cin.ignore(1000, '\n');
		   cin>>write;
		   if (write == 1)
		   {
			   string text;
			   cout<<"Enter the line you want to write to the file:\n";
			   //cin.ignore(numeric_limits<streamsize>::max(),'\n') ;
			   cin.ignore(1000, '\n');
			   std::getline(cin,text);
			   outf<<"1 "<<filename<<" true "<<currentDateTime()<<endl;
			   outf<<text<<endl;
		   }
		   else
		   {
			   outf<<"1 "<<filename<<" false "<<currentDateTime()<<endl;
		   }
	       break;
	  }
	  case 2:
	  {
	       outf<<"2\n"<<filename<<endl;
	       break;
	  }
	  case 3:
	  {
	       string text;
	       cout<<"Enter the line you want to append to the file: \n";
	       //cin.ignore(numeric_limits<streamsize>::max(),'\n') ;
	       cin.ignore(1000, '\n');
		   std::getline(cin,text);
	       outf<<"3 "<<filename<<" "<<currentDateTime()<<endl;
	       outf<<text<<endl;
	       break;
	  }
	  default:
	  {
	       cout<<"Invalid option."<<endl;
	       break;
	  }
     }

     outf.close();
     readfile();
     return 0;
}

