#include "Etudiants.h"

Etudiants::Etudiants() {

}
Etudiants::Etudiants(long un_matricule) {
	this->matricule = un_matricule;
}
Etudiants::Etudiants(std::string un_identifiant, long un_matricule){
	this->identifiant = un_identifiant;
	this->matricule = un_matricule;
}
void  Etudiants::ajouterNote (unsigned short une_note){
	this->tableau_notes.push_back(une_note);
}
void Etudiants::defile() {
	for (int i = 0; i < this->tableau_notes.size(); i++) {
		std::cout<<tableau_notes[i]<<std::endl;
	}
}
double Etudiants::calculerMoyenne() {
	double resultat = 0;

	return resultat;
}
bool Etudiants::operator<(const Etudiants& etudiant_a_droite) const {
	if (this->identifiant<etudiant_a_droite.identifiant) return true;

	return false;
}





