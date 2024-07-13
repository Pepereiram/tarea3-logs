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
    BloomFilter(ll m_, ll k_, vector<ll>& prim_buffer) {
        // Inicializar el vector M con n ceros
        M = vector<bool>(m_, false);
        // Inicializar k y m
        this->k = k_;
        this->m = m_;
        // Inicializar el vector de primos y copiar los primeros k primos
        primes.resize(k);
        copy_n(prim_buffer.begin(), k, primes.begin());
        //fill_primes(prim_buffer, k);
        cout << (this->primes)[0] << endl;
    }


    //Inpirado en GeeksforGeeks, Polynomial Rolling Hash Function
    ll hash (const string& s, ll p){
        ll hash_so_far = 0;
        ll p_pow = 1;
        const ll n = s.length();
        for (ll i = 0; i < n; ++i) {
            ll char_value = s[i] >= 'a' && s[i] <= 'z' ? (s[i] - 'a' + 1) :
                        s[i] >= 'A' && s[i] <= 'Z' ? (s[i] - 'A' + 27) :
                        s[i] >= '0' && s[i] <= '9' ? (s[i] - '0' + 53) :
                        static_cast<ll>(s[i] + 100);
            hash_so_far = (hash_so_far + char_value * p_pow) % BigPrime;
            p_pow = (p_pow * p) % BigPrime;
        }
        return hash_so_far;
    }

    void add(const string& s){
        for (ll i = 0; i < k; ++i) {
            ll h = hash(s, primes[i]);
            // Imprimimos el primo
            cout << "el primo xd " << primes[i] << endl;
            cout << "el hash xd " << h << endl;
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