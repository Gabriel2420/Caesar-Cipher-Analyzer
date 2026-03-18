# Caesar Cipher Analyzer 🔐

A C++ cryptography application designed to encrypt, decrypt, and automatically break Caesar ciphers using statistical frequency analysis. 

## Features
* **Encryption/Decryption:** Securely shifts text characters while preserving casing and ignoring non-alphabet symbols.
* **Frequency Analysis:** Computes letter frequency histograms for given texts.
* **Automated Decryption:** Breaks unknown ciphers by comparing the text's distribution to standard English frequencies using three mathematical distance metrics:
  * Chi-Squared Distance
  * Cosine Distance
  * Euclidean Distance

## Tech Stack
* **Language:** C++
* **Concepts:** Cryptography, Statistical Analysis, File I/O, Pointers.
