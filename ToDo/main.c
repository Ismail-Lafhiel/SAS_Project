#include <stdio.h>
#include <string.h>
#include <time.h>

struct Date
{
    int day;
    int month;
    int year;
};

struct ToDo
{
    int id;
    char titre[100];
    char description[500];
    struct Date deadline;
    char statut[20];
};

//la fonction ajouterUn
void ajouterUn(struct ToDo taches[], int *nombreTaches)
{
    struct ToDo nouveauTache;
    nouveauTache.id = (*nombreTaches) + 1; // pour prendre un id unique

    printf("Entrer le titre: ");
    fgets(nouveauTache.titre, sizeof(nouveauTache.titre), stdin);

    printf("Entrer la description: ");
    fgets(nouveauTache.description, sizeof(nouveauTache.description), stdin);

    printf("Entrer la deadline (jour mois année): ");
    scanf("%d %d %d", &nouveauTache.deadline.day, &nouveauTache.deadline.month, &nouveauTache.deadline.year);
    getchar();

    // assigner la statut par défaut à "To do"
    strcpy(nouveauTache.statut, "To do");

    taches[(*nombreTaches)] = nouveauTache;
    (*nombreTaches)++;
}


// ajouterBeaucoup
void ajouterBeaucoup(struct ToDo taches[], int *nombreTaches)
{
    int nbrTaches;
    printf("\nEntrer le nombre de tâches que vous désirez: ");
    scanf("%d", &nbrTaches);
    getchar();

    for (int i = 1; i <= nbrTaches; i++)
    {
        ajouterUn(taches, nombreTaches);
    }
}


//afficher
void afficher(struct ToDo taches[], int *nombreTaches)
{
    int choix;
    printf("\nSélectionnez l'option d'affichage: \n");
    printf("1. Trier les tâches par ordre alphabétique\n");
    printf("2. Trier les tâches par deadline\n");
    printf("3. Afficher les tâches dont le délai est dans 3 jours ou moins\n");
    printf("Entrer votre choix: ");
    scanf("%d", &choix);
    getchar();

    switch (choix)
    {
    case 1:
        // Trier les tâches par ordre alphabétique
        for (int i = 0; i < (*nombreTaches) - 1; i++)
        {
            for (int j = 0; j < (*nombreTaches) - i - 1; j++)
            {
                if (strcmp(taches[j].titre, taches[j + 1].titre) > 0)
                {
                    struct ToDo temp = taches[j];
                    taches[j] = taches[j + 1];
                    taches[j + 1] = temp;
                }
            }
        }
        break;

    case 2:
        // Trier les tâches par deadline
        for (int i = 0; i < (*nombreTaches) - 1; i++)
        {
            for (int j = 0; j < (*nombreTaches) - i - 1; j++)
            {
                if (taches[j].deadline.year > taches[j + 1].deadline.year ||
                    (taches[j].deadline.year == taches[j + 1].deadline.year && taches[j].deadline.month > taches[j + 1].deadline.month) ||
                    (taches[j].deadline.year == taches[j + 1].deadline.year && taches[j].deadline.month == taches[j + 1].deadline.month && taches[j].deadline.day > taches[j + 1].deadline.day))
                {
                    struct ToDo temp = taches[j];
                    taches[j] = taches[j + 1];
                    taches[j + 1] = temp;
                }
            }
        }
        break;

    case 3:
        // Afficher les tâches dont le délai est dans 3 jours ou moins
        printf("\nListe des tâches dont le délai est dans 3 jours ou moins:\n");
        for (int i = 0; i < (*nombreTaches); i++)
        {
            time_t now;
            struct tm *current_time;
            time(&now);
            current_time = localtime(&now);

            int jour_courant = current_time->tm_mday;
            int mois_courant = current_time->tm_mon + 1;
            int annee_courante = current_time->tm_year + 1900;

            int jours_restants = 0;

            if (annee_courante < taches[i].deadline.year ||
                (annee_courante == taches[i].deadline.year && mois_courant < taches[i].deadline.month) ||
                (annee_courante == taches[i].deadline.year && mois_courant == taches[i].deadline.month && jour_courant < taches[i].deadline.day))
            {
                struct tm deadline_time = {0};
                deadline_time.tm_year = taches[i].deadline.year - 1900;
                deadline_time.tm_mon = taches[i].deadline.month - 1;
                deadline_time.tm_mday = taches[i].deadline.day;

                time_t deadline = mktime(&deadline_time);
                double seconds_remaining = difftime(deadline, now);
                jours_restants = seconds_remaining / (60 * 60 * 24);

                if (jours_restants <= 3)
                {
                    printf("ID: %d\n", taches[i].id);
                    printf("Titre: %s", taches[i].titre);
                    printf("Description: %s", taches[i].description);
                    printf("Deadline: %d/%d/%d\n", taches[i].deadline.day, taches[i].deadline.month, taches[i].deadline.year);
                    printf("Statut: %s\n", taches[i].statut);
                    printf("Jours restants: %d\n", jours_restants);
                    printf("\n");
                }
            }
        }
        return;

    default:
        printf("Choix invalide. Entrer un nombre valide.\n");
        return;
    }

    printf("\nListe des tâches:\n");
    for (int i = 0; i < (*nombreTaches); i++)
    {
        printf("ID: %d\n", taches[i].id);
        printf("Titre: %s", taches[i].titre);
        printf("Description: %s", taches[i].description);
        printf("Deadline: %d/%d/%d\n", taches[i].deadline.day, taches[i].deadline.month, taches[i].deadline.year);
        printf("Statut: %s\n", taches[i].statut);
        printf("\n");
    }
}


void modifier(struct ToDo taches[], int *nombreTaches)
{
    int ID_tache;
    printf("Entrer l'ID de la tâche que vous souhaitez modifier: ");
    scanf("%d", &ID_tache);
    getchar();

    if (ID_tache < 1 || ID_tache > (*nombreTaches))
    {
        printf("\nCette tâche d'ID %d n'existe pas\n", ID_tache);
        return;
    }

    struct ToDo tache = taches[ID_tache - 1];

    printf("Sélectionnez le champ à modifier: \n");
    printf("1. Description\n");
    printf("2. Deadline\n");
    printf("3. Statut\n");
    printf("Entrer votre choix: ");
    int choix;
    scanf("%d", &choix);
    getchar();

    switch (choix)
    {
    case 1:
        printf("Entrer une nouvelle description: ");
        fgets(tache.description, sizeof(tache.description), stdin);
        break;
    case 2:
        printf("Entrer une nouvelle deadline (jour mois année): ");
        scanf("%d %d %d", &tache.deadline.day, &tache.deadline.month, &tache.deadline.year);
        getchar();
        break;
    case 3:
        printf("Entrer un nouveau statut: ");
        fgets(tache.statut, sizeof(tache.statut), stdin);
        break;
    default:
        printf("Choix invalide. Entrer un nombre valide.\n");
        break;
    }

    taches[ID_tache - 1] = tache;
    printf("La tâche d'ID %d a été modifiée avec succès.\n", ID_tache);
}

void supprimer(struct ToDo taches[], int *nombreTaches)
{
    int ID_tache;
    printf("Entrer l'ID de la tâche que vous souhaitez supprimer: ");
    scanf("%d", &ID_tache);
    getchar();

    if (ID_tache < 1 || ID_tache > (*nombreTaches))
    {
        printf("\nCette tâche d'ID %d n'existe pas\n", ID_tache);
        return;
    }

    for (int i = ID_tache - 1; i < (*nombreTaches) - 1; i++)
    {
        taches[i] = taches[i + 1];
        taches[i].id = i + 1; // Mettre à jour l'ID de chaque tâche
    }

    (*nombreTaches)--;
    printf("La tâche d'ID %d a été supprimée avec succès.\n", ID_tache);
}

void rechercher(struct ToDo taches[], int *nombreTaches)
{
    int choix;
    printf("Sélectionnez le champ à rechercher: \n");
    printf("1. ID\n");
    printf("2. Titre\n");
    printf("Entrer votre choix: ");
    scanf("%d", &choix);
    getchar();

    switch (choix)
    {
    case 1:
        int ID_tache;
        printf("Entrer l'ID de la tâche à rechercher: ");
        scanf("%d", &ID_tache);
        getchar();

        if (ID_tache < 1 || ID_tache > (*nombreTaches))
        {
            printf("\nAucune tâche avec l'ID %d.\n", ID_tache);
            break;
        }

        printf("\nTâche trouvée:\n");
        printf("ID: %d\n", taches[ID_tache - 1].id);
        printf("Titre: %s", taches[ID_tache - 1].titre);
        printf("Description: %s", taches[ID_tache - 1].description);
        printf("Deadline: %d/%d/%d\n", taches[ID_tache - 1].deadline.day, taches[ID_tache - 1].deadline.month, taches[ID_tache - 1].deadline.year);
        printf("Statut: %s\n", taches[ID_tache - 1].statut);
        break;

    case 2:
        char titre[100];
        printf("Entrer le titre de la tâche à rechercher: ");
        fgets(titre, sizeof(titre), stdin);

        int found = 0;
        for (int i = 0; i < (*nombreTaches); i++)
        {
            if (strcmp(taches[i].titre, titre) == 0)
            {
                if (!found)
                {
                    printf("\nTâches trouvées:\n");
                    found = 1;
                }
                printf("ID: %d\n", taches[i].id);
                printf("Titre: %s", taches[i].titre);
                printf("Description: %s", taches[i].description);
                printf("Deadline: %d/%d/%d\n", taches[i].deadline.day, taches[i].deadline.month, taches[i].deadline.year);
                printf("Statut: %s\n", taches[i].statut);
                printf("\n");
            }
        }

        if (!found)
        {
            printf("\nAucune tâche avec le titre \"%s\".\n", titre);
        }
        break;

    default:
        printf("Choix invalide. Entrer un nombre valide.\n");
        break;
    }
}
void statistiques(struct ToDo taches[], int *nombreTaches)
{
    int tachesComplet = 0;
    int tachesIncomplet = 0;

    printf("Nombre total de tâches: %d\n", *nombreTaches);

    for (int i = 0; i < *nombreTaches; i++)
    {
        if (strcmp(taches[i].statut, "done\n") == 0)
        {
            tachesComplet++;
        }
        else
        {
            tachesIncomplet++;
        }

        // Calculer le nombre de jours restants jusqu'à la date limite
        time_t now;
        struct tm *current_time;
        time(&now);
        current_time = localtime(&now);

        int jour_courant = current_time->tm_mday;
        int mois_courant = current_time->tm_mon + 1;
        int annee_courante = current_time->tm_year + 1900;

        int jours_restants = 0;

        if (annee_courante < taches[i].deadline.year ||
            (annee_courante == taches[i].deadline.year && mois_courant < taches[i].deadline.month) ||
            (annee_courante == taches[i].deadline.year && mois_courant == taches[i].deadline.month && jour_courant < taches[i].deadline.day))
        {
            struct tm deadline_time = {0};
            deadline_time.tm_year = taches[i].deadline.year - 1900;
            deadline_time.tm_mon = taches[i].deadline.month - 1;
            deadline_time.tm_mday = taches[i].deadline.day;

            time_t deadline = mktime(&deadline_time);
            double seconds_remaining = difftime(deadline, now);
            jours_restants = seconds_remaining / (60 * 60 * 24);
        }

        printf("ID: %d\n", taches[i].id);
        printf("Titre: %s", taches[i].titre);
        printf("Description: %s", taches[i].description);
        printf("Deadline: %d/%d/%d\n", taches[i].deadline.day, taches[i].deadline.month, taches[i].deadline.year);
        printf("Statut: %s\n", taches[i].statut);
        printf("Jours restants: %d\n", jours_restants);
        printf("\n");
    }

    printf("Nombre de tâches terminées: %d\n", tachesComplet);
    printf("Nombre de tâches incomplètes: %d\n", tachesIncomplet);
}

int main()
{
    struct ToDo taches[100]; // supposant 100 est le max des taches
    int nombreTaches = 0;    // Nombre des taches actuellement stockées
    int choix;

    do
    {
        printf("\n\tGestion de Tâches ToDo\n\n");
        printf("1. Ajouter une nouvelle tâche\n");
        printf("2. Ajouter plusieurs nouvelles tâches\n");
        printf("3. Afficher la liste de toutes les tâches\n");
        printf("4. Modifier une tâche\n");
        printf("5. Supprimer une tâche par identifiant\n");
        printf("6. Rechercher les tâches\n");
        printf("7. Statistiques\n");
        printf("8. Quitter\n");
        printf("\n-----------------------\n");
        printf("Entrer votre choix: ");
        scanf("%d", &choix);
        getchar();

        switch (choix)
        {
        case 1:
            // Ajouter une nouvelle tâche
            ajouterUn(taches, &nombreTaches);
            break;
        case 2:
            // Ajouter plusieurs nouvelles tâches
            ajouterBeaucoup(taches, &nombreTaches);
            break;
        case 3:
            // Afficher la liste de toutes les tâches
            afficher(taches, &nombreTaches);
            break;
        case 4:
            // Modifier une tâche
            modifier(taches, &nombreTaches);
            break;
        case 5:
            // Supprimer une tâche par identifiant
            supprimer(taches, &nombreTaches);
            break;
        case 6:
            // Rechercher les tâches
            rechercher(taches, &nombreTaches);
            break;
        case 7:
            // Statistiques
            statistiques(taches, &nombreTaches);
            break;
        case 8:
            // Quitter
            printf("Au revoir!\n");
            break;
        default:
            printf("Choix invalide. Entrer un nombre valide.\n");
            break;
        }
    } while (choix != 8);

    return 0;
}
