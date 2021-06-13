#include <iomanip>
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <sstream>

#include "Etudiants.h"

int main(){

	std::map<long,Etudiants> arbre_eleve;
	std::fstream fichier;
	
	system("echo %cd%");

	fichier.open("donneesbrutes.txt", std::ios::app);  	
	if (fichier.is_open()){ 
		fichier << "PETIT TEST EN GROS CARACTERE \n"; 
		fichier.close(); 
	}
	fichier.open("donneesbrutes.txt", std::ios::in); 
	
	if (fichier.is_open()) { 
	
		std::string ligne;
		std::string un_identifiant;
		long un_matricule;
		unsigned short une_note;
	
		while (std::getline(fichier, ligne)) { 
			
			//std::cout << ligne << std::endl;

			std::stringstream flow(ligne);
			flow >> un_identifiant;
			flow >> un_matricule;

			arbre_eleve[un_matricule]=Etudiants(un_identifiant, un_matricule);
			std::cout << un_identifiant << " " << un_matricule; 
					
			while (true) {
				flow >> une_note;
				if (flow.fail())break;
				std::cout << " " << une_note;
				arbre_eleve[un_matricule].ajouterNote(une_note);	
			}
			std::cout<<std::endl;		
		}
		fichier.close(); 
	}
	arbre_eleve[6123456].defile();
	//std::map<long,Etudiants>::iterator binder;
}
