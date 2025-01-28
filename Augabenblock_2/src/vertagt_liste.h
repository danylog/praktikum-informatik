#pragma once

#include <list>
#include <memory>
#include "vertagt_aktion.h"

namespace vertagt {
    template <class T>
    class VListe {
    private:
        std::list<T> p_objekte;
        std::list<std::unique_ptr<VAktion<T>>> p_aktionen;

    public:
        // Iterator type definitions
        using iterator = typename std::list<T>::iterator;
        using const_iterator = typename std::list<T>::const_iterator;

        // Iterator functions
        iterator begin() { return p_objekte.begin(); }
        iterator end() { return p_objekte.end(); }
        const_iterator begin() const { return p_objekte.begin(); }
        const_iterator end() const { return p_objekte.end(); }

        // List operations
        bool empty() const { return p_objekte.empty(); }

        void push_front(T obj) {
            p_aktionen.push_back(std::make_unique<VPushFront<T>>(p_objekte, std::move(obj)));
        }

        void push_back(T obj) {
            p_aktionen.push_back(std::make_unique<VPushBack<T>>(p_objekte, std::move(obj)));
        }

        void erase(iterator it) {
            p_aktionen.push_back(std::make_unique<VErase<T>>(p_objekte, it));
        }

        // Process all pending actions
        void vAktualisieren() {
            for (auto& aktion : p_aktionen) {
                aktion->vAusfuehren();
            }
            p_aktionen.clear();
        }

        // Clear the list
        void clear() {
            vAktualisieren();
            p_objekte.clear();
        }
    };
}
