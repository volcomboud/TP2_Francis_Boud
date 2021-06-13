#pragma once
#include <vector>
#include <iostream>

class Etudiants
{
private:
    std::vector<unsigned short> tableau_notes;
    std::string identifiant;
    long matricule;
public:
    Etudiants();
    Etudiants(std::string un_identifiant, long un_matricule);
    Etudiants (long un_matricule);

    void ajouterNote (unsigned short une_note);
    void defile();
    double calculerMoyenne();
    bool operator<(const Etudiants& etudiant_a_droite) const;
};

