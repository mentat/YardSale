#include "ys_bitmaps.h"
#include "ys_exception.h"

#include "wx/bitmap.h"
#include "wx/string.h"
#include <iostream>

using namespace std;
#define TEXT_FIELD_WIDTH 40

wxChar filenames [][TEXT_FIELD_WIDTH] = { 
    "images/ys_employee_128x128.png",
    "images/ys_320x93.png",
    "images/back_64x64.png",
    "images/equals_64x64.png",
    "images/exec_64x64.png",
    "images/fileclose_64x64.png",
    "images/pinguim-root3.png",
    "images/pinguim-user.png",
    "images/pinguim-user2.png",
    "images/tux.png",
    "images/ys_customer_128x128.png",
    "images/ys_enlarge_64x64.png",
    "images/ys_inventory_128x128.png",
    "images/ys_logout_128x128.png",
    "images/ys_reports_128x128.png",
    "images/ys_sale_128x128.png",
    "images/ys_shrink_64x64.png",
    "images/calc_80x80.png",
    "images/keyboard_80x80.png",
    "images/undo_80x80.png",
    "images/trashcan_90x90.png"
};

YardBitmaps::YardBitmaps() {
    
    m_index = 0;
    m_length = sizeof(filenames)/TEXT_FIELD_WIDTH;
    m_bitmaps = new wxBitmap * [m_length];
    
    for (unsigned short i = 0; i < m_length; i++)
        m_bitmaps[i] = 0;
    
}

YardBitmaps::~YardBitmaps() {
    
    for (unsigned short i = 0; i < m_length; i++)
        delete m_bitmaps[i];
    
    delete [] m_bitmaps;
    
}

int YardBitmaps::LoadBitmaps() {
    
    m_bitmaps[m_index] = new wxBitmap(filenames[m_index], wxBITMAP_TYPE_PNG);
    
    if (!m_bitmaps[m_index])
        throw YardException("Bitmap not allocated");
    if (!m_bitmaps[m_index]->Ok())
        throw YardException("Bitmap data not present.");
    
    return (m_length - (++m_index));
      
}
    
wxBitmap& YardBitmaps::GetBitmap(unsigned int id) {

    if (id >= m_index)
        throw YardException("Invalid bitmap!");
    
    return *m_bitmaps[id];
    

}

#if (defined(YS_TEST_MAIN) || defined(YS_TEST_BITMAPS))
#include <iostream>
#include <vector>
#include "ys_test.h"

using namespace std;

int main()
{
    YardBitmaps test;
    
    try {
        while(test.LoadBitmaps() != 0){}
    } catch (YardException &e){
        VERIFY(0,1);
        cout << "YardException: " << e.what() << endl;
        return failure;
    }
    catch (exception &e) {
        VERIFY(0,1);
        cout << "std::exception: " << e.what() << endl;
        return failure;
    }
    catch(...) {
        VERIFY(0,1); 
        cout << "Unknown exception" << endl;
        return failure;
    }
    return failure;

}
#endif
