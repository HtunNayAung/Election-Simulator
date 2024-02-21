#include<iostream>
#include<string>
#include <iomanip>
#include "model.h"

///////////////////////////////////////////////////////////
//RANDOM_NUMBER_GENERATOR CLASS
RandomNumberGenerator::RandomNumberGenerator(): rndEng(std::time(0)) {}
int RandomNumberGenerator::generateRandomInt(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(rndEng);
}
double RandomNumberGenerator::generateProbability(){
    std::uniform_real_distribution<> distribution(0.0, 1.0);
    return distribution(rndEng);
};

///////////////////////////////////////////////////////////
//ISSUE CLASS
Issue::Issue(){}
Issue::Issue(std::string name, std::string description): name(name), description(description){}
void Issue::display(){
    std::cout << name <<std::endl << description << std::endl;
}

//////////////////////////////////////////////////////////
//APPLICANT CLASS
Applicant::Applicant(){}
void Applicant::setName(std::string name){
    this->name = name;
}
void Applicant::setDivision(std::string division){
    this->division = division;
}
void Applicant::setStances(std::vector<Stance> stances){
    this->stances = stances;
}
void Applicant::setCharacteristics(std::map<std::string, int> characteristics){
    this->characteristics = characteristics;
}
void Applicant::setEachCharacteristic(std::string skill, int value){
    characteristics[skill] = value;
}
int Applicant::getEachCharacteristic(std::string skill){
    return characteristics[skill];
}
std::string Applicant::getCharaInfo(){
    std::string output;
    for(const auto& characteristic:characteristics){
        output += characteristic.first + " = " + std::to_string(characteristic.second) + ", ";
    }
    output = output.substr(0, output.size() - 2);
    
    return output;
}
std::vector<Stance> Applicant::getStances(){
    return stances;
}
std::string Applicant::getName(){
    return name;
}
std::string Applicant::getDivision(){
    return division;
}


//////////////////////////////////////////////////////////
//LEADER CLASS
Leader::Leader(){}
void Leader::display(){
    std::cout << std::left << std::setw(20) << std::setfill(' ') << "Leader";
    std::cout << std::left << std::setw(20) << std::setfill(' ') << name;
    std::cout << std::left << std::setw(30) << std::setfill(' ') << division;
    std::cout << std::left << std::setw(40) << std::setfill(' ') << getCharaInfo();
    std::cout << std::endl;
}

//////////////////////////////////////////////////////////
//CANDIDATE CLASS
Candidate::Candidate():voteCount(0){}
void Candidate::display(){
    std::cout << std::left << std::setw(20) << std::setfill(' ') << "Candidate";
    std::cout << std::left << std::setw(20) << std::setfill(' ') << name;
    std::cout << std::left << std::setw(30) << std::setfill(' ') << division;
    std::cout << std::left << std::setw(40) << std::setfill(' ') << getCharaInfo();
    std::cout << std::endl;
}
void Candidate::setVoteCount(int count){
    voteCount = count;
}
int Candidate::getVoteCount(){
    return voteCount;
}

//////////////////////////////////////////////////////////
//MANAGERIAL_TEAM CLASS
ManagerialTeam::ManagerialTeam(){}
void ManagerialTeam::setEachCharacteristic(std::string skill, int value){
    characteristics[skill] = value;
}
std::string ManagerialTeam::getCharaInfo(){
    std::string output;
    for(const auto& characteristic:characteristics){
        output += characteristic.first + " = " + std::to_string(characteristic.second) + ", ";
    }
    output = output.substr(0, output.size() - 2);
    
    return output;
}
void ManagerialTeam::display(){
    std::cout << std::left << std::setw(20) << std::setfill(' ') << "Managerial Team";
    std::cout << std::left << std::setw(20) << std::setfill(' ') << " - ";
    std::cout << std::left << std::setw(30) << std::setfill(' ') << " - ";
    std::cout << std::left << std::setw(40) << std::setfill(' ') << getCharaInfo();
    std::cout << std::endl;
}
int ManagerialTeam::getEachCharacteristic(std::string skill){
    return characteristics[skill];
}

//////////////////////////////////////////////////////////
//PARTY CLASS
Party::Party(std::string name, std::string description): name(name), description(description), winAreaCount(0){}
std::string Party::getName(){
    return name;
}
std::string Party::getDescription(){
    return description;
}
Leader Party::getLeader(){
    return leader;
}
ManagerialTeam Party::getManagerialTeam(){
    return managerialTeam;
}
void Party::setManagerialTeam(ManagerialTeam managerialTeam){
    this->managerialTeam = managerialTeam;
}
void Party::setLeader(Leader leader){
    this->leader = leader;
}
void Party::setCandidates(std::vector<Candidate>candidates){
    this->candidates = candidates;
}
void Party::setStances(std::vector<Stance> stances){
    this->stances = stances;
}
std::vector<Candidate> Party::getCandidates(){
    return candidates;
}
std::vector<Stance> Party::getStances(){
    return stances;
}
void Party::updateCandidate(Candidate& updateCandidate){        //for updating characeristics of a candidate
    for(auto& candidate: candidates){
        if(candidate.getName() == updateCandidate.getName()){
            candidate.setEachCharacteristic("POPULARITY", updateCandidate.getEachCharacteristic("POPULARITY"));
        }
    }
}
void Party::updateLeader(Leader& updateLeader){                 //for updating characeristics of a candidate
    if(leader.getName() == updateLeader.getName()){
        leader.setEachCharacteristic("POPULARITY", updateLeader.getEachCharacteristic("POPULARITY"));
    }
}
void Party::increaseWinAreaCount(){
    ++winAreaCount;
}
int Party::getWinAreaCount(){
    return winAreaCount;
}

//////////////////////////////////////////////////////////
//STANCE CLASS
Stance::Stance(int significance, int approach, std::string issue):significance(significance), approach(approach), issue(issue) {}
std::string Stance::getStance(){    //get the display format of stance
    return std::to_string(significance) + "/" + std::to_string(approach);
}
std::string Stance::getIssue(){
    return issue;
}
void Stance::setSignificance(int sig){
    significance = sig;
}
void Stance::setApproach(int appr){
    approach = appr;
}
int Stance::getSignificance(){
    return significance;
}
int Stance::getApproach(){
    return approach;
}

//////////////////////////////////////////////////////////
//ELECTORAL DIVISION CLASS 
ElectoralDivision::ElectoralDivision(std::string name, int population) : name(name), population(population) {}
void ElectoralDivision::setStances(std::vector<Stance> stances){
    this->stances = stances;
}
std::string ElectoralDivision::getName(){
    return name;
}
int ElectoralDivision::getPopulation(){
    return population;
}
std::vector<Stance> ElectoralDivision::getStances(){
    return stances;
}
void ElectoralDivision::updateStance(Stance& updateStance){
    for(Stance& stance:stances){
        if(stance.getIssue() == updateStance.getIssue()){
            stance.setApproach(updateStance.getApproach());
            stance.setSignificance(updateStance.getSignificance());
        }
    }
}


//////////////////////////////////////////////////////////
//EVENT CLASS
Event::Event(){}
void Event::setEventType(std::string eventType){
    this->eventType = eventType;
}
void Event::setDescription(std::string description){
    this->description = description;
}
void Event::setElectoralDivision(std::string division){
    electoralDivision = division;
}
std::string Event::getElectoralDivision(){
    return electoralDivision;
}
void Event::setImpactedSkill(std::string skill){
    impactedSkill = skill;
}
std::string Event::getImpactedSkill(){
    return impactedSkill;
}
void Event::display(std::vector<Party> parties){
    std::cout << "This is event display!";
}

Debate::Debate() : Event(){
    setEventType("DEBATE");
    setImpactedSkill("POPULARITY");
}
void Debate::setImpactedCandidate(std::vector<Candidate> candidates){
    impactedCandidates = candidates;
}
void Debate::display(std::vector<Party> parties){
    std::cout << "Event type         : " << eventType << std::endl;
    std::cout << "Event description  : " << description << std::endl;
    std::cout << "Event location     : " << electoralDivision << std::endl;
    std::cout << "Skill impacted     : " << impactedSkill << std::endl;
    std::cout << "Candidates in event: ";
    std::string output = "";
    for(auto& candidate: impactedCandidates){
        for(auto& party:parties){
            for(auto& partyCandidate:party.getCandidates()){
                if(partyCandidate.getName() == candidate.getName()){
                    output += candidate.getName() + "(" + party.getName() + "), ";
                }
            }
        }
        
    } 
    output = output = output.substr(0, output.size() - 2);
    std::cout << output << std::endl <<std::endl;
}

CandidateEvent::CandidateEvent() : Event(){
    setEventType("CANDIDATE");
    setImpactedSkill("POPULARITY");
}
void CandidateEvent::setImpactedCandidate(std::vector<Candidate> candidates){
    impactedCandidates = candidates;
}
void CandidateEvent::display(std::vector<Party> parties){
    std::cout << "Event type         : " << eventType << std::endl;
    std::cout << "Event description  : " << description << std::endl;
    std::cout << "Event location     : " << electoralDivision << std::endl;
    std::cout << "Skill impacted     : " << impactedSkill << std::endl;
    std::cout << "Candidates in event: ";
    std::string output = "";
    for(auto& candidate: impactedCandidates){
        for(auto& party:parties){
            for(auto& partyCandidate:party.getCandidates()){
                if(partyCandidate.getName() == candidate.getName()){
                    output += candidate.getName() + "(" + party.getName() + "), ";
                }
            }
        }
        
    } 
    output = output = output.substr(0, output.size() - 2);
    std::cout << output << std::endl;
}


LeaderEvent::LeaderEvent() : Event(){
    setEventType("LEADER");
    setImpactedSkill("POPULARITY");
}
void LeaderEvent::setImpactedLeader(std::vector<Leader> leaders){
    impactedLeaders = leaders;
}
void LeaderEvent::display(std::vector<Party> parties){
    std::cout << "Event type         : " << eventType << std::endl;
    std::cout << "Event description  : " << description << std::endl;
    std::cout << "Skill impacted     : " << impactedSkill << std::endl;
    std::cout << "Leaders in event   : ";
    std::string output = "";
    for(auto& leader: impactedLeaders){
        for(auto& party:parties){
            if(party.getLeader().getName() == leader.getName()){
                output += leader.getName() + "(" + party.getName() + "), ";
            }
        }
        
    } 
    output = output = output.substr(0, output.size() - 2);
    std::cout << output << std::endl;
}

IssueEvent::IssueEvent() : Event(){
    setEventType("ISSUE");
}
void IssueEvent::addImpactedDivision(ElectoralDivision& division){
    impactedDivisions.push_back(division);
}
void IssueEvent::display(std::vector<Party> parties){
    std::cout << "Event type         : " << eventType << std::endl;
    std::cout << "Event description  : " << description << std::endl;
    std::cout << "Event location     : " << electoralDivision << std::endl << std::endl;
    

}