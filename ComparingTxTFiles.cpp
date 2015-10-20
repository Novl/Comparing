#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string FileName1, FileName2, FileNameResult;
fstream File1, File2;
fstream FileResult;
char OutFlag;

string StrFile1, StrFile2;
long long LineNum;

void readFileName1(string &str)
{
    cout<<" Enter File 1 name"<<endl;
    cin>>str;
}

void readFileName2(string &str)
{
    cout<<" Enter File 2 name"<<endl;
    cin>>str;
}

void readFileNameResult(string &str)
{
    cout<<" Enter File 2 name"<<endl;
    cin>>str;
}

int main(int args, char* argv[], char* envp[])
{
    if (args==1)
    {
        readFileName1(FileName1);
        readFileName2(FileName2);
        readFileNameResult(FileNameResult);
    }
    else
        if (args==2)
        {
            FileName1.assign((const char*)argv[1]);
            readFileName2(FileName2);
            readFileNameResult(FileNameResult);
        }
        else
            if (args==3)
            {
                FileName1.assign((const char*)argv[1]);
                FileName2.assign((const char*)argv[2]);
                readFileNameResult(FileNameResult);
            }
            if (args==4)
            {
                FileName1.assign((const char*)argv[1]);
                FileName2.assign((const char*)argv[2]);
                FileNameResult.assign((const char*)argv[3]);
            }
            
    cout<<"Opening files"<<endl;        
    File1.open(FileName1.c_str());
    File2.open(FileName2.c_str());
    FileResult.open(FileNameResult.c_str(), fstream::out);
    
    LineNum=1;
    getline(File1, StrFile1, '\n');
    getline(File2, StrFile2, '\n');
    while (!File1.eof() || !File2.eof())
    {
        while (StrFile1.compare(StrFile2)==0 && !File1.eof() && !File2.eof())
        {
            cout<<"read "<<LineNum<<" line"<<endl;
            LineNum++;
            getline(File1, StrFile1, '\n');
            getline(File2, StrFile2, '\n');
            FileResult<<StrFile1<<endl;
        }
        if (!File1.eof() && !File2.eof())
        {
            cout<<"Difference in line "<<LineNum<<endl;
            cout<<"File 1:"<<endl<<StrFile1<<endl<<endl;
            cout<<"File 2:"<<endl<<StrFile2<<endl<<endl;
        
            OutFlag = getchar();
            if (OutFlag == '1')
            {
                while (StrFile1.compare(StrFile2)!=0 && !File1.eof())
                {
                    getline(File1, StrFile1, '\n');
                    FileResult<<StrFile1<<endl;
                }
            }
            else
                if (OutFlag == '2')
                    while (StrFile1.compare(StrFile2)!=0 && !File2.eof())
                    {
                        getline(File2, StrFile2, '\n');
                        FileResult<<StrFile2<<endl;
                    }
                else
                    break;
        }
    }    
    
    
    cout<<"All done"<<endl<<"Goodbye"<<endl;
    getchar();
    File1.close();
    File2.close();
    FileResult.close();
    return 0;
}