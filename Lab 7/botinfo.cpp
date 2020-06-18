#include "botinfo.h"

botInfo::botInfo(Bot& bot, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::botInfo)
{
    ui->setupUi(this);


    if(bot.color/10==1){
        //ui->color_value->setText("Red");
        ui->color_value->setText(QString::number(bot.color));
        ui->superpower_value->setText("tasteless");
    }
    else if(bot.color/10==2){
        //ui->color_value->setText("Yellow");
        ui->color_value->setText(QString::number(bot.color));
        ui->superpower_value->setText("salad eater");
    }
    else if(bot.color/10==3){
        //ui->color_value->setText("Violet");
        ui->color_value->setText(QString::number(bot.color));
        ui->superpower_value->setText("meat eater");
    }
    else if(bot.color/10==4){
        //ui->color_value->setText("Orange");
        ui->color_value->setText(QString::number(bot.color));
        ui->superpower_value->setText("killer");
    }
    else if(bot.color/10==5){
        //ui->color_value->setText("Blue");
        ui->color_value->setText(QString::number(bot.color));
        ui->superpower_value->setText("altruist");
    }
    else{
        //ui->color_value->setText("Green");
        ui->color_value->setText(QString::number(bot.color));
        ui->superpower_value->setText("inspires confidence");
    }
    ui->energy_value->setText(QString::number(bot.energy));
    ui->view_value->setText(QString::number(bot.view));
    ui->age_value->setText(QString::number(bot.age));

    ui->number_of_gens_of_action_value->setText(QString::number(bot.number_of_gens_of_action));
    ui->chance_of_mutation_value->setText(QString::number(bot.chance_of_mutation));
    ui->min_energy_for_division_value->setText(QString::number(bot.min_energy_for_division));
    ui->number_of_gens_of_action_value->setText(QString::number(bot.number_of_gens_of_action));
    ui->condition_for_attack_value->setText(QString::number(bot.condition_for_attack));

    ui->Gens_action_table->setRowCount(10);
    ui->Gens_action_table->setColumnCount(7);
    for(int i=0;i<7;i++){
        ui->Gens_action_table->setColumnWidth(i,70);
    }
    ui->Gens_action_table->setHorizontalHeaderLabels({"Nothing","Meat","Salad","Wall","Friend","Enemy","Fail"});
    ui->Gens_action_table->setVerticalHeaderLabels({"1","2","3","4","5","6","7","8","9","10"});

    ui->Gens_irritation_table->setRowCount(8);
    ui->Gens_irritation_table->setColumnCount(7);
    for(int i=0;i<7;i++){
        ui->Gens_irritation_table->setColumnWidth(i,70);
    }
    ui->Gens_irritation_table->setHorizontalHeaderLabels({"Nothing","Meat","Salad","Wall","Friend","Enemy","Fail"});
    ui->Gens_irritation_table->setVerticalHeaderLabels({"T","TR","R","DR","D","DL","L","TL"});

    for(int i=0;i<bot.number_of_gens_of_action;i++){
        for(int j=0;j<7;j++){
            ui->Gens_action_table->setItem(i,j,new QTableWidgetItem(QString::number(bot.gens_of_action[i][j])));
        }
    }

    for(int i=0;i<8;i++){
        for(int j=0;j<7;j++){
            ui->Gens_irritation_table->setItem(i,j,new QTableWidgetItem(QString::number(bot.gens_of_irritation[i][j])));
        }
    }

}

botInfo::~botInfo()
{
    delete ui;
}
