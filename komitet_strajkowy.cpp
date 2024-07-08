#include <iostream>
#include <bits/stdc++.h>
#include <limits>

using namespace std;

#define STALA 1000000007

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    int k;
    cin >> k;

    int l;
    cin >> l;

    vector<long long> arr (n, 0);
    long long in1 = 0;
    for(int i = 0; i < n; ++i)
    {
        cin >> in1;
		arr.at(i) = in1;
    }
    
    sort(begin(arr), end(arr));

    
    vector<long long> dynamika1 (n, 0);
    vector<long long> dynamika2 (n, 0);
    vector<long long> prefix (n, 0);
    
    long long lewoOpt = arr.at(0);
    long long nieOptLewy = arr.at(0);
    long long nieOptPrawy = arr.at(0);
    
    long long wartosc = 1;
    int lewaGranicaWartosci = 0;
    int prawaGranicaWartosci = 0;
    
    int granicaKonfliktow = -1;
    int ostatniWOkregu = 0;
    int granicaReprezentacji = 0;
    
    prefix.at(0) = 1;
    
    for(int i = 0; i < n; ++i)
    {
        if (abs(arr.at(i) - lewoOpt ) <= k && arr.at(i) - nieOptLewy <= k) {
            lewoOpt = arr.at(i);
            nieOptPrawy = arr.at(i);

            dynamika1.at(i) = wartosc;
        }

        if(abs(arr.at(i) - lewoOpt) <= k && arr.at(i) - nieOptLewy > k) {
            nieOptPrawy = arr.at(i);

            dynamika1.at(i) = wartosc + 1;
        }
        
        if(abs(arr.at(i) - lewoOpt) > k) {
            nieOptLewy = arr.at(i);
            lewoOpt = arr.at(i);
            nieOptPrawy = arr.at(i);
            
            wartosc = wartosc + 1;
            dynamika1.at(i) = wartosc;
        }

        if (i != 0 && i != prawaGranicaWartosci + 1 && dynamika1.at(i) != dynamika1.at(i-1)) {
            if (dynamika1.at(i) != 2) {
                lewaGranicaWartosci = (prawaGranicaWartosci + 1)%STALA;
            }
            prawaGranicaWartosci = (i - 1)%STALA;
        }
        
        if (granicaKonfliktow < 0) {
            if (arr.at(i) - arr.at(0) >= l) {
                granicaKonfliktow = 0;
            }
        }
    
        while(granicaKonfliktow >= 0 && granicaKonfliktow < i - 1 && arr.at(i) - arr.at(granicaKonfliktow) >= l && arr.at(i) - arr.at(granicaKonfliktow +1) >= l) { //PRZESKAKUJE!
                granicaKonfliktow = (granicaKonfliktow + 1)%STALA;
            }

        while(arr.at(i) - arr.at(ostatniWOkregu) > k) {
            ostatniWOkregu = (ostatniWOkregu + 1)%STALA;
        }

        while(ostatniWOkregu > 0 && arr.at(ostatniWOkregu-1) - arr.at(granicaReprezentacji) > k && granicaReprezentacji <= granicaKonfliktow) {
            granicaReprezentacji = (granicaReprezentacji + 1)%STALA;
        }

        if(dynamika1.at(i) == 1) {
            dynamika2.at(i) = 1;
        } else {
            if (granicaKonfliktow == -1) {
                dynamika2.at(i) = 0;
            } else if (lewaGranicaWartosci == 0 && granicaReprezentacji == 0) {
                dynamika2.at(i) = (prefix.at(min(granicaKonfliktow, prawaGranicaWartosci)))%STALA;
            } else if (lewaGranicaWartosci == 0 && granicaReprezentacji != 0) {
                dynamika2.at(i) = ((prefix.at(min(granicaKonfliktow, prawaGranicaWartosci)))%STALA - (prefix.at(granicaReprezentacji-1))%STALA + STALA )%STALA;
            } else if (lewaGranicaWartosci != 0 && granicaReprezentacji == 0) {
                dynamika2.at(i) = ((prefix.at(min(granicaKonfliktow, prawaGranicaWartosci)))%STALA - (prefix.at(lewaGranicaWartosci-1))%STALA + STALA )%STALA;
            } else {
                dynamika2.at(i) = ((prefix.at(min(granicaKonfliktow, prawaGranicaWartosci)))%STALA - (prefix.at(max(lewaGranicaWartosci-1, granicaReprezentacji-1)))%STALA + STALA )%STALA;
            }
        }
        
        if(i > 0) {
            prefix.at(i) = ((prefix.at(i-1))%STALA + (dynamika2.at(i))%STALA )%STALA;
        }
    }

    long long wynik1 = (dynamika1.at(ostatniWOkregu))%STALA;
    long long wynik2 = (dynamika2.at(ostatniWOkregu))%STALA;

    while(ostatniWOkregu + 1 < n && (dynamika1.at(ostatniWOkregu + 1))%STALA == (dynamika1.at(ostatniWOkregu))%STALA) {
        ostatniWOkregu = ostatniWOkregu + 1;
        wynik2 = ((wynik2)%STALA + (dynamika2.at(ostatniWOkregu))%STALA )%STALA;
    }

    cout << (wynik1)%STALA << " " << (wynik2)%STALA;
    
    return 0;
}