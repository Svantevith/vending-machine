//
// Created by szczy on 16.06.2020.
//

#ifndef PROJECT1_PRODUCT_H
#define PROJECT1_PRODUCT_H

#include<string>
#include<vector>
#include<memory>

#include"machine.h"

using namespace std;

class Product : public Machine
{
    string filename = "products.txt";
    double price;
public:
    Product(int idDefinedByUser, string nameDefinedByUser, int stockDefinedByUser, double priceDefinedByUser);

    double getPrice();

    double getStock();

    void display();

    int setDefaultStock();

    void loadFromFile(string filename_txt);

    void saveToFile(string filename_txt);

    void addToCart(Machine& cartDefinedByUser, int& input);

    static void displayUniqueProducts(vector <unique_ptr<Product>>& v_unique);

};

#endif //PROJECT1_PRODUCT_H
