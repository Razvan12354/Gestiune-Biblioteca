#ifndef ABONATI_H
#define ABONATI_H

#include <iostream>

class Abonati{
protected:
    char*nume, *prenume, *telefon, *CNP;
    int varsta, durataAbonament, nrCartiImprumutate;
    double balantaPenalizari;
    static int nrTotalAbonati;

    virtual double calculScorSpecific() const = 0; // = 0 inseamna functie pur virtuala

    virtual void do_print(std::ostream& out) const = 0;


public:
    // Constructori
    Abonati(const char *var_nume, const char *var_prenume, const char *var_CNP, 
            const char *var_telefon, int var_varsta, int var_durataAbonament);
    Abonati(const Abonati& nou);

    // Operator=
    Abonati& operator=(const Abonati& nou);

    // Desctructor Virtual
    virtual ~Abonati();

    // Constructor virtual (clone)
    virtual Abonati* clone() const = 0; // = 0 inseamna functie pur virtuala

    // Interfata non-virtuala pentru calculul scorului de incredere
    double scorIncredere() const{
        return this->calculScorSpecific();
    }

    void afisare(std::ostream& out) const {
        do_print(out);
    }

    // Getters + Setters
    char* getCNP() const { return CNP; }
    char* getNume() const { return nume; }
    int getNrCartiImprumutate() const { return nrCartiImprumutate; }
    double getBalantaPenalizari() const { return balantaPenalizari; }

    void setNrCartiImprumutate(int nr) { nrCartiImprumutate = nr; }

    // Metode 
    void adaugaPenalizare(double suma);
    static bool telefonValid(const char* tel);
    static bool CNPValid(const char* cnp);
    void platestePenalizare(double suma);
    void prelungireAbonament(int luni);
    bool poateImprumuta() const;
    void trecereTimp(int luni);

    friend std::ostream& operator<<(std::ostream& out, const Abonati& a);

    // Copy and swap
    friend void swap(Abonati& first, Abonati& second) noexcept;
};

#endif