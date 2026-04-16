//Ezzat Mohamadein | ComSc 210 | Lab 29

//include necessary headers and use std namespace
#include <iostream>
#include <random>
#include <map>
#include <array>
#include <list>
using namespace std;

//match function prototype, taking the keys for each team and the map as arguments
void match(const string& team1, const string& team2, map<string, array<list<string>, 3>>& tournament);

//define main function
int main() {
    //randomise the seed for random number generation using srand and time
    srand(time(0));

    //initialize the tournament std::map, including 8 std::arrays of 8 teams, each with 3 std::lists for the players' names, power levels, the team's total power level
    map<string, array<list<string>, 3>> tournament;
    //read the names and power levels from the external files and populate the tournament map (use dummy data, 2 teams with 3 players each for mockup)
    tournament["Team A"][0] = {"Player A1", "Player A2", "Player A3"};
    tournament["Team A"][1] = {"80", "85", "90"}; //power levels for Team A players
    tournament["Team A"][2] = {"0"}; //initialize total power level for Team A
    tournament["Team B"][0] = {"Player B1", "Player B2", "Player B3"};
    tournament["Team B"][1] = {"75", "80", "85"}; //power levels for Team B players
    tournament["Team B"][2] = {"0"}; //initialize total power level for Team B

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

    //for loop for the 3 rounds of the tournament (1 for mockup)
        //print the current round (quarterfinals, semifinals, final)
        cout << "Round: Final" << endl;
        //determine matchups by randomly pairing teams from the tournament map
        //for loop to iterate through each match in the current round
            //call the match function with the two teams as arguments
            match("Team A", "Team B", tournament);
        //end of loop
    //end of loop
    //print the tournament winner after the final round
    cout << "Tournament Winner: " << tournament.begin()->first << endl; //the last remaining team in the tournament map is the winner
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