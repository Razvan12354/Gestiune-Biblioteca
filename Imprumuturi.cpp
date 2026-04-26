#include "Imprumuturi.h"
#include "ExceptiiBiblioteca.h"
#include <cstring>

float Imprumuturi::taxaPenalizarePeZi = 0.5;

// Constructor
Imprumuturi::Imprumuturi(Abonati& var_a, Carti& var_c, const char* var_dataImprumut, const int var_perioada) {

    if (var_a.getBalantaPenalizari() > 50) {
        throw ExceptieRegulament("Imprumut refuzat! Abonatul are penalizari neplatite de peste 50 RON.");
    }

    if (!var_c.rezervaCarte()) {
        throw ExceptieStocEpuizat("Cartea '" + std::string(var_c.getTitlu()) + "' nu este disponibila momentan.");
    }

    if (var_perioada <= 0 || var_perioada > 90) {
        throw ExceptieValidare("Perioada de imprumut trebuie sa fie intre 1 si 90 de zile.");
    }

    this->abonatAsociat = &var_a;

    this->carteImprumutata = &var_c;

    this->perioadaZile = var_perioada;

    this->esteReturnata = false;

    this->CNP = new char[std::strlen(var_a.getCNP()) + 1];
    std::strcpy(this->CNP, var_a.getCNP());

    this->idCarte = new char[std::strlen(var_c.getId()) + 1];
    std::strcpy(this->idCarte, var_c.getId());

    this->dataImprumut = new char[std::strlen(var_dataImprumut) + 1];
    std::strcpy(this->dataImprumut, var_dataImprumut);

    if (var_c.rezervaCarte()) {
        std::cout << "Imprumut realizat cu succes pentru cartea " << var_c.getTitlu() << " cu ID " << var_c.getId() << std::endl;
    } else {
        std::cout << "ATENTIE: Stoc epuizat pentru cartea " << var_c.getTitlu() << " cu ID " << var_c.getId() << "! Imprumut realizat FARA stoc." << std::endl;
    }

}

// Constructor de copiere
Imprumuturi::Imprumuturi(const Imprumuturi& nou) {
    this->CNP = new char[std::strlen(nou.CNP) + 1];
    std::strcpy(this->CNP, nou.CNP);

    this->idCarte = new char[std::strlen(nou.idCarte) + 1];
    std::strcpy(this->idCarte, nou.idCarte);

    this->dataImprumut = new char[std::strlen(nou.dataImprumut) + 1];
    std::strcpy(this->dataImprumut, nou.dataImprumut);

    this->perioadaZile = nou.perioadaZile;
    this->esteReturnata = nou.esteReturnata;
    this->carteImprumutata = nou.carteImprumutata;
    this->abonatAsociat = nou.abonatAsociat;
}

// Copy and swap
void swap(Imprumuturi& first, Imprumuturi& second) noexcept {
    std::swap(first.CNP, second.CNP);
    std::swap(first.idCarte, second.idCarte);
    std::swap(first.dataImprumut, second.dataImprumut);
    
    std::swap(first.carteImprumutata, second.carteImprumutata);
    std::swap(first.abonatAsociat, second.abonatAsociat);

    std::swap(first.perioadaZile, second.perioadaZile);
    std::swap(first.esteReturnata, second.esteReturnata);
}

// Operator=
Imprumuturi& Imprumuturi::operator=(const Imprumuturi& nou) {
    if (this != &nou) {
        Imprumuturi copie(nou);
        swap(*this, copie);
    }
    return *this;
}

const char* Imprumuturi::getCNP() const { return CNP; }

const char* Imprumuturi::getIdCarte() const { return idCarte; }

const char* Imprumuturi::getDataImprumut() const { return dataImprumut; }

int Imprumuturi::getPerioadaZile() const { return perioadaZile; }

// Finalizare fara zile (la timp)
void Imprumuturi::finalizeazaImprumut() {
    if (!esteReturnata) {
        esteReturnata = true;
        carteImprumutata->returneazaCarte();
        std::cout << "Cartea " << idCarte << " returnata la timp de " << CNP << std::endl;
    } else {
        std::cout << "Eroare: Imprumut deja finalizat." << std::endl;
    }
}


// Finalizare cu calcul penalizari
void Imprumuturi::finalizeazaImprumut(int var_zileReale) {
    if (esteReturnata) {
        std::cout << "Cartea a fost deja returnata." << std::endl;
        return;
    }

    esteReturnata = true;
    carteImprumutata->returneazaCarte();

    if (var_zileReale > perioadaZile) {
        int zileIntarziere = var_zileReale - perioadaZile;
        double penalizare = 0;

        if (abonatAsociat->scorIncredere() < 50) {
            penalizare = taxaPenalizarePeZi * zileIntarziere;
        } else {
            penalizare = 0.75 * taxaPenalizarePeZi * zileIntarziere;
        }
        
        abonatAsociat->adaugaPenalizare(penalizare);
        std::cout << "Intarziere " << zileIntarziere << " zile. Penalizare: " << penalizare << " RON." << std::endl;
    } else {
        std::cout << "Returnare la timp in " << var_zileReale << " zile." << std::endl;
    }
}

// Setare taxa penalizare
void Imprumuturi::setTaxaPenalizare(float var_taxa) {
    taxaPenalizarePeZi = var_taxa;
}

// Supraincarcare operator<<
std::ostream& operator<<(std::ostream& out, const Imprumuturi& i) {
    out << "Imprumut: " << i.CNP << " | Carte: " << i.idCarte << " | Data: " << i.dataImprumut;
    return out;
}

// Destructor
Imprumuturi::~Imprumuturi() {
    std::cout << "[Destructor Imprumuturi] Finalizare sesiune pentru CNP: " << (CNP ? CNP : "NULL") << std::endl;
    delete[] CNP;
    delete[] idCarte;
    delete[] dataImprumut;
}