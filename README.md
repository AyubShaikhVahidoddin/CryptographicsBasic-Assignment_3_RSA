# CryptographicsBasic-Assignment_3_RSA
Ayub_Shaikh_CryptographyAssignment-3: To compare the timing difference between RSA Encryption and Decryption with and without Chinese Remainder Theorem.
RSA Vs  RSA With CRT timing Difference Table from above program execution screenshots:

The main program file is written in C language.                 
Name of C Program file for timing difference is => RSA_CRTTimingDiff_Implementation.c

The .exe file is also attached Name of EXE is RSA_CRTTimingDiff_Implementation.exe

	input	     RSA(Time in Seconds)	 RSA with Chines Reminder Theorem (Time in Seconds)
1	10	       7.97 Sec	                  0.0957 sec
2	20	       10.99 Sec	                0.0780 Sec
3	30	       9.26 Sec	                  0.06 sec
4	20000	     15.235 Sec	                0.094 sec
5	100000	   18.456 Sec	                0.121 Sec
6 800000     19.385 Sec                 0.169 Sec

RSA encryption algorithm is one of the most powerful public key encryption algorithm. 
The problem with RSA algorithm is that RSA decryption is relatively slow in comparison to RSA encryption.
Chinese Remainder Theorem (CRT), a modulo based mathemati- cal theorem, is proposed by researchers as a way to enhance the performance of decryption. 
CRT minimizes the mathematical computation to large extent, thus improving the speed. CRT is well known for improving RSA’s decryption speed.
