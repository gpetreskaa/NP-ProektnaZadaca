#include <iostream>
#include <string> 
#include <map> 
#include <vector>
#include <fstream> 
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

struct compare //функција за сортирање compare. Користиме struct затоа што овозможува групирање на повеќе поврзани променливи на едно место
{
    template<typename T>//Template користиме за пренос на типот на податоци како параметар за истиот код да не го пишуваме за различни типови податоци
    bool operator()(const T &l, const T &r) const /*Се прави компарација меѓу два члена од типот pair. Прво проверува дали first property на парот е различно
    и доколку е тогаш прави compare на нив два. Доколку се еднакви тогаш прави compare на second property*/
    {
        if (l.second != r.second) {
            return l.second < r.second;
        }
 
        return l.first < r.first;
    }
};

int main() //Main програма
{
    string name = "Gordana"; //име
    string lastname = "Petreska"; //презиме     
    int ix = 753; //индекс
    int dob = 708; //датум на раѓање

    string city[10] =  {"Skopje", "Bitola", "Ohrid", "Stip", "Prilep", "Kicevo", "Sveti Nikole", "Veles", "Gevgelija", "Makedonski Brod"};
    map<string, int> covid2205; //декларираме мапа со име covid2205 за датум 22.05.2022 и итератоr кој ни овозможува пристап до посебни елементи
    map<string, int>::iterator iter; 

    string date; //декларираме стринг дата и внесуваме преку конзола за кој датум важат податоците 
    cout <<"New Covid cases in Macedonia for specific date: ";
    getline(cin, date); 
    cout<<"----------------------------------------"<<endl;
    

    for(;;) { //ги внесуваме грдовите и бројот на заразени
        string in; 
        cout << "Enter city and infected amount: ";
        std::getline(std::cin, in); 
        
        if (in == "") { // доколку не се внеси вредност печатиме 
            cout << endl << "No further data entered, processing..." << endl;
            break;
        }
        cout << endl;
        
        vector<string> words{}; //За кодот да прима градови со две имиња, конвертира карактер вектор во стринг со користење на стринг функцијата

        size_t pos = 0; 
        while ((pos = in.find(" ")) != string::npos) { 
            words.push_back(in.substr(0, pos)); //додавање елемент на крајот на стрингот
            in.erase(0, pos + 1); 
        }
        
        int infected = stoi(in); //конвертира стринг во Integer
        string cityInfected = "";
        for(int i = 0; i != words.size(); ++i) {
             cityInfected = cityInfected + words[i];
        }  
        covid2205[cityInfected] = infected;
    }
    
    if (covid2205.size() < 10) { //Доколку внесиме помалку од 10 градови да се печати вредност за останатите градови 0 како default
        for (int i = 0; i < (sizeof (city) / sizeof city[0]); ++i) {
            if (covid2205.find(city[i]) == covid2205.end()) {
             covid2205[city[i]] = 0;   
            }
        }
    }
    cout<<endl;

    cout << "Cities and infected amounts: "<<endl; //Се печати несортирана листа
    for (iter=covid2205.begin();iter!=covid2205.end();iter++)
    cout << iter->first << " - "<< iter->second <<endl;
    
    cout << endl << endl;
    cout << "Sorted cities by infected amount from lowest to highest: " << endl; //Се печати сортирана листа
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
