#include <iostream>
#include "TrigramSpellCheckerCount.h"
#include "TrigramSpellCheckerFormula.h"

int main() {

	int choice;

	while (1) {
		cout << "\n\n************Spell Checker Through Trigram Analysis************** \n\n";
		cout << "1. Spell Checking Through Trigram Similarity Measure \n";
		cout << "2. Frequency Based Trigram Analysis \n";
		cout << "\nChoice :";
		cin >> choice;

		if (choice == 1) {
			TrigramSpellCheckerFormula *tscf = new TrigramSpellCheckerFormula();
			tscf->checkSpelling();
		} else if (choice == 2) {
			TrigramSpellCheckerCount *tscc = new TrigramSpellCheckerCount();
			tscc->checkSpelling();

		} else {
			cout << "\n Invalid Choice \n";
			exit(1);
		}
	}
}
