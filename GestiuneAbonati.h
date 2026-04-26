#ifndef GESTIUNEABONATI_H
#define GESTIUNEABONATI_H

#include "Abonati.h"
#include <vector>

class GestiuneAbonati {
private:
    std::vector<Abonati*> lista;

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

    // Procesare final de luna
    void proceseazaFinalDeLuna();
    
    // Copy and swap
    friend void swap(GestiuneAbonati& first, GestiuneAbonati& second) noexcept;
};

#endif