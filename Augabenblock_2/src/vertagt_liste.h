#pragma once

#include <list>
#include <memory>

namespace vertagt {

    // Base class for all actions performed on VListe
    template <class T>
    class VAktion {
    protected:
        std::list<T>& p_pListe;  // Reference to the list to be modified

    public:
        explicit VAktion(std::list<T>& liste) : p_pListe(liste) {}
        virtual ~VAktion() = default;
        virtual void vAusfuehren() = 0;  // Pure virtual method for executing the action
    };

    // Derived class for push_front action
    template <class T>
    class VPushFront : public VAktion<T> {
    private:
        T p_objekt;  // Object to be pushed to the front

    public:
        VPushFront(std::list<T>& liste, T obj)
            : VAktion<T>(liste), p_objekt(std::move(obj)) {}

        void vAusfuehren() override {
            this->p_pListe.push_front(std::move(p_objekt));
        }
    };

    // Derived class for push_back action
    template <class T>
    class VPushBack : public VAktion<T> {
    private:
        T p_objekt;  // Object to be pushed to the back

    public:
        VPushBack(std::list<T>& liste, T obj)
            : VAktion<T>(liste), p_objekt(std::move(obj)) {}

        void vAusfuehren() override {
            this->p_pListe.push_back(std::move(p_objekt));
        }
    };

    // Derived class for erase action
    template <class T>
    class VErase : public VAktion<T> {
    private:
        typename std::list<T>::iterator p_iterator;  // Iterator pointing to the element to be erased

    public:
        VErase(std::list<T>& liste, typename std::list<T>::iterator iterator)
            : VAktion<T>(liste), p_iterator(iterator) {}

        void vAusfuehren() override {
            this->p_pListe.erase(p_iterator);
        }
    };

    // Template class for VListe
    template <class T>
    class VListe {
    private:
        std::list<std::unique_ptr<VAktion<T>>> p_aktionen;  // List of deferred actions
        std::list<T> p_objekte;  // List of actual objects

    public:
        // Adds an object to the front
        void push_front(T val) {
            p_aktionen.emplace_back(std::make_unique<VPushFront<T>>(p_objekte, std::move(val)));
        }

        // Adds an object to the back
        void push_back(T val) {
            p_aktionen.emplace_back(std::make_unique<VPushBack<T>>(p_objekte, std::move(val)));
        }

        // Erases an element at a specific position
        void erase(typename std::list<T>::iterator pos) {
            p_aktionen.emplace_back(std::make_unique<VErase<T>>(p_objekte, pos));
        }

        // Executes all deferred actions
        void vAktualisieren() {
            for (auto& aktion : p_aktionen) {
                aktion->vAusfuehren();
            }
            p_aktionen.clear();
        }

        // Other list-like methods
        typename std::list<T>::iterator begin() { return p_objekte.begin(); }
        typename std::list<T>::iterator end() { return p_objekte.end(); }
        bool empty() const { return p_objekte.empty(); }
        void clear() { p_objekte.clear(); p_aktionen.clear(); }
    };
}
