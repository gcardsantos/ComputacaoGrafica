#ifndef VETOR_H
#define VETOR_H


class Vetor
{
    public:
        float x, y, z;
        Vetor();
        Vetor(const float tx, const float ty, const float tz);
        Vetor(const Vetor* v);

        void Add(const Vetor v);
        void setValor(const float tx, const float ty, const float tz);
        void setValor(const Vetor v);
        virtual ~Vetor();
    protected:
    private:
};

#endif // VETOR_H
