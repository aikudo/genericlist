// $Id: main.cpp,v 1.1 2014-05-25 13:17:09-07 - - $

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>

using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"

typedef xpair<string,string> str_str_pair;
//listmap<typename> listvar;
typedef listmap<string,string> str_str_map;

void scan_options (int argc, char** argv) {
   opterr = 0;
   for (;;) {
      int option = getopt (argc, argv, "@:");
      if (option == EOF) break;
      switch (option) {
         case '@':
            traceflags::setflags (optarg);
            break;
         default:
            complain() << "-" << (char) optopt << ": invalid option"
                       << endl;
            break;
      }
   }
}

typedef enum opr {
   op_noop,
   op_readkey,
   op_delkey,
   op_setkey,
   op_printall,
   op_printallkey
}opr;

opr decode(const string & line){
   size_t found = line.find_first_of('=');
   opr op = op_noop;
   string keystr, valuestr;
   if(found == string::npos){ // no equal found
      op = op_readkey;
      keystr = line;
   }else if(line.size() == 1){ // =
      op = op_printall;
   }else if(found == 0){ // = value
      op = op_printallkey;
      valuestr = line.substr(found+1);//all after =
      trim(valuestr);
   }else if(found == line.size()-1){  // = @ end of line
      op = op_delkey;
      keystr = line.substr(0, found-1);
      trim(keystr);
   }else{ //key = value
      op = op_setkey;
      keystr = line.substr(0, found-1);
      valuestr = line.substr(found+1, line.size());
      trim(keystr);
      trim(valuestr);
   }
   return op;
}

int main (int argc, char** argv) {
   sys_info::set_execname (argv[0]);
   scan_options (argc, argv);
   str_str_map test;
   string line;
   ifstream filein;

   test.insert({"key1", "val1"});
   test.insert({"key2", "val2"});
   test.insert({"key3", "val3"});
   str_str_map::iterator itor;
   int  i = 0;
   for(itor = test.begin(); itor != test.end() ; ++itor){
      cout<<  "number of item " << i++ << endl;
      cout <<  *itor  << endl;
   }
   itor.erase();

  // const str_str_map::iterator citor;
   /*
   itor = test.find("key2");
   cout <<  *itor  << endl;
   */

   sys_info::cleanup(); //remove execname
   return(0);
   /*

   for (int argi = 1; argi < argc; ++argi) {
      cout<<"openning " << argv[argi] << endl;
      filein.open(argv[argi]);
      if( filein.is_open() ){
         int linr=0;
         while ( getline (filein, line)){
            trim(line);
            ++linr;
            if(line.size() == 0 || line[0] == '#') continue;
            cout << argv[argi] << ": " << linr 
               << ": " + line << endl;
            decode(line);
         }
      }else{ 
         cout << "can't open file: " << argv[argi] << endl;
      str_str_pair pair (argv[argi], to_string<int> (argi));
      cout << "Before insert: " << pair << endl;
      test.insert (pair);
      }
      filein.close();
   }
   else{
      while( getline(cin, line)){
         cout << line << endl;
      }
   }

   exit(1);

   for (str_str_map::iterator itor = test.begin();
        itor != test.end(); ++itor) {
      cout << "During iteration: " << *itor << endl;
   }

   str_str_map::iterator itor = test.begin();
   itor.erase();
   */

   cout << "EXIT_SUCCESS" << endl;
   return EXIT_SUCCESS;
}

