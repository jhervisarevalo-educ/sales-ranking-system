# Sales Ranking System

A console-based C++ program for a retail store, built for the **Algorithms and Complexities** course. It demonstrates several classic **searching and sorting algorithms** applied to a real-world marketing task: ranking products by how many units they have sold. You can choose which algorithm to run and see how long it takes in milliseconds, making the difference between `O(n^2)` and `O(n log n)` easy to observe.

---

## 1. Project Overview

Retail stores need to know which products are selling well and which are not, so they can make marketing and stocking decisions. This program lets a user manage a list of products, record sales, search for products, and rank them by total units sold.

The program is menu-driven and runs entirely in the console (no GUI). It uses object-oriented programming and only the C++ standard library.

---

## 2. Objectives

- Practice object-oriented programming in C++ (a `Product` class stored in a `std::vector`).
- Implement and explain multiple **search algorithms** (Linear and Binary Search).
- Implement and explain multiple **sorting algorithms** (Bubble, Selection, Insertion, Merge, Quick).
- **Measure and compare** algorithm run times in milliseconds on the same data.
- Analyze the **time complexity** (Big-O) of every major operation.
- Write clean, modular, well-commented, beginner-friendly code with input validation.

---

## 3. Features (Menu Options)

1. **Add a Product** - enter ID, name, category, and price.
2. **Display All Products** - show every product in a table.
3. **Record a Sale** - increase the units sold of a product.
4. **Search Product by ID or Name** - for ID search you choose Linear or Binary Search.
5. **Sort Products by Units Sold** - choose one of five algorithms; shows the time taken in ms.
6. **Display Top 5 Best-Selling Products** (ranked internally with Merge Sort).
7. **Display Lowest-Selling Products** (ranked internally with Merge Sort).
8. **Save Products to File** - type a filename to save the current list (Save As). Press Enter with no filename to save to the default `products.csv`. Supports keeping several data files.
9. **Generate Random Products** - replace the list with N random products for benchmarking.
10. **Compare All Sorting Algorithms** - run every sort on the same data and print a timing table.
11. **Exit** - auto-saves the current data to `products.csv`.

---

## 4. Data Model

Each product is an object of the `Product` class:

| Field       | Type          | Meaning                        |
|-------------|---------------|--------------------------------|
| `id`        | `int`         | Unique product ID              |
| `name`      | `std::string` | Product name                   |
| `category`  | `std::string` | Product category               |
| `price`     | `double`      | Selling price                  |
| `unitsSold` | `int`         | Total units sold (for ranking) |

All products are stored in a `std::vector<Product>`, which grows automatically as products are added.

The code is split into a small set of header-only libraries so the algorithms are reusable and `main.cpp` stays readable:

```
Dynamic-Price-Engine/
  main.cpp                          # menu, I/O, timing, wiring
  product.hpp                       # the shared Product class
  sort-algo/
    sort_algorithms.hpp             # Bubble, Selection, Insertion, Merge, Quick + registry
  search-algo/
    search_algorithms.hpp           # Linear + Binary search
  README.md
```

Because the libraries are header-only, the build is still a single command (see section 7) - no separate compilation step is needed.

---

## 4a. File Storage (CSV Input/Output)

Instead of relying only on hard-coded data, the program reads and writes product data using **CSV** (comma-separated values) files.

**Format** - one product per line, fields in this order:

```
id,name,category,price,unitsSold
```

**Example `products.csv`:**

```
101,Wireless Mouse,Electronics,19.99,120
102,Coffee Mug,Kitchen,8.5,45
103,Notebook,Stationery,3.25,200
104,Bluetooth Speaker,Electronics,45,75
105,Water Bottle,Sports,12.75,30
```

**How loading/saving works:**

- **On startup**, the program automatically loads the default file `products.csv`. If it exists, that data is used; if not, built-in sample data is loaded so the program is never empty.
- **On exit** (option 9), the current data is auto-saved back to `products.csv`.
- **Save Products to File** (option 8) lets you type any filename, so you can keep **multiple data files** (e.g. `products_2024.csv`, `products_2025.csv`). If you press Enter without typing a name, it saves to the default `products.csv`.

**Limitation (beginner-friendly simplification):** because a comma separates the fields, product names and categories should **not contain commas**. Any malformed line is skipped with a warning instead of crashing the program.

---

## 5. Algorithms Used

### Search algorithms (`search-algo/search_algorithms.hpp`)

**Linear Search** - checks each product one by one until a match is found.
- Works on data in **any order**; needs no preparation.
- **Time complexity:** `O(n)`.
- Used for: partial name search, Record a Sale, and as one option for ID search.

**Binary Search** - repeatedly halves the search range.
- **Requires** the data sorted by the key (ID) first; the program sorts a copy by ID before searching.
- **Time complexity:** `O(log n)` for the search itself (plus `O(n log n)` once to sort the copy).
- A great teaching contrast: much faster than Linear Search, but only usable on sorted data.

### Sort algorithms (`sort-algo/sort_algorithms.hpp`)

All sorts rank products in **descending** order of units sold (best-sellers first).

| Algorithm      | Best        | Average      | Worst        | Stable? | Notes                                  |
|----------------|-------------|--------------|--------------|---------|----------------------------------------|
| Bubble Sort    | `O(n)`      | `O(n^2)`     | `O(n^2)`     | Yes     | Simple; early-exit when already sorted |
| Selection Sort | `O(n^2)`    | `O(n^2)`     | `O(n^2)`     | No      | Few swaps, many comparisons            |
| Insertion Sort | `O(n)`      | `O(n^2)`     | `O(n^2)`     | Yes     | Fast on nearly-sorted data             |
| Merge Sort     | `O(n log n)`| `O(n log n)` | `O(n log n)` | Yes     | Divide-and-conquer; `O(n)` extra space |
| Quick Sort     | `O(n log n)`| `O(n log n)` | `O(n^2)`     | No      | Fast in practice; worst case on bad pivots |

**Why offer several?** The whole point of the course is comparing complexity classes. Menu option 10 ("Compare All Sorting Algorithms") runs each of these on the *same* data and prints the measured time, so the `O(n^2)` vs `O(n log n)` gap is visible (see section 8).

**Default for the Top 5 / Lowest displays:** Merge Sort, because it is stable and guarantees `O(n log n)` in every case.

---

## 6. Time Complexity Analysis (Big-O)

Let `n` be the number of products.

| Operation                     | Time Complexity   | Notes                                           |
|-------------------------------|-------------------|-------------------------------------------------|
| Add a Product                 | `O(n)`            | Scans to reject duplicate IDs; `push_back` is `O(1)` amortized |
| Display All Products          | `O(n)`            | Visits each product once                        |
| Record a Sale                 | `O(n)`            | Linear Search to find the product first         |
| Search by ID (Linear)         | `O(n)`            | Linear Search                                   |
| Search by ID (Binary)         | `O(log n)` search | Plus `O(n log n)` once to sort a copy by ID     |
| Search by Name                | `O(n)`            | Linear Search over all products                 |
| Sort (Bubble/Selection/Insertion) | `O(n^2)`      | Quadratic sorts (chosen from option 5)          |
| Sort (Merge/Quick)            | `O(n log n)`      | Merge always; Quick average (worst `O(n^2)`)    |
| Top 5 Best-Selling            | `O(n log n)`      | Merge-sorts a copy, then reads the top 5        |
| Lowest-Selling                | `O(n log n)`      | Merge-sorts a copy, then reads the bottom 5     |
| Generate Random Products      | `O(n)`            | Builds N products                               |
| Compare All Sorting Algorithms| `O(n^2)`          | Dominated by the quadratic sorts it runs        |
| Save to File (option 8)       | `O(n)`            | Writes each product as one CSV line             |
| Load from File (on startup)   | `O(n)`            | Reads and parses each CSV line once             |

---

## 7. How to Build and Run

Requires a C++ compiler that supports C++17 (for example, `g++`).

```bash
# Compile (the sort-algo/ and search-algo/ headers are included automatically)
g++ -std=c++17 -Wall -Wextra -o sales_ranking main.cpp

# Run
./sales_ranking
```

Only `main.cpp` is compiled - the algorithm libraries are header-only and are pulled in by `#include`, so there is no separate build step.

On the first run there is no `products.csv`, so the program pre-loads a few sample products. When you exit, your data is saved to `products.csv` and will be auto-loaded next time.

---

## 8. Sample Input and Output

Below is a short sample session (using the pre-loaded sample products).

**Displaying all products (menu option 2):**

```
--- All Products ---
ID    Name                  Category             Price  Units Sold
------------------------------------------------------------------
101   Wireless Mouse        Electronics          19.99         120
102   Coffee Mug            Kitchen               8.50          45
103   Notebook              Stationery            3.25         200
104   Bluetooth Speaker     Electronics          45.00          75
105   Water Bottle          Sports               12.75          30

Total products: 5
```

**Top 5 Best-Selling (menu option 6) - ranked with Merge Sort:**

```
--- Top 5 Best-Selling Products (ranked via Merge Sort) ---
ID    Name                  Category             Price  Units Sold
------------------------------------------------------------------
103   Notebook              Stationery            3.25         200
101   Wireless Mouse        Electronics          19.99         120
104   Bluetooth Speaker     Electronics          45.00          75
102   Coffee Mug            Kitchen               8.50          45
105   Water Bottle          Sports               12.75          30
```

**Recording a sale (menu option 3):**

```
--- Record a Sale ---
Enter the Product ID of the item sold: 103
Enter quantity sold: 50
  Recorded 50 sale(s) for "Notebook". New total: 250 units.
```

**Searching by name (menu option 4, then 2):**

```
--- Search Product ---
Search by:
  1. Product ID
  2. Product Name
Enter choice (1-2): 2
Enter Product Name (or part of it): mouse
ID    Name                  Category             Price  Units Sold
------------------------------------------------------------------
101   Wireless Mouse        Electronics          19.99         120
```

**Saving to a named file (menu option 8):**

```
--- Save Products to File ---
Enter filename to save to (press Enter for "products.csv"): backup_2026.csv
  Saved 5 product(s) to "backup_2026.csv".
```

**Choosing a sorting algorithm with timing (menu option 5):**

```
--- Sort Products by Units Sold (Highest to Lowest) ---
Choose a sorting algorithm:
  1. Bubble Sort  [O(n^2)]
  2. Selection Sort  [O(n^2)]
  3. Insertion Sort  [O(n^2)]
  4. Merge Sort  [O(n log n)]
  5. Quick Sort  [O(n log n)]
Enter choice (1-5): 5

  Sorted using Quick Sort (O(n log n)) in 0.0039 ms.
```

**Comparing all sorts on 5,000 random products (options 9 then 10):**

```
--- Compare All Sorting Algorithms ---
Sorting 5000 product(s) with each algorithm...

Algorithm         Complexity           Time (ms)
------------------------------------------------
Bubble Sort       O(n^2)               1590.3016
Selection Sort    O(n^2)                 49.9366
Insertion Sort    O(n^2)                414.5508
Merge Sort        O(n log n)              9.4024
Quick Sort        O(n log n)              9.4693

  Tip: notice how O(n log n) sorts scale far better than O(n^2).
```

(Exact times vary by machine, but the `O(n log n)` sorts are consistently much faster.)

**Auto-load on the next run and auto-save on exit (option 11):**

```
Welcome to the Sales Ranking System!
Loaded 5 product(s) from "products.csv".
...
Enter your choice (1-11): 11

Data saved to "products.csv".
Thank you for using the Sales Ranking System. Goodbye!
```

---

## 9. Possible Future Improvements

- **Quoted CSV fields** so names and categories can safely contain commas.
- **Sort by other fields** (price, category, name), ascending or descending.
- **Sales reports** such as total revenue per category (`price * unitsSold`).
- **Edit or delete products** from the list.
- **Undo a sale** in case of mistakes.
- **More algorithms** (e.g. Heap Sort, Shell Sort) added to the sort registry.

---

## 10. File Structure

| File                              | Purpose                                                     |
|-----------------------------------|-------------------------------------------------------------|
| `main.cpp`                        | Menu, input validation, file I/O, timing, and wiring        |
| `product.hpp`                     | The shared `Product` class                                  |
| `sort-algo/sort_algorithms.hpp`   | Bubble, Selection, Insertion, Merge, Quick sorts + registry |
| `search-algo/search_algorithms.hpp` | Linear and Binary search                                   |
| `README.md`                       | This documentation                                          |
| `products.csv`                    | Default data file (auto-created on first exit)              |
