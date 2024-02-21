/*
    In Controller, it performs the main logic and communicate between Model and View
*/

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "view.h"

class ElectionController{
    private:
        std::vector<Issue>issues;
        std::vector<ElectoralDivision>electoralDivisions;
        std::vector<Party>parties;
        RandomNumberGenerator randGenerator;
        View view;

    public:
        void initIssues(std::vector<Issue>&);
        void setParties(std::vector<Party>&, std::vector<ElectoralDivision>, int);
        void startSimulation(int, int);
        void generateCharacteristics(Applicant&);
        void generateStances(int, int, std::vector<Stance>& );
        void setDivisions(std::vector<ElectoralDivision>&, int);
        std::vector<Candidate> generateOneRandomCandidate(std::string, std::vector<Party>&);
        std::vector<Candidate> generateTwoRandomCandidates(std::string, std::vector<Party>&);
        std::vector<Candidate> generateThreeRandomCandidates(std::string, std::vector<Party>&);
        std::vector<Leader> generateOneRandomLeader(std::vector<Party>&);
        std::vector<Leader> generateLeaders(std::vector<Party>&);
        Debate* generateDebates( std::vector<Candidate>&);
        CandidateEvent* generateCandidateEvent1(std::vector<Candidate>&);
        CandidateEvent* generateCandidateEvent2(std::vector<Candidate>&);
        LeaderEvent* generateLeaderEvent1(std::vector<Leader>&);
        LeaderEvent* generateLeaderEvent2(std::vector<Leader>&);
        IssueEvent* generateIssueEvent1(ElectoralDivision&);
        IssueEvent* generateIssueEvent2(ElectoralDivision&);
        ManagerialTeam findManagerialTeam(Candidate&, std::vector<Party>&);
        void processCandidateEvent1(ElectoralDivision, std::vector<Party>& );
        void processCandidateEvent2(ElectoralDivision, std::vector<Party>& );
        void processDebate(ElectoralDivision, std::vector<Party>& );
        void processLeaderEvent1(std::vector<Party>& );
        void processLeaderEvent2(std::vector<Party>& );
        void processCampaignDays(int);
        int calculateEuclideanDistance(Stance&, Stance&);
        double calculateAverageStanceEuclideanDistance( Candidate&,  ElectoralDivision&);
        double calculateVotingScore(Candidate&, ElectoralDivision&, Leader&);
};


#endif