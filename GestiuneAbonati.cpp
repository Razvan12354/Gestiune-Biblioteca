#include "GestiuneAbonati.h"
#include "AbonatStudent.h" // Pentru dynamic_cast

// Constructor de copiere (clone)
GestiuneAbonati::GestiuneAbonati(const GestiuneAbonati& alta) {
    for (Abonati* a : alta.lista) {
        this->lista.push_back(a->clone());
    }
}

// Copy and swap
void swap(GestiuneAbonati& first, GestiuneAbonati& second) noexcept {
    first.lista.swap(second.lista); 
}

// operator=
GestiuneAbonati& GestiuneAbonati::operator=(const GestiuneAbonati& alta) {
    if (this == &alta) return *this;
    GestiuneAbonati copie(alta);
    swap(*this, copie);
    return *this;
}

// Adaugare abonat
void GestiuneAbonati::adaugaAbonat(const Abonati& a) {
    lista.push_back(a.clone());
}

// Simulare trecere timp
void GestiuneAbonati::trecereTimp(int luni) {
    std::cout << "\n>>>>TRECERE TIMP: " << luni << " LUNI <<<<" << std::endl;
    for (auto p : lista) {
        p->trecereTimp(luni);
    }
}

// Cautam in lista "Abonati*" doar pe cei care sunt "AbonatStudent"
void GestiuneAbonati::aplicaPromotieStudenti(int luniExtra) {
    std::cout << "\n---Aplicare promotie pentru studenti---" << std::endl;
    for (auto p : lista) {
        AbonatStudent* s = dynamic_cast<AbonatStudent*>(p);
        
        // Daca reuseste, inseamna ca obiectul e Student
        if (s != nullptr) {
            s->prelungireAbonament(luniExtra);
            std::cout << "Promotie aplicata pentru studentul: " << s->getNume() << std::endl;
        }
        }
    }

// Afiseaza toti abonatii
void GestiuneAbonati::afiseazaToti() const {
    std::cout << "\n---Lista Completa Abonati---" << std::endl;
    for (size_t i = 0; i < lista.size(); ++i) {
        std::cout << i + 1 << ". " << *lista[i] << std::endl;
    }

}
// Proceseaza finalul de luna
void GestiuneAbonati::proceseazaFinalDeLuna() {
    for (auto a : lista) {
        a->trecereTimp(1);
        if (!a->poateImprumuta()) {
            std::cout << "Abonatul " << a->getNume() << " are restrictii." << std::endl;
        }
    }
}

// Destructor
GestiuneAbonati::~GestiuneAbonati() {
    for (Abonati* a : lista) {
        delete a;
    }
    lista.clear();
}