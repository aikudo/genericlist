// $Id: util.h,v 1.1 2014-05-25 13:17:09-07 - - $

//
// util -
//    A utility class to provide various services not conveniently
//    associated with other modules.
//

#ifndef __UTIL_H__
#define __UTIL_H__

#include <iostream>
#include <list>
#include <stdexcept>
#include <string>

using namespace std;

#include "trace.h"

//
// sys_info -
//    Keep track of execname and exit status.  Must be initialized
//    as the first thing done inside main.  Main should call:
//       sys_info::set_execname (argv[0]);
//    before anything else.
//

class sys_info {
   public:
      static void cleanup();
      static const string& get_execname ();
      static void set_exit_status (int status);
      static int get_exit_status ();
   private:
      friend int main (int argc, char** argv);
      static void set_execname (const string& argv0);
      static string* execname;
      static int exit_status;
};

//
// datestring -
//    Return the current date, as printed by date(1).
//

const string datestring ();

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

// trim from start
static inline std::string &ltrim(std::string &s) {
   //erase from beging to first non-white spacespace
   s.erase(s.begin(),
         std::find_if( s.begin(), s.end(),
            //find the first non-white-space
            std::not1( std::ptr_fun<int, int>(std::isspace) )
            )
         );
   return s;
}


// trim from end
static inline std::string &rtrim(std::string &s) {
   s.erase(
         std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
         s.end());
   return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
   return ltrim(rtrim(s));
}



//
// split -
//    Split a string into a list<string>..  Any sequence
//    of chars in the delimiter string is used as a separator.  To
//    Split a pathname, use "/".  To split a shell command, use " ".
//

list<string> split (const string& line, const string& delimiter);


//
// complain -
//    Used for starting error messages.  Sets the exit status to
//    EXIT_FAILURE, writes the program name to cerr, and then
//    returns the cerr ostream.  Example:
//       complain() << filename << ": some problem" << endl;
//

ostream& complain();

//
// syscall_error -
//    Complain about a failed system call.  Argument is the name
//    of the object causing trouble.  The extern errno must contain
//    the reason for the problem.
//

void syscall_error (const string&);

//
// operator<< (list) -
//    An overloaded template operator which allows lists to be
//    printed out as a single operator, each element separated from
//    the next with spaces.  The item_t must have an output operator
//    defined for it.
//

template <typename item_t>
ostream& operator<< (ostream& out, const list<item_t>& vec);

//
// string to_string (thing) -
//    Convert anything into a string if it has an ostream<< operator.
//

template <typename item_t>
string to_string (const item_t&);

//
// thing from_string (cons string&) -
//    Scan a string for something if it has an istream>> operator.
//

template <typename item_t>
item_t from_string (const string&);

//
// Put the RCS Id string in the object file.
//

#include "util.tcc"
#endif

