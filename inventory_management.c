#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Product {
    int id;
    char productName[50];
    int quantity;
    char date[12];
}p;

FILE *fp;

int main() {
    int ch;

    while(1) {
        system("cls");
        printf("== Store Management System ==\n");
        printf("1. Add Product\n");
        printf("2. List Products\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("5. Buy Product\n");
        printf("0. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch(ch) {
        case 0:
            exit(0);
        
        case 1:
            addProduct();
            break;
        
        case 2:
            displayProduct();
            break;
        
        case 3:
            updateProduct();
            break;

        case 4:
            deleteProduct();
            break;
        
        case 5:
            buy();
            break;
        
        default:
            printf("Invalid choice!\n\n");
        }
        printf("\n\nPress Any Key to Continue...");
        getch();
    }

    return 0;
}

void addProduct() {
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(p.date, myDate);

    fp = fopen("product.txt", "ab");

    printf("Enter Product id: ");
    scanf("%d", &p.id);

    printf("Enter Product name: ");
    fflush(stdin);
    gets(p.productName);

    printf("Enter Product Quantity: ");
    fflush(stdin);
    scanf("%d", &p.quantity);

    printf("\nProduct Added Successfully...");

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);
}

void displayProduct() {
    
    system("cls");
    printf("== Product List ==\n\n");
    printf("%-10s %-30s %-30s %s\n", "Id", "Product Name", "Quantity", "Date");
    printf("=====================================================================\n");

    fp = fopen("product.txt", "rb");
    while (fread(&p, sizeof(p), 1, fp) == 1) {
        printf("%-10s %-30s %-30s %s\n", p.id, p.productName, p.quantity, p.date);
    }
    fclose(fp);
}


void updateProduct() {
    int id, f;

    system("cls");
    printf("== Update Product ==\n\n");
    printf("Enter Product id to update: ");
    scanf("%d", &id);

    FILE *ft;
    fp = fopen("product.txt", "rb+");

    while (fread(&p, sizeof(p), 1, fp) == 1) {

        if (id == p.id){
            f=1;
            printf("Enter new product name: ");
            fflush(stdin);
            gets(p.productName);

            printf("Enter new product quantity: ");
            fflush(stdin);
            scanf("%d", &p.quantity);

            fseek(fp, -sizeof(p), 1);
            fwrite(&p, sizeof(p), 1, fp);
            fclose(fp);
            break;
        }
    }

    if (f==1) {
        printf("\nProduct updated...");
    }else{
        printf("\n\nProduct Not Found!");
    }
}

void deleteProduct() {
    int id, f;

    system("cls");
    printf("== Delete Products ==\n\n");
    printf("Enter product id to delete: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("product.txt", "rb");

    while (fread(&p, sizeof(p), 1, fp) == 1) {
        if (id == p.id) {
            f = 1;
            fclose(fp);
            break;
        }
    }

    if (f==1) {
        printf("\nProduct deleted successfully!");
        del(id);
    }else {
        printf("\n\nProduct Not Found!");
    }
}

void buyProduct() {
    int id, f=0;
    system("cls");
    printf("== Buy Products ==\n\n");
    printf("Enter product id to buy: ");
    scanf("%d", &id);

    FILE *ft;
    fp = fopen("product.txt", "rb+");

    while(fread(&p, sizeof(p), 1, fp) == 1) {
        if (id == p.id){
            f = 1;
            p.quantity = p.quantity - 1;
            fseek(fp, -sizeof(p), 1);
            fwrite(&p, sizeof(p), 1, fp);
            fclose(fp);
            if(p.quantity == 0) {
                del(p.id);
            }
            break;
        }
    }

    if (f == 1) {
        printf("\nProduct bought successfully!");
    }else {
        printf("\n\nProduct Not Found!");
    }
}

void del(int id) {
    int f = 0;

    FILE *ft;

    fp = fopen("product.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while(fread(&p, sizeof(p), 1, fp) == 1) {
        if (id == p.id) {
            f = 1;
        } else{
            fwrite(&p, sizeof(p), 1, ft);
        }
    }

    fclose(fp);
    fclose(ft);

    remove("product.txt");
    rename("temp.txt", "product.txt");
}