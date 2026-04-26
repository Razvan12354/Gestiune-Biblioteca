#ifndef CARTI_H
#define CARTI_H

#include <iostream>

class Carti{
private:
    char* titlu, *autor, *idCarte;
    int anAparitie, stocDisponibil;
    static int nrTotalCarti;

public:
    // Constructor
    Carti(const char *var_titlu, const char *var_autor, const char* var_idCarte, 
        int var_anAparitie, int var_stocDisponibil);
    
    Carti(const Carti& noua);

    // operator=
    Carti& operator=(const Carti& noua);

    // Getters + Metode ce inlocuiesc getterii
    bool rezervaCarte();
    void returneazaCarte();
    bool esteDisponibila() const;
    
    const char* getTitlu() const;
    const char* getId() const;

    static int getNrTotalCarti();

    friend std::ostream& operator<<(std::ostream& out, const Carti& c);

    // Copy and swap
    friend void swap(Carti& first, Carti& second) noexcept;

    // Destructor
    ~Carti();
    };

#endif