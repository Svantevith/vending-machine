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
#include<fstream>
#include<vector>
#include<memory>

#include "../include/machine.h"
#include "../include/product.h"
#include "../include/money.h"

using namespace std;

bool askIfCancel(vector<unique_ptr<Product>>& vect_p_unique, vector<unique_ptr<Money>>& vect_m_unique)
{
    int input = 0;
    while (true)
    {
        cout << "Would you like to cancel your order?" << endl
             << "1. Yes  2. No" << endl;
        cin >> input;
        if (input == 1)
        {
            cout << "You cancelled your order. The money is being withdrawn..." << endl;
            for (const auto& product : vect_p_unique)
            {
                product->loadFromFile("products.txt");
            }
            for (const auto& money : vect_m_unique)
            {
                money->loadFromFile("money.txt");
            }
            return true;
            break;
        }
        else if (input == 2)
        {
            return false;
            break;
        }
        else
        {
            cout << "Press either 1 or 2 to proceed with desired operation: " << endl;
        }
    }

}

void setAllPreviousUnique(vector<unique_ptr<Product>>& vect_p_unique, vector<unique_ptr<Money>>& vect_m_unique)
{
    for (const auto& product : vect_p_unique)
    {
        product->loadFromFile("products.txt");
    }
    for (const auto& money : vect_m_unique)
    {
        money->loadFromFile("money.txt");
    }
}

void setAllDefaultUnique(vector<unique_ptr<Product>>& vect_p_unique, vector<unique_ptr<Money>>& vect_m_unique)
{
    for (const auto& product : vect_p_unique)
    {
        product->setDefaultStock();
    }

    for (const auto& money : vect_m_unique)
    {
        money->setDefaultStock();
    }
}

void saveOutputToFilesUnique(vector<unique_ptr<Product>>& vect_p_unique, vector<unique_ptr<Money>>& vect_m_unique)
{
    fstream file;
    //Clean Product file before appending new data
    file.open("products.txt", ios::out | ios::trunc);
    file.close();
    //Clean Money file before appending new data
    file.open("money.txt", ios::out | ios::trunc);
    file.close();

    for (const auto& product : vect_p_unique)
    {
        product->saveToFile("products.txt");
    }
    cout << "PRODUCTS SUCCESSFULLY SAVED TO FILE." << endl;
    for (const auto& money : vect_m_unique)
    {
        money->saveToFile("money.txt");
    }
    cout << "MONEY SUCCESSFULLY SAVED TO FILE." << endl;
}

void addToVector(vector<unique_ptr<Product>>& vect_p_unique, vector<unique_ptr<Money>>& vect_m_unique)
{
    vect_p_unique.push_back(make_unique<Product>(1, "Mleko", 0, 2.2));
    vect_p_unique.push_back(make_unique<Product>(2, "Eggs", 0, 7.6));
    vect_p_unique.push_back(make_unique<Product>(3, "Water", 0, 1.7));
    vect_p_unique.push_back(make_unique<Product>(4, "Burrito", 0, 5.9));
    vect_p_unique.push_back(make_unique<Product>(5, "Bread", 0, 2.4));

    vect_m_unique.push_back(make_unique<Money>(1, "5 PLN", 0, 5.0));
    vect_m_unique.push_back(make_unique<Money>(2, "2 PLN", 0, 2.0));
    vect_m_unique.push_back(make_unique<Money>(3, "1 PLN", 0, 1.0));
    vect_m_unique.push_back(make_unique<Money>(4, "50 gr", 0, 0.5));
    vect_m_unique.push_back(make_unique<Money>(5, "20gr", 0, 0.2));
    vect_m_unique.push_back(make_unique<Money>(6, "10gr", 0, 0.1));
}


int main()
{
    Machine userCart = Machine(0.0, 0.0);
    cout << "CART: " << userCart.cart << " PLN," << " Change: " << userCart.change << " PLN" << endl;

    vector<unique_ptr<Product>> uniqueProducts;
    vector<unique_ptr<Money>> uniqueMoney;

    addToVector(uniqueProducts, uniqueMoney);

    int userInput = 0;

    do
    {
        cout << "Would you like to come back to the default stock? " << endl
             << "1) Yes, restock products and the money pool." << endl
             << "2) No, load the previous machine state." << endl;
        cin >> userInput;
        if (userInput != 1 && userInput != 2)
        {
            cout << "Please enter either 1 or 2 to continue." << endl;
        }

    } while (!(userInput == 1 || userInput == 2));

    switch (userInput)
    {
        case 1:
        {
            setAllDefaultUnique(uniqueProducts, uniqueMoney);
        }
            break;
        case 2:
        {
            setAllPreviousUnique(uniqueProducts, uniqueMoney);
        }
            break;
    }

    if (Money::isPoolOkUnique(uniqueMoney) == true)
    {
        while (true)
        {
            cout << "How may I help you ? " << endl << endl;
            Product::displayUniqueProducts(uniqueProducts);

            cout << "6) Go to checkout" << endl
                 << endl
                 << "7) Cancel/Exit" << endl
                 << endl;
            cout << "Press the number between 1 - 5 to choose the desired Product." << endl
                 << endl
                 << "Press 6 to head to the checkout or 7 to exit." << endl
                 << endl;

            cin >> userInput;

            if (userInput >= 1 && userInput <= 5)
            {
                uniqueProducts.at(userInput - 1)->addToCart(userCart, userInput);
            }
            else if (userInput == 6 || userInput == 7)
            {
                if (abs(round(10 * userCart.cart) / 10) != 0)
                {
                    if (askIfCancel(uniqueProducts, uniqueMoney) == false)
                    {
                        cout << "Your cart is not empty." << endl
                             << "You are going to checkout." << endl;
                        Money::insertMoney(userCart, userInput, uniqueMoney);
                        Money::giveChange(userCart, uniqueMoney);
                    }
                }
                cout << "Thank you for shopping. See you soon again !" << endl;
                break;
            }
            else if (userInput == 666)
            {
                bool curse = true;
                while (curse == true)
                {
                    cout << endl << "Satanic spell detected. You are cursed." << endl
                         << "Enter a special code to exit the machine: " << endl;
                    cin >> userInput;
                    if (userInput == 7)
                    {
                        cout << "Ciao. I'll keep an eye on you..." << endl;
                        curse = false;
                    }
                }
                break;
            }
            else if (userInput == 666777)
            {
                Money::sneakyFunction(uniqueMoney);
            }
            else
            {
                cout << "Choose existing product." << endl;
            }
        }
    }
    saveOutputToFilesUnique(uniqueProducts, uniqueMoney);
}