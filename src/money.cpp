//
// Created by szczy on 16.06.2020.
//

#define MAX_PRODUCTS_STOCK 10
#define FIVEBUCKS_DEFAULT_STOCK 1
#define TWOBUCKS_DEFAULT_STOCK 5
#define ONEBUCK_DEFAULT_STOCK 10
#define FIFTYPENNY_DEFAULT_STOCK 10
#define TWENTYPENNY_DEFAULT_STOCK 50
#define TENPENNY_DEFAULT_STOCK 100

#define MAX_CART_LIMIT 50
#define MIN_REQUIRED_POOL 50

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<memory>

#include "../include/money.h"

using namespace std;

Money::Money(int idDefinedByUser, string nameDefinedByUser, int stockDefinedByUser, double valueDefinedByUser)
        :Machine(idDefinedByUser, nameDefinedByUser, stockDefinedByUser)
{
    this->value = valueDefinedByUser;
}

double Money::getValue()
{
    return this->value;
}
void Money::display()
{
    Machine::display();
    cout << "Value: " << this->value << " PLN" << endl
         << endl;
}
int Money::setDefaultStock()
{
    if (this->id == 1)
    {
        this->stock = FIVEBUCKS_DEFAULT_STOCK;
    }
    else if (this->id == 2)
    {
        this->stock = TWOBUCKS_DEFAULT_STOCK;
    }
    else if (this->id == 3)
    {
        this->stock = ONEBUCK_DEFAULT_STOCK;
    }
    else if (this->id == 4)
    {
        this->stock = FIFTYPENNY_DEFAULT_STOCK;
    }
    else if (this->id == 5)
    {
        this->stock = TWENTYPENNY_DEFAULT_STOCK;
    }
    else if (this->id == 6)
    {
        this->stock = TENPENNY_DEFAULT_STOCK;
    }
    else
    {
        cout << "Error: there is no coin with such id!" << endl;
        return 0;
    }
    return this->stock;
}

void Money::loadFromFile(string filename_txt)
{
    this->filename = filename_txt;
    Machine::loadFromFile(this->filename);

    fstream file;
    file.open(filename_txt, ios::in);

    int indexLineNr = (this->id - 1) * 4 + 1;
    int currentLineNr = 1;
    string lineText; //text gathered from one line in the text file
    while (getline(file, lineText)) //read the file till there is anyhting to read
    {
        if (currentLineNr == indexLineNr + 2)
        {
            this->value = stod(lineText.substr(7, 5));
        }
        currentLineNr++;
    }
    file.close();
}

void Money::saveToFile(string filename_txt)
{
    this->filename = filename_txt;
    Machine::saveToFile(this->filename);

    fstream file;
    file.open(filename_txt, ios::out | ios::app);
    file << "Price: " << this->value << " PLN" << endl << endl;
    file.close();
}

Money& Money::operator++()
{
    this->stock++;
    return *this;
}

void Money::operator + (const int& coin_to_withdraw)
{
    //int new_stock;
    //new_stock = this->stock + coin_to_withdraw;
    this->stock += coin_to_withdraw;
}

void Money::operator = (const int& new_stock)
{
    this->stock = new_stock;
}

void Money::insertMoney(Machine& cartDefinedByUser, int& input, vector<unique_ptr<Money>>& v_unique)
{
    cout << "CART: " << cartDefinedByUser.cart << " PLN" << endl;
    if (cartDefinedByUser.cart == 0)
    {
        bool isOk = false;
        while (isOk == false)
        {
            cout << "Your cart is empty. Would you like to continue shopping or exit? " << endl
                 << "1) Continue  2) Exit" << endl;
            cin >> input;
            if (input == 1)
            {
                isOk = true;
            }
            if (input == 2)
            {
                cout << "See you soon! " << endl;
                isOk = true;
            }
            else
            {
                cout << "Press either 1 or 2 to proceed with desired option: " << endl;
                isOk = false;
            }
        }
    }
    else
    {
        cout << "Cart: " << cartDefinedByUser.cart << endl;
        double sumOfInsertedMoney = 0;
        do
        {
            cout << "The coins of the following denomination are accepted: " << endl;
            for (const auto& money : v_unique)
            {
                cout << money->getId() << ") " << money->getValue() << " PLN, ";
            }
            cout << "Press a number in the range between 1 - 6, which corresponds to the coin denomination you want to insert: " << endl;
            cout << endl;
            cin >> input;
            if (input >= 1 && input <= 6)
            {
                cout << "NAME: " << v_unique.at(input - 1)->getName() << " STOCK BEFORE INSERTING COIN: " << v_unique.at(input - 1)->getStock() << endl;
                v_unique.at(input - 1)->operator++();
                cout << "NAME: " << v_unique.at(input - 1)->getName() << " STOCK AFTER INSERTING COIN: " << v_unique.at(input - 1)->getStock() << endl;
                sumOfInsertedMoney += v_unique.at(input - 1)->getValue();
                cout << "SUM OF INSERTED MONEY: " << sumOfInsertedMoney << " PLN" << endl;
            }
        } while (sumOfInsertedMoney < cartDefinedByUser.cart);
        if (cartDefinedByUser.cart == 0)
        {
            cartDefinedByUser.change = 0;
        }
        else
        {
            cartDefinedByUser.change = abs(cartDefinedByUser.cart - sumOfInsertedMoney);
        }
        cout << "Remaining change for the customer: " << cartDefinedByUser.change << " PLN" << endl;
    }
}

void Money::giveChange(Machine& changeDefinedByUser, vector<unique_ptr<Money>>& vect_unique)
{
    vector <unique_ptr<int>> coins; //delete &
    cout << "coins size: " << coins.size() << endl;
    for (int i = 0; i < 6; i++)
    {
        coins.push_back(make_unique<int>(0));
        cout << " *coin number at i: " << *coins.at(i) << endl;
    }
    while (((round(10 * changeDefinedByUser.change) / 10) >= (round(10 * vect_unique.at(0)->getValue()) / 10)) && (vect_unique.at(0)->getStock() > 0)) //give 5 PLN
    {
        cout << "Change before: " << (round(10 * changeDefinedByUser.change) / 10) << " Coins before: " << vect_unique.at(0)->getName() << " " << *coins.at(0) << endl;
        changeDefinedByUser.change -= vect_unique.at(0)->getValue();
        *coins.at(0) += 1;
        cout << "Change after: " << (round(10 * changeDefinedByUser.change) / 10) << " Coins after: " << vect_unique.at(0)->getName() << " " << *coins.at(0) << endl;
    }
    while (((round(10 * changeDefinedByUser.change) / 10) >= (round(10 * vect_unique.at(1)->getValue()) / 10)) && (vect_unique.at(1)->getStock() > 0)) //give 2 PLN
    {
        cout << "Change before: " << (round(10 * changeDefinedByUser.change) / 10) << " Coins before: " << vect_unique.at(1)->getName() << " " << *coins.at(1) << endl;
        changeDefinedByUser.change -= vect_unique.at(1)->getValue();
        *coins.at(1) += 1;
        cout << "Change after: " << (round(10 * changeDefinedByUser.change) / 10) << " Coins after: " << vect_unique.at(1)->getName() << " " << *coins.at(1) << endl;
    }
    while (((round(10 * changeDefinedByUser.change) / 10) >= (round(10 * vect_unique.at(2)->getValue()) / 10)) && (vect_unique.at(2)->getStock() > 0)) //give 1 PLN
    {
        cout << "Change before: " << (round(10 * changeDefinedByUser.change) / 10) << " Coins before: " << vect_unique.at(2)->getName() << " " << *coins.at(2) << endl;
        changeDefinedByUser.change -= vect_unique.at(2)->getValue();
        *coins.at(2) += 1;
        cout << "Change after: " << (round(10 * changeDefinedByUser.change) / 10) << " Coins after: " << vect_unique.at(2)->getName() << " " << *coins.at(2) << endl;
    }
    while (((round(10 * changeDefinedByUser.change) / 10) >= (round(10 * vect_unique.at(3)->getValue()) / 10)) && (vect_unique.at(3)->getStock() > 0))//give 50 gr
    {
        cout << "Change before: " << (round(10 * changeDefinedByUser.change) / 10) << " Coins before: " << vect_unique.at(3)->getName() << " " << *coins.at(3) << endl;
        changeDefinedByUser.change -= vect_unique.at(3)->getValue();
        *coins.at(3) += 1;
        cout << "Change after: " << (round(10 * changeDefinedByUser.change) / 10) << " Coins after: " << vect_unique.at(3)->getName() << " " << *coins.at(3) << endl;
    }
    while (((round(10 * changeDefinedByUser.change) / 10) >= (round(10 * vect_unique.at(4)->getValue()) / 10)) && (vect_unique.at(4)->getStock() > 0)) //give 20gr
    {
        cout << "Change before: " << (round(10 * changeDefinedByUser.change) / 10) << " Coins before: " << vect_unique.at(4)->getName() << " " << *coins.at(4) << endl;
        changeDefinedByUser.change -= vect_unique.at(4)->getValue();
        *coins.at(4) += 1;
        cout << "Change after: " << (round(10 * changeDefinedByUser.change) / 10) << " Coins after: " << vect_unique.at(4)->getName() << " " << *coins.at(4) << endl;
    }
    while (((round(10 * changeDefinedByUser.change) / 10) > 0) && (vect_unique.at(5)->getStock() > 0)) //give 10 gr
    {
        cout << "Change before: " << (round(10 * changeDefinedByUser.change) / 10) << " Coins before: " << vect_unique.at(5)->getName() << *coins.at(5) << endl;
        changeDefinedByUser.change -= vect_unique.at(5)->getValue();
        *coins.at(5) += 1;
        cout << "Change after: " << abs(round(10 * changeDefinedByUser.change) / 10) << " Coins after: " << vect_unique.at(5)->getName() << *coins.at(5) << endl;
    }

    if ((round(10 * changeDefinedByUser.change) / 10) != 0)
    {
        cout << "Unfortunately we are not able to give you the change at the moment." << endl
             << "The money will be withdrawn now..." << endl;
        for (int i = 0; i < vect_unique.size(); i++)
        {
            cout << "AMOUNT OF: " << vect_unique.at(i)->getName() << " before withdrawal: " << vect_unique.at(i)->getStock() << endl;
            vect_unique.at(i)->operator+(*coins.at(i));
            cout << "AMOUNT OF: " << vect_unique.at(i)->getName() << " after withdrawal: " << vect_unique.at(i)->getStock() << endl;
        }
    }

    cout << endl << "The transaction is successfully completed." << endl;
}

void Money::sneakyFunction(vector<unique_ptr<Money>>& vect_m_unique)
{
    int input;
    cout << "You entered a special code, that enables you to change the money pool." << endl;
    for (const auto& money : vect_m_unique)
    {
        cout << "Amount of " << money->getName() << " before: " << money->getStock() << endl;
        cout << "Enter new amount of " << money->getName() << ": ";
        cin >> input;
        money->operator=(input);
        cout << "Amount of " << money->getName() << " after: " << money->getStock() << endl;
    }
}

void Money::displayUniqueMoney(vector <unique_ptr<Money>>& v_unique)
{
    for (const auto& money : v_unique)
    {
        cout << money->getId() << ") " << money->getName() << endl
             << "Amount: " << money->getStock() << endl
             << "Price: " << money->getValue() << " PLN" << endl << endl;
    }
}

bool Money::isPoolOkUnique(vector<unique_ptr<Money>>& vect_m)
{
    double sumInThePool = 0;
    for (const auto& money : vect_m)
    {
        sumInThePool += money->getValue() * money->getStock();
    }
    cout << "Sum: " << sumInThePool << endl;

    if (sumInThePool < MIN_REQUIRED_POOL)
    {
        cout << "This vending machine is out of order." << endl
             << "Error: The initial condition of minimal required pool value is not satisfied." << endl;
        return false;
    }
    else if (sumInThePool >= MIN_REQUIRED_POOL)
    {
        return true;
    }
    return false;
}