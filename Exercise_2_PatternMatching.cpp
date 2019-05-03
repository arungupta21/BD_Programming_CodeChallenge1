
#include<iostream>
#include<string>
#include<map>

using namespace std;


int TransitionTable[200][26] = {-1};

//Function to validate the pattern
// Returns 'true' if the tsring is valid; 'false' otherwise
bool ValidatePattern(string argPattern)
{
    for(int i = 0; i < argPattern.length(); i++)
    {
        //Check if the pattern contains only {A-Z, *, .}
        if( !(argPattern[i] == '*' ||
            argPattern[i] == '.' ||
            (argPattern[i] >= 'A' && argPattern[i] <= 'Z'))
        )

        return false;
    }

    return true;
}

// Function to validate the text string that is to be matched against the given pattern
// Returns 'true' if the string is valid; 'false' otherwise
bool ValidateText(string argText)
{
    for(int i = 0; i < argText.length(); i++)
    {
        //Check if the pattern contains only {A-Z, *, .}
        if( ! (argText[i] >= 'A' && argText[i] <= 'Z') )
            return false;
    }

    return true;
}

/*
Function: ConstructTransitionTable
Returns: An integer value that denotes the Acceptance State
*/
int ConstructTransitionTable(string argPattern)
{
    int i, j;

    if(argPattern == ".*")
    {
        for (int i = 0; i < 200; i++)
            for(int j = 0; j < 26; j++)
                TransitionTable[i][j] = 1;

        return 1;

    }

    // Initialise the Transition Table
    for (int i = 0; i < 200; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            TransitionTable[i][j] = -1;
        }
    }

    int current_state = 0;
    char prev_char = '\0';

    // Set the state transitions
    for(int i = 0; i < argPattern.length(); i++)
    {
        if(argPattern[i] >= 'A' && argPattern[i] <= 'Z'
           && TransitionTable[current_state][argPattern[i] - 65] == -1) 
        {
            TransitionTable[current_state][argPattern[i] - 65] = current_state+1; //65(the ascii value of 'A') is subtracted to get the corresponding index in the table

            current_state++;
            prev_char = argPattern[i];
            continue;
        }

        if(argPattern[i] == '*' && prev_char != '\0')
        {
            TransitionTable[current_state][prev_char - 65] = current_state; 
            continue;
        }

        if(argPattern[i] == '.')
        {
            for (int j = 0; j < 26; j++)    // For 26 character-set {'A' to 'Z'}
            {
                TransitionTable[current_state][j] = current_state+1;
            }
            prev_char = argPattern[i];
            current_state++;
            continue;
        }
        
    }

    return current_state;
}


// Function to match the text using the Transition Table
// Returns 'true' if the the text matches the pattern defined in transition table; 'false' otherwise
bool MatchText(string argText, int argAcceptanceState)
{
    int current_state = 0;
    for(int i = 0; i < argText.length(); i++)
    {
        current_state = TransitionTable[current_state][argText[i] - 65];
    }

    return (current_state == argAcceptanceState);
}

int main()
{
    string str_Text, str_Pattern;         // Input strings, for Pattern and Text

    cout<<"Enter the Pattern: ";  cin>>str_Pattern;

    // Check the sanity of the pattern
    if(!ValidatePattern(str_Pattern))
    {
        cout<<"\nInvalid Pattern!!\n Please enter a pattern containing {'A-Z', '*', '.'}";
        return 1;
    }


    cout<<"Enter the text to match: ";  cin>>str_Text;   

    //Check the validity of the text 
    if(!ValidateText(str_Text))
    {
        cout<<"\n Invalid Text!!\n Please enter Text containing {'A-Z'} only";
        return 1;
    }

    // Construct the Transition Table for the given pattern
    int Acceptance_State = ConstructTransitionTable(str_Pattern);

    // Match the text using the Transition Table
    if(MatchText(str_Text, Acceptance_State))
        cout<<"\n\nTRUE!!";
    else
        cout<<"\n\nFALSE!!";

    return 0;
}