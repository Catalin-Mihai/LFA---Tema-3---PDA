# Translator stiva nedeterminist cu lambda-tranzitii

Implementarea s-a facut in felul urmator: 
1. Se citesc starile. Fiecarei stari ii este atribuit un index unic prin care va fi identificata in algoritm.
2. Se citeste aflabetele. Fiecarui caracter(sau siruri in cazul stivei sau alfabetului de iesire) ii este asociat un index unic. 
Asemenea starilor, index-urile ajuta la identificare pe parcursul algoritmului. 

Observatii:
- Daca se folosesc caractere ilegale(nedefinite in fisierul de intrare, programul se va opri)
- Prin folosirea acestui mecanism se pot folosi aceleasi caractere pentru mai multe alfabete, fara a perturba functionarea programului.



Liniile unui fisier de input au urmatoarea forma:

1. Nr stari
2. Starile
3. Numarul caracterelor alfabetului de intrare
4. Alfabetul de intrare
5. Numarul caracterelor alfabetului de iesire
6. Alfabetul de iesire
7. Numarul caracterelor alfabetului stivei
8. Alfabetul stivei
9. Starea initiala
10. Numarul starilor finale
11. Starile finale
12. Numarul tranzitiilor
13. Tranzitiile
    plecare | destinatie | caracter intrare citit |  caractere de iesire adaugate | caracter stiva citit | caractere stiva adaugate


Conventii:
- L -> Lambda pentru alfabetul de intrare/iesire/stiva
- $ (dolar) -> caracterul Z0 pentru stiva

