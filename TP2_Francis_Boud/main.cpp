#include <iomanip>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

#include "Etudiants.h"

int main() {
	std::map<long, Etudiants> arbre_eleve;
	std::fstream fichier;
	std::fstream le_scribe;
	
	//system("echo %cd%");
	fichier.open("donneesbrutes.txt", std::ios::in);

	if (fichier.is_open()) {
		std::string ligne;
		std::string un_identifiant;
		long un_matricule;
		unsigned short une_note;
		unsigned short cptr_nb_note = 0;               //petit compteur pour "skip" le premier entier avant les notes(inutilise dans mon code)

		while (std::getline(fichier, ligne)) {        //bloc while pour le deroulement des lignes
			std::stringstream flow_fichier(ligne);
			flow_fichier >> un_identifiant;
			flow_fichier >> un_matricule;

			arbre_eleve[un_matricule] = Etudiants(un_identifiant, un_matricule);
			while (true) {                           //bloc while pour le deroulement des notes
				flow_fichier >> une_note;
				if (flow_fichier.fail())break;
				if (cptr_nb_note)arbre_eleve[un_matricule].ajouterNote(une_note); //Ce "if" saute le premier int (vector.size() est equivalent a la valeur represente)
				cptr_nb_note++;
			}
			cptr_nb_note = 0; //reset le compteur pour que le 0 soit toujours saute dans la boucle
		}
		fichier.close();
	}
	le_scribe.open("moyennes.txt", std::fstream::out);
	if (le_scribe.is_open()) {
		std::string test;
		for (std::map<long, Etudiants>::iterator binder = arbre_eleve.begin(); binder != arbre_eleve.end(); binder++) {
			binder->second.calculerMoyenne();
			test = std::to_string(binder->first)+" "+ std::to_string(binder->second.getMoyenne()).substr(0,5)+"\n";
			le_scribe << test;
		}
		le_scribe.close();
	}
	else
		std::cout << "UNE ERREUR C'EST PRODUITE" << std::endl;
}