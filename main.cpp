//Ezzat Mohamadein | ComSc 210 | Lab 30

//include necessary headers and use std namespace
#include <fstream>
#include <iostream>
#include <random>
#include <map>
#include <array>
#include <list>
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

    /*
    //for loop for the 3 rounds of the tournament (1 for mockup)
    for(int round = 1; round <= 3; round++) {
        //print the current round (quarterfinals, semifinals, final)
        switch (round) {
            case 1: cout << "Quarterfinals" << endl; break;
            case 2: cout << "Semifinals" << endl; break;
            case 3: cout << "Final" << endl; break;
        }
        
        //determine matchups by randomly pairing teams from the tournament map (leave for beta)

        //for loop to iterate through each match in the current round
        for (auto it = tournament.begin(); it != tournament.end(); ) {
            string team1 = it->first; //get the first team from the iterator
            ++it; //move the iterator to the next team
            if (it == tournament.end()) {
                break; //if there is an odd number of teams, break the loop
            }
            string team2 = it->first; //get the second team from the iterator
            //call the match function with the two teams as arguments
            match(team1, team2, tournament);
            //reset the iterator to the beginning of the tournament map for the next matchups in the current round
            it = tournament.begin();
        //end of loop
        }
    //end of loop
    }
    */
    //print the tournament winner after the final round
    //the last remaining team in the tournament map is the winner
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
        //randomised amount of goals scored by each team based on their power levels (higher team has 50% chance to score, lower team has 25%)
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
    //print the results of the match, including the teams, score, winner, and Man of the Match
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
    //print the inputted teams, players, and power levels for testing
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

    //for loop for each team (8 iterations)
    for(auto& team : tournament) {
        //calculate the total power level for each team by summing the power levels of its players and randomising a percentage from
        //80% to 120% to add some variability to the teams' performance in the tournament
        int totalPower = 0;
        for(const auto& playerPower : team.second[1]) {
            totalPower += stoi(playerPower);
        }
        //print the team name and total power level before randomisation for testing
        cout << "Team: " << team.first << endl;
        cout << "Total Power before randomisation: " << totalPower << endl;
        //randomise the total power level by a percentage from 80% to 120%
        totalPower = totalPower * (0.8 + 0.4 * (static_cast<double>(rand()) / RAND_MAX));
        //print the team name and total power level after randomisation for testing
        cout << "Total Power after randomisation: " << totalPower << endl;
        team.second[2] = {to_string(totalPower)}; //store the total power level in the tournament map for each team
    //end of loop
    }
    //test print the tournament map to verify that the total power levels have been correctly calculated and stored
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
}