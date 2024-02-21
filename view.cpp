#include "view.h"
#include <iomanip>


void View::displayIssueInfo(std::vector<Issue>&issues){
    std::cout << "\t\t\t\t\t\t~~~ ISSUES ~~~\n\n";
    std::cout << "There are five main issues that need urgent attention in Cybertron.\n";
    int count = 1;
    for(Issue issue:issues){
        std::cout<<"Issue Number: " << count << ", ";
        issue.display();
        std::cout<<std::endl;
        count++;
    }
    std::cout << "========================================================================================================================================================================\n\n";
}

void View::displayPartyInfo(std::vector<Party>&parties){
    std::cout << "\t\t\t\t\t\t~~~ PARTIES ~~~\n\n";
    int count = 1;
    for(Party party:parties){
        std::cout << "Party Number: " << count  << ", " << party.getName() << std::endl;
        std::cout << party.getDescription() << std::endl;
        std::cout << std::endl << std::left << std::setw(20) << std::setfill(' ') << "POSITION";
        std::cout << std::left << std::setw(20) << std::setfill(' ') << "NAME";
        std::cout << std::left << std::setw(30) << std::setfill(' ') << "ELECTORAL DIVISION";
        std::cout << std::left << std::setw(40) << std::setfill(' ') << "CHARACTERISTICS" << std::endl;
        std::cout<< "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

        Leader leader = party.getLeader();
        leader.display();

        std::vector<Candidate> candidates = party.getCandidates();
        for(auto &candidate: candidates){
            candidate.display();
        }
        party.getManagerialTeam().display();
        std::cout << std::endl;
        std::cout << std::left << std::setw(40) << std::setfill(' ') << "STANCES (significance/approach)";
        for(int i=0; i<5; i++){
            std::cout << std::left << std::setw(20) << std::setfill(' ') << ISSUE_NAMES[i];
        }
        std::cout<< std::endl<< "------------------------------------------------------------------------------------------------------------------------------------------------\n";
        std::cout << std::left << std::setw(40) << std::setfill(' ') << "Leader, Candidates";
        for(int i=0; i<5; i++){
            std::cout << std::left << std::setw(20) << std::setfill(' ') << party.getStances().at(i).getStance();
        }
        
        std::cout << std::endl << std::endl << std::endl;
        count++;
    }
    std::cout << "========================================================================================================================================================================\n\n";
}

void View::displayElectoralDivisionInfo(std::vector<ElectoralDivision>& electoralDivisions, std::vector<Party>& parties){
    std::cout << "\t\t\t\t\t\t~~~ ELECTORAL DIVISIONS ~~~\n\n";
    std::cout << std::left << std::setw(25) << std::setfill(' ') << "ELECTORAL DIVISIONS";
    std::cout << std::left << std::setw(15) << std::setfill(' ') << "POPULATION";
    std::cout << std::left << std::setw(62) << std::setfill(' ') << "CANDIDATES";
    std::cout << std::left << "STANCES(ISSUE)";
    std::cout << std::endl <<
 "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    for(int i=0; i<electoralDivisions.size(); i++){
        ElectoralDivision division = electoralDivisions.at(i);
        std::cout << std::left << std::setw(25) << std::setfill(' ') << division.getName();
        std::cout << std::left << std::setw(15) << std::setfill(' ') << division.getPopulation();
        std::string output = "";
        for(auto& party:parties){
            std::vector<Candidate> candidates = party.getCandidates();
            for(auto& candidate: candidates){
                if(candidate.getDivision() == division.getName()){
                    output += candidate.getName() + "(" + party.getName() + "), ";
                }
            }
        }
        output = output.substr(0, output.size() - 2);
        std::cout << std::left << std::setw(62) << std::setfill(' ') << output;
        output = "";
        for(int i=0; i<5; i++){
            output += division.getStances().at(i).getStance() + "("  + ISSUE_NAMES[i] + ")  ";
        }
        std::cout << output << std::endl;
    }
}

void View::displayCandidateEvent1(Candidate& winner, Candidate& loser, int randomImpact1, int randomImpact2){
    std::cout << "Public are more pleased with the policies of " << winner.getName() << std::endl<< std::endl;
    std::cout << std::left << std::setw(21) << std::setfill(' ') << "";
    std::cout << std::left << std::setw(15) << std::setfill(' ') << winner.getName();
    std::cout << std::left << std::setw(15) << std::setfill(' ') << loser.getName() << std::endl;
    std::cout << std::left << std::setw(21) << std::setfill(' ') << "Current Popularity : "  ;
    std::cout << std::left << std::setw(15) << std::setfill(' ') << winner.getEachCharacteristic("POPULARITY");
    std::cout << std::left << std::setw(15) << std::setfill(' ') << loser.getEachCharacteristic("POPULARITY") << std::endl;
    std::cout << std::left << std::setw(21) << std::setfill(' ') << "Impacted           : +"  ;
    std::cout << std::left << std::setw(15) << std::setfill(' ') << 
    randomImpact1;
    std::cout << std::left << std::setw(15) << std::setfill(' ') << 
    "-" + std::to_string(randomImpact2) << std::endl;
    std::cout << std::left << std::setw(21) << std::setfill(' ') << "Updated Popularity : " ;
    std::cout << std::left << std::setw(15) << std::setfill(' ') << 
    winner.getEachCharacteristic("POPULARITY") + randomImpact1;
    std::cout << std::left << std::setw(15) << std::setfill(' ') << 
    loser.getEachCharacteristic("POPULARITY") - randomImpact2 << std::endl;
    winner.setEachCharacteristic("POPULARITY", winner.getEachCharacteristic("POPULARITY") + randomImpact1);
    loser.setEachCharacteristic("POPULARITY", loser.getEachCharacteristic("POPULARITY") - randomImpact2);
    std::cout << "Updated characters of : " << winner.getName() << " - ";
    std::cout << winner.getCharaInfo() << std::endl ;
    std::cout << "Updated characters of : " << loser.getName()<< " - ";
    std::cout << loser.getCharaInfo() << std::endl << std::endl;
}

void View::displayCandidateEvent2(Candidate& candidate1, int randomImpact){
    std::cout << "Current Popularity : " << candidate1.getEachCharacteristic("POPULARITY") << std::endl;
    std::cout << "Impacted           : -" << randomImpact << std::endl;
    candidate1.setEachCharacteristic("POPULARITY", candidate1.getEachCharacteristic("POPULARITY") - randomImpact);
    std::cout << "Updated Popularity : " << candidate1.getEachCharacteristic("POPULARITY") << std::endl;
    std::cout << "Updated characters : ";
    std::cout << candidate1.getCharaInfo() << std::endl << std::endl;
}

void View::displayLeaderEvent1(Leader& leader, int randomImpact){
    std::cout << "Current Popularity : " << leader.getEachCharacteristic("POPULARITY") << std::endl;
    std::cout << "Impacted           : +" << randomImpact << std::endl;
    leader.setEachCharacteristic("POPULARITY", leader.getEachCharacteristic("POPULARITY") + randomImpact);
    std::cout << "Updated Popularity : " << leader.getEachCharacteristic("POPULARITY") << std::endl;
    std::cout << "Updated characters : ";
    std::cout << leader.getCharaInfo() << std::endl << std::endl;
}

void View::displayLeaderEvent2(Leader& winner, Leader& loser1, Leader& loser2, int randomImpact1, int randomImpact2){
    std::cout << "Public are more into the problem solving skill and future plans of " << winner.getName() << std::endl<< std::endl;
    std::cout << std::left << std::setw(21) << std::setfill(' ') << "";
    std::cout << std::left << std::setw(15) << std::setfill(' ') << winner.getName();
    std::cout << std::left << std::setw(15) << std::setfill(' ') << loser1.getName();
    std::cout << std::left << std::setw(15) << std::setfill(' ') << loser2.getName() << std::endl;
    std::cout << std::left << std::setw(21) << std::setfill(' ') << "Current Popularity : "  ;
    std::cout << std::left << std::setw(15) << std::setfill(' ') << winner.getEachCharacteristic("POPULARITY");
    std::cout << std::left << std::setw(15) << std::setfill(' ') << loser1.getEachCharacteristic("POPULARITY");
    std::cout << std::left << std::setw(15) << std::setfill(' ') << loser2.getEachCharacteristic("POPULARITY") << std::endl;
    std::cout << std::left << std::setw(21) << std::setfill(' ') << "Impacted           : +"  ;
    std::cout << std::left << std::setw(15) << std::setfill(' ') << 
    randomImpact1;
    std::cout << std::left << std::setw(15) << std::setfill(' ') << 
    "-" + std::to_string(randomImpact2);
    std::cout << std::left << std::setw(15) << std::setfill(' ') << 
    "-" + std::to_string(randomImpact2) << std::endl;
    std::cout << std::left << std::setw(21) << std::setfill(' ') << "Updated Popularity : " ;
    std::cout << std::left << std::setw(15) << std::setfill(' ') << 
    winner.getEachCharacteristic("POPULARITY") + randomImpact1;
    std::cout << std::left << std::setw(15) << std::setfill(' ') << 
    loser1.getEachCharacteristic("POPULARITY") - randomImpact2;
    std::cout << std::left << std::setw(15) << std::setfill(' ') << 
    loser2.getEachCharacteristic("POPULARITY") - randomImpact2 << std::endl;
    winner.setEachCharacteristic("POPULARITY", winner.getEachCharacteristic("POPULARITY") + randomImpact1);
    loser1.setEachCharacteristic("POPULARITY", loser1.getEachCharacteristic("POPULARITY") - randomImpact2);
    loser2.setEachCharacteristic("POPULARITY", loser2.getEachCharacteristic("POPULARITY") - randomImpact2);
    std::cout << "Updated characters of : " << winner.getName() << " - ";
    std::cout << winner.getCharaInfo() << std::endl ;
    std::cout << "Updated characters of : " << loser1.getName()<< " - ";
    std::cout << loser1.getCharaInfo() << std::endl;
    std::cout << "Updated characters of : " << loser2.getName()<< " - ";
    std::cout << loser2.getCharaInfo() << std::endl << std::endl;
}


void View::displayDebate(Candidate& winner, Candidate& loser1, Candidate& loser2, int randomImpact1, int randomImpact2){
    std::cout << winner.getName() << " is chosen as the winner by the audience." << std::endl << std::endl;
    std::cout << std::left << std::setw(21) << std::setfill(' ') << "";
    std::cout << std::left << std::setw(15) << std::setfill(' ') << winner.getName();
    std::cout << std::left << std::setw(15) << std::setfill(' ') << loser1.getName();
    std::cout << std::left << std::setw(15) << std::setfill(' ') << loser2.getName() << std::endl;
    std::cout << std::left << std::setw(21) << std::setfill(' ') << "Current Popularity : "  ;
    std::cout << std::left << std::setw(15) << std::setfill(' ') << winner.getEachCharacteristic("POPULARITY");
    std::cout << std::left << std::setw(15) << std::setfill(' ') << loser1.getEachCharacteristic("POPULARITY");
    std::cout << std::left << std::setw(15) << std::setfill(' ') << loser2.getEachCharacteristic("POPULARITY") << std::endl;
    std::cout << std::left << std::setw(21) << std::setfill(' ') << "Impacted           : +"  ;
    std::cout << std::left << std::setw(15) << std::setfill(' ') << 
    randomImpact1;
    std::cout << std::left << std::setw(15) << std::setfill(' ') << 
    "-" + std::to_string(randomImpact2);
    std::cout << std::left << std::setw(15) << std::setfill(' ') << 
    "-" + std::to_string(randomImpact2) << std::endl;
    std::cout << std::left << std::setw(21) << std::setfill(' ') << "Updated Popularity : " ;
    std::cout << std::left << std::setw(15) << std::setfill(' ') << 
    winner.getEachCharacteristic("POPULARITY") + randomImpact1;
    std::cout << std::left << std::setw(15) << std::setfill(' ') << 
    loser1.getEachCharacteristic("POPULARITY") - randomImpact2;
    std::cout << std::left << std::setw(15) << std::setfill(' ') << 
    loser2.getEachCharacteristic("POPULARITY") - randomImpact2 << std::endl;
    winner.setEachCharacteristic("POPULARITY", winner.getEachCharacteristic("POPULARITY") + randomImpact1);
    loser1.setEachCharacteristic("POPULARITY", loser1.getEachCharacteristic("POPULARITY") - randomImpact2);
    loser2.setEachCharacteristic("POPULARITY", loser2.getEachCharacteristic("POPULARITY") - randomImpact2);
    std::cout << "Updated characters of : " << winner.getName() << " - ";
    std::cout << winner.getCharaInfo() << std::endl ;
    std::cout << "Updated characters of : " << loser1.getName()<< " - ";
    std::cout << loser1.getCharaInfo() << std::endl;
    std::cout << "Updated characters of : " << loser2.getName()<< " - ";
    std::cout << loser2.getCharaInfo() << std::endl << std::endl;
}

void View::displayIssueEvent(ElectoralDivision& division, Stance* stanceptr, int randSig, int randAppr, std::string issue){
    std::cout << "Current stance     : " ;
    std::cout << stanceptr->getStance() <<"(" << stanceptr->getIssue() << ")  " << std::endl;
    std::cout << "Significance impact: +" << randSig << ", ";
    std::cout << "Approach impact : +" << randAppr << std::endl;
    stanceptr->setApproach(stanceptr->getApproach() + randAppr);
    stanceptr->setSignificance(stanceptr->getSignificance() + randSig);

    division.updateStance(*stanceptr);
    std::cout << "Updated stance     : " ;
    for(Stance& stance:division.getStances()){
        if(stance.getIssue() == issue){
            std::cout << stance.getStance()<< "(" << stance.getIssue() << ")  "; 
        }
        
    }
}

void View::displayElectionDayIntro(std::vector<ElectoralDivision>& electoralDivisions, std::vector<Party>& parties){
    std::cout << "\n\t\t\t\t\t\t~~~ ELECTION DAY ~~~\n\n";
    std::cout << "After a long wait, the election day has finally arrived.\n\n";
    std::cout << "Here is the finalized info of all parties.\n\n";
    displayPartyInfo(parties);
    std::cout << std::endl;
    std::cout << "Here is the finalized stance distributions of all electoral divisions.\n\n";
    displayElectoralDivisionInfo(electoralDivisions, parties);
    std::cout << std::endl << std::endl;
}




