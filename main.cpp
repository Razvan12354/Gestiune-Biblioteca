#include <iostream>
#include <vector>
#include "Abonati.h"
#include "AbonatCopil.h"
#include "AbonatStudent.h"
#include "AbonatPremium.h"
#include "Carti.h"
#include "Imprumuturi.h"
#include "GestiuneAbonati.h"
#include "ExceptiiBiblioteca.h"

int main() {
    std::cout << "===== TESTARE SISTEM BIBLIOTECA =====" << std::endl;

    // 1. TESTARE EXCEPTII SI VALIDARE (CNP/Telefon)
    std::cout << "\n[1] Testare Validare Date:" << std::endl;
    try {
        AbonatCopil eroare("Ion", "Ionut", "123", "0722", 10, 6); // CNP/Tel invalid
    } catch (const ExceptieValidare& e) {
        std::cout << "Capturat corect: " << e.what() << std::endl;
    }

    // 2. CREARE ENTITATI DE BAZA
    std::cout << "\n[2] Creare Carti si Abonati:" << std::endl;
    Carti c1("Povestea lui Harap-Alb", "Ion Creanga", "C001", 1877, 2);
    Carti c2("Orasul Albastru", "Ana Vintan", "C002", 2018, 1);

    AbonatCopil copil("Ionescu", "Andrei", "5120101123456", "0721123456", 12, 12);
    AbonatStudent student("Popescu", "Maria", "6020202123456", "0733123456", 21, 24, "Universitatea Bucuresti");
    AbonatPremium premium("Vasile", "Deniel", "1850303123456", "0744123456", 38, 36, 50.0);

    // 3. TESTARE NVI SI SCOR INCREDERE (POLIMORFISM)
    std::cout << "\n[3] Testare NVI (do_print) si Scoruri:" << std::endl;
    Abonati* ptrs[] = { &copil, &student, &premium };
    for (auto p : ptrs) {
        p->afisare(std::cout); // Apeleaza do_print() prin NVI
        std::cout << " | Scor calculat: " << p->scorIncredere() << std::endl;
    }

    // 4. TESTARE GESTIUNE ABONATI (CLONE & DESTRUCTOR)
    std::cout << "\n[4] Testare Gestiune (Polimorfism & Memorie):" << std::endl;
    {
        GestiuneAbonati biblioteca;
        biblioteca.adaugaAbonat(copil);   // Face clone()
        biblioteca.adaugaAbonat(student); // Face clone()
        biblioteca.adaugaAbonat(premium); // Face clone()

        std::cout << "Lista initiala:";
        biblioteca.afiseazaToti();

        // Testare dynamic_cast
        biblioteca.aplicaPromotieStudenti(6); 

        // Testare Copy Constructor (Deep Copy prin clone)
        GestiuneAbonati copieBiblioteca = biblioteca;
        std::cout << "\nCopie biblioteca (dupa promotie):";
        copieBiblioteca.afiseazaToti();
    } // Aici se apeleaza destructorul GestiuneAbonati si elibereaza memoria pentru clone

    // 5. TESTARE IMPRUMUTURI SI PENALIZARI
    std::cout << "\n[5] Testare Imprumuturi si Reguli:" << std::endl;
    try {
        Imprumuturi i1(student, c1, "2023-10-01", 14);
        std::cout << "Imprumut creat: " << i1 << std::endl;

        // Testare depasire stoc
        c2.rezervaCarte(); // Stoc devine 0
        try {
            Imprumuturi i2(copil, c2, "2023-10-02", 7);
        } catch (const ExceptieStocEpuizat& e) {
            std::cout << "Capturat corect (Stoc): " << e.what() << std::endl;
        }

        // Finalizare cu intarziere (genereaza penalizari)
        std::cout << "Returnare cu intarziere de 20 zile..." << std::endl;
        i1.finalizeazaImprumut(34); // 34 zile reale vs 14 zile permise

        std::cout << "Balanta penalizari student: " << student.getBalantaPenalizari() << " RON" << std::endl;

        // Testare refuz imprumut din cauza penalizarilor mari
        student.adaugaPenalizare(60.0); // Depasim pragul de 50
        try {
            Imprumuturi i3(student, c1, "2023-11-01", 10);
        } catch (const ExceptieRegulament& e) {
            std::cout << "Capturat corect (Regulament): " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Eroare neasteptata: " << e.what() << std::endl;
    }

    // 6. TESTARE COPY & SWAP (CLASA STUDENT)
    std::cout << "\n[6] Testare Copy & Swap (AbonatStudent):" << std::endl;
    AbonatStudent student2("X", "Y", "6010101111111", "0700000000", 20, 10, "UPB");
    student2 = student; // Operator= foloseste swap
    std::cout << "Dupa student2 = student, student2 este: " << std::endl;
    student2.afisare(std::cout);
    std::cout << std::endl;

    std::cout << "\n===== TESTARE FINALIZATA CU SUCCES =====" << std::endl;
    return 0;
}