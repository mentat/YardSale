#ifndef YS_DB_TYPE_H
#define YS_DB_TYPE_H

/**
 * @ingroup database
 *
 * Abstract base class for datebase objects in YardSale
 * @author Jesse Lovelace
 */
class YardDBType{
    public:
        
    /** Empty constructor */
    YardDBType() {}
        
    /** Empty copy constructor */
    YardDBType(const YardDBType& obj) {}
  
    /** Virtual destructor */
    virtual ~YardDBType() {}
    
};

/**
 * A temporary structure for holding date information
 */
struct DateTime {
    
    unsigned int year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
};

#endif
