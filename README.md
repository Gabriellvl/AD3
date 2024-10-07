
# Unieke Cyclische Strings

Voor een zeer specifiek onderzoeksprobleem hebben we een programma dat een hele hoop strings genereert. De gegenereerde strings worden echter **cyclisch** geïnterpreteerd. Dat wil zeggen dat we alle cyclische rotaties van eenzelfde string dus als equivalent beschouwen. Bijvoorbeeld: `snel`, `nels`, `elsn`, en `lsne` stellen dezelfde cyclische string voor. We willen nu een efficiënte filter maken voor onze generator die elke cyclische string maar één keer output.

Wanneer we alle rotaties van een string zouden moeten opzoeken in een datastructuur, dan wordt dat misschien wel heel traag. Een handige truc om efficiënt unieke cyclische strings te bepalen, is om ze om te zetten naar een _canonieke_ vorm. Dat is een vorm die voor elke rotatie dezelfde is. Een goed voorbeeld daarvan is de lexicografisch minimale rotatie, dat is die cyclische rotatie die eerst zou komen wanneer je alle rotaties sorteert. Voor `snel`  is de lexicografisch minimale rotatie `elns`, voor `banaan` is dat `aanban`.  De canonieke vorm opslaan of opzoeken in een relevante datastructuur is dan voldoende om te weten of je een rotatie al eens gezien hebt.

Het doel van dit project is om een CLI-programma te schrijven dat strings inleest van op standaard invoer en daarvan slechts één per equivalentieklasse terug uitschrijft naar standaard uitvoer. We vergelijken daarbij verschillende datastructuren om de strings in op te slaan.

Vraag gerust aan Steven welk zeer specifiek onderzoeksprobleem hij wil oplossen; maar dat is voor de opgave van dit project niet belangrijk.

## Opdracht

We werken in dit project stapsgewijs toe naar ons finale programma. Je kan elk van onderstaande onderdelen apart implementeren en testen.

Je mag gerust ook experimenteren met andere implementaties of algoritmes om het finale programma sneller te maken.

### Implementatie van lexicografisch minimale rotatie

Implementeer de functie `void lexicographically_minimal_rotation(char* input)` uit `include/cyclic_string.h` die de `input`-string in-place omzet naar de lexicografisch minimale rotatie.

Naïeve algoritmes zullen hiervoor $O(n^2)$ nodig hebben in het slechtste geval. Er bestaan voor dit probleem ook asymptotisch snellere (lineaire) algoritmen, maar het is niet nodig die te implementeren. Probeer natuurlijk wel om je implementatie efficiënt te maken. Als je toch algoritmes gebruikt van het internet moet je die natuurlijk wel goed begrijpen en kunnen uitleggen.

Naast andere algoritmes kan je ook nadenken of je jouw implementatie niet sneller kan maken door slim te werken met de vergelijkingen: je kan bijvoorbeeld meerdere karakters in één keer vergelijken als 64-bit woord i.p.v. één byte. C is namelijk dé taal om met bit-operaties te werken.

De input-string voor deze functie is null-terminated, d.w.z. dat een karakter met waarde 0 (`\0`) het einde van de string markeert. De uitvoer-string moet dat ook zijn. 

### Implementatie van de datastructuren

Je zal drie datastructuren moeten implementeren: een uitbreidbare hashtabel, een trie en een gewone zoekboom.

Je moet minstens de functies uit elk header-bestand implementeren. Maar je mag ook specifieke extra methodes implementeren om je programma sneller te maken of om ze makkelijker te kunnen testen. Misschien bestaat er wel een datastructuur die zich goed leent tot het efficiënt opzoeken van circulaire strings?

Je hoeft geen verwijderoperaties te implementeren, maar de datastructuur mag geen geheugenlekken hebben en moet het gebruikte geheugen dus netjes terug vrijgeven.

#### Hashtabel
 
Maak een hashtabel die het header-bestand `include/hashtable.h` implementeert. Maak zelf een beredeneerde keuze of je Linear of Extendible hashing implementeert en leg die keuze uit in je verslag. Experimenteer met de hoeveelheid sleutels die je opslaat in één bucket en maak een beredeneerde keuze voor een optimale grootte.

Je hoeft zelf geen eigen hashfunctie te implementeren. Je mag open-source implementaties van bestaande hashfuncties overnemen in je project op voorwaarde dat je in het broncodebestand correct verwijst naar de originele implementatie samen met de licentie. Verdedig in je verslag de keuze van deze hashfunctie.

**Hint:** er zijn een hoop verschillende hashfuncties met ieder hun eigen toepassingen. Kies de hashfunctie dus zorgvuldig. MurmurHash3 is een voorbeeld van een efficiënte hashfunctie. 

#### SearchTree

Maak een trie die het header-bestand `include/trie.h` implementeert. Bij de implementatie van je trie mag je gebruikmaken van de technieken die we zien in de cursus bij Patricia Tries en Ternary Tries. Licht de keuze van je implementatie toe in je verslag.

#### Tree

Maak een zoekboom die het header-bestand `include/searchtree.h` implementeert.  Je mag hierbij kiezen welke zoekboom je implementeert. Bijvoorbeeld: semi-splay, rood-zwart boom, AVL-boom... Je hoeft je daarbij niet te beperken tot bomen die eerder in de opleiding aan bod kwamen. Beargumenteer in je verslag waarom je die zoekboom hebt gekozen.

Beredeneer en bespreek je implementatie in je verslag.

### Implementatie van het CLI-programma

Hier komt alles bij elkaar: implementeer een programma `cycluniq` dat één argument neemt: `<datastructuur>` waarbij de datastructuur `hashtable`, `trie` of `searchtree` is.

Op standaard invoer (`stdin`) krijgt je programma lijnen van ASCII-karakters gescheiden door newlines (`\n`).

Als uitvoer schrijf je alle lijnen waarvan een circulaire rotatie nog niet eerder werd verwerkt door het programma.

#### Voorbeeld

**Invoer:**
```
meetsysteem
kadering
schildpadsoep
ringkade
ree
eer
pakketbom
parterretrap
bompakket
ere
soepschildpad
```

**Uitvoer:**
```
meetsysteem
kadering
schildpadsoep
ree
pakketbom
parterretrap
```

### Tips

De functies die je moet implementeren, dienen enkel om te bepalen of jouw implementatie correct is. **Je mag extra functies implementeren zodat je specifieke optimalisaties kan doen**. Bijvoorbeeld: een methode die meerdere strings in één keer opslaat in een datastructuur.

### Programmeertaal

In de opleidingscommissie informatica (OCI) werd beslist dat, om meer ervaring met het programmeren in C te verwerven, het project van Algoritmen en Datastructuren 3 in C geïmplementeerd moet worden. Het is met andere woorden de bedoeling je implementatie in C uit te voeren. Je implementatie moet voldoen aan de ANSI-standaard. Je mag hiervoor dus gebruikmaken van de laatste features in C17, voor zover die ondersteund worden door de `C` compiler die gebruikt wordt voor dit project op SubGIT (GCC 13.2).

Voor het project kun je de standaard libraries gebruiken, externe libraries zijn echter niet toegelaten. Het spreekt voor zich dat je normale, procedurele C-code schrijft en geen platformspecifieke API's (zoals bv. de Win32 API) of features uit C++ gebruikt. Op Windows bestaat van enkele functies zoals `qsort` een "safe" versie (in dit geval `qsort_s`), maar om je programma te kunnen compileren op een Unix-systeem kun je die versie dus niet gebruiken. Let er ook op dat je programma geen geheugenlekken bevat.

**Wat jouw ontwikkelingsplatform ook mag zijn, controleer geregeld de output van SubGIT om te verifiëren dat je programma ook bij ons compileert en slaagt voor de minimale testen!**

### Limieten

We lijsten hieronder enkele limieten op die je kan gebruiken tijdens je implementatie:

- De invoerlijnen hebben een maximale lengte van 4095 ASCII-karakters, inclusief newline.
- Elk karakter van een lijn is 8-bits waarvan enkel de decimale waarden 63 (?) tot en met 126 (~) kunnen voorkomen in de circulaire string.
- Elke lijn eindigt met een line-feed karakter (`\n` ) met decimale waarde 10.
- De strings die je als argument meekrijgt in de functies uit de header-bestanden zal je (tijdens onze testen) krijgen als _referentie_. Dat wil zeggen dat er geen garantie is dat de pointer geldig blijft nadat de toevoegbewerking beëindigd is. In dat geval zal je dus een kopie moeten opslaan van de toegevoegde string. Voor strings die je inleest van `stdin` kies je natuurlijk zelf hoe je er mee omgaat.
- Je datastructuren mogen maximaal 16 MB geheugen reserveren bij de initialisatie, maar moeten groeien wanneer ze meer data moeten opslaan.
- Voor onze grootste dataset mag je programma niet meer dan 1024 MiB geheugen gebruiken.
- Je programma moet de strings al uitschrijven terwijl je nog niet alle invoer verwerkt hebt. Je mag daarbij wel in batches werken van maximaal 1048576 bytes (1 MiB, de maximale pipe buffer van een gemiddeld Unix-systeem).
- Zorg ervoor dat er geen geheugenlekken in je programma zitten en dat al het gealloceerde geheugen op het einde weer wordt vrijgegeven.

### Datasets

In het mapje `data/` zal je de voorbeeld-invoerbestanden vinden en een `generator.py` script die grotere testbestanden kan maken.
Tijdens het verbeteren en benchmarken gaan we gelijkaardige (maar niet dezelfde) invoerbestanden gebruiken.

Je mag deze datasets zelf gebruiken om je implementatie te testen en te benchmarken.

## Verslag

Maak een kort en bondig verslag van maximaal **1500 woorden** waarin onderstaande zaken worden behandeld:

### Datastructuren

- Welke hashtabel heb je gebruikt? Waarom?
- Welke trie heb je geïmplementeerd? Waarom?
- Welke zoekboom heb je geïmplementeerd? Waarom?

### Optimalisaties voor circulaire strings

- Welk algoritme heb je geïmplementeerd om circulaire strings met elkaar te vergelijken of de minimale rotatie te vinden? Welke optimalisaties heb je toegepast?

### Benchmarks & vergelijking

Beantwoord onderstaande vragen door benchmarks uit te voeren waarvan je de tijdmetingen toont in een grafiek.

- Wat is de optimale hoeveelheid strings in één bucket van je hashtabel?
- Welke datastructuur werkt het snelst?
- Welke datastructuur gebruikt het minst geheugen?

### Conclusie

- Welke datastructuur zou je aanbevelen?

## Indienen

### Directorystructuur

Je indiening moet de volgende structuur hebben:

- `include/` bevat onze opgave-headerbestanden
- `src/` bevat alle broncode
- `data/` bevat generators voor testbestanden of héél kleine bestanden (push geen grote testbestanden)
- `test/` alle testcode (je moet testcode hebben)
- `benchmark/` scripts of code voor je benchmarks
- `extra/verslag.pdf` bevat de elektronische versie van je verslag. In deze map
  kun je ook eventueel extra bijlagen plaatsen zoals de broncode van je verslag.
- `sources-{cycluniq,cylic,hashtable,searchtree,trie}`: tekstbestanden met de`.h` en `.c` bronbestanden om elk onderdeel te compileren, 1 per lijn relatief t.o.v. de root van je project Bijvoorbeeld in `sources-hashtable`:

      include/hashtable.h
      src/hashfunctie.c
      src/hashtable.c

Je mappenstructuur ziet er dus ongeveer zo uit:

    |
    |-- extra/
    |   `-- verslag.pdf
    |-- include/
    |   `-- de opgave-headerbestanden
    |-- src/
    |   `-- je broncode
    |-- test/
    |   `-- je testcode
    |-- benchmark/
    |   `-- je benchmark-code
    |-- data/
    |   `-- onze datasets
    |-- sources-cycluniq
    |-- sources-cycliq
    |-- sources-hashtable
    |-- sources-searchtree
    \-- sources-trie

Al je bestanden moeten als UTF-8 opgeslagen zijn.

### Compileren

De code zal bij het indienen gecompileerd worden met (ruwweg) onderstaande
opdracht door SubGIT met **GCC 13**:

```sh
gcc -std=c17 -Og -Wall -Werror $(cat ./sources-cycluniq) -o cycluniq 
```

De `Dockerfile` en bijhorende bronbestanden die SubGIT gebruikt, kan je vinden in de Git-repository `git@SubGIT.UGent.be:2024-2025/AD3/project-dockerfile`. Je kan de testen van SubGIT lokaal uitvoeren met de volgende commando's in deze repository:

```sh
docker build . -t ad3-project-2024 # hoef je maar één keer te doen
docker run -it --rm --mount type=bind,source={PAD},destination=/submission,readonly ad3-project-2024
```

Waarbij `{PAD}` vervangen dient te worden door het absolute pad naar de hoofdmap (niet `src`) van je code.

### SubGIT

Het indienen gebeurt via het [SubGIT](https://SubGIT.ugent.be/) platform. Indien je hier nog geen account op hebt, dien je die aan te maken.

#### Repository afhalen

```bash
git clone git@SubGIT.ugent.be:2024-2025/AD3/project/{studentnr} project-AD3
```

Deze repository zal leeg zijn.

#### Opgave als `upstream` instellen

Je kan de opgave en data voor het project afhalen door de opgave repository als upstream in te stellen met volgende commando's in de `project-AD3` map:

```bash
git remote add upstream git@SubGIT.UGent.be:2024-2025/AD3/project-assignment
git pull upstream main
```

(Je kan niet pushen naar de upstream, alleen de lesgevers kunnen dat.)

#### Feedback

Als je pusht naar SubGIT, zul je in je terminal te zien krijgen of je code
voldoet aan de minimumvereisten. In dat geval krijg je bij het pushen de melding
dat het pushen geslaagd is:

```
remote: Acceptable submission
```

Je kan geen code pushen naar de `main` branch als die niet compileert of niet
aan de minimale vereisten voldoet. Je kan echter wel pushen naar andere
branches en daar zal je push wel aanvaard worden.

#### De `main` branch

De `main` branch op SubGIT stelt jouw indiening voor. Je kan voor de deadline
zoveel pushen als je wilt. Zorg ervoor dat je voor de deadline zeker je finale
versie naar de **`main`** branch hebt gepusht, want enkel die zal verbeterd worden.

**Belangrijke wijziging t.o.v. vorig jaar:** vroeger moest je pushen naar de `master`-branch, dit is nu de `main`-branch geworden.

#### Controleren of je zeker goed hebt ingediend

Je kan jouw indiening bekijken door jouw repository nog eens te clonen in een andere map

```bash
git clone git@SubGIT.ugent.be:2024-2025/AD3/project/{studentnr} project-AD3-Controle
```

### Deadlines en belangrijke data

Zorg ervoor dat je een tussentijdse versie hebt gepusht naar een branch (niet noodzakelijk `main`, moet zelfs niet compileren) op SubGIT voor **woensdag 2024-11-06 om 17:00:00**.
De versie die je hier indient, zal niet beoordeeld worden, we vragen je dit te doen om er zeker van te zijn dat iedereen kan indienen.
Als je niets pusht voor deze deadline verlies je al je punten voor het project.

De code die op **woensdag 2024-12-04 om 17:00:00** op de `main` branch staat, is je finale code-indiening.
Enkel code die op dat moment op de `main` branch staat, wordt verbeterd.
**Als er geen code op je `main` branch staat, krijg je nul op vier voor het project.**
Je kan na deze deadline nog steeds pushen om wijzigingen aan te brengen aan het verslag en je benchmarks.

Na **woensdag 2024-12-11 om 17:00:00** kun je ook helemaal geen wijzigingen meer aanbrengen aan je repo.
Het verslag dat aanwezig is als pdf op de `main` branch in `extra/verslag.pdf` is je finaal verslag.

## Algemene richtlijnen

- Schrijf efficiënte code, maar ga niet over-optimaliseren: **geef de voorkeur
  aan elegante, goed leesbare code**. Kies zinvolle namen voor methoden en
  variabelen en voorzie voldoende commentaar. Let op geheugenhygiëne: ga actief
  op zoek naar geheugenlekken en alloceer niet onnodig veel geheugen.
- Op SubGIT staat een Dockerfile waarmee je een Linux container kan bouwen die
  jouw code compileert en minimale testen uitvoert. Als alle testen slagen zal 
  dit programma `Acceptable submission` uitschrijven als laatste regel en 
  stoppen met exit code 0. Code die hier niet aan voldoet, zal geweigerd worden
  door SubGIT en levert geen punten op (0/4 voor het project).
- Het project wordt gequoteerd op **4** van de 20 te behalen punten voor dit
  vak, en deze punten worden ongewijzigd overgenomen naar de tweede
  examenperiode.
- Projecten die ons niet via de `main`-branch op SubGIT bereiken voor de
  deadline worden niet meer verbeterd: dit betekent het verlies van alle te
  behalen punten voor het project.
- Dit is een individueel project en dient dus door jou persoonlijk gemaakt te
  worden. Het is uiteraard toegestaan om ideeën
  uit te wisselen, maar **het is verboden code uit te wisselen**,
  op welke manier dan ook. Het overnemen van code beschouwen we als fraude (van
  **beide** betrokken partijen) en zal in overeenstemming met het
  examenreglement behandeld worden. Op het internet zullen ongetwijfeld ook
  (delen van) implementaties te vinden zijn. Het overnemen of aanpassen van
  dergelijke code is echter **niet toegelaten** en wordt gezien als fraude. (Als
  je je code op GitHub/Bitbucket/sourcehut/Gitlab/… plaatst moet je die privaat
  houden).
- Het gebruik van AI-assistenten zoals ChatGPT, GitHub CoPilot... is afgeraden, maar niet verboden.
- Alle code die je indient moet je zelf volledig begrijpen en kunnen uitleggen (tenzij voor de hashcode-implementatie). Bij twijfel over fraude moet je ook kunnen aantonen hoe de code eventueel werd gegenereerd door een AI-systeem. Anders krijg je 0 punten voor het project.
- Er worden punten afgetrokken voor tekst die uitzonderlijk rond de pot draait, of foute beweringen maakt, zoals vaak het geval is bij teksten gegenereerd door AI.
- Essentiële vragen worden **niet** meer beantwoord tijdens de week voor de laatste deadline.

## Vragen

Als je vragen hebt over de opgave of problemen ondervindt, dan kun je je vraag
stellen tijdens het practicum op dinsdagvoormiddag. Contacteer je ons per mail,
stuur dan ook je studentennummer en de branch waarop de code met het probleem
zit mee. Zo kunnen we onmiddellijk je code pullen. Stuur geen screenshots van
code of foutboodschappen.

