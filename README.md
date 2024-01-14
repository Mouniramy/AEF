# Finite State Automata Editor (AEditeur)

## Overview

<p> The Finite State Automata (FSA) Editor is a comprehensive C library designed for creating, manipulating, and analyzing finite state automata. It allows users to define automata, set up transitions, save and load configurations, and perform various operations on automata. </p>

## Structures

### AEF

<p> The 'AEF' structure represents an Automaton with its states, transitions, initial state, and final states. It contains the following fields: </p>

<li> transitions: A 3D array representing state transitions. </li>
<li> etatInitial: An integer representing the initial state. </li>
<li> etatsFinaux: An array indicating final states. </li>
<li> nb_etats: The number of states in the automaton. </li>
<li> alphabet: A structure representing the alphabet used by the automaton. </li>

### Alphabet

<p>The 'Alphabet' structure represents the alphabet used by the automaton. It contains the following fields: </p>

<li> symboles: An array of characters representing the symbols in the alphabet. </li>
<li> nb_symboles: The number of symbols in the alphabet. </li>

## Key Functions

<p> The Finite State Automata Editor provides the following functionalities: </p>

### Automaton Initialization and Display

<p>  void initAEF(AEF *aef):  Initializes an automaton with default values. </p>
<p>  void afficherAEF(AEF aef):  Displays the current configuration of the automaton. </p>
<p>  void saisirAEF(AEF *aef): Inputs the automaton details from the user. </p>

### Automaton Storage and Modification
<p>  void sauvegarderAEF(AEF aef, const char *nom_fichier):  Saves the automaton configuration to a file. </p>
<p>  void chargerAEF(AEF *aef, const char *nom_fichier):  Loads an automaton configuration from a file. </p>
<p>  void modifierAEF(AEF *aef):  Modifies the existing configuration of an automaton. </p>
<p>  void supprimerAEF(AEF *aef):  Deletes an automaton and frees up memory. </p>

### Automaton Analysis and Operations
<p>  bool estReconnuParAEF(AEF *aef, const char *mot):  Checks if a given word is recognized by the automaton. </p>
<p>  bool estAEFComplet(AEF *aef):  Determines if the automaton is complete. </p>
<p>  void rendreAEFComplet(AEF*aef):  Converts the automaton into a complete automaton by adding missing transitions. </p>
<p>  bool estAEFDeterministe(AEF *aef): Checks if the automaton is deterministic. </p>
<p>  void rendreAEFDeterministe(AEF *aefNonDeterministe, AEF *aefDeterministe): Converts a non-deterministic automaton into a deterministic one. </p>
<p> void complementAEF(AEF *aefOriginal, AEF *aefComplement): Creates the complement of the given automaton. </p>
<p>  void miroirAEF(AEF *aefOriginal, AEF *aefMiroir): Creates the mirror (reverse) automaton of the given automaton. </p>
<p>  void produitAEFs(AEF *aefA, AEF *aefB, AEF *aefProduit): Produces the product of two automata.</p>
<p>  void concatenationAEFs(AEF *aefA, AEF *aefB, AEF *aefConcatenation): Concatenates two automata.</p>
<p>  void extraireExpressionReguliere(AEF *aef, char *expressionReguliere): Extracts a regular expression from the automaton.</p>
<p>  void trouverLangage(AEF *aef, int etatCourant, char *langage, char *motCourant, bool *visites): Finds the language recognized by the automaton.</p>
<p>  void determinerLangageReconnu(AEF *aef, char *langage): Determines the language recognized by the automaton.</p>
<p>  bool sontEquivalents(AEF *aef1, AEF *aef2): Checks if two automata are equivalent.</p>

### Automaton Optimization

<p>  void marquerEtatsAccessibles(AEF *aef, int etatCourant, bool etatsAccessibles[]): Marks accessible states in the automaton.</p>
<p>  void marquerEtatsCoAccessibles(AEF *aef, int etatCourant, bool etatsCoAccessibles[]): Marks co-accessible states in the automaton.</p>
<p>  void rendreAutomateEmonde(AEF *aef): Prunes the automaton by removing non-accessible and non-co-accessible states.</p>
<p>  void supprimerEtatsInaccessibles(AEF *aef): Removes inaccessible states from the automaton.</p>
<p>  void fusionnerEtatsEquivalents(AEF *aef): Merges equivalent states in the automaton.</p>
<p>  void rendreAutomateMinimal(AEF *aef): Minimizes the automaton.</p>

## Usage

<p> To utilize the Finite State Automata Editor, include the aediteur.h in your C project and compile aediteur.c with your source files. Use the provided functions to create and manipulate finite state automata as per your requirements. </p>
