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
        ofstream printer("/dev/ttyS0");
        printer << "Hi\n\n\n";
    }
    void SetRed()
    {
        ofstream printer("/dev/ttyS0", ios::out | ios::binary);
        printer << 0x1b << 0x2d << 1;
    }
    void SetBlack()
    {

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
