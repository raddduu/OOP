///in cazul in care programul nu afiseaza Process returned 0 inchideti consola si apasati succesiv pe butonul build and run pana cand se executa cu succes
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream in("date.in");

class multime
{
public:
    multime();
    multime(unsigned int);
    multime(int*, unsigned int);
    multime(const multime&);
    ~multime();
    unsigned int get_cardinal();
    int* get_elements();
    void set_cardinal(unsigned int);
    void set_elements(int*);
    void transform_to_set();
    friend istream& operator>> (istream&, multime&);
    friend ostream& operator<< (ostream&, multime&);
    friend multime operator+(multime&, multime&);   ///reuniune
    friend multime operator*(multime&, multime&);   ///intersectie
    friend multime operator-(multime&, multime&);   ///diferenta
    multime operator+=(multime&);            ///A+=B <=> A = A + B
    multime operator-=(multime&);            ///A-=B <=> A = A - B
    multime operator*=(multime&);            ///A*=B <=> A = A * B
    friend bool operator==(multime&, multime&);
    friend bool operator!=(multime&, multime&);
    friend bool operator!=(multime&, multime&);
    multime& operator = (const multime&);
private:
    friend class curierat;
    unsigned int nr_elemente;
    int* elemente;
};
    multime::multime()
    {
        this->elemente = new int[10];
        for (int i = 0; i < 10; i++) this->elemente[i]=0;
        this->nr_elemente = 10;
    }

    multime::multime(unsigned int cardinal)
    {
        this->elemente = new int[cardinal];
        for (int i = 0; i < cardinal; i++) this->elemente[i]=0;
        this->nr_elemente = cardinal;
    }

    multime::multime(int* elem, unsigned int cardinal)
    {
        this->elemente = new int[cardinal];
        for (int i = 0; i < cardinal; i++) this->elemente[i]=elem[i];
        this->nr_elemente = cardinal;
    }

    multime::~multime()
    {
        delete[] this->elemente;
        this->elemente = NULL;
        this->nr_elemente = -1;
    }

    multime::multime(const multime& ob)
    {
        nr_elemente = ob.nr_elemente;

        if(nr_elemente > 0)
        {
            elemente = new int[nr_elemente];

            for (int i = 0; i < nr_elemente; i++) elemente[i] = ob.elemente[i];
        }
    }

    multime& multime::operator = (const multime& ob)
    {
        if (this != &ob)
        {
            nr_elemente = 0;
            delete[] elemente;
            elemente = NULL;
            nr_elemente = ob.nr_elemente;

            if(nr_elemente > 0)
            {
                elemente = new int[nr_elemente];

                for (int i = 0; i < nr_elemente; i++) elemente[i] = ob.elemente[i];
            }
        }
        return *this;
    }

    unsigned int multime::get_cardinal()
    {
        return this->nr_elemente;
    }

    int* multime::get_elements()
    {
        //cout<<"APELAT GETTER ELEMENTE\n";

        int* v = new int[nr_elemente];

        for (int i = 0; i < nr_elemente; i++) v[i] = elemente[i];

        return v;
    }

    void multime::set_cardinal(unsigned int cardinal)
    {
        nr_elemente = cardinal;
    }

    void multime::set_elements(int* elements)
    {
        for (int i = 0; i < nr_elemente; i++)   this->elemente[i] = elements[i];
    }


    istream& operator >> (istream& in,multime& ob)
    {
        in>>ob.nr_elemente;
        for (int i = 0; i < ob.nr_elemente; i++)  in>>ob.elemente[i];
        return in;
    }

    ostream& operator << (ostream& out,multime& ob)
    {
        out<<ob.nr_elemente<<" ";
        for (int i = 0; i < ob.nr_elemente; i++) out<<ob.elemente[i]<<" ";
        return out;
    }

    multime operator+(multime& ob1, multime& ob2)
    {
        unsigned int c1 = ob1.nr_elemente;
        unsigned int c2 = ob2.nr_elemente;
        unsigned int ct = c1+c2;

        int *elem1 = new int [c1];
        int *elem2 = new int [c2];
        int *elemt = new int [ct];

        elem1 = ob1.elemente;
        elem2 = ob2.elemente;

        unsigned int k = 0;

        for (int i = 0; i < c1; i++)    elemt[k++] = elem1[i];
        for (int i = 0; i < c2; i++)    elemt[k++] = elem2[i];

        multime E(elemt,ct);
        E.transform_to_set();
        return E;
    }

    multime operator*(multime& ob1, multime& ob2)
    {
        unsigned int c1 = ob1.get_cardinal();
        unsigned int c2 = ob2.get_cardinal();
        unsigned int ct = min(c1,c2);

        int *elem1 = new int [c1];
        int *elem2 = new int [c2];
        int *elemt = new int [ct];

        elem1 = ob1.get_elements();
        elem2 = ob2.get_elements();

        unsigned int k = 0;

        for (int i = 0; i < c1; i++)
            for (int j = 0; j < c2; j++)
                if (elem1[i] == elem2[j])
                    elemt[k++] = elem1[i];

        multime E(elemt,k);
        return E;
    }

    multime operator-(multime& ob1, multime& ob2)
    {
        unsigned int c1 = ob1.get_cardinal();
        unsigned int c2 = ob2.get_cardinal();
        unsigned int ct = c1;

        int *elem1 = new int [c1];
        int *elem2 = new int [c2];
        int *elemt = new int [ct];

        elem1 = ob1.get_elements();
        elem2 = ob2.get_elements();

        unsigned int k = 0;

        for (int i = 0; i < c1; i++)
        {
            bool ok = 1;

            for (int j = 0; j < c2; j++)
                if (elem1[i] == elem2[j])   ok = 0;

            if(ok)  elemt[k++] = elem1[i];
        }

        multime E(elemt,k);
        //cout<<E<<"\n";
        return E;
    }

    multime multime::operator+=(multime& ob)
    {
        multime A(elemente,nr_elemente),B;

        B=A+ob;

        nr_elemente = B.nr_elemente;
        delete[] elemente;
        elemente = new int[nr_elemente];
        for (int i = 0; i < nr_elemente; i++)   elemente[i] = B.elemente[i];
    }

    multime multime::operator-=(multime& ob)
    {
        multime A(elemente,nr_elemente),B;

        B=A-ob;

        nr_elemente = B.nr_elemente;
        delete[] elemente;
        elemente = new int[nr_elemente];
        for (int i = 0; i < nr_elemente; i++)   elemente[i] = B.elemente[i];
    }

    multime multime::operator*=(multime& ob)
    {
        multime A(elemente,nr_elemente),B;

        B=A*ob;

        nr_elemente = B.nr_elemente;
        delete[] elemente;
        elemente = new int[nr_elemente];
        for (int i = 0; i < nr_elemente; i++)   elemente[i] = B.elemente[i];
    }

    bool operator==(multime& ob1, multime& ob2)
    {
        unsigned int c1 = ob1.get_cardinal();
        unsigned int c2 = ob2.get_cardinal();

        if (c1!=c2) return false;

        int *elem1 = new int [c1];
        int *elem2 = new int [c2];

        elem1 = ob1.get_elements();
        elem2 = ob2.get_elements();

        for (int i = 0; i < c1; i++)
            if (elem1[i]!=elem2[i]) return false;

        return true;
    }

    bool operator!=(multime& ob1, multime& ob2)
    {
        unsigned int c1 = ob1.get_cardinal();
        unsigned int c2 = ob2.get_cardinal();

        if (c1!=c2) return true;

        int *elem1 = new int [c1];
        int *elem2 = new int [c2];

        elem1 = ob1.get_elements();
        elem2 = ob2.get_elements();

        for (int i = 0; i < c1; i++)
            if (elem1[i]!=elem2[i]) return true;

        return false;
    }

    void multime::transform_to_set()
    {
        unsigned int n = this->nr_elemente;

        int *aux,*elemente;

        aux = new int[n];

        elemente = new int[n];

        elemente = this->elemente;

        sort(elemente,elemente+n);

        int crt = elemente[0], k=0;

        aux[0] = elemente[0];

        for (int i = 0; i < n; i++)
        {
            if (elemente[i]!=crt)
            {
                k++;
                aux[k]=elemente[i];
                crt = elemente[i];
            }
        }

        this->nr_elemente = k+1;
        this->elemente = aux;
    }

class curierat
{
public:
    curierat();
    unsigned int nr_clienti();
    void angajeaza(int);
    void concediaza(int);
    void plata_salarii(unsigned int, unsigned int);
    friend istream& operator>> (istream&, curierat&);
    friend ostream& operator<< (ostream&, curierat&);
private:
    string nume_firma;
    multime comenzi;    ///retine numarul total de comenzi si CNP-ul cerut la fiecare comanda
    multime angajati;   ///retine numarul total de angajati si CNP-ul fiecaruia
    unsigned int cifra_de_afaceri;
};

    curierat::curierat()
    {
        nume_firma = "NULL_NAME";

        angajati.nr_elemente = 10;
        angajati.elemente = new int[10];
        for (int i = 0; i < 10; i++)    angajati.elemente[i] = 0;

        comenzi.nr_elemente = 10;
        comenzi.elemente = new int[10];
        for (int i = 0; i < 10; i++)    comenzi.elemente[i] = 0;

        cifra_de_afaceri = 0;
    }

    istream& operator >> (istream& in,curierat& ob)
    {
        in>>ob.nume_firma;

        unsigned int numar_comenzi;
        in>>numar_comenzi;
        int *_comenzi = new int[numar_comenzi];
        for (int i = 0; i < numar_comenzi; i++)  in>>_comenzi[i];
        multime COMENZI(_comenzi, numar_comenzi);
        ob.comenzi.set_cardinal(COMENZI.get_cardinal());
        ob.comenzi.set_elements(COMENZI.get_elements());

        unsigned int numar_angajati;
        in>>numar_angajati;
        int *_angajati = new int[numar_angajati];
        for (int i = 0; i < numar_angajati; i++)  in>>_angajati[i];
        multime ANGAJATI(_angajati, numar_angajati);
        ob.angajati.set_cardinal(ANGAJATI.get_cardinal());
        ob.angajati.set_elements(ANGAJATI.get_elements());

        in>>ob.cifra_de_afaceri;

        return in;
    }

    ostream& operator << (ostream& out,curierat& ob)
    {
        out<<ob.nume_firma<<" "<<ob.comenzi<<" "<<ob.angajati<<" "<<ob.cifra_de_afaceri;
        return out;
    }

    unsigned int curierat::nr_clienti()
    {
        multime X(comenzi);

        X.transform_to_set();

        return X.get_cardinal();
    }

    void curierat::angajeaza(int CNP_angajat)
    {
        angajati.nr_elemente++;

        angajati.elemente[angajati.nr_elemente-1] = CNP_angajat;
    }

    void curierat::concediaza(int CNP_angajat)
    {
        int i;

        for (i = 0; i < angajati.nr_elemente && angajati.elemente[i]!=CNP_angajat; i++);

        if (i == angajati.nr_elemente-1)
        {
            angajati.nr_elemente--;

            return;
        }

        for (int j = angajati.nr_elemente - 1; j>i; j--)    angajati.elemente[i-1] = angajati.elemente[i];

        angajati.nr_elemente--;

        angajati.elemente[angajati.nr_elemente-1] = CNP_angajat;
    }

    void curierat::plata_salarii(unsigned int nr_angajati_de_platit, unsigned int salariu)
    {
        cifra_de_afaceri -=nr_angajati_de_platit*salariu;
    }

int main()
{
    unsigned int dim;
    in>>dim;
    int *v = new int[dim];
    for (int i = 0; i < dim; i++) in>>v[i];

    multime A,B(5),C(v,dim),D,E,F,L,T(C);

    cout<<"Testare constructori de initializare si copiere:\n"<<A<<"\n"<<B<<"\n"<<C<<"\n"<<T<<"\n"; cout<<"\n";

    in>>A>>B;

    cout<<"Testare operatori de citire si afisare:\n"<<A<<"\n"<<B<<"\n"; cout<<"\n";

    cout<<"Testare operatori relationali:\n"<<(A==B)<<" "<<(A!=B)<<"\n";    cout<<"\n";

    cout<<"Testare operatori aritmetici binari:\n";

    C=A+B;
    D=A-B;
    L=B-A;
    E=A*B;
    cout<<"Reuniunea: "<<C<<"\nDiferenta(A - B) "<<D<<"\nDiferenta(B - A) "<<L<<"\nIntersectia: "<<E<<"\n"; cout<<"\n";

    cout<<"Testare operatori compusi de atribuire:\n";

    A+=B;
    cout<<"Adaugarea multimii B la A: "<<A<<"\n";
    A-=B;
    cout<<"Eliminarea lui B din A: "<<A<<"\n";
    A+=E;
    cout<<"Restaurarea1 lui A: "<<A<<"\n";
    A*=B;
    cout<<"Intersectarea lui A cu B: "<<A<<"\n";
    A+=D;
    cout<<"Restaurarea2 lui A: "<<A<<"\n";

    cout<<"Testare transformare array-multime:\n";
    in>>F;
    F.transform_to_set();
    cout<<F<<"\n";  cout<<"\nFINALUL TESTELOR PENTRU MULTIMI\n\n";

    curierat Firma1;

    in>>Firma1;

    cout<<"Datele firmei: "<<Firma1<<"\n";

    Firma1.angajeaza(203);

    cout<<"Firma dupa angajarea unui nou angajat: "<<Firma1<<"\n";

    Firma1.concediaza(203);

    cout<<"Firma dupa concedierea unui angajat: "<<Firma1<<"\n";

    cout<<"Numar de clienti: "<<Firma1.nr_clienti()<<"\n";

    Firma1.plata_salarii(2,1500);

    cout<<"Firma dupa plata salariatilor: "<<Firma1<<"\n\n";

    return 0;
}
