#ifndef YARD_HARDWARE_H
#define YARD_HARDWARE_H

#include <fstream>
#include <string>

using namespace std;

class YardDevice
{
 public:

    virtual bool IsConnected() {};
    virtual bool Test() {};
    virtual bool Start() {};
    virtual bool Stop() {};
};

class YardInputDevice: public YardDevice
{
 public:
    
};

class YardBarcodeScanner: public YardInputDevice
{
 public:

};

class YardCardScanner: public YardInputDevice
{
 public:

};

class YardOutputDevice: public YardDevice
{
 public:
     
    virtual bool Write(const string& str) {};    
    
};

class YardPrinter: public YardOutputDevice
{
 public:
    virtual bool Print(const string& str) {}
    virtual bool Write(const string& str) { Print(str);}
};

class YardOSPrinter: public YardPrinter
{
 public:
    virtual bool Print(const string& str) {} 
};

class YardCommPrinter: public YardPrinter
{
 public:    
    virtual bool Print(const string& str) {}
    virtual void SetPort(unsigned int port) { m_port = port; }
 protected:
    unsigned int m_port;
};

class StarDP8340: public YardCommPrinter
{
 public:
    bool Print(const string& str)
    {
        ofstream printer("/dev/ttyS0", ios::out | ios::binary);
        printer << str;
    }
    void SetRed()
    {   
        ofstream printer("/dev/ttyS0", ios::out | ios::binary);
        printer << (char)0x1b << (char)0x34;
    }
    void SetBlack()
    {
        ofstream printer("/dev/ttyS0", ios::out | ios::binary);
        printer << (char)0x1b << (char)0x35;

    }    
    void SetUnderline(bool enabled = true)
    {
        ofstream printer("/dev/ttyS0", ios::out | ios::binary);
        if (enabled)
            printer << (char)0x1b << (char)0x2d << (char)0x01;
        else
            printer << (char)0x1b << (char)0x2d << (char)0x00;
    }
    
    void TestImage()
    {
        ofstream printer("/dev/ttyS0", ios::out | ios::binary);
        printer << (char)0x1b << (char)0x4b << (char)0x04 << (char)0x00
            << (char)0x10 << (char)0x03 << (char)0x04 << (char)0x06;
    }
            
    
};

class YardDrawer: public YardOutputDevice
{
 public:
     virtual bool Open();
     virtual bool Write(const string& str) { Open(); }
};

class YardDisplayPole: public YardOutputDevice
{
 public:
    virtual bool Write(const string& str) {}
};
    
#endif
