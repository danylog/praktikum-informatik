#pragma once

#include <list>

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

    // Action for push_front
    template <class T>
    class VPushFront : public VAktion<T> {
    private:
        T p_objekt;

    public:
        VPushFront(std::list<T>& liste, T obj)
            : VAktion<T>(liste), p_objekt(std::move(obj)) {}

        void vAusfuehren() override {
            VAktion<T>::p_pListe.push_front(std::move(p_objekt));
        }
    };

    // Action for push_back
    template <class T>
    class VPushBack : public VAktion<T> {
    private:
        T p_objekt;

    public:
        VPushBack(std::list<T>& liste, T obj)
            : VAktion<T>(liste), p_objekt(std::move(obj)) {}

        void vAusfuehren() override {
            VAktion<T>::p_pListe.push_back(std::move(p_objekt));
        }
    };

    // Action for erase
    template <class T>
    class VErase : public VAktion<T> {
    private:
        typename std::list<T>::iterator p_iterator;

    public:
        VErase(std::list<T>& liste, typename std::list<T>::iterator iterator)
            : VAktion<T>(liste), p_iterator(iterator) {}

        void vAusfuehren() override {
            VAktion<T>::p_pListe.erase(p_iterator);
        }
    };
}
