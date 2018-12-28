# Cryptography
A repository of programs regarding Cryptography and Cryptoanalysis.

One Time Pad:

    -Implementation of a One-Time Pad cryptographic technique, where a message is encrypted through character-by-character modular addition with the key.
  
    -The key needed for this cryptographic technique has to be random, as long as the plaintext and never reused (to follow Shannon's perfect secrecy theorem). 
  
    -The key can be generated through the program itself and can be a maximum of 4,294,967,295 characters long.
  
    -The Encryption/Decryption time is proportional to the key size. This issue will be addressed in the future.
  
  
Cyphertext Detector:

    -Distinguishes Cyphertext from Plaintext based on frequency analysis.
    
    -4 .txt files have been provided to test the Cyphertext/Plaintext Detector. 
        There are 2 Plaintext files, 1 in English and 1 in Italian.
        There are 2 Cyphertext files, 1 using a mono-alphabetic substitution cypher and 1 using a poly-alphabetic one.
