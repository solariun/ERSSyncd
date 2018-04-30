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

#include "Tests.hpp"

iniplus *iniConf = nullptr;


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
    
    
    Tests::executeTests(argc, argv);

    return 0;
}
