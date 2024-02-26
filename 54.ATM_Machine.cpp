//
//  main.cpp
//  ATM_StateMachine
//
//  Created by Sathya Babu on 15/02/24.
//

#include <iostream>
using namespace std;

class AtmState {

public:
    virtual void insertCard() = 0;
    virtual void ejectCard() = 0;
    virtual void insertPin(int pinEntered) = 0;
    virtual void requestCash(int cashToWithdraw) = 0;

};

class ATMmachine
{
    AtmState* _atmState;
    int       _cashInMachine;
    bool      _correctPinEntered = false;

public:
    ATMmachine();
    

    void setATMState(AtmState* ipState);

    void insertCard();
   
    void requestCash(int CashToWithdraw);
    
    void ejectCard();
   
    void insertPin(int pinEntered);
        

        void setCashInMachine(int newCashInMachine);
       
        int getCashInMachine() const;
        
        void setCorrectPinEntered(bool iPinStatus);
        

        bool getCorrectPinEntered() const;
       

   

};



 //NO CARD
 class NoCard : public AtmState
 {
     ATMmachine* _pAtmMachine;
 public:
     NoCard(ATMmachine *pAtmMac )
     {
         _pAtmMachine = pAtmMac;
         _pAtmMachine->setCorrectPinEntered(false);
         cout << "\n NoCard ctor";
     }
     ~NoCard()
     {
         cout << "\n NoCard dtor";
     }

     void insertCard();
    /* {
         cout << "\n Please, enter your pin:";
         _pAtmMachine->setATMState(new HasCard(_pAtmMachine));
     }*/

     void ejectCard()
     {
         cout << "\n You have not inserted card.";
     }

     void insertPin(int pinEntered)
     {
         cout << "\n You have not inserted card.";
     }

     void requestCash(int cashToWithdraw)
     {
         cout << "\n You have not inserted card.";
     }
 };

 class HasCard : public AtmState
 {
     ATMmachine* _pAtmMachine;
 public:
     HasCard(ATMmachine* pAtmMachine)
     {
         _pAtmMachine = pAtmMachine;
         cout << "\n HasCard ctor";
     }
     ~HasCard()
     {
         cout << "\n HasCard dtor";
     }

     void insertCard()
     {
         cout <<"Card can be inserted only once";
     }

     void ejectCard()
     {
         cout << "Your card is ejected.";
         _pAtmMachine->setATMState(new NoCard(_pAtmMachine));
     }

     void insertPin(int iPinEntered);
    /* {
         if (1234 == iPinEntered)
         {
             cout << "You entered the correct pin";
             _pAtmMachine->setCorrectPinEntered(true);
             _pAtmMachine->setATMState(new HasPin(_pAtmMachine));
         }
         else
         {
             cout << "You entered the wrong pin";
             _pAtmMachine->setCorrectPinEntered(false);
             cout << "Your card is ejected..";
             _pAtmMachine->setATMState(new NoCard(_pAtmMachine));
         }
     }*/

     void requestCash(int cashToWithdraw)
     {
         cout << "You  have not entered your Pin";
     }
 };


 class HasPin : public AtmState
 {
     ATMmachine* _pAtmMachine;
 public:
     HasPin(ATMmachine* pAtmMachine)
     {
         _pAtmMachine = pAtmMachine;
         cout << "\n HasPin ctor";
     }
     ~HasPin()
     {
         cout << "\n HasPin dtor";
     }

     void insertCard()
     {
         cout << "You already entered a card";
     }

     void ejectCard()
     {
         cout << "Your card is ejected.";
         _pAtmMachine->setATMState(new NoCard(_pAtmMachine));
     }

     void insertPin(int pinEntered)
     {
         cout << "You already entered pin.";
     }

     void requestCash(int cashToWithdraw);
     /*{
         int cashIMachine = _pAtmMachine->getCashInMachine();
         if (cashToWithdraw > cashIMachine)
         {
             cout << "You dont have so much of cash available";
             cout << "Your card is ejected";
             _pAtmMachine->setATMState(new NoCard(_pAtmMachine));
         }
         else
         {
             cout << cashToWithdraw << " is provided by the machine";
             _pAtmMachine->setCashInMachine(cashIMachine - cashToWithdraw);
             cout << "Your card is ejected.";
             _pAtmMachine->setATMState(new NoCard(_pAtmMachine));

             if (_pAtmMachine->getCashInMachine() <= 0)
             {
                 cout << "ATM is out of cash !!";
                 _pAtmMachine->setATMState(new NoCash(_pAtmMachine));
             }
         }
     }*/
 };

 class NoCash : public AtmState
 {
     ATMmachine* _pAtmMachine;
 public:
     NoCash(ATMmachine* pAtmMachine)
     {
         _pAtmMachine = _pAtmMachine;
         cout << "\n NoCash ctor";
     }
     ~NoCash()
     {
         cout << "\n NoCash dtor";
     }

     void insertCard()
     {
        cout <<"You don't have any money";
     }

     void ejectCard()
     {
         cout << "You dont have any money";
         cout << "There is no card to eject";
     }

     void insertPin(int pinEntered)
     {
         cout << "We dont have any money";
     }

     void requestCash(int cashToWithdraw)
     {
         cout << "We dont have any money";
     }
 };


 void HasCard::insertPin(int iPinEntered)
 {
     if (1234 == iPinEntered)
     {
         cout << "You entered the correct pin";
         _pAtmMachine->setCorrectPinEntered(true);
         _pAtmMachine->setATMState(new HasPin(_pAtmMachine));
     }
     else
     {
         cout << "You entered the wrong pin";
         _pAtmMachine->setCorrectPinEntered(false);
         cout << "Your card is ejected..";
         _pAtmMachine->setATMState(new NoCard(_pAtmMachine));
     }
 }
 void NoCard::insertCard()
 {
     cout << "\n Please, enter your pin:";
     _pAtmMachine->setATMState(new HasCard(_pAtmMachine));
 }

 void HasPin::requestCash(int cashToWithdraw)
 {
     int cashIMachine = _pAtmMachine->getCashInMachine();
     if (cashToWithdraw > cashIMachine)
     {
         cout << "You dont have so much of cash available";
         cout << "Your card is ejected";
         _pAtmMachine->setATMState(new NoCard(_pAtmMachine));
     }
     else
     {
         cout << cashToWithdraw << " is provided by the machine";
         _pAtmMachine->setCashInMachine(cashIMachine - cashToWithdraw);
         cout << "Your card is ejected.";
         _pAtmMachine->setATMState(new NoCard(_pAtmMachine));

         if (_pAtmMachine->getCashInMachine() <= 0)
         {
             cout << "ATM is out of cash !!";
             _pAtmMachine->setATMState(new NoCash(_pAtmMachine));
         }
     }
 }
  
 ATMmachine::ATMmachine()
     {
         _atmState            = new NoCard(this);
         _cashInMachine       = 5000;
         _correctPinEntered   = false;
     }

     void ATMmachine::setATMState(AtmState* ipState)
     {
         if (NULL != ipState)
         {
             //delete _atmState;
             _atmState = ipState;
         }
     }

     void ATMmachine::setCashInMachine(int newCashInMachine)
     {
         _cashInMachine = newCashInMachine;

     }
     int ATMmachine::getCashInMachine() const
     {
         return _cashInMachine;
     }

     void ATMmachine::setCorrectPinEntered(bool iPinStatus)
     {
         _correctPinEntered = iPinStatus;
     }

     bool ATMmachine::getCorrectPinEntered() const
     {
         return _correctPinEntered;
     }

     void ATMmachine::insertCard()
     {
         _atmState->insertCard();// nocard
     }

     void ATMmachine::requestCash(int CashToWithdraw)
     {
         _atmState->requestCash(CashToWithdraw);
     }

     void ATMmachine::ejectCard()
     {
         _atmState->ejectCard(); // hascard
     }
     void ATMmachine::insertPin(int pinEntered)
     {
         _atmState->insertPin(pinEntered);
     }

 




//---------------  main()
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Welcome to the ATM machine \n";
    ATMmachine atmMachine ;
//    atmMachine.getCashInMachine();
    atmMachine.insertCard();
    atmMachine.insertPin(1234);
    atmMachine.ejectCard();
    atmMachine.requestCash( 500 );
    
    
    return 0;
}
