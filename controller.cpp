#include "controller.h"
#include "view.h"
#include "functions.h"
#include "model.h"
#include<iomanip>

//the main function for simulation
void ElectionController::startSimulation(int divisionCount, int campaignDays){
    //initialize issues and display
    initIssues(issues);
    view.displayIssueInfo(issues);

    //initialize parties and divisions
    setDivisions(electoralDivisions, divisionCount);
    setParties(parties, electoralDivisions, divisionCount);

    //display parties
    std::cout << "Three leading political parties are participating in the upcoming election.\n\n";
    view.displayPartyInfo(parties);

    //display divisions
    std::cout << "The candidates will compete in these " << electoralDivisions.size()  << " electoral divisions.\n\n";
    view.displayElectoralDivisionInfo(electoralDivisions, parties);
    std::cout << std::endl << std::endl;
    
    //campaign days simulation
    processCampaignDays(campaignDays);

    //start election
    view.displayElectionDayIntro(electoralDivisions, parties);

    //process election 
    for(auto& division: electoralDivisions){
        std::cout << "Electorate Division : " << division.getName() <<", Population : " << division.getPopulation() << std::endl << std::endl;
        std::cout << std::left << std::setw(25) << std::setfill(' ') << "Candidate Name(Party)";
        std::cout << std::left << std::setw(25) << std::setfill(' ') << "Votes"<<std::endl;
        std::cout <<  "--------------------------------------" << std::endl;
        Candidate winner;
        Party winnerParty("", "");
        //get a total score gained by all candidates
        double totalScore = 0;
        int hightestVote = 0;
        for(auto& party:parties){
            Leader leader = party.getLeader();
            for(auto& candidate:party.getCandidates()){
                if(candidate.getDivision() == division.getName()){
                    totalScore += calculateVotingScore(candidate, division, leader);
                }
            }
        }
        //get votes gained by each candidate
        for(auto& party:parties){
            Leader leader = party.getLeader();
            for(auto& candidate:party.getCandidates()){
                if(candidate.getDivision() == division.getName()){
                    std::cout << std::left << std::setw(25) << std::setfill(' ') << candidate.getName() + "(" + party.getName() + ")";
                    double candidateScore = calculateVotingScore(candidate, division, leader);

                    //actual vote received
                    double voteReceived = roundData((candidateScore/totalScore) * division.getPopulation());
                    
                    //find the winner
                    if(voteReceived > hightestVote){
                        hightestVote = voteReceived;
                        winner = candidate;
                        winnerParty = party;
                    }
                    candidate.setVoteCount(voteReceived);
                    std::cout << std::left << std::setw(25) << std::setfill(' ') << candidate.getVoteCount() <<std::endl;
                }
            }
        }
        std::cout << winner.getName() << " from " << winnerParty.getName() << " wins.";
        for(auto& party:parties){
            if(party.getName() == winnerParty.getName()){
                party.increaseWinAreaCount();
            }
        }

        std::cout << std::endl << std::endl;
    }

    //decide winning party
    Party winningParty("", "");
    int highestWinAreaCount = 0;
    std::cout << "\t\t\t\t\t\t~~~ SUMMARY ~~~" << std::endl;
    std::cout << "There are total " << electoralDivisions.size() << " electoral divisions." << std::endl;
    for(auto& party:parties){
        std::cout << party.getName() << " wins in " << party.getWinAreaCount() << " divisions" << std::endl;
        if(party.getWinAreaCount() > highestWinAreaCount){
        highestWinAreaCount = party.getWinAreaCount();
        winningParty = party;
        }
    }
    std::cout << std::endl;
    if(highestWinAreaCount > electoralDivisions.size() / 2){
        std::cout << "The winning party is " << winningParty.getName() << " which wins in " << highestWinAreaCount << " divisions. They will form a government. " << winningParty.getLeader().getName() << " will be the new leader of Cybertron."<<std::endl;
    } else {
        std::cout << "No party has won more than 50% of the electoral divisions. Therefore, a hung parliament will be formed with all parties" << std::endl;
    }
}

void ElectionController::initIssues(std::vector<Issue>&issues){
    Issue issue1(ISSUE_NAMES[0], ISSUE_DESCRIPTIONS[0]);
    Issue issue2(ISSUE_NAMES[1], ISSUE_DESCRIPTIONS[1]);
    Issue issue3(ISSUE_NAMES[2], ISSUE_DESCRIPTIONS[2]);
    Issue issue4(ISSUE_NAMES[3], ISSUE_DESCRIPTIONS[3]);
    Issue issue5(ISSUE_NAMES[4], ISSUE_DESCRIPTIONS[4]);
    issues.push_back(issue1);
    issues.push_back(issue2);
    issues.push_back(issue3);
    issues.push_back(issue4);
    issues.push_back(issue5);
}

void ElectionController::setParties(std::vector<Party>&parties, std::vector<ElectoralDivision>electoralDivisions, int divisionCount){
    int nameIndex = 0;
    for(int i=0; i < 3; i++){
        Party party(PARTY_NAMES[i], PARTY_DESCRIPTIONS[i]); 

        //generate stances for party
        std::vector<Stance> stances;
        generateStances(PARTY_STANCE_RANGES[i][0], PARTY_STANCE_RANGES[i][1], stances);
        party.setStances(stances);  

        //set leader for party
        Leader leader;
        leader.setName(LEADER_NAMES[i]);
        leader.setDivision("-");
        leader.setStances(stances);
        generateCharacteristics(leader);
        party.setLeader(leader);
        
        //set candidates for party
        std::vector<Candidate> candidates;
        for(int j = 0; j< divisionCount; j++){
            Candidate candidate;
            std::string candidateName = CANDIDATE_NAMES[nameIndex++];
            candidate.setName(candidateName);
            candidate.setDivision(electoralDivisions.at(j).getName());
            candidate.setStances(stances);
            generateCharacteristics(candidate);
            candidates.push_back(candidate);
        }
        party.setCandidates(candidates);

        //set managerial team for party
        ManagerialTeam managerialTeam;
        for(int i=0; i<2; i++){
            int value = randGenerator.generateRandomInt(20, 60);
            managerialTeam.setEachCharacteristic(MANAGERIAL_TEAM_CHARACTERISTICS[i], value);
        }
        party.setManagerialTeam(managerialTeam);
        
        parties.push_back(party);
    }
}

//generating random characteristics for leader and candidates
void ElectionController::generateCharacteristics(Applicant& applicant){
    for(int i=0; i<5; i++){
        int value = randGenerator.generateRandomInt(20, 70);
        applicant.setEachCharacteristic(CHARACTERISTICS_LIST[i], value);
    }
}

//generating random stances
void ElectionController::generateStances(int min, int max, std::vector<Stance>& stances){
    for(int i=0; i<5; i++){
        int significance  = randGenerator.generateRandomInt(min, max);
        int approach = randGenerator.generateRandomInt(min, max);
        Stance stance(significance, approach, ISSUE_NAMES[i]);
        stances.push_back(stance);
    }
}

void ElectionController::setDivisions(std::vector<ElectoralDivision>& electoralDivisions, int divisionCount){
    for(int i=0; i<divisionCount; i++){
        //generate a random population
        int population = randGenerator.generateRandomInt(POPULATION_RANGE[0], POPULATION_RANGE[1]);

        ElectoralDivision division(ELECTORAL_DIVISIONS[i], population);

        //set random stances
        std::vector<Stance> stances;
        generateStances(DIVISION_STANCE_RANGE[0], DIVISION_STANCE_RANGE[1], stances);
        division.setStances(stances);

        electoralDivisions.push_back(division);
    }
}

//generate a random candidate for events
std::vector<Candidate> ElectionController::generateOneRandomCandidate(std::string division, std::vector<Party>& parties){
    std::vector<Candidate> candidates;
    int rndPartyIndex = randGenerator.generateRandomInt(0,2);

    std::vector<Candidate> partyCandidates = parties.at(rndPartyIndex).getCandidates();
    for(Candidate candidate: partyCandidates){
        if(candidate.getDivision() == division){ //it needs to be the same division 
            candidates.push_back(candidate);
        }
    }
    return candidates;
    
}

//generating 2 candidates from random parties
std::vector<Candidate> ElectionController::generateTwoRandomCandidates(std::string division, std::vector<Party>& parties){
    std::vector<Candidate> candidates;
    int generatedPartyIndex = -1; //save the generated candidate so that there is no repetition
    int rndPartyIndex;

    for(int i=0; i<2; i++){  //generate two candidates
        do {
            rndPartyIndex = randGenerator.generateRandomInt(0,2);
            
        } while(rndPartyIndex == generatedPartyIndex);
        generatedPartyIndex = rndPartyIndex;
        std::vector<Candidate> partyCandidates = parties.at(rndPartyIndex).getCandidates();
        for(Candidate candidate: partyCandidates){
            if(candidate.getDivision() == division){
                candidates.push_back(candidate);
            }
        }
    }
    return candidates;
    
}

//generating 3 candidates from 3 parties
std::vector<Candidate> ElectionController::generateThreeRandomCandidates(std::string division, std::vector<Party>& parties){
    std::vector<Candidate> candidates;

    for(auto& party:parties){
        std::vector<Candidate> partyCandidates = party.getCandidates();
        for(Candidate candidate: partyCandidates){
            if(candidate.getDivision() == division){
                candidates.push_back(candidate);
            }
        }
    }
    
    return candidates;
    
}

//generate one leader from random party
std::vector<Leader> ElectionController::generateOneRandomLeader(std::vector<Party>& parties){
    std::vector<Leader> leaders;
    int rndPartyIndex = randGenerator.generateRandomInt(0,2);

    Leader leader = parties.at(rndPartyIndex).getLeader();
    leaders.push_back(leader);
    return leaders;
    
}

//generate leaders from 3 parties
std::vector<Leader> ElectionController::generateLeaders(std::vector<Party>& parties){
    std::vector<Leader> leaders;
    for(auto& party:parties){
        leaders.push_back(party.getLeader());
    }
    return leaders;
}

Debate* ElectionController::generateDebates(std::vector<Candidate>& candidates){
    
    Debate* debate = new Debate();

    debate->setDescription("All candidates are having debate!");
    if(candidates.size() != 0 ){
        debate->setElectoralDivision(candidates.at(0).getDivision());
        debate->setImpactedCandidate(candidates);
    }else{
        return nullptr;
    }
    
    
    return debate;
    // events.push_back(debate);
}   

CandidateEvent* ElectionController::generateCandidateEvent1(std::vector<Candidate>& candidates){
    std::vector<CandidateEvent*> candidateEvents;
    CandidateEvent* candidateEvent = new CandidateEvent();

    if(candidates.size() != 0 ){  //make sure there is candidate for the event
        candidateEvent->setDescription("Joint Q&A session between " + candidates.at(0).getName() + " and " + candidates.at(1).getName() + " is held in the townhall. Public asks about policies for post election period.");
        candidateEvent->setElectoralDivision(candidates.at(0).getDivision());
        candidateEvent->setImpactedCandidate(candidates);
    } else{
        return nullptr;
    }
    return candidateEvent;
}

CandidateEvent* ElectionController::generateCandidateEvent2(std::vector<Candidate>& candidates){
    CandidateEvent* candidateEvent = new CandidateEvent();

    if(candidates.size() != 0 ){ //make sure there is candidate for the event
        candidateEvent->setDescription("There are some rumors that " + candidates.at(0).getName() + " is planning to cheat in the election.");
        candidateEvent->setElectoralDivision(candidates.at(0).getDivision());
        candidateEvent->setImpactedCandidate(candidates);
        
    }else{
        return nullptr;
    }
    return candidateEvent;
}
LeaderEvent* ElectionController::generateLeaderEvent1(std::vector<Leader>& leaders){
    LeaderEvent* leaderEvent =  new LeaderEvent();

    if(leaders.size() != 0 ){ //make sure there is leader for the event
        leaderEvent->setDescription(leaders.at(0).getName() + " has proposed a new transport policy that promises to increase funding for tranportation sector.");
        leaderEvent->setElectoralDivision(leaders.at(0).getDivision());
        leaderEvent->setImpactedLeader(leaders);
    }else{
        return nullptr;
    }
    return leaderEvent;
}

LeaderEvent* ElectionController::generateLeaderEvent2(std::vector<Leader>& leaders){
    LeaderEvent* leaderEvent =  new LeaderEvent();

    if(leaders.size() != 0 ){  //make sure there is leader for the event
        leaderEvent->setDescription("All leaders are holding a panel with the public. Leaders have to solve the problems that the citizens are facing and explain their policies for the future.");
        leaderEvent->setElectoralDivision(leaders.at(0).getDivision());
        leaderEvent->setImpactedLeader(leaders);
    }else{
        return nullptr;
    }
    return leaderEvent;
}

IssueEvent* ElectionController::generateIssueEvent1(ElectoralDivision& division){
    IssueEvent* issueEvent = new IssueEvent();
    issueEvent->setDescription(division.getName() + " is facing serious health related issue. A new virus called CSCI251 is spreading and there is not enough room in the healthcare centers.");
    issueEvent->setElectoralDivision(division.getName());
    issueEvent->addImpactedDivision(division);
  
    return issueEvent;
}

IssueEvent* ElectionController::generateIssueEvent2(ElectoralDivision& division){
    IssueEvent* issueEvent = new IssueEvent();
    issueEvent->setDescription("It has been a week all the transportation has been shut down in " + division.getName() + ". The public needs urgent replacement.");
    issueEvent->setElectoralDivision(division.getName());
    issueEvent->addImpactedDivision(division);

    return issueEvent;
}

//given the candidate, find the corresponding managerial team of the candidate
ManagerialTeam ElectionController::findManagerialTeam(Candidate& candidate, std::vector<Party>& parties){
    for(auto& party:parties){
        for(auto& c: party.getCandidates()){
            if(c.getName() == candidate.getName()){
                return party.getManagerialTeam();
            }
        }
    }

    throw std::runtime_error("Managerial team of the candidate is not found in any party");
}

void ElectionController::processCandidateEvent1(ElectoralDivision division, std::vector<Party>& parties){
    //get two candidates first
    std::vector<Candidate> twoCandidates = generateTwoRandomCandidates(division.getName(), parties);

    //create a candidate event
    Event* candidateEvent1 = generateCandidateEvent1(twoCandidates);
    candidateEvent1->display(parties);

    Candidate& candidate1 = twoCandidates.at(0);
    Candidate& candidate2 = twoCandidates.at(1);
    int candidate1Skill = candidate1.getEachCharacteristic("POLICY_EXPERTISE") + candidate1.getEachCharacteristic("TRUSTWORTHINESS");
    int candidate2Skill = candidate2.getEachCharacteristic("POLICY_EXPERTISE") + candidate2.getEachCharacteristic("TRUSTWORTHINESS");
    int randomImpact1 = randGenerator.generateRandomInt(2,5);
    int randomImpact2 = randGenerator.generateRandomInt(1,3);
    
    //compare and update
    if(candidate1Skill > candidate2Skill){
        Candidate& winner = candidate1;
        Candidate& loser = candidate2;
        view.displayCandidateEvent1(winner, loser, randomImpact1, randomImpact2);
        for(auto& party: parties){
            party.updateCandidate(winner);
            party.updateCandidate(loser);
        }
    } else if(candidate2Skill > candidate1Skill){
        Candidate& winner = candidate2;
        Candidate& loser = candidate1;
        view.displayCandidateEvent1(winner, loser, randomImpact1, randomImpact2);
        for(auto& party: parties){
            party.updateCandidate(winner);
            party.updateCandidate(loser);
        }
    } else{
        std::cout << "There is no change in the characteristics of the candidates as they have equal policy attributes." << std::endl;
    }   
    delete candidateEvent1;
};

void ElectionController::processCandidateEvent2(ElectoralDivision division, std::vector<Party>& parties){
    //get one candidate
    std::vector<Candidate> oneCandidate = generateOneRandomCandidate(division.getName(), parties);

    //create a candidate event
    Event* candidateEvent2 = generateCandidateEvent2(oneCandidate);
    candidateEvent2->display(parties);

    Candidate& candidate1 = oneCandidate.at(0);
    int randomImpact = randGenerator.generateRandomInt(2,5);
    view.displayCandidateEvent2(candidate1, randomImpact);

    //update characteristiscs
    for(auto& party: parties){
        party.updateCandidate(candidate1);
    }
    delete candidateEvent2;
}

void ElectionController::processDebate(ElectoralDivision division, std::vector<Party>& parties){
    //get three candidates
    std::vector<Candidate> threeCandidates = generateThreeRandomCandidates(division.getName(), parties);

    //create a debate
    Debate* debate = generateDebates(threeCandidates);
    debate->display(parties);

    //for candidate 1
    Candidate& candidate1 = threeCandidates.at(0);
    ManagerialTeam managerialTeam1 = findManagerialTeam(candidate1, parties);
    int candidate1Skill = candidate1.getEachCharacteristic("DEBATE_SKILLS") + managerialTeam1.getEachCharacteristic("PROBLEM_SOLVING") + managerialTeam1.getEachCharacteristic("STRATEGY");
    
    //for candidate 2
    Candidate& candidate2 = threeCandidates.at(1);
    ManagerialTeam managerialTeam2 = findManagerialTeam(candidate2, parties);
    int candidate2Skill = candidate2.getEachCharacteristic("DEBATE_SKILLS") + managerialTeam2.getEachCharacteristic("PROBLEM_SOLVING") + managerialTeam2.getEachCharacteristic("STRATEGY");

    //for candidate 3
    Candidate& candidate3 = threeCandidates.at(2);
    ManagerialTeam managerialTeam3 = findManagerialTeam(candidate3, parties);
    int candidate3Skill = candidate3.getEachCharacteristic("DEBATE_SKILLS") + managerialTeam3.getEachCharacteristic("PROBLEM_SOLVING") + managerialTeam3.getEachCharacteristic("STRATEGY");
    int randomImpact1 = randGenerator.generateRandomInt(2,5);
    int randomImpact2 = randGenerator.generateRandomInt(1,3);

    //compate and update
    if(candidate1Skill > candidate2Skill && candidate1Skill > candidate3Skill){
            Candidate& winner = candidate1;
            Candidate& loser1 = candidate2;
            Candidate& loser2 = candidate3;
            view.displayDebate(winner, loser1, loser2, randomImpact1, randomImpact2);
            for(auto& party: parties){
                party.updateCandidate(winner);
                party.updateCandidate(loser1);
                party.updateCandidate(loser2);
            }
    } else if(candidate2Skill > candidate1Skill && candidate2Skill > candidate3Skill){
            Candidate& winner = candidate2;
            Candidate& loser1 = candidate1;
            Candidate& loser2 = candidate3;
            view.displayDebate(winner, loser1, loser2, randomImpact1, randomImpact2);
            for(auto& party: parties){
                party.updateCandidate(winner);
                party.updateCandidate(loser1);
                party.updateCandidate(loser2);
            }
    } else if(candidate3Skill > candidate1Skill && candidate3Skill > candidate2Skill){
            Candidate& winner = candidate3;
            Candidate& loser1 = candidate1;
            Candidate& loser2 = candidate2;
            view.displayDebate(winner, loser1, loser2, randomImpact1, randomImpact2);
            for(auto& party: parties){
                party.updateCandidate(winner);
                party.updateCandidate(loser1);
                party.updateCandidate(loser2);
            }
    } else{
        std::cout << "Public cannot decide who is the best. No characteristics of the candidates changed.\n";
    }
    delete debate;
}

void ElectionController::processLeaderEvent1(std::vector<Party>& parties){
    //get one leader
    std::vector<Leader> oneLeader = generateOneRandomLeader(parties);

    //create a leader event
    LeaderEvent* leaderEvent1 = generateLeaderEvent1(oneLeader);
    leaderEvent1->display(parties);
    
    Leader& leader = oneLeader.at(0);
    int randomImpact = randGenerator.generateRandomInt(5,10);
    view.displayLeaderEvent1(leader, randomImpact);

    //update leader
    for(auto& party: parties){
        party.updateLeader(leader);
    }
    delete leaderEvent1;
}

void ElectionController::processLeaderEvent2(std::vector<Party>& parties){
    //get all leaders
    std::vector<Leader> leaders = generateLeaders(parties);

    //create a leader event
    LeaderEvent* leaderEvent2 = generateLeaderEvent2(leaders);
    leaderEvent2->display(parties);

    Leader& leader1 = leaders.at(0);
    Leader& leader2 = leaders.at(1);
    Leader& leader3 = leaders.at(2);
    int randomImpact1 = randGenerator.generateRandomInt(2,7);
    int randomImpact2 = randGenerator.generateRandomInt(2,5);

    //compare and update
    if(leader1.getEachCharacteristic("PROBLEM_SOLVING") > leader2.getEachCharacteristic("PROBLEM_SOLVING") && leader1.getEachCharacteristic("PROBLEM_SOLVING") > leader3.getEachCharacteristic("PROBLEM_SOLVING")){
        Leader& winner = leader1;
        Leader& loser1 = leader2;
        Leader& loser2 = leader3;
        view.displayLeaderEvent2(winner, loser1, loser2, randomImpact1, randomImpact2);
        for(auto& party: parties){
            party.updateLeader(winner);
            party.updateLeader(loser1);
            party.updateLeader(loser2);
        }
    } else if(leader2.getEachCharacteristic("PROBLEM_SOLVING") > leader1.getEachCharacteristic("PROBLEM_SOLVING") && leader2.getEachCharacteristic("PROBLEM_SOLVING") > leader3.getEachCharacteristic("PROBLEM_SOLVING")){
        Leader& winner = leader2;
        Leader& loser1 = leader1;
        Leader& loser2 = leader3;
        view.displayLeaderEvent2(winner, loser1, loser2, randomImpact1, randomImpact2);
        for(auto& party: parties){
            party.updateLeader(winner);
            party.updateLeader(loser1);
            party.updateLeader(loser2);
        }
    } else if(leader3.getEachCharacteristic("PROBLEM_SOLVING") > leader1.getEachCharacteristic("PROBLEM_SOLVING") && leader3.getEachCharacteristic("PROBLEM_SOLVING") > leader2.getEachCharacteristic("PROBLEM_SOLVING")){
        Leader& winner = leader3;
        Leader& loser1 = leader1;
        Leader& loser2 = leader2;
        view.displayLeaderEvent2(winner, loser1, loser2, randomImpact1, randomImpact2);
        for(auto& party: parties){
            party.updateLeader(winner);
            party.updateLeader(loser1);
            party.updateLeader(loser2);
        }
    } else{
        std::cout << "There is no change in the characteristics. All the leader solved the problems quite well and the public believe that they all are effective in their own way." << std::endl;
    }
    delete leaderEvent2;
}

void ElectionController::processCampaignDays(int campaignDays){
    std::cout << "NOW, IT'S TIME TO OFFICIALLY START CAMPAIGN DAYS.\n";
    for(int j =0; j<campaignDays; j++){
        std::cout << "\t\t\t\t\t\t~~~ CAMPAIGN DAY " << j+1 << " ~~~\n\n";
        for(int i = 0; i<electoralDivisions.size(); i++){
            double eventHappens = randGenerator.generateProbability();
            if(eventHappens<0.5){   //if < 0.5, no event happens
                std::cout << "No event happened in " + electoralDivisions.at(i).getName() + " on this day.\n\n";
                std::cout << "------" << std::endl;
                continue;
            } else{
                std::cout << "Event happening in "+ electoralDivisions.at(i).getName() + ".\n";
                /*
                Candidate-related: 0.0 - 0.2
                Debate : 0.2 -0.45
                Leader-related : 0.45-0.7
                Issue-related : 0.7 - 1.0
                */
                double eventTypeProbability = randGenerator.generateProbability();

                //generate and process events according to the cumulative probability above
                if(eventTypeProbability >= 0.0 && eventTypeProbability < 0.2) {
                    int event1or2 = randGenerator.generateRandomInt(1,2);
                    if(event1or2 == 1){
                        processCandidateEvent1(electoralDivisions.at(i), parties);
                    } else{
                        processCandidateEvent2(electoralDivisions.at(i), parties);
                    }
                    
                } else if(eventTypeProbability >= 0.2 && eventTypeProbability < 0.45) {
                    processDebate(electoralDivisions.at(i), parties);

                } else if(eventTypeProbability >= 0.45 && eventTypeProbability < 0.7) {
                    int event1or2 = randGenerator.generateRandomInt(1,2);
                    if(event1or2 == 1){
                        processLeaderEvent1(parties);
                    } else{
                        processLeaderEvent2(parties);
                    }
                    
                } else {
                    //for issue event 1
                    int event1or2 = randGenerator.generateRandomInt(1,2);
                    Stance* stanceptr = nullptr;
                    if(event1or2 == 1){
                        IssueEvent* issueEvent1 = generateIssueEvent1(electoralDivisions.at(i));
                        issueEvent1->display(parties);
                        int randSig = randGenerator.generateRandomInt(5,10);
                        int randAppr = randGenerator.generateRandomInt(5,10);
                        ElectoralDivision& division = electoralDivisions.at(i);
                        std::string issue ="Health";
                        for(Stance stance:division.getStances()){
                            if(stance.getIssue() == issue){
                                stanceptr = &stance;
                                view.displayIssueEvent(division, stanceptr, randSig, randAppr, issue);

                            }
                        }
                        std::cout << std::endl;
                        delete issueEvent1;

                    } else{     //for issue event 2
                        IssueEvent* issueEvent2 = generateIssueEvent2(electoralDivisions.at(i));
                        issueEvent2->display(parties);
                        int randSig = randGenerator.generateRandomInt(5,10);
                        int randAppr = randGenerator.generateRandomInt(5,10);
                        ElectoralDivision& division = electoralDivisions.at(i);
                        std::string issue ="Transportation";
                        for(Stance stance:division.getStances()){
                            if(stance.getIssue() == issue){
                                stanceptr = &stance;
                                view.displayIssueEvent(division, stanceptr, randSig, randAppr, issue);
                            }
                        }
                        
                        std::cout << std::endl;
                        delete issueEvent2;

                    }
                    
                }
            }
            std::cout << "------" << std::endl;
        }
        std::cout << "\t\t\t\t\t\t CAMPAIGN DAY " << (j+1) << " RECAP\n\n";
        view.displayPartyInfo(parties);
        view.displayElectoralDivisionInfo(electoralDivisions, parties);
            std::cout << "========================================================================================================================================================================\n\n";
    }
}

//find the euclidean distance between stances
int ElectionController::calculateEuclideanDistance( Stance& stance1,  Stance& stance2) {
    double diffSignificance = stance1.getSignificance() - stance2.getSignificance();
    double diffApproach = stance1.getApproach() - stance2.getApproach();
    return sqrt(diffSignificance * diffSignificance + diffApproach * diffApproach);
}

//calculate the average ED of a candidate to a division
double ElectionController::calculateAverageStanceEuclideanDistance(Candidate& candidate,  ElectoralDivision& division) {
    double totalDistance = 0.0;
    for (size_t i = 0; i < candidate.getStances().size(); ++i) {
        totalDistance += calculateEuclideanDistance(candidate.getStances().at(i), division.getStances().at(i));
    }
    return totalDistance / candidate.getStances().size();
}

//voting score calculation
double ElectionController::calculateVotingScore(Candidate& candidate, ElectoralDivision& division, Leader& leader) {
    double avgStanceEuclideanDistance = calculateAverageStanceEuclideanDistance(candidate, division);
    int score = 0.45 / avgStanceEuclideanDistance + 0.30 * candidate.getEachCharacteristic("POPULARITY") + 0.25 * leader.getEachCharacteristic("POPULARITY");
    return score;
}