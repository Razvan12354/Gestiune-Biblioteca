#ifndef IMPRUMUTURI_H
#define IMPRUMUTURI_H

#include <iostream>
#include "Carti.h"
#include "Abonati.h"

class Imprumuturi{
private:
    char *CNP, *idCarte, *dataImprumut;
    int perioadaZile;
    bool esteReturnata;
    Carti *carteImprumutata;
    Abonati *abonatAsociat;
    static float taxaPenalizarePeZi;

public:
    // Constructor
    Imprumuturi(Abonati& var_a, Carti& var_c, const char* var_dataImprumut, const int var_perioada);

    Imprumuturi(const Imprumuturi& nou);


    ~Imprumuturi();

    // Getters
    const char* getCNP() const;

    const char* getIdCarte() const;

    const char* getDataImprumut() const;

    int getPerioadaZile() const;

    // Finalizare imprumut + supraincarcare

    void finalizeazaImprumut();
    void finalizeazaImprumut(int var_zileReale);

    static void setTaxaPenalizare(float var_taxa);

    friend std::ostream& operator<<(std::ostream& out, const Imprumuturi& i);

    // Copy and swap
    friend void swap(Imprumuturi& first, Imprumuturi& second) noexcept;
    Imprumuturi& operator=(const Imprumuturi& nou);
};

#endif