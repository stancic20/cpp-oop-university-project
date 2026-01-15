#include <iostream>
#include "dinstring.hpp"
#include "list.hpp"

using namespace std;

class Zivotinja
{
protected:
    int starost;
    DinString ime;
    DinString vrsta;
public:
    Zivotinja(int s=0,DinString i="NEPOZNATO",DinString v="NEPOZNATO"):starost(s),ime(i),vrsta(v){}
    Zivotinja(const Zivotinja&z):starost(z.starost),ime(z.ime),vrsta(z.vrsta){}

    int getStarost()const
    {
        return starost;
    }
    DinString getIme()const
    {
        return ime;
    }
    DinString getVrsta()const
    {
        return vrsta;
    }
    virtual void ispis() const = 0;

    DinString punoImeVrste() const
    {
        return ime+"( "+ vrsta + ")" ;
    }

};

class Lav:public Zivotinja
{
private:
    int broj_grive;
public:
    Lav(int s=5,DinString i="Simba", DinString v="Lav",int bg=15):Zivotinja(s,i,v),broj_grive(bg){}
    Lav(const Lav&l):Zivotinja(l),broj_grive(l.broj_grive){}

    int getBrojGrive()const
    {
        return broj_grive;
    }
    void ispis() const override
    {
        cout<<"ime: "<<ime<<", vrsta: "<<vrsta<<", starost: "<<starost<<", broj grive: "<<broj_grive<<endl;
    }

    void rici() const
    {
        cout<<ime<<"je riknuo: RAWWAW";
    }
};

class Slon:public Zivotinja
{
private:
    int duzina_surle;
public:
    Slon(int s=10,DinString i="Dumbo",DinString v="Slon", int ds=150):Zivotinja(s,i,v),duzina_surle(ds){}
    Slon(const Slon&s):Zivotinja(s),duzina_surle(s.duzina_surle){}

    void ispis() const override
    {
        cout<<"ime: "<<ime<<",vrsta: "<<vrsta<<",starosti: "<<starost<<", duzine surle: "<<duzina_surle<<"cm"<<endl;

    }
    void trubi()const
    {
        cout<<ime<<"je zatrubio"<<endl;
    }
};

class ZooVrt
{
private:
    DinString naziv;
    int kapacitet;
    List <Zivotinja*> lista_zivotinja;
public:
    ZooVrt(DinString n="TARZANCICI",int k=100):naziv(n),kapacitet(k){}

    DinString getNaziv()const
    {
        return naziv;
    }


    bool dodajZivotinju(Zivotinja&z)
    {
    Zivotinja* pz;
    for(int i=1;i<=lista_zivotinja.size();i++) // INT I NEMOJ ZABORAVIT
    {
        lista_zivotinja.read(i,pz);
        if(pz->getIme()==z.getIme()&&pz->getVrsta()==z.getVrsta())
        {
            return false;
        }
    }
    if (lista_zivotinja.size()<kapacitet)
    {
        lista_zivotinja.add(1, &z);
        return true;
    }
    return false;
    }

    void ispisSvihZivotinja()const
    {
        cout<<"moj zoo vrt: "<<naziv<<endl;
        Zivotinja* pz;
        for(int i=1;i<=lista_zivotinja.size();i++ )
        {
            lista_zivotinja.read(i,pz);
            pz->ispis();
        }


    }
    void sortirajPoStarosti()
    {
        Zivotinja* zivotinja1;
        Zivotinja* zivotinja2;
        for(int i=1;i<lista_zivotinja.size();i++)
        {
            for (int j=i+1;j<lista_zivotinja.size();j++)
            {
                lista_zivotinja.read(i,zivotinja1);
                lista_zivotinja.read(j,zivotinja2) ;

                if(zivotinja1->getStarost()<zivotinja2->getStarost())
                {
                    lista_zivotinja.remove(i);
                    lista_zivotinja.add(i,zivotinja2);
                    lista_zivotinja.remove(j);
                    lista_zivotinja.add(j,zivotinja1);
                }
            }
        }
    }
    int pronadjiZivotinju(const DinString &ime) const
    {
        Zivotinja* pz;
        for(int i=1;i<=lista_zivotinja.size();i++)
        {
            lista_zivotinja.read(i,pz) ;
            if(pz->getIme()==ime)
            {
                return i;
            }

            }
            return -1;
        }

    int prebrojVrstu(const DinString& vrsta) const
     {
         int count=0;
         Zivotinja* pz;
         for(int i=1;i<=lista_zivotinja.size();i++)
         {
             lista_zivotinja.read(i,pz);
             if(pz->getVrsta()==vrsta)
             {
                 count++ ;
             }
         }
         return count;
     }
};

int main()
{
    Lav l1(5,"Simba","Lav",12) ;
    Lav l2(9,"Mufasa","Lav",15) ;
    Slon s1(3,"Dumbo","Slon",200);
    Slon s2(6,"Balonko","Slon",250);

    ZooVrt zoo;
    zoo.dodajZivotinju(l1);
    zoo.dodajZivotinju(l2);
    zoo.dodajZivotinju(s1);
    zoo.dodajZivotinju(s2);
    cout<<"ispis svih zivotinja"<<endl;
    zoo.ispisSvihZivotinja();

    cout<<"po starosti"<<endl;
    zoo.ispisSvihZivotinja();
    zoo.sortirajPoStarosti();
    zoo.ispisSvihZivotinja();

    cout<<"pronadji index za Simba:"<<zoo.pronadjiZivotinju("Simba")<<endl;


    cout<<"prebroj vrstu Slon: "<<zoo.prebrojVrstu("Slon")<<endl;



    return 0;
}
