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

<p> <h4> void initAEF(AEF *aef): </h4> Initializes an automaton with default values. </p>
<p> <h4> void afficherAEF(AEF aef): </h4> Displays the current configuration of the automaton. </p>
<p> <h4> void saisirAEF(AEF *aef):</h4> Inputs the automaton details from the user. </p>

### Automaton Storage and Modification
<p> <h4> void sauvegarderAEF(AEF aef, const char *nom_fichier): </h4> Saves the automaton configuration to a file. </p>
<p> <h4> void chargerAEF(AEF *aef, const char *nom_fichier): </h4> Loads an automaton configuration from a file. </p>
<p> <h4> void modifierAEF(AEF *aef): </h4> Modifies the existing configuration of an automaton. </p>
<p> <h4> void supprimerAEF(AEF *aef): </h4> Deletes an automaton and frees up memory. </p>

### Automaton Analysis and Operations
<p> <h4> bool estReconnuParAEF(AEF *aef, const char *mot): </h4> Checks if a given word is recognized by the automaton. </p>
<p> <h4> bool estAEFComplet(AEF *aef): </h4> Determines if the automaton is complete. </p>
<p> <h4> void rendreAEFComplet(AEF*aef): </h4> Converts the automaton into a complete automaton by adding missing transitions. </p>
<p> <h4> bool estAEFDeterministe(AEF *aef):</h4> Checks if the automaton is deterministic. </p>
<p> <h4> void rendreAEFDeterministe(AEF *aefNonDeterministe, AEF *aefDeterministe):</h4> Converts a non-deterministic automaton into a deterministic one. </p>
<p> <h4>void complementAEF(AEF *aefOriginal, AEF *aefComplement):</h4> Creates the complement of the given automaton. </p>
<p> <h4> void miroirAEF(AEF *aefOriginal, AEF *aefMiroir):</h4> Creates the mirror (reverse) automaton of the given automaton. </p>
<p> <h4> void produitAEFs(AEF *aefA, AEF *aefB, AEF *aefProduit):</h4> Produces the product of two automata.</p>
<p> <h4> void concatenationAEFs(AEF *aefA, AEF *aefB, AEF *aefConcatenation):</h4> Concatenates two automata.</p>
<p> <h4> void extraireExpressionReguliere(AEF *aef, char *expressionReguliere):</h4> Extracts a regular expression from the automaton.</p>
<p> <h4> void trouverLangage(AEF *aef, int etatCourant, char *langage, char *motCourant, bool *visites):</h4> Finds the language recognized by the automaton.</p>
<p> <h4> void determinerLangageReconnu(AEF *aef, char *langage):</h4> Determines the language recognized by the automaton.</p>
<p> <h4> bool sontEquivalents(AEF *aef1, AEF *aef2):</h4> Checks if two automata are equivalent.</p>

### Automaton Optimization

<p> <h4> void marquerEtatsAccessibles(AEF *aef, int etatCourant, bool etatsAccessibles[]):</h4> Marks accessible states in the automaton.</p>
<p> <h4> void marquerEtatsCoAccessibles(AEF *aef, int etatCourant, bool etatsCoAccessibles[]):</h4> Marks co-accessible states in the automaton.</p>
<p> <h4> void rendreAutomateEmonde(AEF *aef):</h4> Prunes the automaton by removing non-accessible and non-co-accessible states.</p>
<p> <h4> void supprimerEtatsInaccessibles(AEF *aef):</h4> Removes inaccessible states from the automaton.</p>
<p> <h4> void fusionnerEtatsEquivalents(AEF *aef):</h4> Merges equivalent states in the automaton.</p>
<p> <h4> void rendreAutomateMinimal(AEF *aef):</h4> Minimizes the automaton.</p>

## Usage

<p> To utilize the Finite State Automata Editor, include the aediteur.h in your C project and compile aediteur.c with your source files. Use the provided functions to create and manipulate finite state automata as per your requirements. </p>
