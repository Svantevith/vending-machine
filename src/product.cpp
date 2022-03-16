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

#include "../include/product.h"

using namespace std;

Product::Product(int idDefinedByUser, string nameDefinedByUser, int stockDefinedByUser, double priceDefinedByUser)
        :Machine(idDefinedByUser, nameDefinedByUser, stockDefinedByUser)
{
    this->price = priceDefinedByUser;
}

double Product::getPrice()
{
    return this->price;
}

double Product::getStock()
{
    return this->stock;
}


void Product::display()
{
    Machine::display();
    cout << "Price: " << this->price << " PLN" << endl
         << endl;
}

int Product::setDefaultStock()
{
    this->stock = MAX_PRODUCTS_STOCK;
    return this->stock;
}

void Product::loadFromFile(string filename_txt)
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
            this->price = stod(lineText.substr(7, 5));
        }
        currentLineNr++;
    }
    file.close();
}

void Product::saveToFile(string filename_txt)
{
    this->filename = filename_txt;
    Machine::saveToFile(this->filename);

    fstream file;
    file.open(filename_txt, ios::out | ios::app);
    file << "Price: " << this->price << endl << endl;
    file.close();
}

void Product::addToCart(Machine& cartDefinedByUser, int& input)
{
    //MAIN IF
    if (cartDefinedByUser.cart >= MAX_CART_LIMIT)
    {
        cout << "Your cart cannot any more items. You have reached the cart capacity limit of: " << MAX_CART_LIMIT << endl;
        cout << "Your cart value: " << cartDefinedByUser.cart << endl;
    }
        //END OF MAIN IF
        //MAIN ELSE IF
    else if (cartDefinedByUser.cart < MAX_CART_LIMIT)
    {
        cout << "How many of " << this->name << " would you like to purchase?" << endl;
        cin >> input;
        cout << endl << "Cart before: " << cartDefinedByUser.cart << " PLN" << endl
             << "Amount of " << this->name << " before: " << this->stock << endl;

        if (this->stock >= input && this->stock > 0)
        {
            cartDefinedByUser.cart += this->price * input;
            //this->stock -= input;
            //SECOND IF
            if (cartDefinedByUser.cart > MAX_CART_LIMIT)
            {
                cout << "Your cart cannot any more items. You have reached the cart capacity limit of: " << MAX_CART_LIMIT << endl;
                cout << "Your cart value: " << cartDefinedByUser.cart << endl;
                cout << "Please choose smaller amount, different product or head directly to checkout." << endl;
                cartDefinedByUser.cart -= this->price * input;
            }
            else
            {
                this->stock -= input;
            }
            //END OF SECOND IF
        }
        else
        {
            cout << "We haven't got required amount of " << this->name << " in stock." << endl
                 << "Please choose different product or amount." << endl;
        }
        cout << endl << "Cart after purchase: " << cartDefinedByUser.cart << " PLN" << endl
             << "Remaining amount of " << this->name << ": " << this->stock << endl << endl;
    }
    //END OF MAIN ELSE IF
}

void Product::displayUniqueProducts(vector <unique_ptr<Product>>& v_unique)
{
    for (const auto& product : v_unique)
    {
        cout << product->getId() << ") " << product->getName() << endl
             << "Amount: " << product->getStock() << endl
             << "Price: " << product->getPrice() << " PLN" << endl << endl;
    }
}