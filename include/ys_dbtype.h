#ifndef YS_DB_TYPE_H
#define YS_DB_TYPE_H

/**
 * Abstract base class for datebase objects in YardSale
 * @author Jesse Lovelace
 */
class YardDBType{
    public:
        
    YardDBType() {}
    YardDBType(const YardDBType& obj) {}
  
    virtual ~YardDBType() {}
    
    private:
        
    
};

struct DateTime {
    
    unsigned int year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
};

#endif
