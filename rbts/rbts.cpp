#include "pch.h"
#include <iostream>
using namespace std;
using namespace System;
using namespace System::IO;
using namespace System::IO::Ports;



//array<System::String^>^ args
int main()
{
    //InitializeComponent();
    string ports[] = SerialPort.GetPortNames();
    String^ fileName = "C:\\Users\\karli\\test.txt";
    SerialPort port(ports[0], 9600);
    port.Open();
    while (true)
    {
    try
    {
        String^ sent="";
        Console::WriteLine("trying to open file {0}...", fileName);
        StreamReader^ din = File::OpenText(fileName);
        String^ str;
        int count = 0;
        while ((str = din->ReadLine()) != nullptr)
        {   
            if (str == "LF") {
                sent = sent + "1";
            } else if (str == "RF"){
                sent = sent + "2";
            } else if (str == "LB") {
                sent = sent + "3";
            } else if (str == "RB"){
                sent = sent + "4";
            } else if (str == "L1ON") {
                sent = sent + "5";
            } else if (str == "L2ON"){   
                sent = sent + "6";
            } else if (str == "L1OFF") {
                sent = sent + "7";
            } else if (str == "L2OFF") {
                sent = sent + "8";
            }
            count++;
            Console::WriteLine("line {0}: {1}", count, str);
            Console::WriteLine(sent);
        }
    }
    catch (Exception^ e)
    {
        if (dynamic_cast<FileNotFoundException^>(e))
            Console::WriteLine("file '{0}' not found", fileName);
        else
            Console::WriteLine("problem reading file '{0}'", fileName);
    }
    return 0;
    }
    return 0;
}

