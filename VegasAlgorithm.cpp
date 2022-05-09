#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;

double PredictWinner(string hpf, string hpa, string apf, string apa) {
    double homePF = stod(hpf);
    double homePA = stod(hpa);
    double awayPF = stod(apf);
    double awayPA = stod(apa);
    double offense, defense;

    std::cout << homePF << " " << homePA << " " << awayPF << " " << awayPA << endl;

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

    f.open("VegasNumbers.csv");
    fRatings.open("TeamRatings.csv");

    fRatings.precision(4);
    std::cout.precision(4);

    fRatings << "Team Name,HOR,HDR,AOR,ADR";

    vector<vector<double>> teamRatings(32);

    string tempLine, tempData, teamName;
    int count = 1;
    double awayGames, homeGames, hor, hdr, aor, adr;

    for (int i = 0; i < 32; i++) {
        teamRatings[i].push_back(0.0);
        teamRatings[i].push_back(0.0);
        teamRatings[i].push_back(0.0);
        teamRatings[i].push_back(0.0);
    }

    std::getline(f, tempLine);
    for (int i = 0; i < 32; i++) {
        homeGames = 0;
        awayGames = 0;

        std::getline(f, tempLine);
        stringstream ss(tempLine);
        std::getline(ss, teamName, ','); //gets team's name

        fRatings << '\n' << teamName;

        for (int j = 1; j <= 18*4; j++) {
            std::getline(ss, tempData, ',');
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

        hor = teamRatings[i][0] / homeGames;
        hdr = teamRatings[i][1] / homeGames;
        aor = teamRatings[i][2] / awayGames;
        adr = teamRatings[i][3] / awayGames;

        fRatings << ',' << hor << ',' << hdr << ',' << aor << ',' << adr;
        teamRatings.clear();
    }

    fRatings.close();
    f.close();

    ifstream newF;
    string hTeam, aTeam, newLine, newData;
    string homePF, homePA, awayPF, awayPA;

    newF.open("TeamRatings.csv");

    std::cout << "Which teams are playing? (homeTeam awayTeam)" << endl;
    std::cin >> hTeam >> aTeam;

    while (hTeam != "q") {
        std::getline(newF, newLine);
        for (int i = 0; i < 32; i++) {
            std::getline(newF, newLine);
            stringstream ss(newLine);
            std::getline(ss, newData, ',');
            if (newData == hTeam) {
                std::getline(ss, homePF, ',');
                std::getline(ss, homePA, ',');
                break;
            }
        }
        newF.clear();
        newF.seekg(0, ios::beg);
        std::getline(newF, newLine);
        for (int i = 0; i < 32; i++) {
            std::getline(newF, newLine);
            stringstream ss(newLine);
            std::getline(ss, newData, ',');
            if (newData == aTeam) {
                std::getline(ss, newData, ',');
                std::getline(ss, newData, ',');
                std::getline(ss, awayPF, ',');
                std::getline(ss, awayPA, ',');
                break;
            }
        }
        newF.clear();
        newF.seekg(0, ios::beg);

        int score = PredictWinner(homePF, homePA, awayPF, awayPA);

        if (score > 0)
            std::cout << hTeam << " wins by " << score << "!" << endl;
        else if (score < 0)
            std::cout << aTeam << " wins by " << abs(score) << "!" << endl;
        else
            std::cout << "Too close to accurately predict!" << endl;

        std::cout << "Which teams are playing? (homeTeam awayTeam)" << endl;
        std::cin >> hTeam >> aTeam;
    }

    return 0;
}