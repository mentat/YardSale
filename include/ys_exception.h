/*
    YardSale - The Open Point of Sale
    Copyright (C) 2004 - Jesse Lovelace <jllovela@ncsu.edu>
 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#ifndef YS_EXCEPTION_H
#define YS_EXCEPTION_H

#include <string>

using namespace std;

/**
* Exception class from CryptoPP.
* @author Wei Dai
*/
class YardException : public exception
{
 public:
    explicit YardException(const string &s) : m_what(s) {}
    virtual ~YardException() throw() {}
    const char *what() const throw() { return (m_what.c_str()); }
    const string &GetWhat() const { return m_what; }
    void SetWhat(const string &s) { m_what = s; }

 private:
    string m_what;
};

/**
 * A Database execption
 * @author Jesse Lovelace
 */
class YardDBException: public YardException {
 public:
        
    YardDBException(const string& err, const string& sql="", const string& vars="")
        :YardException(err), m_sql(sql), m_vars(vars) {}
    
    virtual ~YardDBException() throw() {}
    
    string GetSQL() const { return m_sql; }
    string GetVarInfo() const { return m_vars; }
 private:
    string m_sql;
    string m_vars;
};
/**
 * @ingroup database
   Database Error codes

   DB_ERR_GENERAL_WARNING                     // SqlState = '01000'
   DB_ERR_DISCONNECT_ERROR                    // SqlState = '01002'
   DB_ERR_DATA_TRUNCATED                      // SqlState = '01004'
   DB_ERR_PRIV_NOT_REVOKED                    // SqlState = '01006'
   DB_ERR_INVALID_CONN_STR_ATTR               // SqlState = '01S00'
   DB_ERR_ERROR_IN_ROW                        // SqlState = '01S01'
   DB_ERR_OPTION_VALUE_CHANGED                // SqlState = '01S02'
   DB_ERR_NO_ROWS_UPD_OR_DEL                  // SqlState = '01S03'
   DB_ERR_MULTI_ROWS_UPD_OR_DEL               // SqlState = '01S04'
   DB_ERR_WRONG_NO_OF_PARAMS                  // SqlState = '07001'
   DB_ERR_DATA_TYPE_ATTR_VIOL                 // SqlState = '07006'
   DB_ERR_UNABLE_TO_CONNECT                   // SqlState = '08001'
   DB_ERR_CONNECTION_IN_USE                   // SqlState = '08002'
   DB_ERR_CONNECTION_NOT_OPEN                 // SqlState = '08003'
   DB_ERR_REJECTED_CONNECTION                 // SqlState = '08004'
   DB_ERR_CONN_FAIL_IN_TRANS                  // SqlState = '08007'
   DB_ERR_COMM_LINK_FAILURE                   // SqlState = '08S01'
   DB_ERR_INSERT_VALUE_LIST_MISMATCH          // SqlState = '21S01'
   DB_ERR_DERIVED_TABLE_MISMATCH              // SqlState = '21S02'
   DB_ERR_STRING_RIGHT_TRUNC                  // SqlState = '22001'
   DB_ERR_NUMERIC_VALUE_OUT_OF_RNG            // SqlState = '22003'
   DB_ERR_ERROR_IN_ASSIGNMENT                 // SqlState = '22005'
   DB_ERR_DATETIME_FLD_OVERFLOW               // SqlState = '22008'
   DB_ERR_DIVIDE_BY_ZERO                      // SqlState = '22012'
   DB_ERR_STR_DATA_LENGTH_MISMATCH            // SqlState = '22026'
   DB_ERR_INTEGRITY_CONSTRAINT_VIOL           // SqlState = '23000'
   DB_ERR_INVALID_CURSOR_STATE                // SqlState = '24000'
   DB_ERR_INVALID_TRANS_STATE                 // SqlState = '25000'
   DB_ERR_INVALID_AUTH_SPEC                   // SqlState = '28000'
   DB_ERR_INVALID_CURSOR_NAME                 // SqlState = '34000'
   DB_ERR_SYNTAX_ERROR_OR_ACCESS_VIOL         // SqlState = '37000'
   DB_ERR_DUPLICATE_CURSOR_NAME               // SqlState = '3C000'
   DB_ERR_SERIALIZATION_FAILURE               // SqlState = '40001'
   DB_ERR_SYNTAX_ERROR_OR_ACCESS_VIOL2        // SqlState = '42000'
   DB_ERR_OPERATION_ABORTED                   // SqlState = '70100'
   DB_ERR_UNSUPPORTED_FUNCTION                // SqlState = 'IM001'
   DB_ERR_NO_DATA_SOURCE                      // SqlState = 'IM002'
   DB_ERR_DRIVER_LOAD_ERROR                   // SqlState = 'IM003'
   DB_ERR_SQLALLOCENV_FAILED                  // SqlState = 'IM004'
   DB_ERR_SQLALLOCCONNECT_FAILED              // SqlState = 'IM005'
   DB_ERR_SQLSETCONNECTOPTION_FAILED          // SqlState = 'IM006'
   DB_ERR_NO_DATA_SOURCE_DLG_PROHIB           // SqlState = 'IM007'
   DB_ERR_DIALOG_FAILED                       // SqlState = 'IM008'
   DB_ERR_UNABLE_TO_LOAD_TRANSLATION_DLL      // SqlState = 'IM009'
   DB_ERR_DATA_SOURCE_NAME_TOO_LONG           // SqlState = 'IM010'
   DB_ERR_DRIVER_NAME_TOO_LONG                // SqlState = 'IM011'
   DB_ERR_DRIVER_KEYWORD_SYNTAX_ERROR         // SqlState = 'IM012'
   DB_ERR_TRACE_FILE_ERROR                    // SqlState = 'IM013'
   DB_ERR_TABLE_OR_VIEW_ALREADY_EXISTS        // SqlState = 'S0001'
   DB_ERR_TABLE_NOT_FOUND                     // SqlState = 'S0002'
   DB_ERR_INDEX_ALREADY_EXISTS                // SqlState = 'S0011'
   DB_ERR_INDEX_NOT_FOUND                     // SqlState = 'S0012'
   DB_ERR_COLUMN_ALREADY_EXISTS               // SqlState = 'S0021'
   DB_ERR_COLUMN_NOT_FOUND                    // SqlState = 'S0022'
   DB_ERR_NO_DEFAULT_FOR_COLUMN               // SqlState = 'S0023'
   DB_ERR_GENERAL_ERROR                       // SqlState = 'S1000'
   DB_ERR_MEMORY_ALLOCATION_FAILURE           // SqlState = 'S1001'
   DB_ERR_INVALID_COLUMN_NUMBER               // SqlState = 'S1002'
   DB_ERR_PROGRAM_TYPE_OUT_OF_RANGE           // SqlState = 'S1003'
   DB_ERR_SQL_DATA_TYPE_OUT_OF_RANGE          // SqlState = 'S1004'
   DB_ERR_OPERATION_CANCELLED                 // SqlState = 'S1008'
   DB_ERR_INVALID_ARGUMENT_VALUE              // SqlState = 'S1009'
   DB_ERR_FUNCTION_SEQUENCE_ERROR             // SqlState = 'S1010'
   DB_ERR_OPERATION_INVALID_AT_THIS_TIME      // SqlState = 'S1011'
   DB_ERR_INVALID_TRANS_OPERATION_CODE        // SqlState = 'S1012'
   DB_ERR_NO_CURSOR_NAME_AVAIL                // SqlState = 'S1015'
   DB_ERR_INVALID_STR_OR_BUF_LEN              // SqlState = 'S1090'
   DB_ERR_DESCRIPTOR_TYPE_OUT_OF_RANGE        // SqlState = 'S1091'
   DB_ERR_OPTION_TYPE_OUT_OF_RANGE            // SqlState = 'S1092'
   DB_ERR_INVALID_PARAM_NO                    // SqlState = 'S1093'
   DB_ERR_INVALID_SCALE_VALUE                 // SqlState = 'S1094'
   DB_ERR_FUNCTION_TYPE_OUT_OF_RANGE          // SqlState = 'S1095'
   DB_ERR_INF_TYPE_OUT_OF_RANGE               // SqlState = 'S1096'
   DB_ERR_COLUMN_TYPE_OUT_OF_RANGE            // SqlState = 'S1097'
   DB_ERR_SCOPE_TYPE_OUT_OF_RANGE             // SqlState = 'S1098'
   DB_ERR_NULLABLE_TYPE_OUT_OF_RANGE          // SqlState = 'S1099'
   DB_ERR_UNIQUENESS_OPTION_TYPE_OUT_OF_RANGE // SqlState = 'S1100'
   DB_ERR_ACCURACY_OPTION_TYPE_OUT_OF_RANGE   // SqlState = 'S1101'
   DB_ERR_DIRECTION_OPTION_OUT_OF_RANGE       // SqlState = 'S1103'
   DB_ERR_INVALID_PRECISION_VALUE             // SqlState = 'S1104'
   DB_ERR_INVALID_PARAM_TYPE                  // SqlState = 'S1105'
   DB_ERR_FETCH_TYPE_OUT_OF_RANGE             // SqlState = 'S1106'
   DB_ERR_ROW_VALUE_OUT_OF_RANGE              // SqlState = 'S1107'
   DB_ERR_CONCURRENCY_OPTION_OUT_OF_RANGE     // SqlState = 'S1108'
   DB_ERR_INVALID_CURSOR_POSITION             // SqlState = 'S1109'
   DB_ERR_INVALID_DRIVER_COMPLETION           // SqlState = 'S1110'
   DB_ERR_INVALID_BOOKMARK_VALUE              // SqlState = 'S1111'
   DB_ERR_DRIVER_NOT_CAPABLE                  // SqlState = 'S1C00'
   DB_ERR_TIMEOUT_EXPIRED                     // SqlState = 'S1T00'
*/
#endif
