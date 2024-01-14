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

<p> The 'Alphabet' structure represents the alphabet used by the automaton. It contains the following fields: </p>

<li> symboles: An array of characters representing the symbols in the alphabet. </li>
<li> nb_symboles: The number of symbols in the alphabet. </li>

## Key Functions

<p> The Finite State Automata Editor provides the following functionalities: </p>

### Automaton Initialization and Display

<li> <strong> void initAEF(AEF *aef): </strong> Initializes an automaton with default values. </li>
<li> <strong> void afficherAEF(AEF aef): </strong> Displays the current configuration of the automaton. </li>
<li> <strong> void saisirAEF(AEF *aef): </strong> Inputs the automaton details from the user. </li>

### Automaton Storage and Modification

<li> <strong> void sauvegarderAEF(AEF aef, const char *nom_fichier): </strong> Saves the automaton configuration to a file. </li>
<li> <strong> void chargerAEF(AEF *aef, const char *nom_fichier): </strong> Loads an automaton configuration from a file. </li>
<li> <strong> void modifierAEF(AEF *aef): </strong> Modifies the existing configuration of an automaton. </li>
<li> <strong> void supprimerAEF(AEF *aef): </strong> Deletes an automaton and frees up memory. </li>

### Automaton Analysis and Operations

<li> <strong> bool estReconnuParAEF(AEF *aef, const char *mot): </strong> Checks if a given word is recognized by the automaton. </li>
<li> <strong> bool estAEFComplet(AEF *aef):</strong>  Determines if the automaton is complete. </li>
<li> <strong> void rendreAEFComplet(AEF*aef):</strong>  Converts the automaton into a complete automaton by adding missing transitions. </li>
<li> <strong> bool estAEFDeterministe(AEF *aef):</strong> Checks if the automaton is deterministic. </li>
<li> <strong> void rendreAEFDeterministe(AEF *aefNonDeterministe, AEF *aefDeterministe):</strong> Converts a non-deterministic automaton into a deterministic one. </li>
<li> <strong> void complementAEF(AEF *aefOriginal, AEF *aefComplement):</strong> Creates the complement of the given automaton. </li>
<li> <strong> void miroirAEF(AEF *aefOriginal, AEF *aefMiroir):</strong> Creates the mirror (reverse) automaton of the given automaton. </li>
<li> <strong> void produitAEFs(AEF *aefA, AEF *aefB, AEF *aefProduit):</strong> Produces the product of two automata.</li>
<li> <strong> void concatenationAEFs(AEF *aefA, AEF *aefB, AEF *aefConcatenation):</strong> Concatenates two automata.</li>
<li> <strong> void extraireExpressionReguliere(AEF *aef, char *expressionReguliere):</strong> Extracts a regular expression from the automaton.</li>
<li> <strong> void trouverLangage(AEF *aef, int etatCourant, char *langage, char *motCourant, bool *visites):</strong> Finds the language recognized by the automaton.</li>
<li> <strong> void determinerLangageReconnu(AEF *aef, char *langage):</strong> Determines the language recognized by the automaton.</li>
<li> <strong> bool sontEquivalents(AEF *aef1, AEF *aef2):</strong> Checks if two automata are equivalent.</li>

### Automaton Optimization

<li> <strong> void marquerEtatsAccessibles(AEF *aef, int etatCourant, bool etatsAccessibles[]):</strong> Marks accessible states in the automaton.</li>
<li> <strong> void marquerEtatsCoAccessibles(AEF *aef, int etatCourant, bool etatsCoAccessibles[]):</strong> Marks co-accessible states in the automaton.</li>
<li> <strong> void rendreAutomateEmonde(AEF *aef):</strong> Prunes the automaton by removing non-accessible and non-co-accessible states.</li>
<li> <strong> void supprimerEtatsInaccessibles(AEF *aef):</strong> Removes inaccessible states from the automaton.</li>
<li> <strong> void fusionnerEtatsEquivalents(AEF *aef):</strong> Merges equivalent states in the automaton.</li>
<li> <strong> void rendreAutomateMinimal(AEF *aef):</strong> Minimizes the automaton.</li>

## Usage

<p> To utilize the Finite State Automata Editor, include the aediteur.h in your C project and compile aediteur.c with your source files. Use the provided functions to create and manipulate finite state automata as per your requirements. </p>
