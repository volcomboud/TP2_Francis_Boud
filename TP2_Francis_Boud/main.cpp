#include <iomanip>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

#include "Etudiants.h"

void elDestructor(std::map<long, Etudiants>& arbre, long& matricule, unsigned short& ligne_etudiant, int erreur);

int main() {
	std::map<long, Etudiants> arbre_eleve;
	std::fstream le_scribe; //utiliser pour ecrire && pour lire

	//system("echo %cd%");
	le_scribe.open("donneesbrutes.txt", std::ios::in);

	if (le_scribe.is_open()) {
		std::string ligne;
		std::string un_identifiant;
		long un_matricule;
		unsigned short qte_note = 0;
		unsigned short une_note = 0;
		unsigned short cptr_nb_note = 0;               //petit compteur pour "skip" le premier entier avant les notes(inutilise; remplace par .size())
		unsigned short cptr_ligne_etudiant = 0; //

		while (std::getline(le_scribe, ligne)) {        //bloc while pour le deroulement des lignes
			std::stringstream flow_fichier(ligne);
			flow_fichier >> un_identifiant;
			flow_fichier >> un_matricule;
			flow_fichier >> qte_note;

			cptr_ligne_etudiant++;
			arbre_eleve[un_matricule] = Etudiants(un_identifiant, un_matricule);
			while (true) {                           //bloc while pour le deroulement des notes
				flow_fichier >> une_note;
				if (flow_fichier.fail()) {
					if (cptr_nb_note != qte_note)elDestructor(arbre_eleve, un_matricule, cptr_ligne_etudiant, 0);
					arbre_eleve[un_matricule].calculerMoyenne();

					break;
				}
				if (une_note >= 0 && une_note <= 20)arbre_eleve[un_matricule].ajouterNote(une_note);
				else elDestructor(arbre_eleve, un_matricule, cptr_ligne_etudiant, 1);
				cptr_nb_note++;
			}
			cptr_nb_note = 0; //reset le compteur pour que le 0 soit toujours saute dans la boucle
		}
		le_scribe.close();
	}
	else
		std::cout << "==================== ERREUR C'EST PRODUITE====================" << std::endl;

	le_scribe.open("moyennes.txt", std::fstream::out);
	if (le_scribe.is_open()) {
		std::string test;
		for (std::map<long, Etudiants>::iterator binder = arbre_eleve.begin(); binder != arbre_eleve.end(); binder++) {
			if (binder->second.getMoyenne() >= 10) //formattage pour les moyennes superieur a 10
				test = std::to_string(binder->first) + " " + std::to_string(binder->second.getMoyenne()).substr(0, 5) + "\n";
			else    //formattage pour une moyenne inferieur a 10
				test = std::to_string(binder->first) + " " + std::to_string(binder->second.getMoyenne()).substr(0, 4) + "\n";
			le_scribe << test;
		}
		le_scribe.close();
	}
	else
		std::cout << "====================UNE ERREUR C'EST PRODUITE====================" << std::endl;
}

void elDestructor(std::map<long, Etudiants>& arbre, long& matricule, unsigned short& ligne_etudiant, int erreur)
{
	if (erreur) {
		std::cout
			<< "	#######################################################################################\n"
			<< "	|                       UNE ERREUR DANS LE FICHIER DONNEESBRUTES.TXT                  |\n"
			<< "	|                   assurez vous que les valeurs entrees sont conforme.               |\n"
			<< "	|                                                                                     |\n"
			<< "	|                       Les notes doivent etre sur un total de 20                     |\n"
			<< "	|                                                                                     |\n"
			<< "	#######################################################################################" << std::endl;
	}
	else {
		std::cout
			<< "	#######################################################################################\n"
			<< "	|                       UNE ERREUR DANS LE FICHIER DONNEESBRUTES.TXT                  |\n"
			<< "	|                   assurez vous que les valeurs entrees sont conforme.               |\n"
			<< "	|                                                                                     |\n"
			<< "	|    La quantitee de notes entree doit etre coherente a l'indice du nombre de note    |\n"
			<< "	|                                                                                     |\n"
			<< "	#######################################################################################" << std::endl;
	}
	std::cout << "\n\nL'etudiant ne sera pas enregistre dans le systeme.\n  ERREUR LIGNE : " << ligne_etudiant
		<< "\n Faites \"Entrer\" pour continuer" << std::endl;
	std::cin.get();
	arbre.erase(matricule);
}
