#ifndef STATEVAULT_HPP
#define STATEVAULT_HPP

#include <vector>


// include all the different states here
#include "NormalState.hpp"
#include "LeavingState.hpp"

class ClStateVault
{
public:
    ClStateVault() {id = 0;}
    //Cleanup remaining states
    ~ClStateVault()
    {
        for ( unsigned int n = 0; n < StatesVector.size();n++)
        {
            delete StatesVector[n];
        }
    }
    ClAbstractState* requestStartState() {return createState(NORMAL);}
    ClAbstractState* requestState(enum STATES newState, int oldId)
    {
        for ( unsigned int n = 0; n < StatesVector.size();n++)
        {   if(StatesVector[n]->getID() == oldId)
            {
                delete StatesVector[n];
                StatesVector.erase(StatesVector.begin()+n);
                break;
            }
        }
        return createState(newState);
    }
private:
    ClAbstractState* createState(enum STATES state)
    {
        switch (state)
        {
        case (NORMAL):
            {
                ClNormalState *pAddMe = new ClNormalState(id,&StateMachine);
                StatesVector.push_back(pAddMe);
                return pAddMe;
            }
        // To do add more states
        }
    }
    std::vector<ClAbstractState *> StatesVector;
    ClStateMachine StateMachine;
    int id;
};

#endif // STATEVAULT_HPP
