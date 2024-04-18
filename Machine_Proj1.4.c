/********************************************************************
*******
This is to certify that this project is my own work, based on my personal efforts in
studying and applying the concepts learned. I have constructed the functions and
their respective algorithms and corresponding code by myself. The program was
run, tested, and debugged by my own efforts. I further certify that I have not copied
in part or whole or otherwise plagiarized the work of other students and/or persons.
Joel Ethan N. Batac, DLSU ID#
12205532
********************************************************************
*******/



/*
Description: This program is an ordering system that takes in up 3 orders from a customer and outputs the total price.
Programmed by: Joel Ethan Batac S26B
Last modified: 12/05/2022 
Version: 1.4.1 (VERY FINAL VERSION)
Acknowledgements: 
Arrays: 
https://www.w3schools.com/c/c_arrays.php, 
https://www.scaler.com/topics/c/pass-array-to-function-in-c/ 
Harvard CS50 Week 3 & 4

rand: 
https://www.geeksforgeeks.org/generating-random-number-range-c/
*/

#include<stdio.h>
#include<math.h> //pow()
#include<stdlib.h> //rand() and srand()
#include<time.h> //time()

//main prices
#define CHICKEN_PRICE 90.0
#define PORK_PRICE 105.0
#define FISH_PRICE 120.0
#define BEEF_PRICE 135.0

//side prices
#define STEAMED_RICE_PRICE 20.0
#define SHREDDED_CORN_PRICE 35.0
#define MASHED_POTATO_PRICE 50.0
#define STEAM_VEGETABLES_PRICE 65.0

//drink prices
#define MINERAL_WATER_PRICE 25.0
#define ICED_TEA_PRICE 35.0
#define SODA_PRICE 45.0
#define FRUIT_JUICE_PRICE 55.0

//function prototypes.
void takeItem(int nType, int nItemNumber);
void generateRandomMealSet(int *nLuckyMeal);
void printMenu();
void mainMenu(int *nLuckyMeal, int *isRunning);
int promptOrderCount();
void getType(int nType);
int getOrder();
void askCancel(int *bRepeat, int *bCancelAll, int *bCancelSome);
float getPrice(int nType, int nItemNumber);
float getSubtotal(int nOrder, int nLuckyMeal, int orderNumber);
float getTotal(int *nOrderArray, int nDiscounted, int nOrderCount);

//main function
int main()
{    
    int nOrder[3]; //array that will store each order. An order will be stored as a 3-digit integer with the hundreds digit as main, tens as side, and ones as drink.
    int nLuckyMeal, nOrderCount, i;
    int isRepeat = 0, isCancelAll = 0, isCancelThisOnwards = 0; //values for cancel sequence.
    int isRunning; //will terminate the program if set to 0.
    float fTotal;

    //beginning sequence.
    generateRandomMealSet(&nLuckyMeal);
    mainMenu(&nLuckyMeal, &isRunning);


    while(isRunning)
    {
        nOrderCount = promptOrderCount();

        for(i = 0; i < nOrderCount; i++)
        {   
            
            do{
                printf("Order Number: %d\n", i + 1);
                nOrder[i] = getOrder();
                askCancel(&isRepeat, &isCancelAll, &isCancelThisOnwards);
                printf("\n");
            }while(isRepeat); // will repeat if isRepeat is set to 1.

            if(isCancelAll) //if isCancelAll is set to 1, end the for loop, and don't run the amount due sequence.
            {
                nOrderCount = i;
                printf("Order Cancelled! Going back to main menu.\n\n");
            }

            if(isCancelThisOnwards) //if isCancelThisOnwards is set to 1, end the for loop and proceed to amount due.
            {
                nOrderCount = i;
                nOrder[i] = 0;
                printf("Order Cancelled! Proceeding to Amount Due!\n\n");
            }

        }


		if (!isCancelAll)
		{
	        //amount due sequence. DO NOT SHOW IF USER WANTS TO CANCELL ALL ORDERS.
            printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-     AMOUNT DUE:     -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	        fTotal = getTotal(nOrder, nLuckyMeal, nOrderCount);
	        printf("Total: \t\t\t\t\t\t P%0.2f", fTotal);
	        printf("\n\n");
		}

        mainMenu(&nLuckyMeal, &isRunning); //prompt the main menu to exit or to restart the loop.
    }

    return 0;
}

/* This function prints the string of an item based on its type (main, side, or drink) and ID (based on table)
    Precondition: The function can only take in inputs within the given range. Invalid inputs must be checked before being passed through the function.
    @param nType - 0 for main, 1 for side, 2 for drink
    @param nItemNumber - Item number based on table given. 0 for none.
*/
void takeItem (int nType, int nItemNumber)
{
    if (nItemNumber == 0) 
    {
        printf("%-16s", "None");
    }
    else
    {	
	    switch (nType)
	    {
	        case 0: //Main
	            switch (nItemNumber)
	            {
	                case 1:
	                    printf("%-16s", "Chicken");
	                    break;
	                case 2:
	                    printf("%-16s", "Pork");
	                    break;
	                case 3:
	                    printf("%-16s", "Fish");
	                    break;
	                case 4:
	                    printf("%-16s","Beef");
	                    break;
	            }
	            break;
	
	        case 1: //Side
	            switch (nItemNumber)
	            {
	                case 1:
	                    printf("%-16s", "Steamed Rice");
	                    break;
	                case 2:
	                    printf("%-16s", "Shredded Corn");
	                    break;
	                case 3:
	                    printf("%-16s", "Mashed Potato");
	                    break;
	                case 4:
	                    printf("%-16s", "Steam Vegetables");
	                    break;
	            }
	            break;
	
	        case 2: //Drink
	            switch (nItemNumber)
	            {
	                case 1:
	                    printf("%-16s", "Mineral Water");
	                    break;
	                case 2:
	                    printf("%-16s", "Iced Tea");
	                    break;
	                case 3:
	                    printf("%-16s", "Soda");
	                    break;
	                case 4:
	                    printf("%-16s", "Fruit Juice");
	                    break;
	            }
	            break;
	    }
	}
}


/* This function generates a random 3-digit integer to act as the lucky mealset, where each digit ranges from 1 to 4 only. 
It then prints this 3-digit integer with Main, Side and drink separated.
@param *nLuckyMeal - address of a variable in main that stores the meal set of the day.
@return a random 3-digit integer, wherein:
    hundreds digit - main
    tens digit - side
    ones digit - drink 

*/
void generateRandomMealSet(int *nLuckyMeal)
{

    //declaration of variables.
    int nMealSet = 0;
    int i;
    int nTemp;

    //generates seed for pseudo-random number generation 
    srand(time(NULL));
    //run this loop 3 times.
    for (i= 0; i < 3; i++)
    {  
        nTemp = rand() % (4) + 1; //gets one digit from rand within 1-4. from https://www.geeksforgeeks.org/generating-random-number-range-c/

       nMealSet = nMealSet + nTemp * (int)pow(10,i); //adds digit to nMealSet 
    }

    *nLuckyMeal = nMealSet;
}

/*This function prints the menu.
    @param nMealSet - 3-digit integer for the mealset of the day.*/
void printMenu(nMealSet)
{
    printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-     WELCOME TO CCPROG1 EATERY     -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("Item No. \t\t Item \t\t\t Price\n");
    printf("MAINS: \n");
    printf("%d \t\t %-16s \t\t %6.2f\n", 1, "Chicken", CHICKEN_PRICE);
    printf("%d \t\t %-16s \t\t %6.2f\n", 2, "Pork", PORK_PRICE);
    printf("%d \t\t %-16s \t\t %6.2f\n", 3, "Fish", FISH_PRICE);
    printf("%d \t\t %-16s \t\t %6.2f\n", 4, "Beef", BEEF_PRICE);
    printf("SIDES: \n");
    printf("%d \t\t %-16s \t\t %6.2f\n", 1, "Steamed Rice", STEAMED_RICE_PRICE);
    printf("%d \t\t %-16s \t\t %6.2f\n", 2, "Shredded Corn", SHREDDED_CORN_PRICE);
    printf("%d \t\t %-16s \t\t %6.2f\n", 3, "Mashed Potato", MASHED_POTATO_PRICE);
    printf("%d \t\t %-16s \t\t %6.2f\n", 4, "Steam Vegetables", STEAM_VEGETABLES_PRICE);
    printf("DRINKS: \n");
    printf("%d \t\t %-16s \t\t %6.2f\n", 1, "Mineral Water", MINERAL_WATER_PRICE);
    printf("%d \t\t %-16s \t\t %6.2f\n", 2, "Iced Tea", ICED_TEA_PRICE);
    printf("%d \t\t %-16s \t\t %6.2f\n", 3, "Soda", SODA_PRICE);
    printf("%d \t\t %-16s \t\t %6.2f\n", 4, "Fruit Juice", FRUIT_JUICE_PRICE);

    
    printf("The Mealset that receives a discount is: %d\n", nMealSet);
    printf("\tMain: %d ", nMealSet / 100);
    takeItem(0, nMealSet / 100);
    printf("\tSide: %d ", nMealSet / 10 - nMealSet / 100 * 10);
    takeItem(1, nMealSet / 10 - nMealSet / 100 * 10);
    printf("\tDrink: %d ", nMealSet % 10);
    takeItem(2, nMealSet % 10);
    printf("\n\n");
}

/* This function allows the user to take a new order or exit the program. 
    Precondition: The user inputs an integer. 
    @param nLuckyMeal - meal set to receive a discount
    @param *isRunning - variable in main that starts the order sequence when set to 1.*/
void mainMenu(int *nLuckyMeal, int *isRunning)
{
    int nAns;
    int nPass, nKey = 12052022; //passcode to change random mealset.
    do{
        printf("\nMain menu:\n");
        printf("\t[2] Change Random MealSet (FOR MANAGERS ONLY)\n ");
        printf("\t[1] Input an order\n");
        printf("\t[0] Exit the program\n");
        printf("Input: ");
        scanf("%d", &nAns);
        if (nAns < 0 || nAns > 3) // check if input is invalid.
            printf("Invalid input. Please use integer 2, 1, or 0.\n");
        if (nAns == 2) //change random meal set.
        {
            printf("PIN: ");
            scanf("%d", &nPass);

            if (nPass == nKey)
            {
                printf("PIN IS CORRECT... GENERATING NEW MEAL SET OF THE DAY.\n");
                generateRandomMealSet(nLuckyMeal);
                nAns = 1; //set nAns to 1 so that program will proceed to take order.
            }
            else
            {
                printf("PIN IS INCORRECT. PLEASE CONTACT A MANAGER TO CHANGE MEAL SET.\n");
                nAns = -3; //set nAns to a negative number so that loop will restart.
            } 
        }

    }while(nAns < 0 || nAns > 3);

    if (nAns == 1)
    {
        printMenu(*nLuckyMeal);
    }



    *isRunning = nAns;
}

/* This function prompts the user for the quantity of orders they will be placing. It also take cares of invalid inputs
    Precondition: The user inputs an integer.
    @return An integer within the range of 1 - 3
*/
int promptOrderCount()
{
    int nInput;
    do{
        printf("Quantity of Orders (integer from 1 - 3 only): ");
        scanf("%d", &nInput);
        if (nInput > 3 || nInput < 1)
            printf("Please input an integer within the range of 1-3\n");
    }while(nInput > 3 || nInput < 1);

    return nInput;
}


/* This function converts an integer from 0-2 to a print Type (e.g. Main, Side, Drink) statement
    Precondition: the function only works with an input integer from 0 - 2.
    @param int nType - Control variable in a for loop.
    @return Prints the type based on parameter nType. Wherein:
        0 - "Main:"
        1 - "Side: "
        2 - "Drink "

*/
void getType(int nType)
{
    switch(nType)
    {
        case 0:
            printf("Main: \t");
            break;
        case 1:
            printf("Side: \t");
            break;
        case 2:
            printf("Drink: \t");
            break;
    }
}

/* This function gets a single order from the user.
    Precondition: The user inputs an integer for each part of the order.
    @return - A 3-digit integer based on the user's inputs. Wherein each dish is represented by the:
        Hundreds digit - Main dish
        Tens digit - Side dish
        Ones digit - Drink
*/
int getOrder()
{
    int nInput, i, nOrderCode = 0;
    for(i = 0; i < 3; i++)
    {
        do{
        	getType(i); //print part of order (i.e. Main, Side, Drink)
        	scanf("%d", &nInput); //ask for input
        	if (nInput < 0 || nInput > 4)
            	printf("Please input an integer within range 1-4.\n");
        }while(nInput < 0 || nInput > 4); //loop until input given is valid

        printf("\t");
        takeItem(i, nInput); //print name of item based on ID.
        printf("\n");

        nOrderCode += nInput * (int)pow(10, 2 - i); //add nInput as another digit to nOrderCode
    }
    return nOrderCode;
}

/* This function acts as the cancel sequence. It prompts the user whether the order is correct and whether they want to cancel or modify.
    Precondition: The user inputs a char for the first prompt and an integer within 0-3 in the next prompt.
    @param *repeat - address of the boolean in main that loops starting the order sequence if set to 1.
    @param *cancelAll - address of a boolean, loops back to  starting the main menu if set to 1.
    @param *cancelSome - address of a boolean, clears the current order and ends the order sequence if set to 1.
*/ 
void askCancel(int *repeat, int *cancelAll, int *cancelSome)
{
    char cAns;
    int nAns;

    //do-while loop for taking user input
    do{
        printf("Is your order correct? (y/n): ");
        scanf(" %c", &cAns);
        if(cAns != 'Y' && cAns != 'N' && cAns != 'n' && cAns != 'y')
            printf("Please input a valid answer (Y, y, N, n). \n");
    }while(cAns != 'Y' && cAns != 'N' && cAns != 'n' && cAns != 'y');

    
    if (cAns == 'y' || cAns == 'Y')
    {
        nAns = 0;
    }
    else
    {
        //prompt user for input.
        do{
            printf("Cancel Menu : \n");
            printf("\t [1] Modify order\n");
            printf("\t [2] Cancel All orders and go back to main menu\n");
            printf("\t [3] Cancel this Order and proceed to amount due\n");
            printf("\t [0] My order is correct actually\n");
            printf("Input answer: ");
            scanf("%d", &nAns);
            if(nAns < 0 || nAns > 3)
                printf("Please input a valid input (1, 2, 3)\n");
        }while(nAns < 0 || nAns > 3);
    }

    switch(nAns)
    {
        case 0:
            *repeat = 0;
            *cancelAll = 0;
            *cancelSome = 0;
            break;
        case 1:
            *repeat = 1;
            break;
        case 2:
            *repeat = 0;
            *cancelAll = 1;
            break;
        case 3: 
            *repeat = 0;
            *cancelSome = 1;
            break;
    }
}

/* This function returns the item price based on item number and the for loop control variable
    Precondition: nType has range 0-2 and nItemNumber has range 0-4.
    @param int nType - for loop control variable with the range 0-2, indicates whether the item is a main, side, or drink.
    @param int nItemNumber - Item Number of dish.
    @return fPrice - price of item. */
float takePrice (int nType, int nItemNumber)
{
    float fPrice = 0.0;
        switch (nType)
        {
            case 0:
                switch (nItemNumber)
                {
                    case 1:
                        fPrice = CHICKEN_PRICE;
                        break;
                    case 2:
                        fPrice = PORK_PRICE;
                        break;
                    case 3:
                        fPrice = FISH_PRICE;
                        break;
                    case 4:
                        fPrice = BEEF_PRICE;
                        break;
                }
                break;

            case 1:
                switch (nItemNumber)
                {
                    case 1:
                        fPrice = STEAMED_RICE_PRICE;
                        break;
                    case 2:
                        fPrice = SHREDDED_CORN_PRICE;
                        break;
                    case 3:
                        fPrice = MASHED_POTATO_PRICE;
                        break;
                    case 4:
                        fPrice = STEAM_VEGETABLES_PRICE;
                        break;
                }
                break;

            case 2:
                switch (nItemNumber)
                {
                    case 1:
                        fPrice = MINERAL_WATER_PRICE;
                        break;
                    case 2:
                        fPrice = ICED_TEA_PRICE;
                        break;
                    case 3:
                        fPrice = SODA_PRICE;
                        break;
                    case 4:
                        fPrice = FRUIT_JUICE_PRICE;
                        break;
                }
                break;
        }
    return fPrice;
}

/* This function gets the subtotal of an order, it also subtracts 15% off of the order if it is the meal set of the day.
    Precondition: Each digit in nOrder and nLuckyMeal are within the range of 0-4
    @param nOrder - A 3-digit integer set by the user where the hundreds, tens, and ones digits represent the main, side, and drink respectively.
    @param nLuckyMeal - A 3-digit integer wherin the hundreds, tens, and ones, digits represent the main, side, and drink respectively. This is randomly generated by
    the function generateRandomMealSet().
    @param i - states order number.
    @return  float fSubtotal - The total of the given order.*/
float getSubtotal (int nOrder, int nLuckyMeal, int orderNumber) 
{
    float fSubtotal = 0;
    int nCurrentItem;
    int i;

    if (nOrder != 0) //if nOrder is equal to zero (All None), no need to prin subtotal.
    {
        printf("Order Number: %d\n", orderNumber);
        for (i = 0; i < 3; i++)
        {
            nCurrentItem = nOrder / (int)pow(10,2-i) - nOrder/ (int)pow(10, 3-i) * 10; //takes a single digit from nOrder.
            printf("\t");
            getType(i);
            printf(" \t");
            takeItem(i, nCurrentItem);
            printf("\t P%6.2f", takePrice(i, nCurrentItem));
            printf("\n");
            fSubtotal += takePrice(i,nCurrentItem);
        }
        if (nOrder == nLuckyMeal)
        {
            printf("Meal Set of the day discount 15%% off\n");
            fSubtotal = fSubtotal - fSubtotal * 0.15;
        }     
        printf("Subtotal: \t\t\t\t\t\t P%6.2f\n", fSubtotal);
    }
    return fSubtotal;
}

/* This function gets the subtotal of an order, it also subtracts 15% off of the order if it is the meal set of the day.
    Precondition: Each digit in nOrderArray and nLuckyMeal are within the range of 0-4
    @param *nOrderArray - The array that stores up to 3 orders. Passing an array as a pointer: https://www.scaler.com/topics/c/pass-array-to-function-in-c/
    @param nDiscounted - A 3-digit integer wherin the hundreds, tens, and ones, digits represent the main, side, and drink respectively. This is randomly generated by
    the function generateRandomMealSet().
    @param nOrderCount - The quantity of orders set by the user with a maximum of 3.
    @return  fTotal - The total price of the array of orders given.*/
float getTotal(int *nOrderArray, int nDiscounted, int nOrderCount) 
{
    float fTotal = 0;
    int i;

    for (i = 0; i < nOrderCount; i++)
    {
        fTotal += getSubtotal(*(nOrderArray + i), nDiscounted, i + 1); //Pointer arithmetic from CS50 Week 4: https://www.youtube.com/watch?v=nvO1sq_b_zI
        printf("\n");
    }
    return fTotal;
}
