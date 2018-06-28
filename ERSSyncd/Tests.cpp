//
//  Tests.cpp
//  ERSSyncd
//
//  Created by GUSTAVO CAMPOS on 04/04/18.
//  Copyright © 2018 GUSTAVO CAMPOS. All rights reserved.
//

#include "Tests.hpp"


extern iniplus *iniConf;

void Tests::executeTests (int argc, char * const argv [])
{
    
    
    regex regexINI ("(ini|INI)$");
    string strFileName;
    
    cerr << "Loking into: " << argv [argc-1] << endl;
    
    if (regex_search (argv [argc-1], regexINI))
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
        int nCount=0;
        
        iniConf = new iniplus  (strFileName.c_str());
        
        //cerr << iniConf->getULongLongFromBinary  ("TESTS.Value_4") << endl;
        
        VERIFY (iniConf->getLong ("TESTS.Value_1") == 1, ++nCount, "Error, no Long returned");
        VERIFY (iniConf->getInteger ("TESTS.Value_2") == 2, ++nCount, "Error, no Integer returned");
        VERIFY (iniConf->getLong  ("TESTS.Value_3") == 0xfaaf3, ++nCount, "Error, no Long returned");
        VERIFY (iniConf->getULongLongFromBinary  ("TESTS.Value_4") == 81593, ++nCount, "Error, no valid binary convertion");
        
        VERIFY (iniConf->getDouble ("TESTS.Level_1.Level_2.Value_1") == 10.34f, ++nCount, "Error, no float on multi-level returned");

        
        StringPrettify strPrettify (iniConf);
        
        strPrettify.updateVariable("CurrentPath", "In order to examine all matches within the target sequence, std::regex_search may be called in a loop, restarting each time from m[0].second of the previous call. std::regex_iterator offers an easy interface to this iteration.");
        
        strPrettify.process("_${NE_NAME}/ransharing02/tim/vivo/ericsson/performance/SubNetwork=ONRM_ROOT_MO/MeContext=<${NE_NAME}>/");
        
    } catch (Exception& metaEx)
    {
        cerr << "mensagem: " << metaEx.what() << endl;
    }
    
    if (iniConf != nullptr)
    {
        delete iniConf;
    }
    
}
