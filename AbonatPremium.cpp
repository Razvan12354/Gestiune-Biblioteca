#include "AbonatPremium.h"

AbonatPremium::AbonatPremium(const char* var_nume, const char* var_prenume, const char* var_cnp, const char* var_nrTelefon, 
                             int var_varsta, int var_durataAbonament, double var_taxaPremium) 
    : Abonati(var_nume, var_prenume, var_cnp, var_nrTelefon, var_varsta, var_durataAbonament), taxaPremium(var_taxaPremium) {}

AbonatPremium* AbonatPremium::clone() const {
    return new AbonatPremium(*this);
}

double AbonatPremium::calculScorSpecific() const {
    double scorBaza = (this->varsta * 0.5) + (this->durataAbonament > 12 ? 40 : this->durataAbonament * 3);
    return scorBaza + 30.0; // Bonus fix pentru abonament de tip premium
}

void AbonatPremium::do_print(std::ostream& out) const {
    out << "Abonat PREMIUM | " << nume << " " << prenume 
        << " | Taxa: " << taxaPremium << " RON | Scor: " << scorIncredere() << "/100";
}

void swap(AbonatPremium& first, AbonatPremium& second) noexcept {
    swap(static_cast<Abonati&>(first), static_cast<Abonati&>(second));

    std::swap(first.taxaPremium, second.taxaPremium);
}

AbonatPremium& AbonatPremium::operator=(const AbonatPremium& nou) {
    AbonatPremium copie(nou);
    swap(*this, copie);
    return *this;
}

AbonatPremium::~AbonatPremium() {
    std::cout << "[Destructor AbonatPremium] Obiect distrus." << std::endl;
}