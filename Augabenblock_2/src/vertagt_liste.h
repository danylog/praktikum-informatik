// vertagt_liste.h
#pragma once

#include <list>
#include <memory>

namespace vertagt {
    template <class T>
    class VListe {
    public:
        // Default constructor
        VListe() = default;

        // No copy constructor
        VListe(const VListe&) = delete;

        // No copy assignment
        VListe& operator=(const VListe&) = delete;

        // Move constructor
        VListe(VListe&&) = default;

        // Move assignment
        VListe& operator=(VListe&&) = default;

        void push_back(T&& obj) {
            // Use move semantics
            p_aktionen.push_back(std::move(obj));
        }

        void push_front(T&& obj) {
            // Use move semantics
            p_aktionen.push_front(std::move(obj));
        }

        bool empty() const {
            return p_liste.empty();
        }

        void vAktualisieren() {
            // Move all elements from p_aktionen to p_liste
            for (auto& aktion : p_aktionen) {
                p_liste.push_back(std::move(aktion));
            }
            p_aktionen.clear();
        }

        // Iterator access
        using iterator = typename std::list<T>::iterator;
        using const_iterator = typename std::list<T>::const_iterator;

        iterator begin() { return p_liste.begin(); }
        iterator end() { return p_liste.end(); }
        const_iterator begin() const { return p_liste.begin(); }
        const_iterator end() const { return p_liste.end(); }

        // Erase with proper iterator handling
        iterator erase(iterator it) {
            return p_liste.erase(it);
        }

    private:
        std::list<T> p_liste;
        std::list<T> p_aktionen;
    };

    // VAktion class for delayed operations
    template <class T>
    class VAktion {
    public:
        virtual ~VAktion() = default;
        virtual void vAusfuehren() = 0;
    };
}
