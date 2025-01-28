// vertagt_aktion.h
#ifndef VERTAGT_AKTION_H
#define VERTAGT_AKTION_H

#include <list>
#include <memory>

namespace vertagt {
    template <class T>
    class VAktion {
    protected:
        std::list<T>& p_pListe;  // Reference to the list to be modified

    public:
        VAktion(std::list<T>& liste) : p_pListe(liste) {}
        virtual ~VAktion() = default;
        virtual void vAusfuehren() = 0;
    };

    template <class T>
    class VPushBack : public VAktion<T> {
    private:
        T p_objekt;

    public:
        VPushBack(std::list<T>& liste, T obj)
            : VAktion<T>(liste), p_objekt(std::move(obj)) {}

        void vAusfuehren() override {
            this->p_pListe.push_back(std::move(p_objekt));
        }
    };

    template <class T>
    class VPushFront : public VAktion<T> {
    private:
        T p_objekt;

    public:
        VPushFront(std::list<T>& liste, T obj)
            : VAktion<T>(liste), p_objekt(std::move(obj)) {}

        void vAusfuehren() override {
            this->p_pListe.push_front(std::move(p_objekt));
        }
    };

    template <class T>
    class VErase : public VAktion<T> {
    private:
        typename std::list<T>::iterator p_it;

    public:
        VErase(std::list<T>& liste, typename std::list<T>::iterator it)
            : VAktion<T>(liste), p_it(it) {}

        void vAusfuehren() override {
            this->p_pListe.erase(p_it);
        }
    };
}

#endif
