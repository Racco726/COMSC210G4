// Group 4

#include <iostream>
#include <string>
using namespace std;

#include <fstream>
#include <cstring>
#include <iomanip>

#include "FP_AssociativeArray.h"

#include <algorithm> //


struct Major
{
    string name;
    string department;
    double admitGpaHigh;
    double admitGpaLow;
    double enrollGpaHigh;
    double enrollGpaLow;

    string applicationNum;
    string admitNum;
    string enrollNum;

    string admitRate;
    string yieldRate;
};


// prototype
void displayMajorInfo(AssociativeArray<string, AssociativeArray<string, Major>>& , vector<vector<string>>&, vector<string>);
int menu(AssociativeArray<string, AssociativeArray<string, Major>>& , vector<vector<string>>&, vector<string>);
void specificInfo(AssociativeArray<string, AssociativeArray<string, Major>>& , string , string );

//from 9
void associativeBubbleSorting(AssociativeArray<int, string>&);
void vectorBubbleSorting(vector<string>&);


int main()
{
    AssociativeArray<string, AssociativeArray<string, Major>> schools;

    AssociativeArray<string,string> filenames;
    filenames["UCB"] = "UC_Berkeley.txt";
    filenames["UCLA"] = "UC_LosAngeles.txt"; // need to add all

    vector<string> v_fstring = filenames.keys();

    // Input Declaration
    char *token;
    char buf[1000];
    const char *const tab = "\t";


    ifstream fin;
    // Loop & Parsing
    for (int i = 0; i < v_fstring.size(); i++)
    {
        fin.open(filenames[v_fstring.at(i)]);

        if (!fin.good())
            throw "I/O error";

        while (fin.good())
        {
            string line;
            getline(fin, line);
            strcpy(buf, line.c_str());

            if (buf[0] == 0)
                continue;

            // parsing
            const string broadDiscipline(token = strtok(buf, tab));
            if (broadDiscipline == "Broad Discipline ")
            {
                continue;
            }
            const string college((token = strtok(0, tab)) ? token : "");
            const string majorName((token = strtok(0, tab)) ? token : "");
            const string admitGPA((token = strtok(0, tab)) ? token : "");
            const string admitR((token = strtok(0, tab)) ? token : "");
            const string enrollGPA((token = strtok(0, tab)) ? token : "");
            const string yieldR((token = strtok(0, tab)) ? token : "");
            const string admitNum((token = strtok(0, tab)) ? token : "");
            const string applicantNum((token = strtok(0, tab)) ? token : "");
            const string enrollNum((token = strtok(0, tab)) ? token : "");

            // store strings
            string enrollGpaL;
            string enrollGpaH;
            if (enrollGPA.find('-') == string::npos) // if data is masked
            {
                enrollGpaL = "0";
                enrollGpaH = "0";
            }
            else
            {
                string temp1(enrollGPA.begin(), enrollGPA.begin() + enrollGPA.find('-'));
                enrollGpaL = temp1;
                string temp2(enrollGPA.begin() + enrollGPA.find('-') + 1, enrollGPA.end());
                enrollGpaH = temp2;
            }

            string admitGpaL;
            string admitGpaH;
            if (admitGPA.find('-') == string::npos)
            {
                admitGpaL = "0";
                admitGpaH = "0";
            }
            else
            {
                string temp1(admitGPA.begin(), admitGPA.begin() + admitGPA.find('-'));
                admitGpaL = temp1;
                string temp2(admitGPA.begin() + admitGPA.find('-') + 1, admitGPA.end());
                admitGpaH = temp2;
            }

            // check duplicates & store key & counts
            Major tempMajor = {majorName, college, 
            atof(admitGpaH.c_str()), 
            atof(admitGpaL.c_str()), 
            atof(enrollGpaH.c_str()), 
            atof(enrollGpaL.c_str()),
            applicantNum,
            admitNum,
            enrollNum,
            admitR,
            yieldR};
            schools[v_fstring.at(i)][majorName] = tempMajor;
        }
        fin.close();
    }
    //----------------------------------------------------------------------------------------------------------------------------------------------------
    

    // sort and store
    vector<vector<string>> v_majors;

    for(int i = 0; i < schools.size(); i++)
    {
            v_majors.push_back(schools[v_fstring.at(i)].keys());
    }
    
    for(int i = 0; i < v_majors.size(); i++)
    {
        vectorBubbleSorting(v_majors.at(i));
    }


    // user interface begins
    menu(schools, v_majors, v_fstring);
    
    cout << "\n\n    GOOD BYE ! \n\n";

    return 0;
}



int menu(AssociativeArray<string, AssociativeArray<string, Major>>& schools, vector<vector<string>>& v_majors, vector<string> v_fstring)
{
    cout << "------------------------" << endl;
    cout << "1. Search Major" << endl;
    cout << "2. Check Required Course" << endl;
    cout << "3. Check My GPA" << endl;
    cout << "4. QUIT" << endl;
    cout << "------------------------" << endl;

    int choice;
    do
    {
        cout << "\nEnter a number(1-5):  ";
        choice = 0;
        string buf = string();
        getline(cin, buf);
        choice = atoi(buf.c_str());
        
    }while (choice < 0 || choice > 5);

    switch(choice)
    {
        case 1:
            displayMajorInfo(schools, v_majors, v_fstring);
            break;
        case 2:
            
        case 3:
            cout << "NOT VALIABLE" << endl;
            break;
        case 4:
            return 1;
    }

    cout << "Enter Q/q to Quit: ";
    string buf;
    getline(cin, buf);
    if(buf == "Q" || buf == "q")
    {
        return 1;
    }else
    {
        menu(schools, v_majors, v_fstring);
    }
}


// show major info by every school
void displayMajorInfo(AssociativeArray<string, AssociativeArray<string, Major>>& array, vector<vector<string>>& v_majors, vector<string> univName) 
{
    string tempmajor;
    cout << "Enter Name of Major: ";
    getline(cin, tempmajor);

    string keyword = string();
    for(int i = 0; i < tempmajor.length(); i++)
    {
        keyword += toupper(tempmajor.at(i));
    }
    int listNum = 1;

    vector<string> mlist;

    vector<vector<string>> major2D = v_majors;
    vector<string> temp_UnivName = univName;
    for(int i = 0; i < major2D.size(); i++)
    {   
        cout << "\n" << temp_UnivName.at(i) << ":" << endl;
        for(int j = 0; j < v_majors.at(i).size(); j++){
            if (strstr(array[temp_UnivName.at(i)][major2D.at(i).at(j)].name.c_str(),keyword.c_str()) != NULL)
            {
                cout << "(" << listNum++ << ") > " << setw(45) << left << array[temp_UnivName.at(i)][major2D.at(i).at(j)].name << endl;
                mlist.push_back(temp_UnivName.at(i));
                mlist.push_back(array[temp_UnivName.at(i)][major2D.at(i).at(j)].name);
            }
        }
    }
    cout << "\nEnter The Number to Look Specific Information(Q/q to Quit): ";
    getline(cin, keyword);
    int choice = atoi(keyword.c_str());
    specificInfo(array, mlist.at(choice*2),mlist.at(choice*2-1));
}

// sort vector
void vectorBubbleSorting(vector<string>& array)
{
    for (int i = 0; i < array.size(); i++)
    {
        for (int j = i + 1; j < array.size(); j++)
        {
            if (array[j] < array[i])
            {
                swap(array[i], array[j]);
            }
        }
    }
}

// sort AssociativeArray
void associativeBubbleSorting(AssociativeArray<int, string>& array)
{
    for (int i = 0; i < array.size(); i++)
    {
        for (int j = i + 1; j < array.size(); j++)
        {
            if (array[j] < array[i])
            {
                swap(array[i], array[j]);
            }
        }
    }
}

void specificInfo(AssociativeArray<string, AssociativeArray<string, Major>>& array, string school, string major)
{
    cout << "\n > " << school << ",\n   " << major << endl;
    cout << setw(45) << "" << "  Department:   " <<  array[school][major].department << endl;
    cout << setw(45) << "" << "   Admit GPA:   "; 
    if(array[school][major].admitGpaHigh == 0)
    {
        cout << "masked" << endl;
    }else{
      cout << setprecision(2) << fixed << array[school][major].admitGpaLow << "-" << array[school][major].admitGpaHigh << endl;
    }
    cout << setw(45) << "" << "  Enroll GPA:   ";
    if(array[school][major].enrollGpaHigh == 0)
    {
        cout << "masked" << endl;
    }else{
      cout << setprecision(2) << fixed << array[school][major].enrollGpaLow << "-" << array[school][major].enrollGpaHigh << endl;
    }
    cout << setw(45) << "" << "  Applicants:   ";
    if(array[school][major].applicationNum == "masked")
    {
        cout << "masked" << endl;
    }else{
      cout << array[school][major].applicationNum << endl;
    }
    cout << setw(45) << "" << "      Admits:   ";
    if(array[school][major].admitNum == "masked")
    {
        cout << "masked" << endl;
    }else{
      cout << array[school][major].admitNum << endl;
    }
    cout << setw(45) << "" << "     Enrolls:   ";
    if(array[school][major].enrollNum == "masked")
    {
        cout << "masked" << endl;
    }else{
      cout << array[school][major].enrollNum << endl;
    }
    cout << setw(45) << "" << "   Admit Rate:   ";
    if(array[school][major].admitRate == "masked")
    {
        cout << "masked" << endl;
    }else{
      cout << array[school][major].admitRate << endl;
    }
    cout << setw(45) << "" << "   Yield Rate:   ";
    if(array[school][major].yieldRate == "masked")
    {
        cout << "masked" << endl;
    }else{
      cout << array[school][major].yieldRate << endl;
    }
    
}

void checkMyGpa(double myGpa)
{

}