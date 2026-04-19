//Ezzat Mohamadein | ComSc 210 | Lab 31

//include necessary headers and use std namespace
#include <fstream>
#include <iostream>
#include <random>
#include <map>
#include <array>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

//match function prototype, taking the keys for each team and the map as arguments
void match(const string& team1, const string& team2, map<string, array<list<string>, 3>>& tournament);
//function to calculate the total power level for each team based on the individual player power levels, and update the tournament map with the total power levels
void totalPower(map<string, array<list<string>, 3>>& tournament);

//define main function
int main() {
    //randomise the seed for random number generation using srand and time
    srand(time(0));

    //initialize the tournament std::map, including 8 std::arrays of 8 teams, each with 3 std::lists for the players' names, power levels, the team's total power level
    map<string, array<list<string>, 3>> tournament;
    //read the names and power levels from the external files teams.txt, players.txt and powers.txt and populate the tournament map (8 teams, 11 players and power levels each)
    ifstream tin("teams.txt");
    ifstream plin("players.txt");
    ifstream poin("powers.txt");
    string teamName, playerName, powerLevel;
    for(int i = 0; i < 8; i++) {
        getline(tin, teamName);
        tournament[teamName] = array<list<string>, 3>(); //initialize the array for each team in the tournament map
        for(int j = 0; j < 11; j++) {
            getline(plin, playerName);
            tournament[teamName][0].push_back(playerName); //store player names in the first list of the array for each team
            getline(poin, powerLevel);
            tournament[teamName][1].push_back(powerLevel); //store player power levels in the second list of the array for each team
        }
        //initialize the total power level for each team to 0 in the third list of the array for each team
        tournament[teamName][2] = {"0"};
    }
    //close the input file streams
    tin.close();
    plin.close();
    poin.close();

    //call the totalPower function to calculate the total power level for each team and update the tournament map
    totalPower(tournament);

    /*test print the tournament map to verify that the teams, players, power levels, and total power levels have been correctly stored
    for(const auto& team : tournament) {
        cout << "Team: " << team.first << endl;
        cout << "Players: ";
        for(const auto& player : team.second[0]) {
            cout << player << " ";
        }
        cout << endl;
        cout << "Power Levels: ";
        for(const auto& power : team.second[1]) {
            cout << power << " ";
        }
        cout << endl;
        cout << "Total Power: " << team.second[2].front() << endl;
        cout << "------------------------" << endl;
    }
    */

    
    //for loop for the 3 rounds of the tournament (1 for mockup)
    for(int round = 1; round <= 3; round++) {
        //print the current round (quarterfinals, semifinals, final)
        switch (round) {
            case 1: cout << "________________________" << endl << "Quarterfinals" << endl << "________________________" << endl; break;
            case 2: cout << "________________________" << endl << "Semifinals" << endl << "________________________" << endl; break;
            case 3: cout << "________________________" << endl << "Final" << endl << "________________________" << endl; break;
        }
        
        //determine matchups by randomly pairing teams from the tournament map
        vector<string> teams;
        for(const auto& team : tournament) {
            teams.push_back(team.first);
        }
        random_shuffle(teams.begin(), teams.end()); //had to look this up, but this is the simplest way I found to do this the way I want it

        //for loop to iterate through each match in the current round
        for(size_t i = 0; i < teams.size(); i += 2) {
            //call the match function for each pair of teams, passing the team names and the tournament map as arguments
            match(teams[i], teams[i + 1], tournament);
            //end of loop
        }
    //end of loop
    }
    //print the tournament winner after the final round
    cout << "________________________" << endl << "Tournament Winner: " << tournament.begin()->first << endl << "________________________" << endl;
//end of main function
    return 0;
}

//match function definition
void match(const string& team1, const string& team2, map<string, array<list<string>, 3>>& tournament) {
    //create variables to keep track of the score for each team
    int score1 = 0, score2 = 0;
    int power1 = stoi(tournament[team1][2].front());
    int power2 = stoi(tournament[team2][2].front());
    //for loop for the 4 time periods in the match
    for(int i = 0; i < 4; i++) {
        //randomised amount of goals scored by each team based on their power levels (favouring team with higher level)
        int goals1 = 0, goals2 = 0;
        if(power1 > power2) {
            goals1 = (rand() % 2) + (rand() % 2); //0, 1, or 2 goals for team1
            goals2 = (rand() % 2); //0 or 1 goal for team2
        } else if(power2 > power1) {
            goals1 = (rand() % 2); //0 or 1 goal for team1
            goals2 = (rand() % 2) + (rand() % 2); //0, 1, or 2 goals for team2
        }

        //update the score for each team based on the goals scored in the current time period
        score1 += goals1;
        score2 += goals2;
        //end of loop
    }
    //determine the match winner based on the score
    string winner;
    if(score1 > score2) {
        winner = team1;
    } else if(score2 > score1) {
        winner = team2;
    } else {
        //in case of a tie, select team with the higher power level as the winner
        if(power1 > power2) {
            winner = team1;
        } else {
            winner = team2;
        }
    }
    //print the results of the match, including the teams, score, winner
    cout << "Match: " << team1 << " vs " << team2 << endl;
    cout << "Score: " << score1 << " - " << score2 << endl;
    cout << "Winner: " << winner << endl;
    //delete the losing team from the tournament map
    if(winner == team1) {
        tournament.erase(team2);
    } else {
        tournament.erase(team1);
    }
//end of match function definition
}

//totalPower function definition
void totalPower(map<string, array<list<string>, 3>>& tournament) {
    //for loop for each team (8 iterations)
    for(auto& team : tournament) {
        //calculate the total power level for each team by summing the power levels of its players and randomising a percentage from
        //80% to 120% to add some variability to the teams' performance in the tournament
        int totalPower = 0;
        for(const auto& playerPower : team.second[1]) {
            totalPower += stoi(playerPower);
        }
        //randomise the total power level by a percentage from 80% to 120%
        totalPower = totalPower * (0.8 + 0.4 * (static_cast<double>(rand()) / RAND_MAX));
        team.second[2] = {to_string(totalPower)}; //store the total power level in the tournament map for each team
    //end of loop
    }
}