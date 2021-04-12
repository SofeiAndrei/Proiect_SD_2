#include <iostream>
#include <fstream>
using namespace std;
ifstream f("abce.in");
ofstream g("abce.out");
int N,operatie,x,y;
struct nod{
    int valoare,inaltime;
    nod* left;
    nod* right;
};
class AVL{
    public:
    nod* root;
    //constructor de initializare
    AVL(){
        root=NULL;
    }
    //destructor
    ~AVL(){
        root=NULL;
    }
    int INALTIME(nod* NOD){
        if(NOD==NULL){
            return -1;
        }
        else
        return NOD->inaltime;
    }
    nod* inserare(int x, nod* tata){
        if(tata==NULL){
            tata=new nod;
            tata->valoare=x;
            tata->inaltime=0;
            tata->left=NULL;
            tata->right=NULL;
        }
        else
        if(x<tata->valoare){
            //inseram in stanga;
            tata->left=inserare(x, tata->left);
            //trebuie sa vedem daca e balanced
            int h1,h2;
            h1=INALTIME(tata->left);
            h2=INALTIME(tata->right);
            if(h1-h2>=2){
                if(x<tata->left->valoare){
                    tata=rotire_dreapta(tata);
                    //rotire dreapta
                }
                else{
                tata=rotire_stanga_dreapta(tata);
                //rotire stanga+dreapta
                }
            }
        }
        else
        if(x>tata->valoare){
            //inseram in dreapta;
            tata->right=inserare(x, tata->right);
            //trebuie sa vedem daca e balanced
            int h1,h2;
            h1=INALTIME(tata->left);
            h2=INALTIME(tata->right);
            if(h2-h1>=2){
                if(x>tata->right->valoare){
                    tata=rotire_stanga(tata);
                    //rotire stanga
                }
                else{
                tata=rotire_dreapta_stanga(tata);
                //rotire dreapta+stanga
                }
            }
        }
        int h1,h2;
        h1=INALTIME(tata->left);
        h2=INALTIME(tata->right);
        tata->inaltime=max(h1, h2)+1;
        return tata;
    }
    nod* stergere(int x, nod* tata){
        nod* temp;
        if(tata==NULL){
            return NULL;
        }
        else
        if(x<tata->valoare){
            tata->left=stergere(x, tata->left);
        }
        else
        if(x>tata->valoare){
            tata->right=stergere(x, tata->right);
        }
        else
        //doi copii
        if(tata->left!=NULL && tata->right!=NULL){
            temp=Min(tata->right);
            tata->valoare=temp->valoare;
            tata->right=stergere(tata->valoare, tata->right);
        }
        //unul sau niciun copil
        else{
            temp=tata;
            if(tata->left==NULL){
                tata=tata->right;
            }
            else
            if(tata->right==NULL){
                tata=tata->left;
            }
            else
            delete temp;
        }
        if(tata==NULL){
            return tata;
        }
        else{
            int h1,h2;
            h1=INALTIME(tata->left);
            h2=INALTIME(tata->right);
            tata->inaltime=max(h1, h2)+1;
            //daca stergem nodul din stanga
            if(h1-h2>=2){
                int h3,h4;
                h3=INALTIME(tata->left->left);
                h4=INALTIME(tata->left->right);
                if(h3-h4==1){
                    return rotire_stanga(tata);
                }
                else
                return rotire_stanga_dreapta(tata);
            }
            else
            //daca stergem nodul din dreapta
            if(h2-h1>=2){
                int h3,h4;
                h3=INALTIME(tata->right->left);
                h4=INALTIME(tata->right->right);
                if(h4-h3==1){
                    return rotire_dreapta(tata);
                }
                else
                return rotire_dreapta_stanga(tata);
            }
            return tata;
        }
    }
    nod* rotire_dreapta(nod* tata){
        nod* temp;
        temp=tata->left;
        tata->left=temp->right;
        temp->right=tata;
        int h1,h2,h3;
        h1=INALTIME(tata->left);
        h2=INALTIME(tata->right);
        h3=INALTIME(temp->left);
        tata->inaltime=max(h1, h2)+1;
        temp->inaltime = max(h3, max(h1, h2)+1)+1;
        return temp;
    }

    nod* rotire_stanga(nod* tata){
        nod* temp;
        temp=tata->right;
        tata->right=temp->left;
        temp->left=tata;
        int h1,h2;
        h1=INALTIME(tata->left);
        h2=INALTIME(tata->right);
        tata->inaltime=max(h1,h2)+1;
        temp->inaltime=max(h2, max(h1,h2)+1)+1;
        return temp;
    }
    nod* rotire_stanga_dreapta(nod* tata){
        ///mai intai rotim la stanga si dupa la dreapta
        tata->left=rotire_stanga(tata->left);
        return rotire_dreapta(tata);
    }
    nod* rotire_dreapta_stanga(nod* tata){
        ///mai intai rotim la dreapta ce e si dupa la stanga
        tata->right=rotire_dreapta(tata->right);
        return rotire_stanga(tata);
    }
    void sortat(nod* tata, int a, int b){
        if(tata!=NULL){
            sortat(tata->left,a,b);
            if(tata->valoare>=a && tata->valoare<=b){
                g<<tata->valoare<<" ";
            }
            sortat(tata->right,a,b);
        }
    }
    void INSERARE(int x){
        root=inserare(x,root);
    }
    void afisare(int a, int b){
        sortat(root, a, b);
    }
    void STERGERE(int x){
        root=stergere(x,root);
    }
    bool cautare(int x){
        nod* NOD=root;
        bool OK=0;
        while(OK==0 && NOD!=NULL){
            if(x<NOD->valoare){
                NOD=NOD->left;
            }
            else
            if(x>NOD->valoare){
                NOD=NOD->right;
            }
            else
            OK=1;
        }
        if(OK==1){
            return 1;
        }
        else
        return 0;
    }
    int cel_mai_mic_mai_mare(int x){
        if(x==root->valoare){
            return x;
        }
        else{
            nod* NOD;
            nod* Predecesor=NULL;
            if(x<root->valoare){
                NOD=root->left;
                Predecesor=root;
            }
            else
            NOD=root->right;
            bool OK=0;
            while(OK==0 && NOD!=NULL){
                if(x==NOD->valoare){
                    return x;
                }
                if(x<NOD->valoare){
                    if(NOD->left==NULL){
                        return NOD->valoare;
                        OK=1;
                    }
                    else{
                        Predecesor=NOD;
                        NOD=NOD->left;
                    }
                }
                else
                if(x>NOD->valoare){
                    if(NOD->right==NULL){
                        return Predecesor->valoare;
                        OK=1;
                    }
                    else{
                        NOD=NOD->right;
                    }
                }
            }
        }
    }
    int cel_mai_mare_mai_mic(int x){
        if(x==root->valoare){
            return x;
        }
        else{
            nod* NOD;
            nod* Predecesor=NULL;
            if(x<root->valoare){
                NOD=root->left;
            }
            else{
            NOD=root->right;
            Predecesor=root;
            }
            bool OK=0;
            while(OK==0 && NOD!=NULL){
                if(x==NOD->valoare){
                    return x;
                }
                if(x<NOD->valoare){
                    if(NOD->left==NULL){
                        return Predecesor->valoare;
                        OK=1;
                    }
                    else{
                        NOD=NOD->left;
                    }
                }
                else{
                    if(NOD->right==NULL){
                        return NOD->valoare;
                        OK=1;
                    }
                    else{
                        Predecesor=NOD;
                        NOD=NOD->right;
                    }
                }
            }
        }
    }
    nod* Min(nod* tata)
    {
        if(tata==NULL){
            return NULL;
        }
        else
        if(tata->left==NULL){
            return tata;
        }
        else
        return Min(tata->left);
    }
};
int main ()
{
    f>>N;
    AVL avl;
    for(int indice=0;indice<N;indice++){
        f>>operatie>>x;
        ///operatie=1 -> inserare
        if(operatie==1){
            avl.INSERARE(x);
        }
        ///operatie=2 -> stergere
        if(operatie==2){
            avl.STERGERE(x);
        }
        ///operatie=3 -> cautare
        if(operatie==3){
            g<<avl.cautare(x)<<'\n';
        }
        ///operatie=4 -> cel mai mare mai mic
        if(operatie==4){
            g<<avl.cel_mai_mare_mai_mic(x)<<'\n';
        }
        ///operatie=5 -> cel mai mic mai mare
        if(operatie==5){
            g<<avl.cel_mai_mic_mai_mare(x)<<'\n';
        }
        ///operatie=6 -> afisare elemente sortate
        if(operatie==6){
            f>>y;
            avl.afisare(x,y);
            g<<'\n';
        }
    }
    return 0;
}
