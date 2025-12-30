#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 10
#define MAX_ORDER 20
#define GST_RATE 0.05
#define DISC_THRESHOLD 500.0
#define DISC_RATE 0.10

char foodItems[MAX_ITEMS][30] = {
    "Margherita Pizza",
    "Veggie Burger",
    "French Fries",
    "Coke",
    "Pasta Alfredo",
    "Paneer Tikka",
    "Coffee",
    "Chicken Biryani",
    "Chocolate Cake",
    "Ice Cream"
};

float foodPrices[MAX_ITEMS] = {
    250.00, 120.00, 60.00, 40.00, 180.00, 200.00, 70.00, 220.00, 90.00, 80.00
};

int orderItems[MAX_ORDER];
int orderQty[MAX_ORDER];
int orderCount = 0;

void showMenu();
void takeOrder();
void generateBill();
void clearOrder();

int main() {
    int choice;
    printf("====== Welcome to College Canteen Restaurant Billing System ======\n");

    do {
        printf("\n-------- Main Menu --------\n");
        printf("1. Show Menu\n");
        printf("2. Place Order\n");
        printf("3. Generate Bill\n");
        printf("4. Clear Order\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                showMenu();
                break;
            case 2:
                takeOrder();
                break;
            case 3:
                generateBill();
                break;
            case 4:
                clearOrder();
                printf("Order cleared successfully!\n");
                break;
            case 5:
                printf("Thank you for visiting! Have a great day!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 5);

    return 0;
}

void showMenu() {
    printf("\n----------- Food Menu -----------\n");
    printf("%-5s %-25s %10s\n", "No.", "Item", "Price");
    for(int i = 0; i < MAX_ITEMS; i++) {
        printf("%-5d %-25s %10.2f\n", i+1, foodItems[i], foodPrices[i]);
    }
    printf("---------------------------------\n");
}

void takeOrder() {
    int itemNo, qty, more;

    do {
        showMenu();
        printf("Enter food item number (1-%d): ", MAX_ITEMS);
        scanf("%d", &itemNo);

        if(itemNo < 1 || itemNo > MAX_ITEMS) {
            printf("Invalid item number! Please try again.\n");
            continue;
        }

        printf("Enter quantity: ");
        scanf("%d", &qty);

        if(qty <= 0) {
            printf("Invalid quantity! Must be greater than 0.\n");
            continue;
        }

        if(orderCount >= MAX_ORDER) {
            printf("Maximum order limit (%d items) reached!\n", MAX_ORDER);
            break;
        }

        orderItems[orderCount] = itemNo - 1;
        orderQty[orderCount] = qty;
        orderCount++;

        printf("Item added successfully!\n");
        printf("Add more items? (1-Yes, 0-No): ");
        scanf("%d", &more);

    } while(more == 1);

    printf("Order taking completed. Total items in cart: %d\n", orderCount);
}

void generateBill() {
    if(orderCount == 0) {
        printf("No items in the order. Please place an order first.\n");
        return;
    }

    float subtotal = 0.0;

    printf("\n============== YOUR BILL ==============\n");
    printf("%-5s %-20s %-7s %10s\n", "No.", "Item", "Qty", "Total");
    printf("--------------------------------------------\n");

    for(int i = 0; i < orderCount; i++) {
        int itemIdx = orderItems[i];
        int qty = orderQty[i];
        float itemTotal = foodPrices[itemIdx] * qty;

        printf("%-5d %-20s %-7d %10.2f\n", i+1, foodItems[itemIdx], qty, itemTotal);
        subtotal += itemTotal;
    }

    printf("--------------------------------------------\n");
    printf("Subtotal:                          %10.2f\n", subtotal);

    float gst = subtotal * GST_RATE;
    printf("GST @ %.0f%%:                         %10.2f\n", GST_RATE * 100, gst);

    float totalBeforeDiscount = subtotal + gst;

    float discount = 0.0;
    if(totalBeforeDiscount > DISC_THRESHOLD) {
        discount = totalBeforeDiscount * DISC_RATE;
        printf("Discount (%.0f%% on bill > %.0f):   -%10.2f\n", DISC_RATE * 100, DISC_THRESHOLD, discount);
    }

    float grandTotal = totalBeforeDiscount - discount;

    printf("--------------------------------------------\n");
    printf("Grand Total:                       %10.2f\n", grandTotal);
    printf("===========================================\n");

    printf("Thank you for dining with us!\n");
}

void clearOrder() {
    orderCount = 0;
}