# Sistem Gestiune Biblioteca

Proiect de gestiune a activitatii unei bibliotec. Sistemul permite gestionarea stocurilor de carti,
a diferitelor tipuri de abonati (Copil, Student, Premium) si procesarea imprumuturilor cu calcul 
automat al penalizarilor.

# Gestiunea diferitelor tipuri de Abonati:
Abonati: Clasa de baza care gestioneaza datele personale (nume, CNP, telefon) si balanta penalizarilor
- AbonatCopil: Include un scor bazat pe varsta si o penalizare educativa.
- AbonatStudent: Include prezenta universitatii si beneficiaza de promotii.
- AbonatPremium: Include o taxa speciala si un scor de incredere ridicat de la inceput.

# Gestiunea Resurselor:
- Carti: Gestioneaza titlul, autorul si stocul disponibil.
- Imprumuturi: Realizeaza legatura intre un Abonat si o Carte. Calculeaza penalizarile daca perioada
de returnare este depasita.
- GestiuneAbonati: Simuleaza trecerea timpului pentru toti abonatii (poate fi folosit la procesarea finalului de luna), aplica bonusuri.
