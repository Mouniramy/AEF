#ifndef AEDITEUR_H
#define AEDITEUR_H

#define NOMBRE_ETATS 10
#define NOMBRE_SYMBOLES 10
#define NOMBRE_RESULTATS 2



typedef struct {
    char symboles[NOMBRE_SYMBOLES];
    int nb_symboles;
} Alphabet;

typedef struct {
    int transitions[NOMBRE_ETATS][NOMBRE_SYMBOLES][NOMBRE_RESULTATS];
    int etatInitial;
    bool etatsFinaux[NOMBRE_ETATS];
    int nb_etats;
    Alphabet alphabet;               
} AEF;


void initAEF(AEF *aef);
void saisirAEF(AEF *aef);
void afficherAEF(AEF aef);
void modifierAEF(AEF *aef);
void supprimerAEF(AEF *aef);
void chargerAEF(AEF *aef, const char *nom_fichier);


bool estAEFComplet(AEF *aef);
AEF rendreAEFComplet(AEF *aef);
AEF miroirAEF(AEF *aefOriginal);
bool estAEFDeterministe(AEF *aef);
AEF rendreAutomateEmonde(AEF *aef);
AEF complementAEF(AEF *aefOriginal);
AEF rendreAutomateMinimal(AEF *aef);
AEF produitAEFs(AEF *aefA, AEF *aefB);
AEF fusionnerEtatsEquivalents(AEF *aef);
AEF supprimerEtatsInaccessibles(AEF *aef);
bool sontEquivalents(AEF *aef1, AEF *aef2);
AEF concatenationAEFs(AEF *aefA, AEF *aefB);
bool estReconnuParAEF(AEF *aef, const char *mot);
AEF rendreAEFDeterministe(AEF *aefNonDeterministe);
void sauvegarderAEF(AEF aef, const char *nom_fichier);
void determinerLangageReconnu(AEF *aef, char *langage);
void extraireExpressionReguliere(AEF *aef, char *expressionReguliere);
void marquerEtatsAccessibles(AEF *aef, int etatCourant, bool etatsAccessibles[]);
void marquerEtatsCoAccessibles(AEF *aef, int etatCourant, bool etatsCoAccessibles[]);
void trouverLangage(AEF *aef, int etatCourant, char *langage, char *motCourant, bool *visites);

#endif
