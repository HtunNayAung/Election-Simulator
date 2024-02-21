/*
    View is used for displaying info to the users.
*/

#ifndef VIEW_H
#define VIEW_H

#include<vector>
#include<iostream>
#include "functions.h"
#include"model.h"
class View{
    public:
        void displayIssueInfo(std::vector<Issue>&);
        void displayPartyInfo(std::vector<Party>&);
        void displayElectoralDivisionInfo(std::vector<ElectoralDivision>&, std::vector<Party>&);
        void displayCandidateEvent1(Candidate&, Candidate&, int, int);
        void displayCandidateEvent2(Candidate&, int);
        void displayLeaderEvent1(Leader&, int);
        void displayLeaderEvent2(Leader&, Leader&, Leader&, int, int);
        void displayDebate(Candidate&, Candidate&, Candidate&, int, int);
        void displayIssueEvent(ElectoralDivision&, Stance*, int, int, std::string);
        void displayElectionDayIntro(std::vector<ElectoralDivision>&, std::vector<Party>&);
};



#endif