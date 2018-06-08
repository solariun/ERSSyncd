//
//  StringPrettify.hpp
//  ERSSyncd
//
//  Created by GUSTAVO CAMPOS on 04/04/18.
//  Copyright © 2018 GUSTAVO CAMPOS. All rights reserved.
//

#ifndef StringPrettify_hpp
#define StringPrettify_hpp

#include <stdio.h>
#include <map>

#include "iniplus.hpp"


#define EXCEPT_PRETTY_VAR_NOT_FOUND             300
#define EXCEPT_PRETTY_VAR_INSERT_ERROR          301
#define EXCEPT_PRETTY_VAR_PARAMS_COUNT_ERR      302


class StringPrettify
{
protected:
    iniplus* iniConf = nullptr;
    map<string, string> mapVariable;
    
    map<string, string>::iterator getVarIterator (const string& strVarName);

    map<string, string>::iterator getSafeVarIterator (const string& strVarName);
    
    string call (const string pszIniPath);
    
public:
    StringPrettify (iniplus* iniConf);
    
    string process (const string strStringBase);

    
    void updateVariable (const string& strVarName, const string& strValue);
    string getVariableValue (const string& strVarName);
};


#endif /* StringPrettify_hpp */



