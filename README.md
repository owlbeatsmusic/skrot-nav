# SKROT-NAV
A general navigation system for a debris-collecting spacecraft, placed in a simulated earth orbit with the idea of being able to be used in real space (not possible at current state). This code is part of my upper secondary school graduation project.

![screenshot of skrot-nav from 2025-02-07](https://github.com/owlbeatsmusic/skrot-nav/blob/main/docs/images/screenshot_2025-02-07.png?raw=true)

</br>

> [!IMPORTANT]
> Everything from this point forward is in **swedish**. For **english**, see [README-english.md](https://github.com/owlbeatsmusic/skrot-nav/blob/main/README-english.md).


<br>

## 1.2 Syfte
Genom att programmera ett eget navigationssystem är syftet att få
en bättre förståelse för hur delsystemen är uppbyggda och även få insikt i tillgängligheten av
resurser inom området. Den allmänna egenskapen av navigationssystemet valdes i syftet att
skapa en mall för att öka tillgängligheten av att konstruera ett navigationssystem i rymden för
en skrotinsamlande farkost.

<br>

## 1.5 Metod

### 1.5.1 Introduktion  
Denna del av metoden kommer att i huvudsak innefatta en redovisning och förklaring av
programmets struktur. Den mest övergripande indelningen av programmet är motorn och
navigationssystemet. Motorn hanterar simulationen som navigationssystemet befinner sig i
samt hanterar det visuella användargränssnittet. Navigationssystemet är självaste programmet
som i praktiken skulle köras på en farkost i rymden.

Inledningsvis kommer programmeringsmiljön att kortfattat beskrivas, därefter motorn och sist
navigationssystemet. Motorn kan liknas med miljön runt om navigationssystemet och består
av tre delar. Den första delen är rymdsimulationen som beräknar krafter och uppdaterar
positioner. Den andra delen är renderaren som hanterar användargränssnittet och därmed
kopplingen mellan programmet och användaren. Den sista delen är simulationen av
nedlänken, vilket är kommunikationen ned till jorden. Navigationssystemet delas upp i
framför allt kärnan som är navigationssystemets utgångspunkt, flygvägsbestämningen som
skapar vägen för att samla in rymdskrot och sist positionsbestämning vilket behövs för
skapandet av flygvägar. Navigationssystemet innehåller även en del som hanterar
kommunikation och en del för interaktion med enheter som exempelvis RADAR.

![project-structure-overview](https://github.com/owlbeatsmusic/skrot-nav/blob/main/docs/images/project-overview-diagram.png?raw=true)

**Figur 1.** Diagram över den övergripande filstrukturen och interaktionen mellan motor (/src/engine/) och navigationssystem
(/src/nav/).

Navigationssystemet har i huvudsyfte att fungera som en mall för praktiska applikationer
medan det fortfarande ska vara operativt i simulationen. Delarna ska vara fristående ty
navigationssystemet ska kunna separeras från motorn och kunna appliceras i praktiken.
Programmet har även öppen källkod i syfte av användning i praktiken. Öppen källkod innebär
att koden finns tillgänglig på internet och därmed för allmänheten. Den tvådelade strukturen
av programmet i form av motor och navigationssystem är därmed basen för hela projektet.

Det finns även en tredje del i den övergripande strukturen som är hjälparfunktioner. Dessa
funktioner är allmänna vilket innebär att de kan användas i andra funktioner över hela
programmet och är inte specifika för någon del av programmet. Ett exempel på en
hjälparfunktion är funktionen: ”vector_normalize()” i filen ”/src/common/vector.c” som
beräknar normalen av en vektor.

För att påbörja planeringen av motorn och navigationssystemet söktes relevanta källor.
NASA:s ”Basics of Spaceflight”, en webbsida skriven av Dave Doody (Doody, 2024), ger en
översiktlig bild av grunderna inom rymdflygning. Sidan diskuterar olika typer av farkoster,
deras komponenter och hur navigationen går till i rymden. Varav det senare är av störst
intresse för denna undersökning men även tekniska specifikationer av somliga komponenter
är av intresse. Den grova uppdelningen av navigationssystemet är att skapa och kontrollera
flygvägar. För att skapa dessa flygvägar behövs information om farkostens position (Doody,
2024) och närliggande skrots position.

---

</br>

### 1.5.2 Programmeringsmiljö  
Hela projektet är programmerat i programmeringsspråket C och följer iso9899:1999, vilket är
standarden för C år 1999. Kompilering och i huvudsak hela koden följer JPL:s (NASA Jet
Propulsion Laboratory) standard för C (JPL, 2009).

---

</br>

### 1.5.3 Motorn 

#### 1.5.3.1 Rymdsimulationen (`src/engine/space.c`)  
Skapandet av motorn påbörjas innan navigationssystemet. Simulationen av rymden avgränsas
till det minsta nödvändiga för att navigationssystemet ska fungera. Anledningen till
avgränsningen är att simulationen inte är det huvudsakliga fokuset av undersökningen och
eftersom tiden för arbetet är begränsad. Målet med rymdsimulationen är att skapa rymdskrot
och sedan simulera både skrotet och den skrotinsamlande farkostens bana runt jorden. Kärnan
i rymdsimulationen är en slinga som primärt uppdaterar alla positioner med Eulers
Stegmetod. Slingan upprepar ett variabelt antal gånger (steg) med mellanrummet ∆t. För varje
steg används en funktion för att beräkna gravitationskraften som varje objekt utsätts för vilket
används för att beräkna accelerationen som därefter används för att beräkna objektets
hastighet med Eulers Stegmetod genom följande:  

$v_x = a_x \cdot \Delta t$

$v_y = a_y \cdot \Delta t$

$v_z = a_z \cdot \Delta t$

Alla objekts, d.v.s. farkostens och rymdskrotets, initiala positioner sätts slumpmässigt i jorden
LEO. För att gå i en korrekt bana runt jorden behöver även deras initiala hastigheter sättas till
omloppshastigheten samt att hastigheternas riktningar behöver vara vinkelräta mot objektens
positionsvektorer. För varje objekt tas hastigheten fram genom att beräkna storleken på
hastighetsvektorn med formeln för omloppshastighet och därefter beräkna hastighetsvektorns
riktning genom att ta kryssprodukten av positionsvektorn med en godtycklig vektor. Sist sätts
objektets hastighet. Dessa beräkningar representeras i programmet på detta vis:

```c
int r = vector_distance(position, earth_pos);
float orbital_velocity = sqrt(G * M / r);

Vector3 temp_vector = {0, 0, 1};
Vector3 velocity_direction = vector_cross_product(position, temp_vector);
velocity_direction = vector_normalize(velocity_direction);

SpaceObject temp_space_object = {
    type,
    (Vector3){ position.x, position.y, position.z },
    (Vector3){ velocity_direction.x * orbital_velocity,
               velocity_direction.y * orbital_velocity, 
               velocity_direction.z * orbital_velocity }, 
    mass
};
```

---

</br>

#### 1.5.3.2 Renderaren (`src/engine/renderer.c`)  
Det grafiska användargränssnittet är inte direkt relevant för frågeställningen, likt
rymdsimulationen, utan har som mål att snabbt visualisera nödvändig information till
användaren för att kunna bekräfta navigationssystemets funktion. Renderarens viktigaste
funktion är att visualisera jordensomloppsbana för att kunna redogöra för positionen av
rymdskrot och farkost. Denna redogörelse görs genom vyer som visar en tvådimensionell bild
av två axlar.

```c
View renderer_views[] = {
    {0, 0, -1, RENDERER_SPACE_WIDTH/2, 'x', 'z'}, 
    {1, 0, -1, RENDERER_SPACE_WIDTH,   'x', 'z'},
    {2, 0, -1, RENDERER_SPACE_WIDTH,   'x', 'y'},
};
```

I denna lista av vyer kan ordning de befinner sig i användargränssnittet modifieras med de två
första argumenten. Skalan på vyn bestäms genom det fjärde argumentet genom att ange
bredden som vyn ska visa. Det tredje argumentet avgör ifall vyn ska centrera och följa något
objekt, där -1 är inget objekt. I filen ”main.c” sätts den första vyn till att följa farkosten: 

```c
renderer_views[0].center_object_index = nav_spaceobjects_index;
```

Dessa vyer kan skapas och modifieras av användaren genom att anpassa listan samt att sätta
centrering.

#### 1.5.3.3 Nedlänken(`src/engine/downlink.c`)  
Nedlänken är kommunikationen från farkosten upp till jorden. Målet med simulationen av
nedlänken är att både skicka förfrågningar om information från farkosten, som exempelvis
den aktiva flygbanan, och att ta emot och svara på förfrågningar från farkosten.

---

</br>

### 1.5.4 Navigationssystemet (`src/nav/`)  
Navigationssystemet styrs i grunden från kärnan där den centrala processen, alltså slingan,
befinner sig. I den processen startas navigationssystemet genom att påbörja systemets
huvudsakliga syfte: skapandet av en flygväg. En flygväg är den bana som
navigationssystemet planerar för att ta sig till rymdskrot. Skrotet lokaliseras genom
sammanställning av hämtad och samlad information. Innan rymdvägen skapas behövs
positionen av farkosten i rymden vilket beräknas med information från nedlänken.

![navigation-system-diagram](https://github.com/owlbeatsmusic/skrot-nav/blob/main/docs/images/navigation-system-diagram.png?raw=true)

**Figur 2.** Diagram över den huvudsakliga interaktionen mellan navigationssystemets delar för subsystemet för
flygvägsbestämnig. Flygväg, objektsdetektering, bästa flygväg och drift från flygväg sker i flight_path.c. Position
bestämning sker i position.c. Kommunikation sker i communication.c och enheter hanteras i devices.c.

</br>

#### 1.5.4.1 Navigation: Kärnan (`src/nav/core.c`)  
Kärnan av programmet hanterar två olika delar som kategoriserar enligt följande: styra
programmet genom den centrala processen och att koppla samman navigationssystemet med
simulationen. Detta innebär att kärnan även är startpunkten för systemet. Kärnan hanterar då
som följd avstängning av systemet samt andra basnivåfunktioner. Systemet och den interna
klockan startas, och navigationssystemet kopplas samman med simulationen genom följande
funktion (pseudokod):

```c
nav_core_create() {
    nav_spaceobjects_index = space_append_spaceobject();
    start_time = time(NULL);
    nav_core_proc_main_internal();
}
```

</br>

#### 1.5.4.2 Navigation: Flygväg (`src/nav/flight_path.c`)  

Flygvägsdelen av programmet hanterar fyra olika delar som kategoriserar enligt följande:
skapande av flygväg, lokalisering av rymdskrot, skapandet och utförande manövrar, och drift
från flygväg. Främst är startpunkten för skapandet av en flygväg samt uppdatering av den
flygvägen. Skapandet av en flygväg sker i två tre steg. Först avgöra farkostens egen position
(1.5.4.3) sedan lokalisera närliggande skrot, och sist skapa och utföra nödvändiga manövrar.
Rymdskrotets position tas reda på genom att skanna farkostens omgivning med de valda
enheter som exempelvis RADAR och LIDAR.

</br>

#### 1.5.4.3 Navigation: Position (`src/nav/position.c`)  

Positionsdelen av programmet hanterar tre olika delar som kategoriseras enligt följande:
utvärdering och förutsägelse av position, kollisionsdetektering, och förfrågning och
inställning av mätdata. Utvärderingen av farkostens position inleds genom att skicka
mätdataförfrågningar till nedlänken. När den förfrågade informationen anlänt från nedlänken
kommer den användas för att beräkna farkostens position.

Här kommer steget från förfrågning till inställning av mätdata att beskrivas. I NASA:s ”Basic
of Spaceflight” lyfts de tre viktigaste mätdata för bestämning av position i rymden. Dessa tre
är farkostens avstånd från jorden, radialhastigheten och position på jordens himmel. Denna
information behöver hämtas från nedlänken och sker genom att först skicka en förfrågan om
informationen. Förfrågan är ett kommunikationsdatapaket som innehåller variabler för de
olika mätdata och ett unikt ID samt ett förfrågnings-ID (se variablers representation i kod i
tabell 1)

Paketet förs till filen ”communication.c” där den sänds vidare till transmittern i ”devices.c”
.
Därifrån skickas paketet till nedlänken. I nedlänken skapas ett nytt paket vars förfrågnings-ID
sätts till förfrågningspaketets ID. Den förfrågade informationen läggs även in i det nya
paketet. Därefter skickas paket tillbaka till ”communication.c ” i farkosten och uppdaterar
informationen om den förfrågade mätdata i ”position.c”.

![request-set-diagram](https://github.com/owlbeatsmusic/skrot-nav/blob/main/docs/images/request-set-diagram.png?raw=true)

**Figur 3.** Diagram över förfrågning och inställning av mätdata. Informationen hämtas från nedlänken och uppdateras i
programmets positionsdel (src/nav/position.c)

</br>

#### 1.5.4.4 Navigation: Kommunikation (`src/nav/communication.c`)  
Kommunikationsdelen av programmet hanterar i huvudsak två delar som kategoriserar enligt
följande: pakethantering och kösystem för förfrågningar. Pakethanteringen består i sin tur av
fyra funktioner: att skapa paket, skicka paket, ta emot paket och att lagra paket.
Paketen består av informationen som skickas mellan olika delsystem, och mellan farkosten
och jorden. Det finns två typer av paket: kommunikationspaket och hälsopaket.
Kommunikationspaketen används för generell kommunikation och är antingen av skickande
typ, som exempelvis ett svar på en dataförfrågning, eller av mottagande typ som exempelvis
manuella styrningsinstruktioner från jorden. Hälsopaketet används främst vid kontroller av
fysiska enheter och innehåller information som temperatur och tryck.

---

</br>


### 2. Slutsats  

Det är möjligt att skapa ett mycket grundläggande allmänt navigationssystem i rymden för en
skrotinsamlande farkost. Systemet kan struktureras genom att delas upp i huvudsakligen kärna
och flygvägsbestämnig. Flygvägsbestämningen delas upp i positionsbestämning,
objektsdetektering, skapandet av serier av manövrar och koppling till kommunikation och
enheter.

---

</br>

### Källor
Doody, D. (2024-10-04). Basics of Spaceflight. From NASA: https://science.nasa.gov/learn/basics-of-space-flight/

JPL. (2009-03-03). JPL Institutional Coding Standard for the C Programming Language. From: https://yurichev.com/mirrors/C/JPL_Coding_Standard_C.pdf
