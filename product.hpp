// ============================================================================
//  product.hpp
//  ---------------------------------------------------------------------------
//  The shared data model for the Sales Ranking System.
//
//  The Product class lives in its own header so that the main program AND the
//  algorithm libraries (sort-algo/, search-algo/) can all use the same type.
//
//  A Product is one item sold by the store. Products are stored in a
//  std::vector<Product>, which grows automatically as products are added.
// ============================================================================
#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>

class Product
{
  public:
    int id;               // Unique product ID
    std::string name;     // Product name (e.g. "Wireless Mouse")
    std::string category; // Product category (e.g. "Electronics")
    double price;         // Selling price
    int unitsSold;        // Total units sold so far (used for ranking)

    // Constructor: create a product with a starting sales count of 0.
    Product(int id, const std::string &name, const std::string &category,
            double price)
        : id(id), name(name), category(category), price(price), unitsSold(0)
    {
    }
};

#endif // PRODUCT_HPP
