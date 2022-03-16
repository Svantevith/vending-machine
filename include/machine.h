//
// Created by szczy on 16.06.2020.
//

#ifndef PROJECT1_MACHINE_H
#define PROJECT1_MACHINE_H

#include<string>

using namespace std;

class Machine
{
protected:
    int id;
    string name;
    int stock;
public:
    double cart;
    double change;

    Machine(double cartDefinedByUser, double changeDefinedByUser);
    Machine(int idDefinedByUser, string nameDefinedByUser, int stockDefinedByUser);

    double getCart();
    double getChange();
    int getId();
    string getName();
    int getStock();

    void setId(int idDefinedByUser);
    void setName(int nameDefinedByUser);
    void setStock(int stockDefinedByUser);

    void display();
    void loadFromFile(string filename_txt);
    void saveToFile(string filename_txt);
};

#endif //PROJECT1_MACHINE_H
