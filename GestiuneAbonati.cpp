#include "GestiuneAbonati.h"
#include "AbonatStudent.h"
#include "AbonatCopil.h"
#include "AbonatPremium.h"
#include "AbonatPensionar.h"
#include <fstream>
#include <cstring>
#include <iostream>
#include <iomanip>

// Constructor de copiere
GestiuneAbonati::GestiuneAbonati(const GestiuneAbonati& alta) {
    for (Abonati* a : alta.lista) this->lista.push_back(a->clone());
    for (Carti* c : alta.listaCarti) this->listaCarti.push_back(new Carti(*c));
    for (Imprumuturi* i : alta.listaImprumuturi) this->listaImprumuturi.push_back(new Imprumuturi(*i));
}

// Functie de swap
void swap(GestiuneAbonati& first, GestiuneAbonati& second) noexcept {
    first.lista.swap(second.lista);
    first.listaCarti.swap(second.listaCarti);
    first.listaImprumuturi.swap(second.listaImprumuturi);
}

// Operator assignment
GestiuneAbonati& GestiuneAbonati::operator=(const GestiuneAbonati& alta) {
    if (this == &alta) return *this;
    GestiuneAbonati copie(alta);
    swap(*this, copie);
    return *this;
}

// Destructor
GestiuneAbonati::~GestiuneAbonati() {
    for (Abonati* a : lista) delete a;
    for (Carti* c : listaCarti) delete c;
    for (Imprumuturi* i : listaImprumuturi) delete i;
    lista.clear();
    listaCarti.clear();
    listaImprumuturi.clear();
}

// Cautare abonat
Abonati* GestiuneAbonati::gasesteAbonat(const char* cnp) {
    for (auto a : lista) {
        if (std::strcmp(a->getCNP(), cnp) == 0) return a;
    }
    return nullptr;
}

// Cautare carte
Carti* GestiuneAbonati::gasesteCarte(const char* id) {
    for (auto c : listaCarti) {
        if (std::strcmp(c->getId(), id) == 0) return c;
    }
    return nullptr;
}

// Scade o zi din durata abonamentului tuturor
void GestiuneAbonati::proceseazaFinalDeZi() {
    std::cout << "--- PROCESARE ZILNICA ---" << std::endl;
    for (auto a : listaImprumuturi) {
        a->crestereZileScurse(1);
        }
    for (auto b : lista){
        b->trecereTimp(1);
    }
}

void GestiuneAbonati::aplicaPromotieStudenti(int luniExtra) {
    std::cout << "Se cauta studenti pentru prelungire..." << std::endl;
    for (auto p : lista) {
        AbonatStudent* s = dynamic_cast<AbonatStudent*>(p);
        if (s != nullptr) {
            s->prelungireAbonament(luniExtra);
            std::cout << "S-au adaugat " << luniExtra << " luni pentru: " << s->getNume() << std::endl;
        }
    }
}

void GestiuneAbonati::trecereTimp(int luni) {
    for (auto p : lista) {
        p->trecereTimp(luni);
    }
}

void GestiuneAbonati::incarcaCarti(const std::string& numeFisier) {
    std::ifstream f(numeFisier);
    if (!f.is_open()) return;

    std::string titlu, autor, id;
    int an, stoc;
    int adult, promo; // citit ca 0 sau 1 din fisier

    while (f >> std::quoted(titlu) >> std::quoted(autor) >> id >> an >> stoc >> adult>> promo) {
        listaCarti.push_back(new Carti(titlu.c_str(), autor.c_str(), id.c_str(), an, stoc, (bool)adult, (bool)promo));
    }
    f.close();
}

void GestiuneAbonati::incarcaImprumuturi(const std::string& numeFisier) {
    std::ifstream f(numeFisier);
    if (!f.is_open()) return;

    std::string cnp, idCarte, data;
    int perioada, scurse;

    while (f >> cnp >> idCarte >> data >> perioada >> scurse) {
        Abonati* ab = gasesteAbonat(cnp.c_str());
        Carti* ct = gasesteCarte(idCarte.c_str());

        if (ab && ct) {
            Imprumuturi* nou = new Imprumuturi(*ab, *ct, data.c_str(), perioada);

            nou->setZileScurse(scurse);

            this->listaImprumuturi.push_back(nou);
        }
    }
    f.close();
}

void GestiuneAbonati::incarcaDinFisier(const std::string& numeFisier) {
    std::ifstream f(numeFisier);
    if (!f.is_open()) return;

    char tip;
    while (f >> tip) {
        std::string n, p, cnp, tel;
        int v, d, scor;
        double balanta;

        if (!(f >> std::quoted(n) >> std::quoted(p) >> cnp >> tel >> v >> d >> balanta >> scor)) {
            continue; 
        }

        Abonati* nou = nullptr;
        try {

            if (tip == 'S') {
                std::string univ; f >> std::quoted(univ);
                nou = new AbonatStudent(n.c_str(), p.c_str(), cnp.c_str(), tel.c_str(), v, d, univ.c_str());
            } else if (tip == 'C') {
                nou = new AbonatCopil(n.c_str(), p.c_str(), cnp.c_str(), tel.c_str(), v, d);
            } else if (tip == 'P') {
                double taxa; f >> taxa;
                nou = new AbonatPremium(n.c_str(), p.c_str(), cnp.c_str(), tel.c_str(), v, d, taxa);
            } else if (tip == 'R') {
                nou = new AbonatPensionar(n.c_str(), p.c_str(), cnp.c_str(), tel.c_str(), v, d);
            }

            if (nou) {
                nou->setScorIncredere(scor);
                nou->adaugaPenalizare(balanta); 
                this->lista.push_back(nou);
            }
        } catch (const std::exception& e) {
            std::cerr << "Eroare la incarcarea abonatului " << n << ": " << e.what() << std::endl;
        }
    }
    f.close();
}

void GestiuneAbonati::adaugaAbonat(const Abonati& a) {
    lista.push_back(a.clone());
}

void GestiuneAbonati::afiseazaToti() const {
    for (size_t i = 0; i < lista.size(); ++i) {
        std::cout << *lista[i] << std::endl;
    }
}

void GestiuneAbonati::salveazaImprumuturi(const std::string& numeFisier) {
    std::ofstream f(numeFisier);
    if (!f.is_open()) return;

    for (auto imp : listaImprumuturi) {
        f << imp->getAbonat().getCNP() << " " 
          << imp->getIdCarte() << " "
          << imp->getDataImprumut() << " "
          << imp->getPerioadaZile() << " "
          << imp->getZileScurse() << "\n";

    }
    f.close();
}

void GestiuneAbonati::adaugaImprumutInFisier(Imprumuturi* imp, const std::string& numeFisier) {
    std::ofstream f(numeFisier, std::ios::app);
    
    if (!f.is_open()) {
        std::cerr << "EROARE: Nu s-a putut deschide fisierul " << numeFisier << " pentru scriere!" << std::endl;
        return;
    }
    f << imp->getAbonat().getCNP() << " " 
      << imp->getIdCarte() << " " 
      << imp->getDataImprumut() << " "
      << imp->getPerioadaZile() << " "
      << imp->getZileScurse() << "\n";;

    f.close();
    std::cout << "[Debug] Scriere reusita in " << numeFisier << std::endl;
}

void GestiuneAbonati::salveazaCartiInFisier(const std::string& numeFisier) {
    std::ofstream f(numeFisier);
    if (!f.is_open()) return;

    for (auto c : listaCarti) {
        f << std::quoted(c->getTitlu()) << " " 
          << std::quoted(c->getAutor()) << " " 
          << c->getId() << " " 
          << c->getAnAparitie() << " "
          << c->getStoc() << " " 
          << (c->esteDoarAdulti() ? 1 : 0) << " " 
          << (c->esteLaPromotie() ? 1 : 0) << "\n";
    }
    f.close(); }

void GestiuneAbonati::salveazaAbonatiInFisier(const std::string& numeFisier) {
    std::ofstream f(numeFisier);
    if (!f.is_open()) return;

    for (auto a : lista) {
        // Determinam caracterul pentru tip
        char tip = 'R'; 
        if (dynamic_cast<AbonatStudent*>(a)) tip = 'S';
        else if (dynamic_cast<AbonatCopil*>(a)) tip = 'C';
        else if (dynamic_cast<AbonatPremium*>(a)) tip = 'P';
        else if (dynamic_cast<AbonatPensionar*>(a)) tip = 'R';

        // Salvam: Tip, Nume, Prenume, CNP, Telefon, Varsta, Durata, Penalizari
        f << tip << " "
          << std::quoted(a->getNume()) << " "
          << std::quoted(a->getPrenume()) << " "
          << a->getCNP() << " "
          << a->getTelefon() << " "
          << a->getVarsta() << " "
          << a->getDurataAbonament() << " "
          << a->getBalantaPenalizari() << " "
          << a->getScorIncredere() << " ";

        if (tip == 'S') {
            AbonatStudent* s = dynamic_cast<AbonatStudent*>(a);
            f << std::quoted(s->getUniversitate());
        } else if (tip == 'P') {
            AbonatPremium* p = dynamic_cast<AbonatPremium*>(a);
            f << p->getTaxaMentenanta();
        }

        f << "\n";
    }
    f.close();
}