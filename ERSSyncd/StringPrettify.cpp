//
//  StringPrettify.cpp
//  ERSSyncd
//
//  Created by GUSTAVO CAMPOS on 04/04/18.
//  Copyright © 2018 GUSTAVO CAMPOS. All rights reserved.
//

#include "StringPrettify.hpp"
#include <Exception.hpp>
#include <iniplus.hpp>

#include <sstream>
#include <queue>
#include <vector>
#include <regex>

static const string str = "";

StringPrettifyException::StringPrettifyException (std::string strMessage, uint nErrorID): Exception ("iniplus", strMessage, nErrorID)
{}


StringPrettify::StringPrettify (iniplus* iniConf) : iniConf(iniConf)
{
    return;
}


map<string, string>::iterator StringPrettify::getSafeVarIterator (const string& strVarName)
{
    return  mapVariable.find(strVarName);;
}


map<string, string>::iterator StringPrettify::getVarIterator (const string& strVarName)
{
    map<string,string>::iterator mapPos = getSafeVarIterator(strVarName);
    
    Verify (mapPos != mapVariable.end(), (str + "Error, Variable not found.  (" + strVarName + ")").c_str(), EXCEPT_PRETTY_VAR_NOT_FOUND, StringPrettifyException);
    
    return mapPos;
}


void StringPrettify::updateVariable (const string& strVarName, const string& strValue)
{
    map<string,string>::iterator mapPos = getSafeVarIterator(strVarName);
    
    try
    {
        if (mapPos != mapVariable.end())
        {
            mapVariable [strVarName] = strValue;
        }
        else
        {
            mapVariable.insert (pair<string,string>(strVarName, strValue));
        }
    } catch (exception ex)
    {
        throw Exception("StringPrettify", str + "Error, no new " + ex.what(), EXCEPT_PRETTY_VAR_INSERT_ERROR);
    }
    
}

string StringPrettify::getVariableValue (const string& strVarName)
{
    map<string,string>::iterator mapPos = getVarIterator (strVarName);
    
    return mapPos->second;
}

string StringPrettify::process (const string strStringBase)
{
    string strWork = "";
    string strData = "";
    
    char chChar = '\0';
    
    enum _tp
    {
        none,
        string
    };
    
    _tp nType = none;
    
    for (int nCount=0; nCount < strStringBase.length(); nCount++)
    {
        chChar = strStringBase [nCount];
        
        if (nType == none)
        {
            if (chChar == '$' && (nCount+1) < strStringBase.length() && strStringBase [nCount+1] == '{')
            {
                nCount++;
                
                nType = string;
                strData = "";
                
            }
            else
            {
                strWork += chChar;
            }
        }
        else if (nType == string)
        {
            if (chChar == '}')
            {
                if (strData.length() > 0)
                {
                    strData = call ("TRANSFORM_" + Util::strToUpper(strData));
                }
                
                nType = none;
            }
            else
            {
                strData += chChar;
            }
        }
    }
    
    return strWork;
}



string StringPrettify::call (const string strIniPath)
{
    string strWorking;
    
    string strProcData = "";
    
    const char szToken [2] = { ' ', '\t' };
    
    iniConf->getStringFromRef(strWorking, (strIniPath + ".Source").c_str());
    
    TRACE << "Source data [" << strWorking << "]: Value: [";
    
    //Revieling the data used
    strWorking = getVariableValue(strWorking);
    
    TRACE << strWorking << "]" << endl; 
    
    queue<string> queueCommand;
    vector<std::string> vectorContainer;
    
    vectorContainer.resize(10);
    
    
    for (int nCount=1; iniConf->Exists((strIniPath + ".Steps." + to_string(nCount)).c_str()); nCount++)
    {
        strProcData = iniConf->getRawString((strIniPath + ".Steps." + to_string(nCount)).c_str());
        
        TRACE << "Retriving: Steps." << nCount << ": " << strProcData << endl;
        
        uint nParams = Util::getCSVlikeParser(strProcData, szToken, sizeof (szToken), vectorContainer);
        
        TRACE << "Command: [" << vectorContainer [0] << "]" << endl;
       

        if (vectorContainer [0].compare("Get") == 0)
        {
            VERIFY (nParams == 2, EXCEPT_PRETTY_VAR_PARAMS_COUNT_ERR, (str+"Number of params is wrong.... (" + to_string(nParams) + ")").c_str());
            
            string strRegex = vectorContainer [1];
            
            TRACE << "    -> Param [" << strRegex << "]" << endl;
            
            regex regexSentence (strRegex);
            smatch smatchData;
            
            if (regex_search (strWorking, smatchData, regexSentence))
            {
                TRACE << "   REGEX: [" << smatchData [0] << "]" << endl;
            }
        }
    }
    
    return strWorking;
}





