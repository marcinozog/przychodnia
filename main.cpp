#include <stdio.h>
#include <stdlib.h>
#include "przychodnia.h"

using namespace std;

void pause() {
    cout << "\nPress Enter to continue..." << endl;
    getchar();
    getchar();
    // string t;
    // getline(cin, t);
}

int main(int argc, char* argv[]) {
    Przychodnia przychodnia = Przychodnia();

    if( przychodnia.init() == -1) {
        cout << "Open database failed!!!\n";
        return (0);
    }

    while (1)
    { 
        string choice; 

        system("clear"); 

        printf("********* MENU *********\n\n");
        printf("A - Wyświetl całą bazę\n"); 
        printf("W - Wyświetl lekarzy\n"); 
        printf("D - Dodaj lekarza\n"); 
        printf("U - Usuń lekarza\n"); 
        printf("w - Wyświetl pacjentów\n"); 
        printf("d - Dodaj pacjenta\n"); 
        printf("u - Usuń pacjenta\n"); 
        printf("t - Wyświetl wizyty\n"); 
        printf("i - Dodaj wizytę\n"); 
        printf("K - Zamknij aplikację\n\n"); 
        printf("**********************\n");
        printf("Wybierz opcje: "); 

        getline(cin, choice);

        if(choice == "A") {
            przychodnia.wyswietl_lekarzy();
            przychodnia.wyswietl_pacjentow();
            przychodnia.wyswietl_poradnie();
            przychodnia.wyswietl_wizyty(true);
            przychodnia.wyswietl_leki();
            pause();
        }
        else if(choice == "W") {
            przychodnia.wyswietl_lekarzy();
            pause();
        }
        else if(choice == "D") {
            przychodnia.dodaj_lekarza();
            pause();
        }
        else if(choice == "U") {
            przychodnia.usun_lekarza();
            pause();
        }
        else if(choice == "w") {
            przychodnia.wyswietl_pacjentow();
            pause();
        }
        else if(choice == "d") {
            przychodnia.dodaj_pacjenta();
            pause();
        }
        else if(choice == "u") {
            przychodnia.usun_pacjenta();
            pause();
        }
        else if(choice == "t") {
            przychodnia.wyswietl_wizyty(false);
            pause();
        }
        else if(choice == "i") {
            pause();
        }
        else if(choice == "K") {
            break;
        }
        else {
            cout << "Błędny wybór" << endl;
            pause();
        }
    } 

    return 0;
}