# Inl-mningsuppgift-2
Det här är min kod till inlämningsuppgift 2. Språk c++

Det är ett ganska enkelt C++-program för att samla in, visa, sortera och spara mätdata med tidsstämplar.

Programmet låter användaren:
	Lägga till nya mätvärden 
	Visa alla sparade värden
	Sortera listan stigande eller fallande
	Visa statistik (antal, medelvärde, min, max, standardavvikelse)
	Ta bort specifika värden
	Spara all data till fil 

Data sparas automatiskt vid avslut och laddas in igen nästa gång programmet startas.

Så här kan det se ut till exempel.
--- MENY ---
1. Lägg till mätvärde
2. Visa alla
3. Sortera
4. Visa statistik
5. Ta bort värde
6. Avsluta
Val: 1
Skriv in mätvärden (skriv 'q' för att avsluta):
Värde: 23.4
Värde: 25.1
Värde: q

Jag har också gjort att data sparas i filen data.csv det innebär:

Datum och tid
Mätvärde
2025-10-24 13:45
21.5
2025-10-24 14:02
19.8

 Krav
	•	C++20 eller senare (p.g.a. ranges::sort)
	•	Filen data.csv skapas automatiskt om den inte finns


  


Det här var en liten förklaring på min kod i c++
