— Optimize your code in order to occupy less ROM memory. Keep a record or screenshots "before" and "after".

se poate vedea in puze o reducere semnificativa, am reusit asta implementand urmatoarele schimbari:
1.Am setat la c++/compiler sa fie optimizarea pe high
2.am setat array-urile sa fie statice asta inseamna ca sunt restransa la propriul fisier, iar compilatorul poate sa elimina linking code inutil
3.am modificat variabilele sa foloseasca cel mai mic tip de memorie posibil adica unsigned char, daca se putea