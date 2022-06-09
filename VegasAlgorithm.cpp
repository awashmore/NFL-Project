#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;

double PredictWinner(string hpf, string hpa, string apf, string apa) {
    double homePF = stod(hpf); //turns all of the string values into doubles
    double homePA = stod(hpa);
    double awayPF = stod(apf);
    double awayPA = stod(apa);
    double offense, defense;

    //Current algorithm
    //TODO: Update algorithm
    if (homePF > awayPF) 
        offense = abs(homePF - awayPF);
    else
        offense = 0.0 - abs(homePF - awayPF);
    if (homePA < awayPA) 
        defense = abs(awayPA - homePA);
    else
        defense = 0.0 - abs(awayPA - homePA);

    double score = offense + defense;
    return score;
}

int main(int argc, char *argv[]) {
    ifstream f;
    ofstream fRatings;

    f.open("VegasNumbers.csv"); //opens excel spreadsheet made from Vegas.py
    fRatings.open("TeamRatings.csv"); //opens new excel spreadsheet to write to

    fRatings.precision(4);
    std::cout.precision(4);

    fRatings << "Team Name,HOR,HDR,AOR,ADR"; //write the columns to the spreadhseet

    vector<vector<double>> teamRatings(32); //create a vector of vectors to contain all of the data from VegasNumbers.csv

    string tempLine, tempData, teamName;
    int count = 1;
    double awayGames, homeGames, hor, hdr, aor, adr;

    for (int i = 0; i < 32; i++) { //initialize the vector
        teamRatings[i].push_back(0.0);
        teamRatings[i].push_back(0.0);
        teamRatings[i].push_back(0.0);
        teamRatings[i].push_back(0.0);
    }

    getline(f, tempLine);
    for (int i = 0; i < 32; i++) {
        homeGames = 0;
        awayGames = 0;

        getline(f, tempLine);
        stringstream ss(tempLine);
        getline(ss, teamName, ','); //gets team's name

        fRatings << '\n' << teamName;

        for (int j = 1; j <= 18*4; j++) { //18 weeks times 4 columns, the 18 will be updated anytime a new week occurs
            getline(ss, tempData, ',');
            if (tempData == "") {}
            else {
                switch(count) {
                    case 1: //this is the week
                    count++;
                    break;

                    case 2: //home or away case
                    if (tempData == "1.0") {
                        homeGames++;
                        count = 3;
                    }
                    else {
                        awayGames++;
                        count = 5;
                    }
                    break;

                    case 3: //home points for case
                    hor = stod(tempData);
                    teamRatings[i][0] += hor;
                    count++;
                    break;

                    case 4: //home points against case
                    hdr = stod(tempData);
                    teamRatings[i][1] += hdr;
                    count = 1;
                    break;

                    case 5: //away points for case
                    aor = stod(tempData);
                    teamRatings[i][2] += aor;
                    count++;
                    break;

                    case 6: //away points against case
                    adr = stod(tempData);
                    teamRatings[i][3] += adr;
                    count = 1;
                    break;
                }
                // getTeamRatings(teamRatings, hor, hdr, aor, adr);
            }
            
        }

        hor = teamRatings[i][0] / homeGames; //gets fome offense rating
        hdr = teamRatings[i][1] / homeGames; //home defense rating
        aor = teamRatings[i][2] / awayGames; //away offense rating
        adr = teamRatings[i][3] / awayGames; //away defense rating

        fRatings << ',' << hor << ',' << hdr << ',' << aor << ',' << adr; //input the ratings for every team
        teamRatings.clear(); //clear the vector for the current team
    }

    fRatings.close();
    f.close();

    ifstream newF,matchups;
    string hTeam, aTeam, newLine, newData;
    string homePF, homePA, awayPF, awayPA;

    newF.open("TeamRatings.csv");
    matchups.open("WeeklyGames.txt");

    // cout << "Which teams are playing? (homeTeam awayTeam)" << endl; //gets the matchup that the user wants the winner of
    // cin >> hTeam >> aTeam;

    for (int i = 0; i < 32; i++) { //finds the home and away team's data for every matchup
        getline(matchups, newLine);

        newLine.pop_back();

        hTeam = newLine.substr(0, newLine.find(','));
        aTeam = newLine.substr(newLine.find(',') + 1);

        getline(newF, newLine);
        for (int i = 0; i < 32; i++) {
            getline(newF, newLine);
            stringstream ss(newLine);
            getline(ss, newData, ',');
            if (newData == hTeam) {
                getline(ss, homePF, ',');
                getline(ss, homePA, ',');
                break;
            }
        }
        newF.clear(); //resets and finds the away team's data
        newF.seekg(0, ios::beg);
        getline(newF, newLine);
        for (int i = 0; i < 32; i++) {
            getline(newF, newLine);
            stringstream ss(newLine);
            getline(ss, newData, ',');
            if (newData == aTeam) {
                getline(ss, newData, ',');
                getline(ss, newData, ',');
                getline(ss, awayPF, ',');
                getline(ss, awayPA, ',');
                break;
            }
        }
        newF.clear();
        newF.seekg(0, ios::beg);

        int score = PredictWinner(homePF, homePA, awayPF, awayPA); //plug the data into the algorithm

        if (score > 0)
            std::cout << hTeam << " beat the " << aTeam << " by " << score << "!" << endl;
        else if (score < 0)
            std::cout << aTeam << " beat the " << hTeam << " by " << score*(-1.0) << "!" << endl;
        else
            std::cout << "Too close to accurately predict between " << hTeam << " and " << aTeam << "!" << endl;

        std::cout << endl;
    }

    return 0;
}
