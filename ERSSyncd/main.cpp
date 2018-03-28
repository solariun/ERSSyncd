//
//  main.cpp
//  ERSSyncd
//
//  Created by GUSTAVO CAMPOS on 26/03/18.
//  Copyright © 2018 GUSTAVO CAMPOS. All rights reserved.
//

#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <regex>
#include <string>

#include "iniplus.hpp"
#include "MetaException.hpp"



bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}


int main(int argc, char * const argv [])
{
    // insert code here...

    int aflag = 0;
    int bflag = 0;
    char *cvalue = NULL;
    int index;
    int c;
    
    opterr = 0;
    
    while ((c = getopt (argc, argv, "abc:-:")) != -1)
        switch (c)
    {
        case 'a':
            aflag = 1;
            break;
        case 'b':
            bflag = 1;
            break;
        case 'c':
            cvalue = optarg;
            break;
        case '-':
            fprintf (stderr, "special values: %s\n", optarg);
            break;
        case '?':
            if (optopt == 'c')
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr,
                         "Unknown option character `\\x%x'.\n",
                         optopt);
            return 1;
        default:
            abort ();
    }
    
    printf ("aflag = %d, bflag = %d, cvalue = %s\n",
            aflag, bflag, cvalue);
    
    for (index = optind; index < argc; index++)
        printf ("Non-option argument %s\n", argv[index]);
    
    
    regex regexINI (".*(ini|INI)");
    string strFileName; 
    
    cerr << "Loking into: " << argv [argc-1] << endl;
    
    if (regex_match (argv [argc-1], regexINI))
    {
        strFileName = argv [argc-1];
    }
    else
    {
        strFileName = "/desenv/samples/ERSSync.ini";
    }

    cerr << "Setting up to use INI: [" << strFileName << "]"  << endl;
    
    try
    {
        
        iniplus iniConf (strFileName.c_str());
        
    } catch (MetaException* metaEx)
    {
        cerr << "mensagem: " << metaEx->getExMessage() << endl;
    }
    
    
    return 0;
}
