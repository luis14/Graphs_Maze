#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_H


class Temporizador : public Runnable
{
    public:
        Temporizador();
        virtual ~Temporizador();
        void run(){
            int S;
            for(S=100; S >= 0; ){
                cout<<S--;
                Sleep(999);
                system("cls" );
            }
        }
    protected:
    private:
};

#endif // TEMPORIZADOR_H
