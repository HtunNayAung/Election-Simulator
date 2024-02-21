/*
    In Model, all the core classes and data are defined.
*/

#ifndef MODEL_H
#define  MODEL_H
#include<string>
#include<map>
#include<random>
#include<ctime>

class RandomNumberGenerator {
private:
    std::default_random_engine rndEng;

public:
    RandomNumberGenerator() ;
    int generateRandomInt(int, int);
    double generateProbability();
    
};

/////////////////////////////////////////////////////////////

class Stance{
    private:
        int significance;
        int approach;
        std::string issue;
    public:
        Stance(int, int, std::string);
        std::string getStance();
        std::string getIssue();
        void setSignificance(int);
        void setApproach(int);
        int getSignificance();
        int getApproach();
};

/////////////////////////////////////////////////////////////

const std::string ISSUE_NAMES[5] = {"Transportation", "Inflation" , "Crime" , "Cybersecurity", "Health"};
const std::string ISSUE_DESCRIPTIONS[5] = {
    "The country faces pressing transportation issues marked by traffic congestion, limited public transit options, and the need for modernizing aging infrastructure.",
    "Inflation has become an enduring challenge for the nation, resulting in persistent price increases and economic instability.",
    "Drug-related crimes have become a significant problem in the country, raising concerns about public safety.",
    "Cybersecurity vulnerabilities have emerged as a pressing concern in the country, demanding immediate attention to protect critical infrastructure and sensitive data from cyber threats.",
    "The country is grappling with a range of health-related issues, from unequal access to healthcare to the pressing need for healthcare system improvements."
};

class Issue{
    private:
        std::string name;
        std::string description;
    public:
        Issue();
        Issue(std::string, std::string);
        void display();
};

//////////////////////////////////////////////////////////
const std::string CHARACTERISTICS_LIST[5] = {
        "POPULARITY",
        "DEBATE_SKILLS",
        "POLICY_EXPERTISE",
        "PROBLEM_SOLVING",
        "TRUSTWORTHINESS"
};

//DATA FOR ELECTORAL DIVISIONS
const int divisionCount = 10;
const std::string ELECTORAL_DIVISIONS[divisionCount] = {"Technoville", "Harmony Harbor", "Pixelburg", "Astralan", "Crystalhaven", "Skyline Heights", "Starlight Valley", "Moonlight Bay", "Lumina Springs", "Steelton"};

class Applicant{
    protected:
        std::string name;
        std::string division;
        std::vector<Stance> stances;
        std::map<std::string, int> characteristics;
    public:
        Applicant();
        void setName(std::string);
        void setDivision(std::string);
        void setStances(std::vector<Stance>);
        void setCharacteristics(std::map<std::string, int>);
        void setEachCharacteristic(std::string, int);
        int getEachCharacteristic(std::string);
        std::string getCharaInfo();
        std::vector<Stance> getStances();
        std::string getName();
        std::string getDivision();
        virtual void display() = 0;
};

const std::string LEADER_NAMES[3] = {"Tom Aung", "Theresa Zin", "Christ Kyaw"};
const std::string CANDIDATE_NAMES[30] = {
        "John Smith", "Mary Johnson", "David Brown", "Jennifer Davis", "Michael Wilson",
        "Linda Chen", "James Lee", "Maddie Moore", "Robert Martin", "Aggy Taylor",
        "William Garcia", "Susan Yu", "Joseph King", "Jessica Clark", "Charles Ryan",
        "Sarah Lewis", "Thomas Walker", "Karen Young", "Daniel Hall", "Nancy White",
        "Matthew Adams", "Lisa Hall", "Donald King", "Betty Turner", "Steven Lewis",
        "Sandra Turner", "George Moore", "Helen Parker", "Edward Jackson", "Emily Harris"
    };

class Leader: public Applicant{
    public:
        Leader();
        void display();
};

class Candidate: public Applicant{
    int voteCount;
    public:
        Candidate();
        void display();
        void setVoteCount(int);
        int getVoteCount();
};

//////////////////////////////////////////////////////////
const std::string MANAGERIAL_TEAM_CHARACTERISTICS[] = {"STRATEGY", "PROBLEM_SOLVING"};
class ManagerialTeam{
    private:
        std::map<std::string, int>characteristics;
    public:
        ManagerialTeam();
        void setEachCharacteristic(std::string, int);
        std::string getCharaInfo();
        void display();
        int getEachCharacteristic(std::string);
};

//////////////////////////////////////////////////////////
const std::string PARTY_NAMES[3] = {"ACP", "CLP", "PFP"};
const std::string PARTY_DESCRIPTIONS[3] = {
    "The ACP, or Alliance for Cybertron Prosperity, focuses on economic growth, innovation, and fostering entrepreneurship to drive Cybertron's prosperity and competitiveness in the global market.",
    "The CLP, or Cybertron Labour Party, champions workers' rights, social justice, and economic equality as the cornerstones of their political platform.",
    "THe PFP, or the Progressive Freedom Party, advocates for individual liberties, civil rights, and social justice, working to ensure that every Cybertronian enjoys equal freedoms and opportunities."};
const int PARTY_STANCE_RANGES[3][2] = {{20,55}, {25,55}, {20,50}};

class Party{
    private:
        std::string name;
        std::string description;
        Leader leader;
        std::vector<Candidate> candidates;
        ManagerialTeam managerialTeam;
        std::vector<Stance> stances;
        int winAreaCount;
    public:
        Party(std::string, std::string);
        void setManagerialTeam(ManagerialTeam);
        void setLeader(Leader);
        void setCandidates(std::vector<Candidate>);
        void setStances(std::vector<Stance>);
        std::string getName();
        std::string getDescription();
        Leader getLeader();
        ManagerialTeam getManagerialTeam();
        std::vector<Candidate> getCandidates();
        std::vector<Stance> getStances();
        void updateCandidate(Candidate&);
        void updateLeader(Leader&);
        void increaseWinAreaCount();
        int getWinAreaCount();
};

///////////////////////////////////////////////////////////////////////////
const int POPULATION_RANGE[] = {500, 2000};
const int DIVISION_STANCE_RANGE[] = {50, 90};
class ElectoralDivision{
    private:
        std::string name;
        int population;
        std::vector<Stance> stances;
    public:
        ElectoralDivision(std::string, int);
        void setStances(std::vector<Stance>);
        std::string getName();
        int getPopulation();
        std::vector<Stance> getStances();
        void updateStance(Stance&);

};

///////////////////////////////////////////////////////////////////////////
const std::string EVENT_TYPES[] = {"DEBATE", "CANDIDATE", "LEADER", "ISSUE"};
class Event{
    protected:
        std::string eventType;
        std::string description;
        std::string electoralDivision;
        std::string impactedSkill;
    public:
        Event();
        void setEventType(std::string);
        void setDescription(std::string);
        void setElectoralDivision(std::string);
        std::string getElectoralDivision();
        void setImpactedSkill(std::string);
        std::string getImpactedSkill();
        virtual void display(std::vector<Party>);
};

class Debate : public Event{
    private:
        std::vector<Candidate> impactedCandidates;
    public:
        Debate();
        void setImpactedCandidate(std::vector<Candidate>);
        void display(std::vector<Party>);
};

class CandidateEvent : public Event{
    private:
        std::vector<Candidate> impactedCandidates;
    public:
        CandidateEvent();
        void setImpactedCandidate(std::vector<Candidate>);
        void display(std::vector<Party>);
};

class LeaderEvent : public Event{
    private:
        std::vector<Leader> impactedLeaders;
    public:
        LeaderEvent();
        void setImpactedLeader(std::vector<Leader>);
        void display(std::vector<Party>);
};

class IssueEvent : public Event{
    private:
        std::vector<ElectoralDivision> impactedDivisions;
    public:
        IssueEvent();
        void addImpactedDivision(ElectoralDivision&);
        void display(std::vector<Party>);
};

///////////////////////////////////////////////////////////////////////////
#endif