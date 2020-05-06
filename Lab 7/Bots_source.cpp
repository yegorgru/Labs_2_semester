#include "Bots.h"

extern std::mt19937 mersenne;


/*Bot::Bot()
{
    energy = 20;
    max_energy=100;
    max_damage=10;
    counter = 0;
    posX = -1;
    posY = -1;
    number_of_gens_of_action=4;
    min_energy_for_division=50;
    max_age=5000;
    view = mersenne()%8;
    alive = true;
    color=1+mersenne()%6;
    for(int i=0;i<8;i++){
        for(int j=0;j<6;j++){
            gens_of_irritation[i][j]=mersenne() % 9;
        }
    }
    for(int i=0;i<8;i++){
        gens_of_irritation[i][6]=mersenne() % 8;
    }
    for(int i=0;i<number_of_gens_of_action;i++){
        int* to_add=new int[7];
        gens_of_action.push_back(to_add);
        for (int j = 0; j < 6; j++) {
            gens_of_action[i][j] = mersenne() % 9;
        }
    }
    for(int i=0;i<number_of_gens_of_action;i++){
        gens_of_irritation[i][6]=mersenne() % 8;
    }
}*/


Bot::Bot(int energy,int max_energy,int number_of_gens_of_action,int min_energy_for_division){
    this->energy=energy;
    this->max_energy=max_energy;
    this->number_of_gens_of_action=number_of_gens_of_action;
    this->min_energy_for_division=min_energy_for_division;
    posX = -1;
    posY = -1;
    counter = 0;
    view = mersenne()%8;
    alive = true;
    condition_for_attack=mersenne()%(max_energy/2);
    chance_of_mutation=10;
    irritation=10;
    color=1+mersenne()%6;
    superpower=color;

    for(int i=0;i<8;i++){
        for(int j=0;j<6;j++){
            gens_of_irritation[i][j]=mersenne() % 10;
        }
    }
    for(int i=0;i<8;i++){
        gens_of_irritation[i][6]=mersenne() % 9;
    }
    for(int i=0;i<number_of_gens_of_action;i++){
        std::vector<int>to_add;
        gens_of_action.push_back(to_add);
        for (int j = 0; j < 6; j++) {
            gens_of_action[i].push_back(mersenne() % 10);
        }
    }
    for(int i=0;i<number_of_gens_of_action;i++){
        gens_of_action[i].push_back(mersenne() % 9);
    }
}

Bot::Bot(const Bot& another){
    for(int i=0;i<8;i++){
        for(int j=0;j<7;j++){
            this->gens_of_irritation[i][j]=another.gens_of_irritation[i][j];
        }
    }
    this->gens_of_action=another.gens_of_action;

    //changeless
    this->energy=another.energy;
    this->max_energy=another.max_energy;
    this->counter=0;
    this->posX=another.posX;
    this->posY=another.posY;
    this->view=another.view;
    this->alive=true;
    this->irritation=10;


    //changeable
    this->number_of_gens_of_action=another.number_of_gens_of_action;
    this->min_energy_for_division=another.min_energy_for_division;
    this->condition_for_attack=another.condition_for_attack;
    this->color=another.color;
    this->chance_of_mutation=another.chance_of_mutation;

    int is_mutation=mersenne()%100;
    int what_mutation=-1;
    if(is_mutation<chance_of_mutation){
        what_mutation=mersenne()%(56+number_of_gens_of_action*7+5);
        if(what_mutation==0){
            int half_chance=mersenne()%2;
            if(half_chance==0){
                if(number_of_gens_of_action>1){
                    int what_delete=mersenne()%(this->number_of_gens_of_action);
                    gens_of_action.erase(gens_of_action.begin()+what_delete);
                    this->number_of_gens_of_action--;
                }
            }
            else{
                std::vector<int>to_add;
                gens_of_action.push_back(to_add);
                for (int j = 0; j < 6; j++) {
                    gens_of_action[number_of_gens_of_action].push_back(mersenne() % 10);
                }
                gens_of_action[number_of_gens_of_action].push_back(mersenne() % 9);
                number_of_gens_of_action++;
            }
        }
        else if(what_mutation==1){
           min_energy_for_division*=((double(mersenne()%20))/10);
           if(min_energy_for_division>max_energy-1){
               min_energy_for_division=max_energy-1;
           }
           else if(min_energy_for_division<1){
               min_energy_for_division=1;
           }
        }
        else if(what_mutation==2){
            condition_for_attack*=((double(mersenne()%20))/10);
            if(condition_for_attack>max_energy-1){
                condition_for_attack=max_energy-1;
            }
            else if(condition_for_attack<1){
                condition_for_attack=1;
            }
        }
        else if(what_mutation==3){
            color=1+mersenne()%6;
        }
        else if(what_mutation==4){
            chance_of_mutation*=((double(mersenne()%20))/10);
            if(chance_of_mutation>99){
                chance_of_mutation=99;
            }
            else if(chance_of_mutation<1){
                chance_of_mutation=1;
            }
        }
        else{
            what_mutation-=5;
            if(what_mutation<56 && what_mutation%7==6){
                gens_of_irritation[what_mutation/7][6]=mersenne()% 9;
            }
            else if(what_mutation<56){
                gens_of_irritation[what_mutation/7][what_mutation%7]=mersenne()% 10;
            }
            else{
                what_mutation-=56;
                if(what_mutation%7==6){
                    gens_of_action[what_mutation/number_of_gens_of_action][6]=mersenne()% 9;
                }
                else{
                    gens_of_action[what_mutation/number_of_gens_of_action][what_mutation%7]=mersenne()% 10;
                }
            }
        }
    }

    this->superpower=this->color;

}

























