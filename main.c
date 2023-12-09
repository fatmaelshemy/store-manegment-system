#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

#define maxLength 15

void gotoxy(int x, int y)
{
    COORD coord = {0, 0};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
typedef struct product product;
typedef struct category category;

struct product
{
    char productName[15];
    char catName[15];
    int quantity;
    float price;
};

struct category
{
    product *products;
    char categoryName[15];
    int productCount;
};

int counterOfCategory = 0;
category *arrayofCategory = NULL;

void clearScreen()
{
    system("cls");
}

void displayMenu()
{
    clearScreen();
    gotoxy(20, 3);
    printf("Welcome to My Online Store ^_^\n\n");
    printf("1. Display All Products\n");
    printf("2. Add Category\n");
    printf("3. Add Product\n");
    printf("4. move&UpdateProduct\n");
    printf("5. Buy Product\n");
    printf("0. Exit\n\n");
    printf("Enter Your Choice: ");
}

void displayCategoryDetails(int i)
{
    printf("Category %d: %s (Products: %d)\n", i + 1, arrayofCategory[i].categoryName, arrayofCategory[i].productCount);
}

void addCategory()
{
    clearScreen();
    gotoxy(20, 3);
    int numOfCat;
    printf("Enter the number of categories you are adding: ");
    scanf("%d", &numOfCat);

    arrayofCategory = realloc(arrayofCategory, (counterOfCategory + numOfCat) * sizeof(category));

    for (int i = counterOfCategory; i < counterOfCategory + numOfCat; i++)
    {
        arrayofCategory[i].productCount = 0;

        char cname[maxLength];
        printf("Enter category name: ");
        scanf("%s", cname);

        for (int x = 0; x < counterOfCategory; x++)
        {
            if (strcmp(arrayofCategory[x].categoryName, cname) == 0)
            {
                printf("This category already exists.\n");
                printf("Press Enter to continue...\n");
                _getch();
                return;
            }
        }

        strcpy(arrayofCategory[i].categoryName, cname);
        printf("Are you adding products to this category? (Y/N)\n");
        char choice = getch();
        int size;
        if (choice == 'y' || choice == 'Y')
        {
            printf("How many products are you adding? ");
            scanf("%d", &size);

            arrayofCategory[i].products = malloc(size * sizeof(product));

            for (int j = 0; j < size; j++)
            {
                printf("Enter product name: ");
                scanf("%s", arrayofCategory[i].products[j].productName);

                printf("Enter quantity of this product: ");
                scanf("%d", &arrayofCategory[i].products[j].quantity);

                printf("Enter price of this product: ");
                scanf("%f", &arrayofCategory[i].products[j].price);
                printf("Product(%s) added successfully!\n", arrayofCategory[i].products[j].productName);
            }
            arrayofCategory[i].productCount += size;

        }
        else
        {
            arrayofCategory[i].products = NULL;
            arrayofCategory[i].productCount = 0;
        }
    }

    printf("Categories added successfully!\n");
    printf("Press Enter to continue...\n");
    _getch();
    counterOfCategory += numOfCat;
}


void displayall()
{
    clearScreen();
    gotoxy(45, 0);

    if (counterOfCategory <= 0)
    {
        gotoxy(45, 13);
        printf("No Categories\n");
    }
    else
    {
        printf("Categories and Products:\n");
        for (int i = 0; i < counterOfCategory; i++)
        {
            printf("--------------------------------------------\n");
            displayCategoryDetails(i);

            if (arrayofCategory[i].products != NULL)
            {
                for (int j = 0; j < arrayofCategory[i].productCount; j++)
                {
                    printf("Product Name %d: %s\n", j + 1, arrayofCategory[i].products[j].productName);
                    printf("  Quantity %d: %d\n", j + 1, arrayofCategory[i].products[j].quantity);
                    printf("  Price %d: %.2f\n", j + 1, arrayofCategory[i].products[j].price);
                }
            }
        }
    }
    printf("Press Enter to continue...\n");
    _getch();
}
void addProduct()
{
    displayall();
    int flag = 0;

    char catName[maxLength];


    printf("Enter Category Name : ");
    scanf("%s", catName);

    int size;
    for (int i = 0; i < counterOfCategory; i++)
    {
        if (strcmp(arrayofCategory[i].categoryName, catName) == 0)
        {

            printf("How many products are you adding? ");
            scanf("%d",&size);
            if( size<=0 )
            {

                printf("Please enter a valid positive number.\n");
                printf("Press Enter to continue...\n");

                _getch();
                return ;

            }


            arrayofCategory[i].products = realloc(arrayofCategory[i].products, (arrayofCategory[i].productCount + size) * sizeof(product));

            for (int j = arrayofCategory[i].productCount; j < arrayofCategory[i].productCount + size; j++)
            {
                printf("Enter product name: ");


                char pname[maxLength];
                scanf("%s", &pname);

                for (int x = 0; x < arrayofCategory[i].productCount; x++)
                {
                    if (strcmp(arrayofCategory[i].products[x].productName, pname) == 0)
                    {
                        printf("This product already exists.\n");
                        printf("Press Enter to continue...\n");
                        _getch();
                        return;
                    }
                }

                strcpy(arrayofCategory[i].products[j].productName, pname);



                printf("Enter quantity of this product: ");
                scanf("%d", &arrayofCategory[i].products[j].quantity);

                printf("Enter price of this product: ");
                scanf("%f", &arrayofCategory[i].products[j].price);

                printf("Product(%s) added successfully!\n", arrayofCategory[i].products[j].productName);

            }

            arrayofCategory[i].productCount += size;
            flag = 1;
        }
    }


    if (flag == 0)
    {
        printf("No category of this name \n");
    }

    printf("Press Enter to continue...\n");

    _getch();
}


void buyProduct()
{
    displayall();

    char productName[maxLength];
    int quantity, numofproduct;

    char customerName[maxLength];
    printf("Enter customer name: ");
    scanf("%s", customerName);

    printf("How many products are you buying?");
    scanf("%d", &numofproduct);
    int productBought = 0;

    product *invoiceItems = malloc(numofproduct * sizeof(product));


    float totalAmount = 0;
    for (int index = 0; index < numofproduct; index++) //2
    {
        printf("Enter product Name: \n");
        scanf("%s", productName);

        printf("Enter quantity: \n");
        scanf("%d", &quantity);



        for (int i = 0; i < counterOfCategory; i++)
        {
            for (int j = 0; j < arrayofCategory[i].productCount; j++)
            {
                if (strcmp(arrayofCategory[i].products[j].productName, productName) == 0)
                {
                    if (arrayofCategory[i].products[j].quantity >= quantity)
                    {
                        arrayofCategory[i].products[j].quantity -= quantity;

                        printf("Product '%s' bought successfully!\n", productName);
                        printf("Press Enter to continue... \n");
                        _getch();


                        strcpy(invoiceItems[index].productName, productName);
                        invoiceItems[index].quantity = quantity;
                        invoiceItems[index].price = arrayofCategory[i].products[j].price;


                        totalAmount += (quantity * arrayofCategory[i].products[j].price);

                        productBought = 1;


                        if (arrayofCategory[i].products[j].quantity == 0)
                        {

                            for (int k = j; k < arrayofCategory[i].productCount - 1; k++)
                            {
                                arrayofCategory[i].products[k] = arrayofCategory[i].products[k + 1];
                            }
                            arrayofCategory[i].productCount--;


                            arrayofCategory[i].products = realloc(arrayofCategory[i].products,
                                                                  arrayofCategory[i].productCount * sizeof(product));
                        }


                    }

                }

            }
        }


    }
    if (!productBought)
    {
        printf("Product '%s' not found or not enough quantity available.\n", productName);
    }
    else
    {

        system("cls");
        printf("\nInvoice:\n");
        printf("Customer: %s\n", customerName);
        printf("Date: %s\n", __DATE__);

        printf("\n%-20s%-10s%-15s%-15s\n", "Product Name", "Quantity", "Unit Price", "Total Price");

        for (int i = 0; i < numofproduct; i++)
        {
            float unitPrice = invoiceItems[i].price;
            float totalPrice = invoiceItems[i].quantity * unitPrice;

            printf("%-20s%-10d$%-14.2f$%-14.2f\n", invoiceItems[i].productName,
                   invoiceItems[i].quantity, unitPrice, totalPrice);
        }


        free(invoiceItems);

        printf("\nTotal Amount: $%.2f\n", totalAmount);
    }


    printf("Press Enter to continue... \n");
    _getch();
}

void moveAndupdateProduct() {
    int update = 0;
    displayall();

    if (counterOfCategory >= 2) {
        char catName[maxLength];
        int categoryFound = 0;

        printf("Enter name of category you want to remove from: ");
        scanf("%s", catName);

        for (int i = 0; i < counterOfCategory; i++) {
            if (strcmp(arrayofCategory[i].categoryName, catName) == 0) {
                categoryFound = 1;

                for (int j = 0; j < arrayofCategory[i].productCount; j++) {
                    char productName[maxLength];
                    printf("Enter name of product you are moving: ");
                    scanf("%s", productName);

                    if (strcmp(arrayofCategory[i].products[j].productName, productName) == 0) {
                        int quantity = arrayofCategory[i].products[j].quantity;
                        float price = arrayofCategory[i].products[j].price;

                        // Remove the product from the current category
                        for (int k = j; k < arrayofCategory[i].productCount - 1; k++) {
                            arrayofCategory[i].products[k] = arrayofCategory[i].products[k + 1];
                        }
                        arrayofCategory[i].productCount--;

                        // Resize the memory for products in the current category
                        arrayofCategory[i].products = realloc(arrayofCategory[i].products,
                                                              arrayofCategory[i].productCount * sizeof(product));

                        // Prompt user for the category to move the product to
                        printf("Enter name of category you want to add to: ");
                        char catName2[maxLength];
                        scanf("%s", catName2);

                        // Find the destination category
                        int f;
                        for (f = 0; f < counterOfCategory; f++) {
                            if (strcmp(arrayofCategory[f].categoryName, catName2) == 0) {
                                // Resize the memory for products in the destination category
                                arrayofCategory[f].products = realloc(arrayofCategory[f].products,
                                                                      (arrayofCategory[f].productCount + 1) * sizeof(product));

                                // Ask user if they want to add the product without changes
                                printf("Are you adding the product without changes? (Y/N)\n");
                                char choice = getch();

                                if (choice == 'y' || choice == 'Y') {
                                    // Add the product to the destination category without changes
                                    strcpy(arrayofCategory[f].products[arrayofCategory[f].productCount].productName, productName);
                                    arrayofCategory[f].products[arrayofCategory[f].productCount].quantity = quantity;
                                    arrayofCategory[f].products[arrayofCategory[f].productCount].price = price;

                                    arrayofCategory[f].productCount++;
                                    break;
                                } else {
                                    // Ask for new product details
                                    char name[maxLength];
                                    int q = 0;
                                    float p = 0;

                                    printf("Enter New Product Name:\n");
                                    scanf("%s", name);

                                    printf("Enter New quantity:\n");
                                    scanf("%d", &q);

                                    printf("Enter New price:\n");
                                    scanf("%f", &p);

                                    // Add the new product details to the destination category
                                    strcpy(arrayofCategory[f].products[arrayofCategory[f].productCount].productName, name);
                                    arrayofCategory[f].products[arrayofCategory[f].productCount].quantity = q;
                                    arrayofCategory[f].products[arrayofCategory[f].productCount].price = p;

                                    arrayofCategory[f].productCount++;
                                    update = 1;
                                    break;
                                }
                            }
                        }

                        if (f == counterOfCategory) {
                            printf("No category of this name\n");
                        }
                    } else {
                        printf("No product of this name\n");
                    }
                }
                break;  // Exit the outer loop once the category is found and processed
            }
        }

        if (!categoryFound) {
            printf("No category of this name\n");
        }
    } else {
        printf("you must add 2 categories first \n ");
    }

    if (update > 0) {
        printf("product update successfully \n");
    }

    if (counterOfCategory <= 0) {
        clearScreen();
        gotoxy(4, 3);
        printf("No Category just added \n ");
    }

    printf("Press Enter to continue... \n");
    _getch();
}


int main()
{
    int choice;
    do
    {
        displayMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            exit(0);
            break;
        case 1:
            displayall();
            break;
        case 2:
            addCategory();
            break;
        case 3:
            addProduct();
            break;
        case 4:
            moveAndupdateProduct();
            break;
        case 5:
            buyProduct();
            break;
        }
    }
    while (choice != 0);

    for (int i = 0; i < counterOfCategory; i++)
    {
        free(arrayofCategory[i].products);
    }
    free(arrayofCategory);
    return 0;
}
