//
// Created by szczy on 16.06.2020.
//

#ifndef PROJECT1_MONEY_H
#define PROJECT1_MONEY_H

#include<string>
#include<vector>
#include<memory>

#include"machine.h"

class Money : public Machine
{
    string filename = "money.txt";
    double value;
public:
    Money(int idDefinedByUser, string nameDefinedByUser, int stockDefinedByUser, double valueDefinedByUser);

    double getValue();

    void display();

    int setDefaultStock();

    void loadFromFile(string filename_txt);

    void saveToFile(string filename_txt);

    Money& operator++();

    void operator + (const int& coin_to_withdraw);

    void operator = (const int& new_stock);

    static void insertMoney(Machine& cartDefinedByUser, int& input, vector<unique_ptr<Money>>& v_unique);

    static void giveChange(Machine& changeDefinedByUser, vector<unique_ptr<Money>>& vect_unique);

    static void sneakyFunction(vector<unique_ptr<Money>>& vect_m_unique);

    static void displayUniqueMoney(vector <unique_ptr<Money>>& v_unique);

    static bool isPoolOkUnique(vector<unique_ptr<Money>>& vect_m);

};

#endif //PROJECT1_MONEY_H
