#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct {
    int jj;
    int mm;
    int aa;
}Date;

typedef struct
{
    int code;
    char nom[50];
    int quantite;
    float prix;
    float prix_TTC;
    Date date;
} Produit;

// increment everytime a product is added
int n = 0;
// increment everytime a product is sold
int achate = 0;

// check if found and store the product index in pos var
int found = 0, pos;

// menu
void main_menu();
// ajoute
Produit ajoute_produit();
// lister les produits par alphabite
Produit lister_produits_a();
// lister les produits par prix
Produit lister_produits_p();
// affiche
void affichage_produit();
// achete produite
Produit achete_produit();
// search
Produit search_produit();
// Etat de stock
void etat_stock();
// alimenter le stock
Produit alimenter_stock();
// supprimer le produit
Produit supreimer_produit();
// Statistique de vente
Produit statistique_vent();
// find max price
int max_price();

int main()
{
    main_menu();
    // printf("\nCombien de produits voulez-vous ajouter: ");
    // scanf("%d", &taille);
    // ajoute_produit(produits, taille);
    // affichage_produit(produits, taille);
    return 0;
}

void main_menu()
{
    
    Produit *produits;
    float produits_solde[achate];
    int choice;
    int taille;
    int list_method;
    printf("\t=====================================================\n");
    printf("\t\t\tGestion de Pharmacie");
    printf("\n\t_____________________________________________________\n");
    printf("\n\t=====================================================\n");
    do
    { 
        printf("\n\t_____________________Menu Principal________________\n\n");
        printf("\t1 + Ajouter un nouveau produit ou plusieurs produits\n");
        printf("\t2 + Lister tous les produits\n");
        printf("\t3 + Acheter produit\n");
        printf("\t4 + Rechercher les produits\n");
        printf("\t5 + Etat du stock\n");
        printf("\t6 + Alimenter le stock\n");
        printf("\t7 + Supprimer les produits\n");
        printf("\t8 + Statistique de vente\n");
        printf("\t0 + Exite\n");
        printf("\n\t- Entrez vous choix > ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\n\tCombien de produits voulez-vous ajouter: ");
            scanf("%d", &taille);
            ajoute_produit(&produits, taille);
            break;
        case 2:
            printf("\n\t1 => lister tous les produits par alphabetique\n\t2 => lister tous les produits par prix\n\t> ");
            scanf("%d", &list_method);
            if(list_method == 1)
            {
                lister_produits_a(&produits);
            } else if(list_method == 2)
            {
                lister_produits_p(&produits);
            }
            affichage_produit(&produits);
            break;
        case 3:
            printf("\n\tAcheter produit");
            achete_produit(&produits, &produits_solde[achate]);
            break;
        case 4:
            printf("\n\tRechercher les produits");
            search_produit(&produits);
            break;
        case 5:
            printf("\n\tEtat du stock");
            etat_stock(&produits);
            break;
        case 6:
            printf("\n\tAlimenter le stock");
            alimenter_stock(&produits);
            break;
        case 7:
            printf("\n\tSupprimer les produits");
            supreimer_produit(&produits);
            break;
        case 8:
            printf("\n\tStatistique de vente");
            statistique_vent(&produits_solde[achate]);
            break;
        case 0:
            printf("\n\tExited");
            exit(0);
            break;
        
        default:
            printf("\n\tvous n-avez choisi aucune des options ci-dessus\n");
            break;
        }
    } while (choice != 0);
}
// AJOUTE
Produit ajoute_produit(Produit produits[], int taille)
{
    for(int i = 0; i < taille; i++)
    {
        printf("\n\tProdiut n%d:\n", i+1);
        printf("\n\tEntrer le code du produit: ");
        scanf("%d", &produits[n].code);
        printf("\n\tEntrer le nom du produit: ");
        scanf("%s", produits[n].nom);
        // fflush(stdin);
        // gets(produits[n].nom);
        printf("\n\tEntrer la quantite du produit: ");
        scanf("%d", &produits[n].quantite);
        printf("\n\tEntrer le prix du produit: ");
        scanf("%f", &produits[n].prix);
        produits[n].prix_TTC = produits[n].prix + ((produits[n].prix * 15) / 100);
        printf("\n\t___________________________\n");
        n++;
    }
    return produits[taille];
}

// lister les produits par alphabite
Produit lister_produits_a(Produit produits[])
{
    Produit temp;
    for(int i=0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(strcmp(produits[i].nom, produits[j].nom) < 0)
            {
                temp = produits[i];
                produits[i] = produits[j];
                produits[j] = temp;
            }
        }
    }
}
// lister les produits par prix
Produit lister_produits_p(Produit produits[])
{
    Produit temp;
    for(int i=0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(produits[i].prix > produits[j].prix)
            {
                temp = produits[i];
                produits[i] = produits[j];
                produits[j] = temp;
            }
        }
    }
}

// affichage
void affichage_produit(Produit produits[])
{
    // printf("How many products you want to see: ");
    // scanf("%d", &taille);
    for (int i = 0; i < n; i++)
    {
        printf("\n\tProdiut n%d:\n", i+1);
        printf("\n\tle code du produit: %d", produits[i].code);
        printf("\n\tle nom du produit: %s", produits[i].nom);
        printf("\n\tla quantite du produit: %d", produits[i].quantite);
        printf("\n\tle prix du produit: %.2f MAD", produits[i].prix);
        printf("\n\tle prixTTC du produit: %.2f MAD", produits[i].prix_TTC);
        printf("\n\t________________________________\n");
    }
    
}


// search for product
Produit search_produit(Produit produits[])
{
    int i;
    int code;
    printf("\n\trechercher un produit avec son code ou sa quantite: ");
    scanf("%d", &code);
    for ( i = 0; i < n; i++)
    {
        if(code == produits[i].code || code == produits[i].quantite)
        {
            found = 1;
            pos = i;
            break;
        }else
        {
            found = 0;
        }
    }
    if (found == 1)
    {
        printf("\n\tle produit %s Existe", produits[pos].nom);
    }else
    {
        printf("\n\tle produit %d n-existe pas", code);
    }
    return produits[pos];
}

// achete produit
Produit achete_produit(Produit produits[], float produits_solde[])
{
    int packs;
    search_produit(produits);
    if (found == 1)
    {
        printf("\n\tcombien de packs vous voulez acheter: ");
        scanf("%d", &packs);
        if (produits[pos].quantite > 0 && produits[pos].quantite >= packs)
        {
            printf("\n\tentrer la date de vente(jj mm aa): ");
            scanf("%d %d %d", &produits[pos].date.jj, &produits[pos].date.mm, &produits[pos].date.aa);
            produits[pos].quantite = produits[pos].quantite - packs;
            printf("\n\tle produit %s vendu avec succes", produits[pos].nom);
            produits_solde[achate] += produits[pos].prix;
            achate++;
        }else
        {
            printf("\n\tle produit %s hors-stock", produits[pos].nom);
        }
    }else
    {
        printf("\n\tle produit n-existe pas");
    }
}

// etat de stock
void etat_stock(Produit produits[])
{
    for(int i=0; i < n; i++)
    {
        if(produits[i].quantite < 3)
        {
            printf("\n\tProdiut n%d:\n", i+1);
            printf("\n\tle code du produit: %d", produits[i].code);
            printf("\n\tle nom du produit: %s", produits[i].nom);
            printf("\n\tla quantite du produit: %d", produits[i].quantite);
            printf("\n\tle prix du produit: %.2f MAD", produits[i].prix);
            printf("\n\tle prixTTC du produit: %.2f MAD", produits[i].prix_TTC);
            printf("\n\t________________________________\n");
        }
    }
}

// alimenter le stock
Produit alimenter_stock(Produit produits[])
{
    int packs;
    search_produit(produits);
    if (found == 1)
    {
        printf("\n\tcombien de packs vous voulez ajouter: ");
        scanf("%d", &packs);
        produits[pos].quantite = produits[pos].quantite + packs;
        printf("\n\tle quantite de produit %s mise a jour avec succes", produits[pos].nom);
    }else
    {
        printf("\n\tle produit n-existe pas");
    }
}

// suprimer le produit
Produit supreimer_produit(Produit produits[])
{
    search_produit(produits);
    int i;
    int confirm;
    printf("\n\tvous souhaitez supprimer ce produit [oui = 1][no = 0]: ");
    scanf("%d", &confirm);
    if(confirm == 1)
    {
        for(i=pos; i<n-1; i++)
        {
            produits[i] = produits[i + 1];
        }
        //Decrement array size by 1 
        n--;
        printf("\n\tle produit a ete supprime avec succes");
    }
}

// // Statistique de vente
Produit statistique_vent(float produits_solde[achate])
{
    int choice;
    printf("\n\t1 => Afficher le total des prix des produits vendus en journée courante");
    printf("\n\t2 => Afficher la moyenne des prix des produits vendus en journée courante");
    printf("\n\t3 => Afficher le Max des prix des produits vendus en journée courante");
    printf("\n\t4 => Afficher le Min des prix des produits vendus en journée courante");
    printf("\n\t  => taper n’importe quel bouton pour continuer...");
    printf("\n\t  > ");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
            break;
        case 2:
            break;
        case 3:
            max_price(&produits_solde[achate]);
            break;
        case 4:
            break;
        default:
            break;
    }
}
int max_price(float produits_solde[achate])
{
    int i;
    for (i = 1; i < achate; i++)
    {
        if(produits_solde[0] < produits_solde[i])
        {
            produits_solde[0] = produits_solde[i];
        }
    }
    printf("\n\tle Max des prix des produits vendus en journee courante: %.2f", produits_solde[0]);
}