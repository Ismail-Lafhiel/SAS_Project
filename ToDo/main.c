#include <stdio.h>
#include <string.h>

struct ToDo
{
    int id;
    char titre[100];
    char description[500];
    char deadline[20];
    char statut[20];
};

void addOne(struct ToDo taches[], int *nombreTaches)
{
    struct ToDo nouveauTache;
    nouveauTache.id = (*nombreTaches) + 1; // pour prendre un id unique

    printf("entrer le titre: ");
    // if(nouveauTache.titre == " ") printf("You have to fill the titre field\n"); else
    fgets(nouveauTache.titre, sizeof(nouveauTache.titre), stdin);
    printf("entrer la description: ");
    //  if(nouveauTache.description == " ") printf("You have to fill the description field\n"); else
    fgets(nouveauTache.description, sizeof(nouveauTache.description), stdin);
    printf("entrer le deadline: ");
    //  if(nouveauTache.deadline == "") printf("You have to fill the deadline field\n"); else
    fgets(nouveauTache.deadline, sizeof(nouveauTache.deadline), stdin);
    printf("entrer la statut: ");
    //  if(nouveauTache.statut == "" ) printf("You have to fill the statut field\n"); else
    fgets(nouveauTache.statut, sizeof(nouveauTache.statut), stdin);

    taches[(*nombreTaches)] = nouveauTache;
    (*nombreTaches)++;
}

void addMany(struct ToDo taches[], int *nombreTaches)
{
    int nbrTaches;
    printf("\nentrer le nombre des taches que vous desirez: ");
    scanf("%d", &nbrTaches);
    getchar();
    for (int i = 1; i <= nbrTaches; i++)
    {
        addOne(taches, nombreTaches);
    }
}

void show(struct ToDo taches[], int *nombreTaches)
{
    for (int i = 0; i < (*nombreTaches); i++)
    {
        printf("\nID: %d\n", taches[i].id);
        printf("\nTitre: %s\n", taches[i].titre);
        printf("Description: %s\n", taches[i].description);
        printf("Deadline: %s\n", taches[i].deadline);
        printf("Statut: %s\n", taches[i].statut);
        printf("\n");
    }
}
void edit(struct ToDo taches[], int *nombreTaches)
{
    int ID_tache;
    printf("entrer ID du taches pour modifier: ");
    scanf("%d", &ID_tache);
    getchar();

    if (ID_tache < 1 || ID_tache > (*nombreTaches))
    {
        printf("\ncette tache d'ID %d n'exite pas\n", ID_tache);
        return;
    }

    struct ToDo tache = taches[ID_tache - 1];

    printf("Sélectionnez le champ à modifier: \n");
    printf("1. Description\n");
    printf("2. Deadline\n");
    printf("3. Statut\n");
    printf("Entrer votre choix: ");

    int choice;

    if (scanf("%d", &choice) != 1)
    {
        printf("Choix invalide. entrer un nombre.\n");
        scanf("%*s"); // Efface le buffer (stockage temporel) d'entrée
        return;
    }
    getchar();

    switch (choice)
    {
    case 1:
        printf("Entrer une nouvelle description: ");
        fgets(tache.description, sizeof(tache.description), stdin);
        break;
    case 2:
        printf("Entrer un nouveau deadline: ");
        fgets(tache.deadline, sizeof(tache.deadline), stdin);
        break;
    case 3:
        printf("Entrer une nouvelle status: ");
        fgets(tache.statut, sizeof(tache.statut), stdin);
        break;
    default:
        printf("Choix invalide.\n");
        return;
    }

    taches[ID_tache - 1] = tache;
}
void delete(struct ToDo taches[], int *nombreTaches)
{
    int ID_tache;
    printf("Entrer ID du tache qui vous desirez de suprimer: ");
    scanf("%d", &ID_tache);
    getchar();
    if (ID_tache < 1 || ID_tache > (*nombreTaches))
    {
        printf("\ncette tache d'ID %d n'exite pas\n", ID_tache);
    }
    // Glisser les tâches après la tâche supprimée vers la gauche
    for (int i = ID_tache - 1; i < (*nombreTaches) - 1; i++)
    {
        taches[i] = taches[i + 1];
        taches[i].id = i + 1; // Modier ID du chaque tache
    }
    (*nombreTaches)--;
    printf("La tache du id %d a ete suprimer avec succes", ID_tache);
}

int main()
{
    struct ToDo taches[100]; // supposant 100 est le max des taches
    int nombreTaches = 0;    // Nombre des taches actuellement stocker
    int choix;

    do
    {
        printf("\n\tGestion de Tâches ToDo\n\n");
        printf("1 .Ajouter une nouvelle tâche\n");
        printf("2 .Ajouter plusieurs nouvelles tâches\n");
        printf("3 .Afficher la liste de toutes les tâches\n");
        printf("4 .Modifier une tâche\n");
        printf("5 .Supprimer une tâche par identifiant\n");
        printf("6 .Rechercher les tâches\n");
        printf("7 .Statistiques\n");
        printf("8 .Quitter\n");
        printf("\n-----------------------\n");
        printf("entrer votre choix: ");
        scanf("%d", &choix);
        getchar();
        switch (choix)
        {
        case 1:
            // Ajouter nouveau tache
            addOne(taches, &nombreTaches);
            break;
        case 2:
            addMany(taches, &nombreTaches);
            break;

        case 3:
            // afficher tous les taches
            show(taches, &nombreTaches);
            break;
        case 4:
            // afficher tous les taches
            edit(taches, &nombreTaches);
            break;
        case 5:
            // afficher tous les taches
            delete(taches, &nombreTaches);
            break;
        default:
            printf("\nInvalid choice\n");
            break;
        }
    } while (choix != 8);

    return 0;
}