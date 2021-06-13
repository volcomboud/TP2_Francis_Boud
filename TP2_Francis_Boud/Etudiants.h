#pragma once
#include <vector>
#include <iostream>

class Etudiants
{
private:
	std::vector<unsigned short> tableau_notes;
	std::string identifiant;
	long matricule;
	float moyennne;
public:
	Etudiants();
	Etudiants(std::string un_identifiant, long un_matricule);
	Etudiants(long un_matricule);

	void calculerMoyenne();
	void ajouterNote(unsigned short une_note);
	void defile();
	float getMoyenne();
	bool operator<(const Etudiants& etudiant_a_droite) const;
};
