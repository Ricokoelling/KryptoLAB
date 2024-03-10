# KryptoLAB

### Vorlesung 1 

#### Aufgabe 1.1 
- aufgabe.cpp 
- Ausführung : 
      - c++ .\aufgabe.cpp .\kryp.h  -> .\a.exe Klartext Key Verschlüsseltertext
      - oder die exe "one.exe" ausführen welche "Klartext_1.txt 7 Verschlüsseltertext.txt" als Argumente benutzt

#### Aufgabe 1.2 
- aufgabe1_2.cpp
- Ausführung: 
      - c++ .\aufgabe1_2.cpp .\kryp.h  -> .\a.exe Verschlüsseltertext Key Klartext 
      - oder die exe "two.exe" ausführen welche "Kryptotext_1_Key_7.txt 7 Klartext.txt" als Argumente benutzt

#### Aufgabe 2
- german_texts.cpp
- Ausführung: 
      - c++ .\german_texts.cpp .\kryp.h  -> .\a.exe Verschlüsseltertext
      - oder die exe "german.exe" ausführen welche das Argument "sampleEncrypted.txt" verwendet 

#### Comment
- Es wurde ein Header benutzt um die einzelnen Funktionen zu implementieren. 
- Es wurden nur Cpp standard funktionen verwendet. 
- Die Funktion wurde mit mehreren Unit tests versehen um die Einzelnen Funktionen zu testen
      - Sowie wurde das System als ganzen Getestet 

### Vorlesung 2

#### Aufgabe 1 
- aufgabe.cpp
- Ausführung: 
      - c++ .\aufgabe.cpp .\kryp.h  -> .\a.exe Klartext Key Verschlüsseltertext
      - oder die exe "one.exe" ausführen welche "Klartext_1.txt TAG Output.txt" als Argumente benutzt

#### Aufgabe 2
- aufgabe2.cpp
-  Ausführung: 
      - c++ .\aufgabe2.cpp .\kryp.h  -> .\a.exe Verschlüsseltertext
      - oder die exe "two.exe" ausführen welche "Kryptotext_TAG.txt TAG Klartext.txt" als Argumente benutzt
      - Der dazugehörigen Key muss dann in einem folgenden Textfeld eingeben werden 

#### Comment
- Es wurde ein Header benutzt um die einzelnen Funktionen zu implementieren. 
- Es wurden nur Cpp standard funktionen verwendet. 
- Die Funktion wurde mit mehreren Unit tests versehen um die Einzelnen Funktionen zu testen
      - Sowie wurde das System als ganzen Getestet 

### Vorlesung 3
- aufgabe.cpp
- Ausführung
      - c++ .\aufgabe.cpp .\betriebsmodi.h -> .\a.exe
      - oder .\a.exe ausführen 

#### Comment 
- Es wurde ein Header benutzt um die einzelnen Funktionen zu implementieren. 
- Es wurden nur Cpp standard funktionen verwendet. 
- Die Funktion wurde mit mehreren Unit tests versehen um die Einzelnen Funktionen zu testen

### Vorlesung 4
- aufgaben.cpp 
- Ausführung 
      - c++ .\aufgabe.cpp .\AES.h -> 
            - .\a.exe e/d Klartext.txt Key.txt Output.txt  
                  - e : enkrypt
                  - d : dekrypt
            - oder einfach aes.exe welches die Beispiel_1 Vorlagen verwendet 
#### Comment 
- Es wurde ein Header benutzt um die einzelnen Funktionen zu implementieren. 
- Es wurden nur Cpp standard funktionen verwendet. 
- Die Funktion wurde mit mehreren Unit tests versehen um die Einzelnen Funktionen zu testen

### Vorlesung 5
- aufgaben.cpp
- Ausführung
      - c++ .\aufgabe.cpp .\AES.h -> 
            - .\a.exe (Betriebsmodi) Klartext.txt Key.txt Output.txt (IV)
                  - ECB und De_ECB (ohne IV sonst wird dieser ignoriert)
                  - CBC und De_CBC (mit IV sonst fehler)
                  - OFB und De_OFB (mit IV sonst fehler)
                  - CTR und De_CTR (mit IV sonst fehler,  da der Counter mit IV startet und von diesen weiter läuft )
            - oder einfach aes.exe welches die Beispiel_1 Vorlagen verwendet 
#### Comment 
- Es wurde ein Header benutzt um die einzelnen Funktionen zu implementieren. 
- Es wurden nur Cpp standard funktionen verwendet. 
- Die Funktion wurde mit mehreren Unit tests versehen um die Einzelnen Funktionen zu testen
      - Es wurden nur zusätzliche Funktion für die KeyGen getestet da die anderen Funktion zuvor getestet wurden

### Vorlesung 6
- aufgabe.cpp für SPN
- aufgaben2.cpp für Lineare Approximation
- Ausführung
      - c++ .\aufgabe.cpp .\ExampleTexts .\SPN.h -> 
            - .\a.exe 
                  - da die Texte selber erzeugt werden soll habe ich die eingabe Bereits vorgeben (sonst einfach in aufgabe.cpp ändern)
            - oder einfach spn.exe welches die Vorlagen verwendet 
      - c++ .\aufgaben2.cpp .\ExampleTexts .\LinApprox.h ->
            - .\a.exe 
                  - eingaben wurden wieder vorgegeben, kann in aufgaben2.cpp geändert werden
#### Comment 
- Es wurde ein Header benutzt um die einzelnen Funktionen zu implementieren. 
- Es wurden nur Cpp standard funktionen verwendet. 
- Die Funktion wurde mit mehreren Unit tests versehen um die Einzelnen Funktionen zu testen.

### Vorlesung 7
- aufgaben.cpp 
- Ausführung
      - c++ .\aufgaben.cpp .\gueteapprox.h -> 
            - .\a.exe (SBOX Approximation)
            - oder einfach guete.exe welches die Vorlagen verwendet 
#### Comment 
- Es wurde ein Header benutzt um die einzelnen Funktionen zu implementieren. 
- Es wurden nur Cpp standard funktionen verwendet. 
- Die Funktion wurde in ihrer Fülle getestest da die einzelnen Funktion keine Tests benötigen (keine größeren Aufgaben)

### Vorlesung 8
- aufgaben.cpp 
- Ausführung
      - c++ .\aufgaben.cpp .\RSA.h -lgmp -lgmpxx -> .\a.exe
#### Comment 
- Es wurde ein Header benutzt um die einzelnen Funktionen zu implementieren. 
- Es wird die mingw gmp library verwendet.
      - diese wurde über msys2 installiert und ist auch in den "tasks.json" mit enthalten
      - 
- Die Funktion wurde in ihrer Fülle getestest da die einzelnen Funktion keine Tests benötigen (keine größeren Aufgaben)

### Vorlesung 9
- aufgaben.cpp 
- Ausführung
      - c++ .\aufgaben.cpp .\RSAKeyGen.h -lgmp -lgmpxx -> .\a.exe
#### Comment 
- Es wurde ein Header benutzt um die einzelnen Funktionen zu implementieren. 
- Es wird die mingw gmp library verwendet.
      - diese wurde über msys2 installiert und ist auch in den "tasks.json" mit enthalten
- Die Funktion wurde mit mehreren Unit tests versehen um die Einzelnen Funktionen zu testen und das Programm in seiner Fülle wurde getestet.
