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

#include "../include/machine.h"

using namespace std;

Machine::Machine(double cartDefinedByUser, double changeDefinedByUser)
{
    this->cart = cartDefinedByUser;
    this->change = changeDefinedByUser;
}
Machine::Machine(int idDefinedByUser = 1, string nameDefinedByUser = "default", int stockDefinedByUser = 0)
{
    this->id = idDefinedByUser;
    this->name = nameDefinedByUser;
    this->stock = stockDefinedByUser;
}

double Machine::getCart()
{
    return this->cart;
}
double Machine::getChange()
{
    return this->change;
}
int Machine::getId()
{
    return this->id;
}
string Machine::getName()
{
    return this->name;
}
int Machine::getStock()
{
    return this->stock;
}
void Machine::setId(int idDefinedByUser)
{
    this->id = idDefinedByUser;
}
void Machine::setName(int nameDefinedByUser)
{
    this->name = nameDefinedByUser;
}
void Machine::setStock(int stockDefinedByUser)
{
    this->stock = stockDefinedByUser;
}
void Machine::display()
{
    cout << this->id << ") " << this->name << endl
         << "Amount: " << this->stock << endl;
}
void Machine::loadFromFile(string filename_txt)
{
    fstream file;
    file.open(filename_txt, ios::in);

    if (file.good() == false)
    {
        cout << "Unable to load the file. Try again later." << endl;
    }
    else
    {
        int indexLineNr = (this->id - 1) * 4 + 1;
        int currentLineNr = 1;
        string lineText; //text gathered from one line in the text file
        while (getline(file, lineText)) //read the file till there is anyhting to read
        {
            if (currentLineNr == indexLineNr)
            {
                this->name = lineText.substr(3);
            }
            if (currentLineNr == indexLineNr + 1)
            {
                this->stock = stoi(lineText.substr(8));
            }
            currentLineNr++;
        }

        file.close();
    }
}
void Machine::saveToFile(string filename_txt)
{
    fstream file;
    file.open(filename_txt, ios::out | ios::app);
    if (file.good() == false)
    {
        cout << "Unable to load the file. Try again later." << endl;
    }
    else
    {
        file << this->id << ") " << this->name << endl
             << "Amount: " << this->stock << endl;
    }
    file.close();
}