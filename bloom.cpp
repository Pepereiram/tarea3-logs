// Implementación de la clase BloomFilter

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;
// Definimos long long como ll
typedef long long ll;

class BloomFilter {
    vector<bool> M;
    vector<ll> primes;
    ll k;
    ll m;
    ll BigPrime = 1e9 + 7;

    //Constructor
    public:
    BloomFilter(ll n, ll k) {
        // Inicializar el vector M con n ceros
        M = vector<bool>(n, false);
        // Inicializar el vector de primos
        primes = vector<ll>(k);
        // Inicializar k y m
        this->k = k;
        this->m = n;
        // Llenar el vector de primos
        fill_primes();
    }

    void fill_primes(){
        // Llenar el vector de k primos distintos
        // asumimos que existe un archivo JSON con x >> k primos
        // y que podemos leerlos de ahí
        // En este caso, se generan los primeros k primos
        
        //Abrimos el archivo JSON, llamado "primes.json" 
    }

    //Inpirado en GeeksforGeeks, Polynomial Rolling Hash Function
    ll hash (const string& s, ll p){
        ll hash_so_far = 0;
        ll p_pow = 1;
        const ll n = s.length();
        for (ll i = 0; i < n; ++i) {
            hash_so_far
                = (hash_so_far + (s[i] - 'a' + 1) * p_pow)
                  % BigPrime;
            p_pow = (p_pow * p) % BigPrime;
        }
        return hash_so_far;
    }

    void add(const string& s){
        for (ll i = 0; i < k; ++i) {
            ll h = hash(s, primes[i]);
            M[h % m] = true;
        }
    }

    bool lookup(const string& s){
        // Verificar si s está en el filtro
        for (ll i = 0; i < k; ++i) {
            ll h = hash(s, primes[i]);
            if (!M[h % m]) {
                return false;
            }
        }
        return true;
    }
};