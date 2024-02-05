#include "connectorDB.h"
#include "response.h"

class Przychodnia{
    private:
        void wyswietl_response(string sql);
        ConnectorDB *cDB;
        string sql;
    public:
        ~Przychodnia();
        int init();
        void wyswietl_lekarzy();
        void dodaj_lekarza();
        void usun_lekarza();
        void wyswietl_pacjentow();
        void dodaj_pacjenta();
        void usun_pacjenta();
        void wyswietl_wizyty(bool wszystkie = true);
        void dodaj_wizyte();
        void usun_wizyte();
        void wyswietl_poradnie();
        void wyswietl_leki();
};