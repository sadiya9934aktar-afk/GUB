#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 50
#define MENU_SIZE 10
#define DELIVERY_CHARGE 60

struct Menu
{
    int id;
    char name[50];
    float price;
};

struct Order
{
    int id;
    char name[50];
    float price;
    int quantity;
    float total;
};

struct Menu menu[] =
{
    {1, "Burger", 250},
    {2, "Pizza", 600},
    {3, "Fried Rice", 300},
    {4, "Chicken Fry", 180},
    {5, "Soft Drink", 50},
    {6, "Coffee", 120},
    {7, "Ice Cream", 100},
    {8, "Sandwich", 150},
    {9, "French Fries", 140},
    {10, "Chicken BBQ", 450}
};

struct Order orders[MAX_ITEMS];

int orderCount = 0;

/* Delivery Information */
int orderType;
char customerName[50];
char phone[20];
char address[100];


/* Function declarations */
void showMenu();
void takeOrder();
void printBill();
void saveBill();
void deliveryInfo();


/* Display Menu */
void showMenu()
{
    int i;

    printf("\n");
    printf("=========================================\n");
    printf("              RESTAURANT MENU\n");
    printf("=========================================\n");

    printf("%-5s %-20s %-10s\n", "ID", "Item", "Price");
    printf("-----------------------------------------\n");

    for(i = 0; i < MENU_SIZE; i++)
    {
        printf("%-5d %-20s %.2f TK\n",
               menu[i].id,
               menu[i].name,
               menu[i].price);
    }

    printf("=========================================\n");
}


/* Delivery Information */
void deliveryInfo()
{
    printf("\n=========================================\n");
    printf("          ORDER TYPE\n");
    printf("=========================================\n");

    printf("1. Dine In\n");
    printf("2. Home Delivery\n");

    printf("\nEnter Order Type: ");
    scanf("%d", &orderType);

    while(orderType != 1 && orderType != 2)
    {
        printf("Invalid choice! Please enter 1 or 2: ");
        scanf("%d", &orderType);
    }

    if(orderType == 2)
    {
        printf("\nEnter Customer Name: ");
        scanf(" %[^\n]", customerName);

        printf("Enter Phone Number: ");
        scanf(" %[^\n]", phone);

        printf("Enter Delivery Address: ");
        scanf(" %[^\n]", address);

        printf("\nHome Delivery Selected Successfully.\n");
        printf("Delivery Charge: %d TK\n", DELIVERY_CHARGE);
    }
    else
    {
        strcpy(customerName, "N/A");
        strcpy(phone, "N/A");
        strcpy(address, "N/A");

        printf("\nDine In Selected Successfully.\n");
    }
}


/* Take Order */
void takeOrder()
{
    int id, qty, i, found;

    while(1)
    {
        showMenu();

        printf("\nEnter Item ID (0 to Finish): ");

        if(scanf("%d", &id) != 1)
        {
            printf("\nInvalid input! Please enter a number.\n");

            while(getchar() != '\n');

            continue;
        }

        if(id == 0)
        {
            break;
        }

        found = 0;

        for(i = 0; i < MENU_SIZE; i++)
        {
            if(menu[i].id == id)
            {
                found = 1;

                printf("Enter Quantity: ");

                if(scanf("%d", &qty) != 1)
                {
                    printf("\nInvalid quantity!\n");

                    while(getchar() != '\n');

                    break;
                }

                if(qty <= 0)
                {
                    printf("\nQuantity must be greater than 0.\n");
                    break;
                }

                if(orderCount >= MAX_ITEMS)
                {
                    printf("\nOrder limit reached! Cannot add more items.\n");
                    return;
                }

                orders[orderCount].id = menu[i].id;

                strcpy(orders[orderCount].name, menu[i].name);

                orders[orderCount].price = menu[i].price;

                orders[orderCount].quantity = qty;

                orders[orderCount].total =
                    menu[i].price * qty;

                orderCount++;

                printf("\nItem Added Successfully.\n");

                break;
            }
        }

        if(found == 0)
        {
            printf("\nInvalid Item ID.\n");
        }
    }
}


/* Print Bill */
void printBill()
{
    int i;
    float subtotal = 0;
    float vat, discount = 0;
    float deliveryCharge = 0;
    float grandTotal;

    printf("\n");
    printf("==============================================\n");
    printf("            RESTAURANT FINAL BILL\n");
    printf("==============================================\n");

    /* Customer Information */
    if(orderType == 2)
    {
        printf("Order Type    : Home Delivery\n");
        printf("Customer Name : %s\n", customerName);
        printf("Phone         : %s\n", phone);
        printf("Address       : %s\n", address);
    }
    else
    {
        printf("Order Type    : Dine In\n");
    }

    printf("==============================================\n");

    printf("%-5s %-18s %-8s %-8s %-10s\n",
           "ID", "Item", "Price", "Qty", "Total");

    printf("------------------------------------------------\n");

    for(i = 0; i < orderCount; i++)
    {
        printf("%-5d %-18s %-8.2f %-8d %-10.2f\n",
               orders[i].id,
               orders[i].name,
               orders[i].price,
               orders[i].quantity,
               orders[i].total);

        subtotal += orders[i].total;
    }

    vat = subtotal * 0.05;

    if(subtotal >= 2000)
    {
        discount = subtotal * 0.10;
    }

    /* Home Delivery Charge */
    if(orderType == 2)
    {
        deliveryCharge = DELIVERY_CHARGE;
    }

    grandTotal = subtotal + vat + deliveryCharge - discount;

    printf("------------------------------------------------\n");

    printf("Subtotal        : %.2f TK\n", subtotal);
    printf("VAT (5%%)        : %.2f TK\n", vat);
    printf("Discount        : %.2f TK\n", discount);

    if(orderType == 2)
    {
        printf("Delivery Charge : %.2f TK\n", deliveryCharge);
    }

    printf("-----------------------------------------------\n");
    printf("Grand Total     : %.2f TK\n", grandTotal);

    printf("===============================================\n");
    printf("          Thank You! Visit Again.\n");
    printf("===============================================\n");
}


/* Save Bill to File */
void saveBill()
{
    FILE *fp;
    int i;

    float subtotal = 0;
    float vat, discount = 0;
    float deliveryCharge = 0;
    float grandTotal;

    fp = fopen("bill.txt", "w");

    if(fp == NULL)
    {
        printf("File could not be created.\n");
        return;
    }

    fprintf(fp, "========== RESTAURANT BILL ==========\n");

    /* Save Order Type */
    if(orderType == 2)
    {
        fprintf(fp, "Order Type    : Home Delivery\n");
        fprintf(fp, "Customer Name : %s\n", customerName);
        fprintf(fp, "Phone         : %s\n", phone);
        fprintf(fp, "Address       : %s\n", address);
    }
    else
    {
        fprintf(fp, "Order Type    : Dine In\n");
    }

    fprintf(fp, "=====================================\n");

    fprintf(fp, "ID\tItem\t\tPrice\tQty\tTotal\n");

    for(i = 0; i < orderCount; i++)
    {
        fprintf(fp, "%d\t%s\t\t%.2f\t%d\t%.2f\n",
                orders[i].id,
                orders[i].name,
                orders[i].price,
                orders[i].quantity,
                orders[i].total);

        subtotal += orders[i].total;
    }

    vat = subtotal * 0.05;

    if(subtotal >= 2000)
    {
        discount = subtotal * 0.10;
    }

    /* Home Delivery Charge */
    if(orderType == 2)
    {
        deliveryCharge = DELIVERY_CHARGE;
    }

    grandTotal = subtotal + vat + deliveryCharge - discount;

    fprintf(fp, "\nSubtotal        : %.2f TK", subtotal);
    fprintf(fp, "\nVAT             : %.2f TK", vat);
    fprintf(fp, "\nDiscount        : %.2f TK", discount);

    if(orderType == 2)
    {
        fprintf(fp, "\nDelivery Charge : %.2f TK", deliveryCharge);
    }

    fprintf(fp, "\nGrand Total     : %.2f TK\n", grandTotal);

    fprintf(fp, "\n=====================================\n");
    fprintf(fp, "        Thank You! Visit Again.\n");
    fprintf(fp, "=====================================\n");

    fclose(fp);

    printf("\nBill Saved Successfully in bill.txt\n");
}


/* Main Function */
int main()
{
    printf("=====================================\n");
    printf("   RESTAURANT ORDER & BILLING SYSTEM\n");
    printf("=====================================\n");

    /* Select Order Type */
    deliveryInfo();

    /* Take Food Order */
    takeOrder();

    if(orderCount == 0)
    {
        printf("\nNo items were ordered.\n");
        return 0;
    }

    /* Print Bill */
    printBill();

    /* Save Bill */
    saveBill();

    return 0;
}
