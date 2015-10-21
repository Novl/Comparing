#include <iostream>
#include <string>
#include <fstream>
#include <clocale>

using namespace std;

string support;
string FileName1, FileName2, FileNameResult, OutFlag;
fstream File1, File2;
fstream FileResult;

string StrFile1, StrFile2;
long long LineNumFile1, LineNumFile2;
bool f1, f2;


void HelpMenu()
{
    cout<<" Help "<<endl;
    cout<<" 1 or 2   - to print only 1 lane from file #"<<endl;
    cout<<" 1s or 2s - to print 1 lane and skip another"<<endl;
    cout<<" s1 or s1 - to just skip selected lane"<<endl; 
    cout<<" 1a or 2a - to read # until they equal or end of file"<<endl;
    
}
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
    setlocale(LC_ALL, "Russian");
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
    
    
    
    // ------ MAIN PART -------
    LineNumFile1 = LineNumFile1 = 1;
    getline(File1, StrFile1, '\n');
    getline(File2, StrFile2, '\n');
    while (!File1.eof() && !File2.eof())
    {
        while (StrFile1.compare(StrFile2)==0 && !File1.eof() && !File2.eof())
        {
            //cout<<"read "<<LineNum<<" line"<<endl;
            FileResult<<StrFile1<<endl<<endl;
            
            do {getline(File1, StrFile1, '\n'); LineNumFile1++;} while (StrFile1.compare(" ")==0 || StrFile1.empty() && !File1.eof());
            do {getline(File2, StrFile2, '\n'); LineNumFile2++;} while (StrFile2.compare(" ")==0 || StrFile2.empty() && !File2.eof());
        }
        if (!File1.eof() && !File2.eof())
        {
            f1 = (StrFile1.size() < StrFile2.size()) && (StrFile2.find(StrFile1) == 0);
            f2 = (StrFile1.size() > StrFile2.size()) && (StrFile1.find(StrFile2) == 0);
            if (f1)
            {
                getline(File1, support, '\n');
                LineNumFile1++;
                if (StrFile2[StrFile1.size()]==' ' && support[0]!=' ') StrFile1+=" ";
                StrFile1+=support;
            }
            else
            if (f2)
            {
                getline(File2, support, '\n');
                LineNumFile2++;
                if (StrFile1[StrFile2.size()]==' ' && support[0]!=' ') StrFile2+=" ";
                StrFile2+=support;
            }
            else
            {
                cout<<endl<<"///////////////////"<<endl;
                cout<<"Difference in lines "<<endl;
                cout<<"FILE1 str: "<<LineNumFile1<<endl;
                cout<<"File 1:"<<endl<<StrFile1<<endl<<endl;
                cout<<"FILE2 str: "<<LineNumFile2<<endl;
                cout<<"File 2:"<<endl<<StrFile2<<endl<<endl;
                
                HelpMenu();
                
                getline(cin, OutFlag);
                if (OutFlag.compare("1")==0)
                {
                    FileResult<<StrFile1<<endl;
                    getline(File1, StrFile1, '\n');                        
                    LineNumFile1++;
                }
                else
                    if (OutFlag.compare("2")==0)
                        {
                            FileResult<<StrFile2<<endl;
                            getline(File2, StrFile2, '\n');
                            LineNumFile2++;
                        }
                        else
                            if (OutFlag.compare("1s")==0)
                            {
                                FileResult<<StrFile1<<endl;
                                getline(File1, StrFile1, '\n');
                                getline(File2, StrFile2, '\n');
                                LineNumFile1++;
                                LineNumFile2++;
                            }
                            else
                                if (OutFlag.compare("2s")==0)
                                    {
                                        FileResult<<StrFile2<<endl;
                                        getline(File1, StrFile1, '\n');
                                        getline(File2, StrFile2, '\n');
                                        LineNumFile1++;
                                        LineNumFile2++;
                                    }
                                    else
                                        if (OutFlag.compare("s1")==0)
                                        {
                                            getline(File1, StrFile1, '\n');
                                            LineNumFile1++;
                                        }
                                        else
                                            if (OutFlag.compare("s2")==0)
                                            {    
                                                getline(File2, StrFile2, '\n');
                                                LineNumFile2++;
                                            }
                                            else
                                                if (OutFlag.compare("1a")==0)
                                                {
                                                    while (StrFile1.compare(StrFile2)!=0 && !File1.eof())
                                                    {
                                                        FileResult<<StrFile1<<endl;
                                                        getline(File1, StrFile1, '\n');
                                                        LineNumFile1++;
                                                    }
                                                }
                                                else
                                                    if (OutFlag.compare("2a")==0)
                                                    {    
                                                        while (StrFile1.compare(StrFile2)!=0 && !File2.eof())
                                                        {
                                                            FileResult<<StrFile2<<endl;
                                                            getline(File2, StrFile2, '\n');
                                                            LineNumFile2++;
                                                        }
                                                    }
                                                    else
                                                        goto short_end;
            }
        }
    }    
    
    while (!File1.eof())
    {
        FileResult<<StrFile1<<endl;
        getline(File1, StrFile1, '\n');
    }
    
    while (!File2.eof())
    {
        FileResult<<StrFile2<<endl;
        getline(File2, StrFile2, '\n');
    }
    
    cout<<"All done"<<endl;
    short_end:
    cout<<"Goodbye"<<endl;
    getchar();
    File1.close();
    File2.close();
    FileResult.close();
    return 0;
}