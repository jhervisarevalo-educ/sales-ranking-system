// ============================================================================
//  search-algo/search_algorithms.hpp
//  ---------------------------------------------------------------------------
//  A small library of search algorithms for the Sales Ranking System.
//
//  Both functions search by Product ID and return the INDEX of the match in the
//  vector they are given, or -1 if not found. They are in the `searchalgo`
//  namespace and marked `inline` (header-only library).
//
//  * Linear Search  - O(n),     works on data in ANY order.
//  * Binary Search  - O(log n), REQUIRES the vector to be sorted by id ascending.
//  A helper `sortByIdAscending` is provided so callers can prepare a sorted copy.
// ============================================================================
#ifndef SEARCH_ALGORITHMS_HPP
#define SEARCH_ALGORITHMS_HPP

#include <vector>
#include <algorithm>
#include "../product.hpp"

namespace searchalgo {

// ---------------------------------------------------------------------------
//  Linear Search
//  Checks each product one by one until the ID is found.
//  Time: O(n). Works no matter how the data is ordered.
// ---------------------------------------------------------------------------
inline int linearSearchById(const std::vector<Product>& products, int id) {
    for (std::size_t i = 0; i < products.size(); ++i) {
        if (products[i].id == id) {
            return static_cast<int>(i);
        }
    }
    return -1; // not found
}

// ---------------------------------------------------------------------------
//  Helper: sort a copy of the products by ID in ascending order.
//  Binary Search only works on data sorted by the key being searched.
//  Time: O(n log n) (uses the standard library's introsort).
// ---------------------------------------------------------------------------
inline std::vector<Product> sortByIdAscending(const std::vector<Product>& products) {
    std::vector<Product> sorted = products;
    std::sort(sorted.begin(), sorted.end(),
              [](const Product& a, const Product& b) { return a.id < b.id; });
    return sorted;
}

// ---------------------------------------------------------------------------
//  Binary Search
//  Repeatedly halves the search range. REQUIRES `products` sorted by id ascending.
//  Time: O(log n). Returns the index within the given (sorted) vector, or -1.
// ---------------------------------------------------------------------------
inline int binarySearchById(const std::vector<Product>& products, int id) {
    int low  = 0;
    int high = static_cast<int>(products.size()) - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (products[mid].id == id) {
            return mid;                 // found it
        } else if (products[mid].id < id) {
            low = mid + 1;              // search the upper half
        } else {
            high = mid - 1;             // search the lower half
        }
    }
    return -1; // not found
}

} // namespace searchalgo

#endif // SEARCH_ALGORITHMS_HPP
