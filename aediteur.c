#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "aediteur.h"


// ****************************** Constructeur *******************************

void initAEF(AEF *aef) {
    aef->nb_etats = 0;
    aef->alphabet.nb_symboles = 0;

    // Initialiser toutes les transitions à -1, indiquant qu'elles ne sont pas définies
    for (int i = 0; i < NOMBRE_ETATS; i++) {
        for (int j = 0; j < NOMBRE_SYMBOLES; j++) {
            for (int k = 0; k < NOMBRE_RESULTATS; k++) {
                aef->transitions[i][j][k] = -1;
            }
        }
    }
}

// ********************************** tools ********************************** 

// Fonction pour vérifier si un état existe dans l'automate
bool etatExiste(AEF *aef, int etat) {
    return (etat >= 0 && etat < aef->nb_etats);
}

// Fonction pour vérifier si une entrée est un nombre entier positif
bool estNombreEntierPositif(char *chaine) {
    for (int i = 0; chaine[i] != '\0'; i++) {
        if (chaine[i] < '1' || chaine[i] > '9') {
            return false;
        }
    }
    return true;
}

// Fonction pour vérifier si un symbole existe dans l'alphabet
bool symboleExiste(AEF *aef, char symbole) {
	printf("%c \n", symbole);
    for (int i = 0; i < aef->alphabet.nb_symboles; i++) {
		printf("%c \n", aef->alphabet.symboles[i]);
        if (aef->alphabet.symboles[i] == symbole) {
            return true;
        }
    }
    return false;
}

AEF copyAEF(const AEF *originalAEF) {
    AEF newAEF;

    // Copying value types and fixed-size arrays directly
    newAEF.etatInitial = originalAEF->etatInitial;
    newAEF.nb_etats = originalAEF->nb_etats;
    newAEF.alphabet = originalAEF->alphabet; // Copying the entire Alphabet struct

    // Copying fixed-size arrays
    for (int i = 0; i < NOMBRE_ETATS; i++) {
        newAEF.etatsFinaux[i] = originalAEF->etatsFinaux[i];
        for (int j = 0; j < NOMBRE_SYMBOLES; j++) {
            for (int k = 0; k < NOMBRE_RESULTATS; k++) {
                newAEF.transitions[i][j][k] = originalAEF->transitions[i][j][k];
            }
        }
    }

    return newAEF;
}

// ********************************** Méthodes ******************************

// Fonction pour saisir un symbole existant dans l'alphabet
char saisirSymboleExistant(AEF *aef) {
    char symbole;
    do {
        printf("Entrez un symbole existant : ");
        while ((getchar()) != '\n'); // Nettoyage du tampon d'entrée
        scanf("%c", &symbole);

        if (symboleExiste(aef, symbole)) {
            return symbole;
        } else {
            printf("Erreur : Le symbole n'existe pas dans l'alphabet. Veuillez entrer un symbole existant.\n");
        }
    } while (true);
}


// Fonction pour saisir un nombre entier positif
int saisirNombreEntierPositif() {
    char input[20];
    int nombre;
    do {
        printf("Entrez un nombre entier positif : ");
        scanf("%s", input);

        if (!estNombreEntierPositif(input)) {
            printf("Vous avez entré une valeur négative \n");
        } else {
            nombre = atoi(input);
            return nombre;
        }
    } while (true);
}


// Fonction pour saisir un symbole
char saisirSymbole() {
    char symbole;
    do {
        printf("Entrez un symbole : ");
        symbole = getchar();  // on utilise getchar() pour lire un caractère
        while ((getchar()) != '\n');  // Nettoyage du tampon d'entrée
        //scanf("%c", &symbole);

        // Affichage pour le débogage
        printf("Symbole saisi : %c\n", symbole);  

        if ((symbole >= 'a' && symbole <= 'z') || (symbole >= 'A' && symbole <= 'Z')) {
            return symbole;
        } else {
            printf("Entrée invalide. Veuillez entrer une lettre de l'alphabet.\n");
        }
    } while (true);
    return symbole;

}


// Fonction pour saisir un état existant dans l'automate
int saisirEtatExistant(AEF *aef) {
    int etat;
    do {
        printf("Entrez un état existant : ");
        scanf("%d", &etat);

        if (etatExiste(aef, etat)) {
            return etat;
        } else {
            printf("Erreur : L'état n'existe pas \n");
        }
    } while (true);
}

// Fonction pour saisir une transition en s'assurant que l'état de destination est valide
void saisirTransitions(AEF *aef, int etatSource, char symbole) {
    int indexSymbole = symbole - 'a';
    printf("Transition de l'état %d avec le symbole %c :\n", etatSource, symbole);

    for (int i = 0; i < NOMBRE_RESULTATS; i++) {
        printf("Entrez l'état de destination %d (-1 pour ignorer cette destination) : ", i + 1);
        int etatDest;
        scanf("%d", &etatDest);

        // Gérer l'entrée -1 pour ignorer cette destination sans sortir de la saisie
        if (etatDest == -1) {
            aef->transitions[etatSource][indexSymbole][i] = -1;
            continue;  // Continue avec la prochaine destination possible
        }

        // Vérifier si l'état de destination existe
        if (etatExiste(aef, etatDest)) {
            aef->transitions[etatSource][indexSymbole][i] = etatDest;
        } else {
            printf("Erreur : L'état de destination n'existe pas. Veuillez entrer un état existant.\n");
            i--; // Permettre à l'utilisateur de saisir à nouveau
        }
    }
}

void saisirAEF(AEF *aef) {
    printf("Entrez le nombre d'états : ");
    scanf("%d", &aef->nb_etats);

    printf("Entrez le nombre de symboles : ");
    scanf("%d", &aef->alphabet.nb_symboles);

    printf("Saisir les symboles de l'alphabet :\n");
    for (int i = 0; i < aef->alphabet.nb_symboles; i++) {
        scanf(" %c", &aef->alphabet.symboles[i]);
    }

    aef->etatInitial = 0; // L'état initial est défini à 0 par convention

    bool auMoinsUnEtatFinal = false;
    do {
        auMoinsUnEtatFinal = false;
        for (int i = 0; i < aef->nb_etats; i++) {
            aef->etatsFinaux[i] = true; // Initialement, on suppose que tous les états sont finaux
            for (int j = 0; j < aef->alphabet.nb_symboles; j++) {
                for (int k = 0; k < NOMBRE_RESULTATS; k++) {
                    printf("Transition de l'état %d avec le symbole %c, destination %d (-1 pour aucune) : ", i, aef->alphabet.symboles[j], k + 1);
                    scanf("%d", &aef->transitions[i][j][k]);
                    if (aef->transitions[i][j][k] != -1 && aef->transitions[i][j][k] != i) {
                        aef->etatsFinaux[i] = false;
                    }
                }
            }
            auMoinsUnEtatFinal |= aef->etatsFinaux[i];
        }

        // Vérifie qu'il y a au moins un état final
        if (!auMoinsUnEtatFinal) {
            printf("Aucun état final n'a été défini. Veuillez revoir les transitions pour définir au moins un état final.\n");
        }
    } while (!auMoinsUnEtatFinal);
}


void afficherAEF(AEF aef) {
    printf("Nombre d'états : %d\n", aef.nb_etats);
    printf("Alphabet : ");
    for (int i = 0; i < aef.alphabet.nb_symboles; i++) {
        printf("%c ", aef.alphabet.symboles[i]);
    }
    printf("\n");

    printf("Transitions :\n");
    for (int i = 0; i < aef.nb_etats; i++) {
        for (int j = 0; j < aef.alphabet.nb_symboles; j++) {
            printf("(q%d, %c) --> ", i, aef.alphabet.symboles[j]);
            for (int k = 0; k < NOMBRE_RESULTATS; k++) {
                int dest = aef.transitions[i][j][k];
                if (dest != -1) {
                    printf("q%d", dest);
                    if (k < NOMBRE_RESULTATS - 1 && aef.transitions[i][j][k + 1] != -1) {
                        printf(", ");
                    }
                }
            }
            printf("\n");
        }
    }
}

void modifierAEF(AEF *aef) {
    // Permettre à l'utilisateur de modifier une transition spécifique
    // Après modification, mettre à jour l'état final de l'état source de la transition

    int etatSource, symboleIndex, resultatIndex, etatDest;
    printf("Entrez l'état source, l'index du symbole, l'index du résultat et l'état de destination :\n");
    scanf("%d %d %d %d", &etatSource, &symboleIndex, &resultatIndex, &etatDest);

    aef->transitions[etatSource][symboleIndex][resultatIndex] = etatDest;

    // Mettre à jour l'état final de l'état source
    aef->etatsFinaux[etatSource] = true;
    for (int j = 0; j < aef->alphabet.nb_symboles; j++) {
        for (int k = 0; k < NOMBRE_RESULTATS; k++) {
            if (aef->transitions[etatSource][j][k] != -1 && aef->transitions[etatSource][j][k] != etatSource) {
                aef->etatsFinaux[etatSource] = false;
                break;
            }
        }
    }
}



void chargerAEF(AEF *aef, const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    fscanf(fichier, "État initial: %d\n", &aef->etatInitial);
    for (int i = 0; i < NOMBRE_ETATS; i++) {
        int estFinal;
        fscanf(fichier, "%d", &estFinal);
        aef->etatsFinaux[i] = estFinal != 0;
    }
    fgetc(fichier); // Pour lire le caractère de nouvelle ligne

    int etat;
    char symbole;
    int destination;
    while (fscanf(fichier, "Transition: État %d, Symbole %c, Destination %d\n", &etat, &symbole, &destination) == 3) {
        // Trouver l'index du symbole dans l'alphabet
        int indexSymbole = -1;
        for (int i = 0; i < aef->alphabet.nb_symboles; i++) {
            if (aef->alphabet.symboles[i] == symbole) {
                indexSymbole = i;
                break;
            }
        }
        if (indexSymbole != -1) {
            for (int k = 0; k < NOMBRE_RESULTATS; k++) {
                if (aef->transitions[etat][indexSymbole][k] == -1) {
                    aef->transitions[etat][indexSymbole][k] = destination;
                    break;
                }
            }
        }
    }

    fclose(fichier);
}


void sauvegarderAEF(AEF aef, const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "w");
    if (!fichier) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    fprintf(fichier, "État initial: %d\n", aef.etatInitial);
    fprintf(fichier, "États finaux: ");
    
    for (int i = 0; i < NOMBRE_ETATS; i++) {
        fprintf(fichier, "%d ", aef.etatsFinaux[i] ? 1 : 0);
    }
    fprintf(fichier, "\n");

    for (int i = 0; i < aef.nb_etats; i++) {
        for (int j = 0; j < aef.alphabet.nb_symboles; j++) {
            for (int k = 0; k < NOMBRE_RESULTATS; k++) {
                if (aef.transitions[i][j][k] != -1) {
                    fprintf(fichier, "Transition: État %d, Symbole %c, Destination %d\n", i, aef.alphabet.symboles[j], aef.transitions[i][j][k]);
                }
            }
        }
    }

    fclose(fichier);
}


void supprimerAEF(AEF *aef) {
	printf("Supprimer un état :\n");
	
    int etatASupprimer = saisirEtatExistant(aef);

    // Décaler les transitions pour les états suivant l'état supprimé
    for (int i = etatASupprimer; i < aef->nb_etats - 1; i++) {
        for (int j = 0; j < aef->alphabet.nb_symboles; j++) {
            for (int k = 0; k < NOMBRE_RESULTATS; k++) {
                aef->transitions[i][j][k] = aef->transitions[i + 1][j][k];
            }
        }
    }

    // Mise à jour des références aux états dans les transitions
    for (int i = 0; i < aef->nb_etats; i++) {
        for (int j = 0; j < aef->alphabet.nb_symboles; j++) {
            for (int k = 0; k < NOMBRE_RESULTATS; k++) {
                if (aef->transitions[i][j][k] > etatASupprimer) {
                    aef->transitions[i][j][k]--;
                }
            }
        }
    }

    // Réduire le nombre d'états de l'automate
    aef->nb_etats--;

    printf("État %d supprimé.\n", etatASupprimer);
}

// ********************************** Question 2 ****************************** 

bool estReconnuParAEF(AEF *aef, const char *mot) {
    int etatActuel = aef->etatInitial;
    int longueurMot = strlen(mot);

    for (int i = 0; i < longueurMot; i++) {
        char symboleActuel = mot[i];
        bool transitionTrouvee = false;

        // Trouver l'index du symbole dans l'alphabet
        int indexSymbole = -1;
        for (int j = 0; j < aef->alphabet.nb_symboles; j++) {
            if (aef->alphabet.symboles[j] == symboleActuel) {
                indexSymbole = j;
                break;
            }
        }

        if (indexSymbole == -1) {
            return false; // Symbole non trouvé dans l'alphabet
        }

        // Vérifier les transitions pour le symbole actuel
        for (int k = 0; k < NOMBRE_RESULTATS; k++) {
            int etatSuivant = aef->transitions[etatActuel][indexSymbole][k];
            if (etatSuivant != -1) {
                etatActuel = etatSuivant;
                transitionTrouvee = true;
                break; // Transition trouvée, passer au prochain symbole du mot
            }
        }

        if (!transitionTrouvee) {
            return false; // Aucune transition valide pour ce symbole
        }
    }

    // Vérifier si l'état final atteint est un état acceptant
    return aef->etatsFinaux[etatActuel];
}



// ********************************** Question 3 ***********************************


bool estAEFComplet(AEF *aef) {
    for (int i = 0; i < aef->nb_etats; i++) {
        for (int j = 0; j < aef->alphabet.nb_symboles; j++) {
            bool transitionTrouvee = false;
            for (int k = 0; k < NOMBRE_RESULTATS; k++) {
                if (aef->transitions[i][j][k] != -1) {
                    transitionTrouvee = true;
                    break;
                }
            }
            if (!transitionTrouvee) {
                return false; // Si aucune transition n'est trouvée pour un symbole, l'AEF n'est pas complet
            }
        }
    }
    return true; 
}


// ********************************** Question 4 ***********************************


AEF rendreAEFComplet(AEF *aef) {
	AEF nouvelAEF = copyAEF(aef); // Copie de l'AEF original
	
	if (estAEFComplet(&nouvelAEF)){
		return nouvelAEF; 
	}
	
	int etatPhi = nouvelAEF.nb_etats; // Ajout de l'état phi comme nouvel état
	nouvelAEF.nb_etats += 1;

	// S'assurer que l'état phi boucle sur lui-même pour chaque symbole
	for (int j = 0; j < nouvelAEF.alphabet.nb_symboles; j++) {
		for (int k = 0; k < NOMBRE_RESULTATS; k++) {
			nouvelAEF.transitions[etatPhi][j][k] = etatPhi;
		}
	}

	// Vérifier chaque état pour chaque symbole, et ajouter une transition vers phi si nécessaire
	for (int i = 0; i < etatPhi; i++) { // Ne pas inclure l'état phi lui-même
		for (int j = 0; j < nouvelAEF.alphabet.nb_symboles; j++) {
			bool transitionTrouvee = false;
			for (int k = 0; k < NOMBRE_RESULTATS; k++) {
				if (nouvelAEF.transitions[i][j][k] != -1) {
					transitionTrouvee = true;
					break;
				}
			}
			if (!transitionTrouvee) {
				nouvelAEF.transitions[i][j][0] = etatPhi; // Ajouter une transition vers phi
			}
		}
	}
	
	return nouvelAEF;
}


// ********************************** Question 5 ***********************************

bool estAEFDeterministe(AEF *aef) {
    for (int i = 0; i < aef->nb_etats; i++) {
        for (int j = 0; j < aef->alphabet.nb_symboles; j++) {
            int transitionCompteur = 0;
            for (int k = 0; k < NOMBRE_RESULTATS; k++) {
                if (aef->transitions[i][j][k] != -1) {
                    transitionCompteur++;
                }
                if (transitionCompteur > 1) {
                    return false; // Plus d'une transition pour un symbole dans un état, donc non déterministe
                }
            }
        }
    }
    return true; // Aucun état n'a plus d'une transition pour un symbole donné
}


// ********************************** Question 6 ***********************************


AEF rendreAEFDeterministe(AEF *aef) {
	AEF aefDeterministe = copyAEF(aef); // Copie de l'AEF original
	
	if(estAEFDeterministe(&aefDeterministe)){
		return aefDeterministe;
	}
    
    // Tableau pour suivre les nouveaux états créés
    bool nouveauxEtats[1 << NOMBRE_ETATS] = {false};
    int nouvelIndiceEtat = 0;
    
    // Traiter l'état initial
    int etatInitial = (1 << aef->etatInitial);
    nouveauxEtats[etatInitial] = true;
    aefDeterministe.etatInitial = nouvelIndiceEtat++;

    // Boucle principale pour créer de nouveaux états
    for (int i = 0; i < (1 << NOMBRE_ETATS); i++) {
        if (!nouveauxEtats[i]){
			continue;
		}

        // Parcourir chaque symbole de l'alphabet
        for (int symbole = 0; symbole < aef->alphabet.nb_symboles; symbole++) {
            int nouvelEtat = 0;
            bool estFinal = false;

            // Parcourir chaque état possible
            for (int etat = 0; etat < NOMBRE_ETATS; etat++) {
                if (i & (1 << etat)) {
                    for (int k = 0; k < NOMBRE_RESULTATS; k++) {
                        int transition = aef->transitions[etat][symbole][k];
                        if (transition != -1) {
                            nouvelEtat |= (1 << transition);
                            estFinal |= aef->etatsFinaux[transition];
                        }
                    }
                }
            }

            if (!nouveauxEtats[nouvelEtat]) {
                nouveauxEtats[nouvelEtat] = true;
                aefDeterministe.transitions[i][symbole][0] = nouvelIndiceEtat++;
            } else {
                aefDeterministe.transitions[i][symbole][0] = nouvelEtat;
            }
            aefDeterministe.etatsFinaux[i] = estFinal;
        }
    }

    aefDeterministe.nb_etats = nouvelIndiceEtat;
    return aefDeterministe;
}


// ********************************** Question 7 ***********************************

AEF complementAEF(AEF *aefOriginal) {
    AEF aefComplement = copyAEF(aefOriginal); // Copie de l'AEF original

    // Inverser les états finaux et non finaux
    for (int i = 0; i < aefComplement.nb_etats; i++) {
        aefComplement.etatsFinaux[i] = !aefComplement.etatsFinaux[i];
    }
    return aefComplement;
}


AEF miroirAEF(AEF *aefOriginal) {
	AEF aefMiroir;
	initAEF(&aefMiroir);

    // Copier l'alphabet
    aefMiroir.alphabet = aefOriginal->alphabet;
    aefMiroir.nb_etats = aefOriginal->nb_etats;

    // Inverser les transitions
    for (int etat = 0; etat < aefOriginal->nb_etats; etat++) {
        for (int symbole = 0; symbole < aefOriginal->alphabet.nb_symboles; symbole++) {
            for (int k = 0; k < NOMBRE_RESULTATS; k++) {
                int etatCible = aefOriginal->transitions[etat][symbole][k];
                if (etatCible != -1) {
                    aefMiroir.transitions[etatCible][symbole][0] = etat;
                }
            }
        }
    }

    // Inverser les états finaux et l'état initial
    for (int i = 0; i < aefOriginal->nb_etats; i++) {
        aefMiroir.etatsFinaux[i] = false;
    }
    aefMiroir.etatsFinaux[aefOriginal->etatInitial] = true;
    aefMiroir.etatInitial = -1; // Un AEF miroir peut avoir plusieurs états initiaux

    // Les états finaux de l'AEF original deviennent les états initiaux dans l'AEF miroir
    for (int i = 0; i < aefOriginal->nb_etats; i++) {
        if (aefOriginal->etatsFinaux[i]) {
            aefMiroir.etatInitial = i; // Dans le cas simple où il n'y a qu'un seul état final
            break;
        }
    }
    
    return aefMiroir;
}


AEF produitAEFs(AEF *aefA, AEF *aefB) {
	AEF aefProduit;
    initAEF(&aefProduit);

    // Copier l'alphabet (supposons que les deux AEFs ont le même alphabet)
    aefProduit.alphabet = aefA->alphabet;

    // Calculer les états et transitions du produit
    for (int etatA = 0; etatA < aefA->nb_etats; etatA++) {
        for (int etatB = 0; etatB < aefB->nb_etats; etatB++) {
            int etatProduit = etatA * aefB->nb_etats + etatB;

            // Déterminer si l'état du produit est final
            aefProduit.etatsFinaux[etatProduit] = aefA->etatsFinaux[etatA] && aefB->etatsFinaux[etatB];

            // Créer les transitions pour l'état du produit
            for (int symbole = 0; symbole < aefProduit.alphabet.nb_symboles; symbole++) {
                int transitionA = aefA->transitions[etatA][symbole][0];
                int transitionB = aefB->transitions[etatB][symbole][0];
                
                if (transitionA != -1 && transitionB != -1) {
                    aefProduit.transitions[etatProduit][symbole][0] = transitionA * aefB->nb_etats + transitionB;
                }
            }
        }
    }

    // Définir l'état initial et le nombre d'états de l'AEF produit
    aefProduit.etatInitial = aefA->etatInitial * aefB->nb_etats + aefB->etatInitial;
    aefProduit.nb_etats = aefA->nb_etats * aefB->nb_etats;
    
    return aefProduit;
}


AEF concatenationAEFs(AEF *aefA, AEF *aefB) {
	AEF aefConcatenation;
    initAEF(&aefConcatenation);

    // Copier l'alphabet (supposons que les deux AEFs ont le même alphabet)
    aefConcatenation.alphabet = aefA->alphabet;

    // Ajouter les états et transitions de A
    for (int etatA = 0; etatA < aefA->nb_etats; etatA++) {
        for (int symbole = 0; symbole < aefA->alphabet.nb_symboles; symbole++) {
            aefConcatenation.transitions[etatA][symbole][0] = aefA->transitions[etatA][symbole][0];
        }
    }

    // Ajouter les états et transitions de B, en décalant les indices des états
    int decalage = aefA->nb_etats;
    for (int etatB = 0; etatB < aefB->nb_etats; etatB++) {
        for (int symbole = 0; symbole < aefB->alphabet.nb_symboles; symbole++) {
            if (aefB->transitions[etatB][symbole][0] != -1) {
                aefConcatenation.transitions[etatB + decalage][symbole][0] = aefB->transitions[etatB][symbole][0] + decalage;
            }
        }
        aefConcatenation.etatsFinaux[etatB + decalage] = aefB->etatsFinaux[etatB];
    }

    // Ajouter des transitions des états finaux de A vers l'état initial de B
    for (int i = 0; i < aefA->nb_etats; i++) {
        if (aefA->etatsFinaux[i]) {
            for (int symbole = 0; symbole < aefA->alphabet.nb_symboles; symbole++) {
                aefConcatenation.transitions[i][symbole][0] = aefB->etatInitial + decalage;
            }
        }
    }

    // Définir l'état initial et le nombre d'états de la concaténation
    aefConcatenation.etatInitial = aefA->etatInitial;
    aefConcatenation.nb_etats = aefA->nb_etats + aefB->nb_etats;
    
    return aefConcatenation;
}



// ********************************** Question 8 ***********************************

void extraireExpressionReguliere(AEF *aef, char *expressionReguliere) {
    bool visited[NOMBRE_ETATS] = {false};
    strcpy(expressionReguliere, "");

    for (int etat = 0; etat < aef->nb_etats; etat++) {
        if (!visited[etat] && aef->etatsFinaux[etat]) {
            char tempExp[NOMBRE_SYMBOLES * NOMBRE_ETATS] = "";
            for (int symbole = 0; symbole < aef->alphabet.nb_symboles; symbole++) {
                for (int k = 0; k < NOMBRE_RESULTATS; k++) {
                    int dest = aef->transitions[etat][symbole][k];
                    if (dest != -1) {
                        visited[dest] = true;
                        char symboleStr[2] = {aef->alphabet.symboles[symbole], '\0'};
                        strcat(tempExp, symboleStr);
                        if (aef->etatsFinaux[dest]) {
                            strcat(expressionReguliere, tempExp);
                            strcat(expressionReguliere, "|");
                        }
                    }
                }
            }
        }
    }
    
    // Supprimer le dernier caractère '|' si présent
    size_t len = strlen(expressionReguliere);
    if (len > 0 && expressionReguliere[len - 1] == '|') {
        expressionReguliere[len - 1] = '\0';
    }
}


// ********************************** Question 9 ***********************************

void trouverLangage(AEF *aef, int etatCourant, char *langage, char *motCourant, bool *visites) {
    if (aef->etatsFinaux[etatCourant]) {
        strcat(langage, motCourant);
        strcat(langage, "\n");
    }

    for (int symbole = 0; symbole < aef->alphabet.nb_symboles; symbole++) {
        int etatSuivant = aef->transitions[etatCourant][symbole][0];
        if (etatSuivant != -1) {
            char nouveauMot[100];
            strcpy(nouveauMot, motCourant);
            strncat(nouveauMot, &aef->alphabet.symboles[symbole], 1);

            if (etatCourant == etatSuivant) {
                // Gérer la répétition de symboles
                strcat(nouveauMot, "*");
            }

            if (!visites[etatSuivant]) {
                visites[etatSuivant] = true;
                trouverLangage(aef, etatSuivant, langage, nouveauMot, visites);
                visites[etatSuivant] = false; // Pour permettre d'autres chemins
            }
        }
    }
}

void determinerLangageReconnu(AEF *aef, char *langage) {
    bool visites[NOMBRE_ETATS] = {false};
    char motCourant[100] = "";

    trouverLangage(aef, aef->etatInitial, langage, motCourant, visites);
}



// ********************************** Question 10 ***********************************

bool sontEquivalents(AEF *aef1, AEF *aef2) {
    // Cette fonction suppose que aef1 et aef2 sont déjà des AFD minimaux

    if (aef1->nb_etats != aef2->nb_etats) {
        return false; // Les automates avec un nombre différent d'états ne peuvent pas être équivalents
    }

    for (int i = 0; i < aef1->nb_etats; i++) {
        if (aef1->etatsFinaux[i] != aef2->etatsFinaux[i]) {
            return false; // Les états finaux doivent correspondre
        }
    }

    for (int i = 0; i < aef1->nb_etats; i++) {
        for (int j = 0; j < aef1->alphabet.nb_symboles; j++) {
            if (aef1->transitions[i][j][0] != aef2->transitions[i][j][0]) {
                return false; // Les transitions pour chaque symbole doivent correspondre
            }
        }
    }

    return true; // Les automates sont équivalents
}


// ********************************** Question 11 ***********************************


void marquerEtatsAccessibles(AEF *aef, int etatCourant, bool etatsAccessibles[]) {
    if (etatsAccessibles[etatCourant]) {
        return; // État déjà visité
    }

    etatsAccessibles[etatCourant] = true;

    for (int symbole = 0; symbole < aef->alphabet.nb_symboles; symbole++) {
        for (int k = 0; k < NOMBRE_RESULTATS; k++) {
            int etatSuivant = aef->transitions[etatCourant][symbole][k];
            if (etatSuivant != -1) {
                marquerEtatsAccessibles(aef, etatSuivant, etatsAccessibles);
            }
        }
    }
}

void marquerEtatsCoAccessibles(AEF *aef, int etatCourant, bool etatsCoAccessibles[]) {
    if (etatsCoAccessibles[etatCourant]) {
        return; // État déjà visité
    }

    etatsCoAccessibles[etatCourant] = true;

    for (int i = 0; i < aef->nb_etats; i++) {
        for (int symbole = 0; symbole < aef->alphabet.nb_symboles; symbole++) {
            for (int k = 0; k < NOMBRE_RESULTATS; k++) {
                if (aef->transitions[i][symbole][k] == etatCourant) {
                    marquerEtatsCoAccessibles(aef, i, etatsCoAccessibles);
                }
            }
        }
    }
}

AEF rendreAutomateEmonde(AEF *aef) {
    bool etatsAccessibles[NOMBRE_ETATS] = {false};
    bool etatsCoAccessibles[NOMBRE_ETATS] = {false};

    marquerEtatsAccessibles(aef, aef->etatInitial, etatsAccessibles);
    for (int i = 0; i < aef->nb_etats; i++) {
        if (aef->etatsFinaux[i]) {
            marquerEtatsCoAccessibles(aef, i, etatsCoAccessibles);
        }
    }

    // Supprimer les états qui ne sont ni accessibles ni co-accessibles
    bool etatsASupprimer[NOMBRE_ETATS] = {false};
    for (int i = 0; i < aef->nb_etats; i++) {
        etatsASupprimer[i] = !(etatsAccessibles[i] && etatsCoAccessibles[i]);
    }

    // Créer un nouvel automate sans les états à supprimer
    AEF nouvelAEF;
    int nouvelIndex[NOMBRE_ETATS];
    int index = 0;
    for (int i = 0; i < aef->nb_etats; i++) {
        if (!etatsASupprimer[i]) {
            nouvelIndex[i] = index;
            nouvelAEF.etatsFinaux[index] = aef->etatsFinaux[i];
            index++;
        } else {
            nouvelIndex[i] = -1;
        }
    }
    nouvelAEF.nb_etats = index;
    nouvelAEF.etatInitial = nouvelIndex[aef->etatInitial];
    nouvelAEF.alphabet = aef->alphabet;

    // Recopier les transitions valides
    for (int i = 0; i < aef->nb_etats; i++) {
        if (!etatsASupprimer[i]) {
            for (int symbole = 0; symbole < aef->alphabet.nb_symboles; symbole++) {
                for (int k = 0; k < NOMBRE_RESULTATS; k++) {
                    int etatSuivant = aef->transitions[i][symbole][k];
                    if (etatSuivant != -1 && !etatsASupprimer[etatSuivant]) {
                        nouvelAEF.transitions[nouvelIndex[i]][symbole][k] = nouvelIndex[etatSuivant];
                    } else {
                        nouvelAEF.transitions[nouvelIndex[i]][symbole][k] = -1;
                    }
                }
            }
        }
    }

    return nouvelAEF;
}


// ********************************** Question 12 ***********************************

AEF supprimerEtatsInaccessibles(AEF *aef) {
    bool etatsAccessibles[NOMBRE_ETATS] = {false};

    // Marquer tous les états accessibles à partir de l'état initial
    marquerEtatsAccessibles(aef, aef->etatInitial, etatsAccessibles);

    // Compter le nombre d'états accessibles
    int nbEtatsAccessibles = 0;
    for (int i = 0; i < aef->nb_etats; i++) {
        if (etatsAccessibles[i]) {
            nbEtatsAccessibles++;
        }
    }

    // Créer une nouvelle structure AEF pour les états accessibles
    AEF nouvelAEF;
    nouvelAEF.nb_etats = nbEtatsAccessibles;
    nouvelAEF.etatInitial = aef->etatInitial;
    nouvelAEF.alphabet = aef->alphabet;
    
    int indexNouvelEtat[NOMBRE_ETATS];
    for (int i = 0, newIndex = 0; i < aef->nb_etats; i++) {
        if (etatsAccessibles[i]) {
            indexNouvelEtat[i] = newIndex++;
            nouvelAEF.etatsFinaux[newIndex - 1] = aef->etatsFinaux[i];
        } else {
            indexNouvelEtat[i] = -1;
        }
    }

    // Recopier les transitions pour les états accessibles
    for (int i = 0; i < aef->nb_etats; i++) {
        if (etatsAccessibles[i]) {
            for (int j = 0; j < aef->alphabet.nb_symboles; j++) {
                int etatSuivant = aef->transitions[i][j][0];
                if (etatSuivant != -1) {
                    nouvelAEF.transitions[indexNouvelEtat[i]][j][0] = indexNouvelEtat[etatSuivant];
                } else {
                    nouvelAEF.transitions[indexNouvelEtat[i]][j][0] = -1;
                }
            }
        }
    }

    return nouvelAEF;
}


AEF fusionnerEtatsEquivalents(AEF *aef) {
    // Cette fonction est une simplification et peut ne pas être complète pour tous les cas.
    // L'idée ici est de fusionner les états qui ont des transitions identiques et qui sont tous les deux soit finaux, soit non finaux.

    bool etatsFusionnes[NOMBRE_ETATS] = {false};

    for (int i = 0; i < aef->nb_etats; i++) {
        for (int j = i + 1; j < aef->nb_etats; j++) {
            if (aef->etatsFinaux[i] == aef->etatsFinaux[j] && !etatsFusionnes[j]) {
                bool equivalent = true;
                for (int symbole = 0; symbole < aef->alphabet.nb_symboles; symbole++) {
                    if (aef->transitions[i][symbole][0] != aef->transitions[j][symbole][0]) {
                        equivalent = false;
                        break;
                    }
                }
                if (equivalent) {
                    etatsFusionnes[j] = true;
                    // Rediriger toutes les transitions de j vers i
                    for (int k = 0; k < aef->nb_etats; k++) {
                        for (int symbole = 0; symbole < aef->alphabet.nb_symboles; symbole++) {
                            if (aef->transitions[k][symbole][0] == j) {
                                aef->transitions[k][symbole][0] = i;
                            }
                        }
                    }
                }
            }
        }
    }

	int nouvelIndex[NOMBRE_ETATS];
	int index = 0;
	for (int i = 0; i < aef->nb_etats; i++) {
		if (!etatsFusionnes[i]) {
			nouvelIndex[i] = index++;
		} else {
			nouvelIndex[i] = -1; // Marquer l'état comme fusionné
		}
	}

	// Créer un nouvel automate pour les états restants
	AEF nouvelAEF;
	nouvelAEF.nb_etats = index;
	nouvelAEF.etatInitial = nouvelIndex[aef->etatInitial];
	nouvelAEF.alphabet = aef->alphabet;

	// Copier et renuméroter les transitions
	for (int i = 0; i < aef->nb_etats; i++) {
		if (nouvelIndex[i] != -1) {
			nouvelAEF.etatsFinaux[nouvelIndex[i]] = aef->etatsFinaux[i];
			for (int symbole = 0; symbole < aef->alphabet.nb_symboles; symbole++) {
				for (int k = 0; k < NOMBRE_RESULTATS; k++) {
					int etatSuivant = aef->transitions[i][symbole][k];
					if (etatSuivant != -1 && nouvelIndex[etatSuivant] != -1) {
						nouvelAEF.transitions[nouvelIndex[i]][symbole][k] = nouvelIndex[etatSuivant];
					} else {
						nouvelAEF.transitions[nouvelIndex[i]][symbole][k] = -1;
					}
				}
			}
		}
	}
	
	return nouvelAEF;
}

AEF rendreAutomateMinimal(AEF *aef) {
    AEF tempAEF = supprimerEtatsInaccessibles(aef);
    return fusionnerEtatsEquivalents(&tempAEF);
}

// ****************************************************** fonctions de tests **********************************************************************************

void testEstReconnuParAEF(AEF *aef, const char *mot) {
    if (estReconnuParAEF(aef, mot)) {
        printf("Le mot '%s' est reconnu par l'automate.\n", mot);
    } else {
        printf("Le mot '%s' n'est pas reconnu par l'automate.\n", mot);
    }
}

void testEstAEFComplet(AEF *aef) {
    if (estAEFComplet(aef)) {
        printf("L'automate est complet.\n");
    } else {
        printf("L'automate n'est pas complet.\n");
    }
}

void testEstAEFDeterministe(AEF *aef) {
    if (estAEFDeterministe(aef)) {
        printf("L'automate est deterministe.\n");
    } else {
        printf("L'automate n'est pas deterministe.\n");
    }
}

void testRendreAEFComplet(AEF *aef) {
    AEF result = rendreAEFComplet(aef);
    printf("L'automate complet : \n");
    afficherAEF(result);
}

void testRendreAEFDeterministe(AEF *aefNonDeterministe) {
    AEF aefDeterministe;
    initAEF(&aefDeterministe);

    AEF result = rendreAEFDeterministe(aefNonDeterministe);
    printf("L'automate déterministe : \n");
    afficherAEF(result);
}

void testComplementAEF(AEF *aefOriginal) {
    AEF aefComplement;
    initAEF(&aefComplement); // Initialize the complement AEF

    AEF result = complementAEF(aefOriginal);
    printf("Le complément de l'automate : \n");
    afficherAEF(result);
}

void testMiroirAEF(AEF *aefOriginal) {
    AEF aefMiroir;
    initAEF(&aefMiroir); // Initialize the mirror AEF

    AEF result = miroirAEF(aefOriginal);
    printf("L'automate miroir : \n");
    afficherAEF(result);
}

void testProduitAEFs(AEF *aefA, AEF *aefB) {
    AEF aefProduit;
    initAEF(&aefProduit); // Initialize the product AEF

    AEF result = produitAEFs(aefA, aefB);
    printf("Le produit des automates : \n");
    afficherAEF(result);
}

void testConcatenationAEFs(AEF *aefA, AEF *aefB) {
    AEF aefConcatenation;
    initAEF(&aefConcatenation); // Initialize the concatenation AEF

    AEF result = concatenationAEFs(aefA, aefB);
    printf("La concaténation des automates: \n");
    afficherAEF(result);
}

void testExtraireExpressionReguliere(AEF *aef) {
    char expressionReguliere[100]; 
    extraireExpressionReguliere(aef, expressionReguliere);
    printf("Expression régulière extraite : %s\n", expressionReguliere);
}

void testTrouverLangage(AEF *aef) {
    char langage[100]; 
    trouverLangage(aef, aef->etatInitial, langage, "", NULL);
    printf("Langage trouvé : %s\n", langage);
}

void testDeterminerLangageReconnu(AEF *aef) {
    char langage[100]; 
    determinerLangageReconnu(aef, langage);
    printf("Langage reconnu : %s\n", langage);
}


void testSontEquivalents(AEF *aef1, AEF *aef2) {
    if (sontEquivalents(aef1, aef2)) {
        printf("Les automates sont équivalents.\n");
    } else {
        printf("Les automates ne sont pas équivalents.\n");
    }
}

void testRendreAutomateEmonde(AEF *aef) {
    AEF result = rendreAutomateEmonde(aef);
    printf("L'automate émondé : \n");
    afficherAEF(result);
}

void testRendreAutomateMinimal(AEF *aef) {
	AEF result = rendreAutomateMinimal(aef);
	printf("L'automate minimal : \n");
    afficherAEF(result);
}


// ************************************************************** main *****************************************************************************************

int main() {
    AEF monAEF;
    const char *mot = "bab";
    initAEF(&monAEF);

    saisirAEF(&monAEF);
    afficherAEF(monAEF);
    sauvegarderAEF(monAEF, "mon_aef.txt");
    
    AEF aefA, aefB;
    initAEF(&aefA);
    initAEF(&aefB);
	
	testEstAEFDeterministe(&monAEF);
	testEstAEFComplet(&monAEF);
	testEstReconnuParAEF(&monAEF, mot);
	testRendreAEFDeterministe(&monAEF);
	testRendreAEFComplet(&monAEF);
    testComplementAEF(&monAEF);
    testMiroirAEF(&monAEF);
    testExtraireExpressionReguliere(&monAEF);
    testTrouverLangage(&monAEF);
    testDeterminerLangageReconnu(&monAEF);
	testRendreAutomateEmonde(&monAEF);
	testRendreAutomateMinimal(&monAEF);
	
	saisirAEF(&aefA);
    afficherAEF(aefA);
	saisirAEF(&aefB);
    afficherAEF(aefB);
	
	testProduitAEFs(&aefA, &aefB);
	testSontEquivalents(&aefA, &aefB);
    testConcatenationAEFs(&aefA, &aefB);

    return 0;
}
