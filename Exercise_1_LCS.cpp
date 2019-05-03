
#include<iostream>
#include<string>

using namespace std;

/*
Function to get the Longest Common Sequence(LCS)
Author: Arun Gupta

Parameters:
str1: The pivot string
str2: The string to get the LCS from, using the pivot string
strLCS: Reference to the LCS String, which can be used by the calling function.

Return Value: 
-1 : If no LCS is found
>= 0: If some LCS is found 

*/
int CommonSubsequence(string str1, string str2, string& strLCS)
{
    strLCS = "";
    int nLastMatchIndex = -1;   //Integer to keep the index of the last match in str2

    for(int i = 0; i < str1.length(); i++)
    {
        for(int j = (nLastMatchIndex + 1); j < str2.length(); j++ )
        {
            if(str1[i] == str2[j]) //match
            {                  
                strLCS.append(1, str1[i]);
                nLastMatchIndex = j;
                break;  // skip reading str2 further for current iteration of str1
            }
        }
    }

    return nLastMatchIndex;
}


int main()
{
    string str1, str2;         // For 2 input strings
    
    string strLCS1, strLCS2;   // For 2 LCS's  
  
    cout<<"Enter String 1: ";  cin>>str1;
    cout<<"Enter String 2: ";  cin>>str2;   

    int nResult1 = CommonSubsequence(str1, str2, strLCS1);     //Get the LCS taking first string as the pilot
    int nResult2 = CommonSubsequence(str2, str1, strLCS2);     //Get the LCS taking second string as the pilot
    

    if(nResult1 <= 0 && nResult2 <= 0)
    {
        cout<<"No LCS found";
    }
    else
    {
        if(strLCS1.length() > strLCS2.length())
            cout<<"\nThe LCS = "<<strLCS1<<"\n\n";
        else
            cout<<"\nThe LCS = "<<strLCS2<<"\n\n";        
    }   

    return 0;
}