# meal
Simple Meal Ordering System in C

## Project Details

- **Description:** The program acts as an ordering system for a restaurant, where customers can input up to three orders consisting of a main dish, a side dish, and a drink. The program calculates the total price of the orders and applies discounts if certain conditions are met.
- **Programming Language:** C

## Functionality

### Main Features

1. **Ordering:** Customers can input their orders, specifying a main dish, a side dish, and a drink for each order.
2. **Cancellation:** Customers have the option to cancel their entire order, cancel a specific order, or modify their order before finalizing.
3. **Random Meal Set:** The program generates a random meal set of the day, which qualifies for a discount on the total price.

### Discount Logic

- If the customer's order matches the random meal set of the day, a 15% discount is applied to the total price.

### Manager Access

- Managers have access to change the random meal set of the day by entering a PIN code.

## Function Overview

The program consists of several functions to facilitate different aspects of the ordering process:

1. **`generateRandomMealSet(int *nLuckyMeal)`**: Generates a random meal set of the day.
2. **`printMenu(int nMealSet)`**: Prints the menu options including mains, sides, and drinks, along with their respective prices and the meal set of the day.
3. **`mainMenu(int *nLuckyMeal, int *isRunning)`**: Displays the main menu options and manages program flow.
4. **`promptOrderCount()`**: Prompts the user for the quantity of orders to be placed.
5. **`getOrder()`**: Takes input for a single order from the user.
6. **`askCancel(int *repeat, int *cancelAll, int *cancelSome)`**: Manages the cancellation sequence based on user input.
7. **`getSubtotal(int nOrder, int nLuckyMeal, int orderNumber)`**: Calculates the subtotal for a single order, considering discounts.
8. **`getTotal(int *nOrderArray, int nDiscounted, int nOrderCount)`**: Calculates the total price for all orders, considering discounts.

## Usage

1. Compile the program using a C compiler.
2. Run the compiled executable.
3. Follow the on-screen prompts to input orders, cancel orders, or exit the program.
4. Managers can access additional options by entering the manager PIN when prompted.

## Acknowledgements

- Arrays: [W3Schools - C Arrays](https://www.w3schools.com/c/c_arrays.php), [Scaler - Pass Array to Function in C](https://www.scaler.com/topics/c/pass-array-to-function-in-c/)
- Random Number Generation: [GeeksforGeeks - Generating Random Number Range in C](https://www.geeksforgeeks.org/generating-random-number-range-c/)
- Harvard CS50 Week 3 & 4: [CS50 Week 3 & 4 - Arrays and Pointers](https://www.youtube.com/watch?v=nvO1sq_b_zI)

## Note

This README provides an overview of the ordering system program. For detailed information about the code structure, function parameters, and algorithms, please refer to the source code comments.
