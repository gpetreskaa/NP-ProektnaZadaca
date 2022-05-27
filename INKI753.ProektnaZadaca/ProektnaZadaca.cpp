#include <iostream>
#include <string> 
#include <map> 
#include <vector>
#include <fstream> 
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

struct compare // sorting function
{
    template<typename T>
    bool operator()(const T &l, const T &r) const
    {
        if (l.second != r.second) {
            return l.second < r.second;
        }
 
        return l.first < r.first;
    }
};

int main() //Main program
{
    string name = "Gordana"; //info
    string lastname = "Petreska";
    int ix = 753; 
    int dob = 708;

    string city[10] =  {"Skopje", "Bitola", "Ohrid", "Stip", "Prilep", "Kicevo", "Sveti Nikole", "Veles", "Gevgelija", "Makedonski Brod"};
    map<string, int> covid2205; //declaring map
    map<string, int>::iterator iter; 

    string date; //specific date
    cout <<"New Covid cases in Macedonia for specific date: ";
    getline(cin, date); 
    cout<<"----------------------------------------"<<endl;
    

    for(;;) { //entering cities and infected amount
        string in; 
        cout << "Enter city and infected amount: ";
        std::getline(std::cin, in); 
        
        if (in == "") { 
            cout << endl << "No further data entered, processing..." << endl;
            break;
        }
        cout << endl;
        
        vector<string> words{}; //for cities with 2 names

        size_t pos = 0; 
        while ((pos = in.find(" ")) != string::npos) { 
            words.push_back(in.substr(0, pos)); 
            in.erase(0, pos + 1); 
        }
        
        int infected = stoi(in);
        string cityInfected = "";
        for(int i = 0; i != words.size(); ++i) {
             cityInfected = cityInfected + words[i];
        }  
        covid2205[cityInfected] = infected;
    }
    
    if (covid2205.size() < 10) { //if entered less than 10 cities, print 0 as default
        for (int i = 0; i < (sizeof (city) / sizeof city[0]); ++i) {
            if (covid2205.find(city[i]) == covid2205.end()) {
             covid2205[city[i]] = 0;   
            }
        }
    }
    cout<<endl;

    cout << "Cities and infected amounts: "<<endl; //print unsorted list
    for (iter=covid2205.begin();iter!=covid2205.end();iter++)
    cout << iter->first << " - "<< iter->second <<endl;
    
    cout << endl << endl;
    cout << "Sorted cities by infected amount from lowest to highest: " << endl; //print sorted list
    std::set<std::pair<std::string, int>, compare> set(covid2205.begin(), covid2205.end());
    for (auto const &pair: set) {
        std::cout << pair.first << " - " << pair.second << std::endl;
    }
    cout<<endl;

    
    covid2205.insert ( std::pair<string,int>("Gordana", 708) ); //adding two more pairs
    covid2205.insert ( std::pair<string,int>("INKI", 753) );

    /*If we were to print the pairs
    cout<<"List of cities and infected amounts plus two added pairs of information: "<<endl;
    for (iter=covid2205.begin();iter!=covid2205.end();iter++)
    cout << iter->first << " - "<< iter->second <<endl; 
    */
    
  

    covid2205["INKI"] = ix; 
    covid2205[name] = dob;
    string filename("INKI" + to_string(ix) + name + lastname); //creating file 
    ofstream file_out;

    file_out.open(filename, std::ios_base::app);
    file_out << "Date: " << date << endl;
    for (map<string, int>::iterator it = covid2205.begin(); it != covid2205.end(); it++)
    {
        file_out << it->first << " - " << it->second << endl;
    }
    
    file_out << endl;
    
    

    return 0;
}
