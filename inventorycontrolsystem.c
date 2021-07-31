#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct items
{
    int itemid;
    char itemname[50];
    float itemcost;
    float itemvalue;
    int itemqty;
    int unitsold;
    float profit;
};
struct items itemarr[10];

void displayitems()
{
    system("clear");
    FILE *fptr;
    int i;
    fptr = fopen("inventory.txt", "rb");
    if (fptr == NULL)
    {
        printf("\n\nYour Inventory looks empty, consider adding some Items first.\n");
    }
    else
    {
        fread(itemarr, sizeof(struct items), 10, fptr);
        printf("\nDETAILS OF ITEMS IN YOUR INVENTORY\n");
        printf("--------------------------------------------------------\n");
        printf("| ID |    ITEM NAME    | QUANTITY | COST | TOTAL VALUE |\n");
        printf("--------------------------------------------------------\n");
        for (i = 0; i < 10; i++)
        {
            if (itemarr[i].itemname != "" && itemarr[i].itemqty != 0)
            {
                printf("\n ");
                printf("%-8d", itemarr[i].itemid);
                printf("%-16s", itemarr[i].itemname);
                printf("%-10d", itemarr[i].itemqty);
                printf("%0.2f", itemarr[i].itemcost);
                printf("    ");
                printf("%0.2f", itemarr[i].itemvalue);
            }
        }
        fclose(fptr);
    }
}

void ordernewitems()
{
    system("clear");
    FILE *fptr;
    int i;
    int qty;
    fptr = fopen("inventory.txt", "wb");
    if (fptr == NULL)
    {
        printf("\n\nSomething went wrong, Please contact the Programmer");
        exit(1);
    }
    printf("\n\nOrder New Items\n");
    printf("\nHow many items do you wish to order? : ");
    scanf(" %d", &qty);
    for (i = 0; i < qty; i++)
    {
        printf("\n\nEnter the ID of the Item No. %d : ", i + 1);
        fflush(stdin);
        scanf(" %d", &itemarr[i].itemid);
        getchar();
        printf("Enter the Name of the Item No. %d : ", i + 1);
        fflush(stdin);
        gets(itemarr[i].itemname);
        printf("Enter the cost of the Item No. %d : ", i + 1);
        fflush(stdin);
        scanf(" %f", &itemarr[i].itemcost);
        printf("Enter the Quantity for the Item No. %d : ", i + 1);
        fflush(stdin);
        scanf(" %d", &itemarr[i].itemqty);
        itemarr[i].itemvalue = itemarr[i].itemqty * itemarr[i].itemcost;
    }
    fwrite(itemarr, sizeof(struct items), 10, fptr);
    printf("\n%d Items have been successfully stored\n", qty);
    fclose(fptr);
}

void ordermoreitem()
{
    system("clear");
    FILE *fptr;
    int i;
    int id;
    int mqty;
    float val;
    fptr = fopen("inventory.txt", "wb+");
    if (fptr == NULL)
    {
        printf("\n\nSomething went wrong, Please contact the Programmer");
    }
    printf("\n\nOrder More Items\n");
    printf("Enter the ID of the Item you wish to Place an Order for : ");
    scanf("%d", &id);
    fread(itemarr, sizeof(struct items), 10, fptr);
    struct moreitems
    {
        int itemid;
        char itemname[50];
        float itemcost;
        float itemvalue;
        int itemqty;
        int unitsold;
        float profit;
    };
    struct moreitems moreitemarr[10];
    for (i = 0; i < 10; i++)
    {
        moreitemarr[i].itemid = itemarr[i].itemid;
        strcpy(moreitemarr[i].itemname, itemarr[i].itemname);
        moreitemarr[i].itemcost = itemarr[i].itemcost;
        moreitemarr[i].itemvalue = itemarr[i].itemvalue;
        moreitemarr[i].itemqty = itemarr[i].itemqty;
        moreitemarr[i].unitsold = itemarr[i].unitsold;
        moreitemarr[i].profit = itemarr[i].profit;
    }
    for (i = 0; i < 10; i++)
    {
        if (id == itemarr[i].itemid)
        {
            printf("How many more Items do you wish to order ? : ");
            scanf("%d", &mqty);
            val = itemarr[i].itemqty;
            break;
        }
        else
        {
            printf("\nItem with ID %d does not exist in your inventory", id);
            break;
        }
    }
    moreitemarr[i].itemqty = val + mqty;
    moreitemarr[i].itemvalue = moreitemarr[i].itemqty * moreitemarr[i].itemcost;
    printf("\nOrder for %d Items Placed Successfully\n", mqty);
    fwrite(moreitemarr, sizeof(struct items), 10, fptr);
    fclose(fptr);
}

void saleitem()
{
    system("clear");
    FILE *fptr;
    int i;
    int id;
    int saleqty;
    fptr = fopen("inventory.txt", "wb+");
    if (fptr == NULL)
    {
        printf("\n\nSomething went wrong, Please contact the Programmer");
    }
    printf("\n\nOrder More Items\n");
    printf("Enter the ID of the Item you wish to Place an Order for : ");
    scanf("%d", &id);
    fread(itemarr, sizeof(struct items), 10, fptr);
    struct moreitems
    {
        int itemid;
        char itemname[50];
        float itemcost;
        float itemvalue;
        int itemqty;
        int unitsold;
        float profit;
    };
    struct moreitems moreitemarr[10];
    for (i = 0; i < 10; i++)
    {
        moreitemarr[i].itemid = itemarr[i].itemid;
        strcpy(moreitemarr[i].itemname, itemarr[i].itemname);
        moreitemarr[i].itemcost = itemarr[i].itemcost;
        moreitemarr[i].itemvalue = itemarr[i].itemvalue;
        moreitemarr[i].itemqty = itemarr[i].itemqty;
        moreitemarr[i].unitsold = itemarr[i].unitsold;
        moreitemarr[i].profit = itemarr[i].profit;
    }
    for (i = 0; i < 10; i++)
    {
        if (id == itemarr[i].itemid)
        {
            printf("How many more Items do you wish to sell ? : ");
            scanf("%d", &saleqty);
            break;
        }
        else
        {
            printf("\nItem with ID %d does not exist in your inventory", id);
            break;
        }
    }
    moreitemarr[i].unitsold = saleqty;
    float saleval = saleqty * moreitemarr[i].itemcost;
    moreitemarr[i].profit = saleval * .45;
    moreitemarr[i].itemqty = moreitemarr[i].itemqty - saleqty;
    moreitemarr[i].itemvalue = moreitemarr[i].itemqty * moreitemarr[i].itemcost;
    printf("\n %d Items sold successfully", saleqty);
    fwrite(moreitemarr, sizeof(struct items), 10, fptr);
    fclose(fptr);
}
void displaysale()
{
    system("clear");
    FILE *fptr;
    int i;
    float tprofit = 0;
    fptr = fopen("inventory.txt", "rb");
    if (fptr == NULL)
    {
        printf("\n\nYour Inventory seems empty, consider adding some Items first.\n");
    }
    else
    {
        fread(itemarr, sizeof(struct items), 10, fptr);
        printf("\nDETAILS OF SALE OF ITEMS IN YOUR INVENTORY\n");
        printf("--------------------------------------------------------\n");
        printf("| ID |    ITEM NAME    | QUANTITY SOLD | TOTAL PROFIT |\n");
        printf("--------------------------------------------------------\n");
        for (i = 0; i < 10; i++)
        {
            if (itemarr[i].itemname != "" && itemarr[i].itemqty != 0)
            {
                printf("\n ");
                printf("%-8d", itemarr[i].itemid);
                printf("%-16s", itemarr[i].itemname);
                printf("%-15d", itemarr[i].unitsold);
                printf("%0.2f", itemarr[i].profit);
            }
            tprofit = tprofit + itemarr[i].profit;
        }
        printf("\n\nTotal store profit is %0.2f", tprofit);
        fclose(fptr);
    }
}

void menu()
{
    system("clear");
    printf("\n\n\nTo choose an Operation enter it's coresponding letter:- (eg:a,b,etc.)\n\n");
    printf("[a] Display the name, identification number and number of each item in stock including the cost of each item and total value of each item in stock. \n");
    printf("[b] Display the number of units sold each time, the profit for each item in stock and the total store profit \n");
    printf("[c] Order more of an existing item \n");
    printf("[d] Order new items \n");
    printf("[e] Enter the sale of an item \n");
    printf("[f] Quit the program \n\n");
    printf("Enter your choice : ");
    char ch;
    scanf(" %c", &ch);
    switch (ch)
    {
    case 'a':
        displayitems();
        break;
    case 'b':
        displaysale();
        break;
    case 'c':
        ordermoreitem();
        break;
    case 'd':
        ordernewitems();
        break;
    case 'e':
        saleitem();
        break;
    case 'f':
        exit(0);
        break;
    default:
        printf("\nPlease enter a valid choice");
    }
}

int main()
{
    system("clear");
    char res;
    do
    {
        menu();
        printf("\n\nDo you want to see the menu again ? ( y / n ) : ");
        scanf(" %c", &res);
    } while (res == 'y');
    return 0;
}
