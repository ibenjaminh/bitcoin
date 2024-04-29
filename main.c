#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct {
    char* tickerSymbol;
    float currentCoins;
    float cashBank;
}wallet;

typedef struct ledger {
    char* transactions;
    struct ledger *next;
}ledger;

int getLive(){
    int lower = 25000, upper = 35000;
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

char* Date() {
    time_t t = time(NULL);
    char* str_time = ctime(&t);
    return str_time;
}

bool updateBuy(float amount, wallet* wallet1, int currentPriceBTC) { // adding bools to the function so if its successful we can add trans
    float desirecBTCprice;
    desirecBTCprice = currentPriceBTC * amount;

    if (wallet1->cashBank > desirecBTCprice) {
        wallet1->cashBank -= desirecBTCprice;
        wallet1->currentCoins += amount;
        return true;
    }
    else {
        printf("Not enough cash!\n");
        return false;
    }
}

bool updateSell(float amount, wallet* wallet1, int currentPriceBTC) {
    float desiredBTCprice;
    desiredBTCprice = currentPriceBTC * amount;

    if (wallet1->currentCoins >= amount) {
        wallet1->currentCoins -= amount;
        wallet1->cashBank += desiredBTCprice;
        return true;
    }
    else {
        printf("You dont even have that many coins, man!");
        return false;
    }
}

// call function that prints transactions in linked list inside ledger


// store transactions strings (maybe take the printf("bought ### BTC on DATE"); and turn that into a string and also use for record in linked list



int main (void) {

    wallet myWallet;
    myWallet.cashBank = 75000;
    myWallet.tickerSymbol = "BTC";
    myWallet.currentCoins = 0;

    char input[20];
    char command[10];
    float amount;

    printf("Welcome to BTC Trader!\n");
    while (1) {
        printf("Type buy #, sell #, price, balance, history, or exit: \n");

        fgets(input, sizeof(input), stdin); // Reading full line of input

        // Checking if input is buy or sell first
        if (sscanf(input, "%s %f", command, &amount) == 2) {
            if (strcmp(command, "buy") == 0) {
                // enter function to buy, check if they can even buy, deduct cash amount, add coins to wallet, getDate, createTransaction, addTransaction, get live
                int currentPrice = getLive();

                if (updateBuy(amount, &myWallet, currentPrice) == true) { // if buy is successful
                    // get date, create transaction string, add transaction string to ledger
                    printf("Bought %.2f coins of %s\n", amount, myWallet.tickerSymbol);

                }


            }
            else if (strcmp(command, "sell") == 0) {

                // enter function to sell, check if they can even sell, add cash amount, deduct coins from wallet, get date, createTransaction, addTransaction
                int currentPrice = getLive();

                if (updateSell(amount, &myWallet, currentPrice) == true) {

                    // get date, create transaction string, add transaction string to ledger

                    printf("Sold %.2f coins of %s\n", amount, myWallet.tickerSymbol);
                }

            }
            else {
                printf("Invalid input\n");
            }
        }

        else if (sscanf(input, "%s", command) == 1) { // Only one word entered (price, balance, history)
            if (strcmp(command, "price") == 0) {
                printf("The current price per %s is $%d\n", myWallet.tickerSymbol, getLive());
            }
            else if (strcmp(command, "history") == 0) {
                // call function that prints transactions in linked list inside ledger
                printf("Transaction history is: \n");
            }
            else if(strcmp(command, "balance") == 0) {
                printf("Current balance is: $%lf \n", myWallet.cashBank);
                printf("Current # of %s: %lf\n", myWallet.tickerSymbol, myWallet.currentCoins);
                int currentValue;
                currentValue = getLive() * myWallet.currentCoins;
                printf("Market Value: $%d\n", currentValue);
            }
            else if(strcmp(command, "exit") == 0) {
                break;
            }
        }
        else {
            printf("Incorrect command format");
        }
    }

    return 0;
}
