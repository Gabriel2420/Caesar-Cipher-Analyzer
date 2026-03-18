DOCUMENTATION

Test cases:

// First case consists of a text with an unusual frequency of letters. This case in my implementation is a case that is not decrypted back to what is should be. The most accurate (close to actually decrypt the text) option is the chi_squared_distance function.

ZigzaggingacrossfuzzyhillsZorazealouslyzoomedzippingpastzigzagzonesziggingzaggingandzappingallzanyzeroesZebrazoomersziggedzappedandzigzaggedallzestfulandzippyZorazealwasvisibleasvividasazigzagzigzaggingfarbeyondzoningZanyzipsandzapsbuzzedaszigzagszippedzappingzingyzestinazestfulzipZorazestinesswaszappedzingingzoomingzigzaggingwithanuncannyzigzapzapzappingzigzaggingzeal

// This cases is taken into account to see if the implementation works well on a short text. It works! =)
Caesar
Apple
E

// This is a mid size text and it's stored in encryptedText.txt file already encrypted with 7 shifts ready to be decrypted. Works well with every way to calculate the distance.
THECAESARCIPHERISONEOFTHEEARLIESTKNOWNANDSIMPLESTCIPHER 
SITISATYPEOFSUBSTITUTIONCIPHERINWHICHEACHLETTERINTHEPLA 
INTEXTISSHIFTEDACERTAINNUMBEROFPLACESDOWNTHEALPHABET



My implementation consists of the following files:

1) CaesarChiperCracker.h

This is the header file where the most important functions used for solving the problem are defined.

2) CaesarChiperCracker.c

This is the file where I have the actual implementation of every function.

3) main.c

Here I did some other required functions, and I implemented an user friendly menu in console.

4) distribution.txt

Here I have the letter distribution in English. I need this for the computation of the distances in the encrypted texts.

5) encryptedText.txt

Here I can put any text I want for decryption and encryption operations.

