#ifndef GESTIUNEABONATI_H
#define GESTIUNEABONATI_H

#include "Abonati.h"
#include "Carti.h"
#include "Imprumuturi.h"
#include <string>
#include <vector>

class GestiuneAbonati {
private:
    std::vector<Abonati*> lista;
    std::vector<Carti*> listaCarti;
    std::vector<Imprumuturi*> listaImprumuturi;

public:
    GestiuneAbonati() = default;

    // Constructor de copiere
    GestiuneAbonati(const GestiuneAbonati& alta);

    // Operator=
    GestiuneAbonati& operator=(const GestiuneAbonati& alta);

    // Destructor
    ~GestiuneAbonati();

    // Metoda pentru adaugat abonati (primeste pointer la baza)
    void adaugaAbonat(const Abonati& a);

    // Metoda pentru Trecere timp
    void trecereTimp(int luni);

    // Acorda bonus de durata daca abonatul e Student (Dynamic_cast)
    void aplicaPromotieStudenti(int luniExtra);

    // Afisarea intregii liste
    void afiseazaToti() const;

    // Procesare final de zi
    void proceseazaFinalDeZi();

    Imprumuturi* getImprumut(size_t index) {
    if (index < listaImprumuturi.size()) return listaImprumuturi[index];
    return nullptr;
}

    // Citirea din fisier
    void incarcaDinFisier(const std::string& numeFisier);
    void incarcaCarti(const std::string& numeFisier);
    void incarcaImprumuturi(const std::string& numeFisier);

    Abonati* gasesteAbonat(const char* cnp);
    Carti* gasesteCarte(const char* id);
    
    // Copy and swap
    friend void swap(GestiuneAbonati& first, GestiuneAbonati& second) noexcept;

    std::vector<Abonati*>& getListaAbonati() { return lista; }
    std::vector<Carti*>& getListaCarti() { return listaCarti; }
    std::vector<Imprumuturi*>& getListaImprumuturi() { return listaImprumuturi; }

    void salveazaImprumuturi(const std::string& numeFisier);

    void adaugaImprumutInFisier(Imprumuturi* imp, const std::string& numeFisier);

    void salveazaCartiInFisier(const std::string& numeFisier);

    void salveazaAbonatiInFisier(const std::string& numeFisier);
};

#endif