// vertagt_liste.h
#ifndef VERTAGT_LISTE_H
#define VERTAGT_LISTE_H

#include <list>
#include <memory>
#include "vertagt_aktion.h"

namespace vertagt {
    template <class T>
    class VListe {
    public:
        using iterator = typename std::list<T>::iterator;
        using const_iterator = typename std::list<T>::const_iterator;

        // Read operations - direct access
        iterator begin() { return p_objekte.begin(); }
        iterator end() { return p_objekte.end(); }
        const_iterator begin() const { return p_objekte.begin(); }
        const_iterator end() const { return p_objekte.end(); }
        bool empty() const { return p_objekte.empty(); }

        // Write operations - delayed through actions
        void push_front(T obj) {
            p_aktionen.push_back(
                std::make_unique<VPushFront<T>>(p_objekte, std::move(obj))
            );
        }

        void push_back(T obj) {
            p_aktionen.push_back(
                std::make_unique<VPushBack<T>>(p_objekte, std::move(obj))
            );
        }

        void erase(iterator it) {
            p_aktionen.push_back(
                std::make_unique<VErase<T>>(p_objekte, it)
            );
        }

        // Update function - processes all pending actions
        void vAktualisieren() {
            for (auto& pAktion : p_aktionen) {
                pAktion->vAusfuehren();
            }
            p_aktionen.clear();
        }

        // Clear function - update and clear all elements
        void clear() {
            vAktualisieren();  // Process any pending actions first
            p_objekte.clear();
        }

    private:
        std::list<T> p_objekte;  // The actual list of objects
        std::list<std::unique_ptr<VAktion<T>>> p_aktionen;  // List of pending actions
    };
}

#endif
