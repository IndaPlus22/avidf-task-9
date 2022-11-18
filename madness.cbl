       IDENTIFICATION DIVISION.
       PROGRAM-ID. MADNESS.
       DATA DIVISION.
       WORKING-STORAGE SECTION.


       *> Factorial in COBOL
       77 N PIC 9(4).
       77 A PIC S9(4) VALUE 0.
       77 F PIC 9(4) VALUE 1.       
       PROCEDURE DIVISION.
       PARA.
           DISPLAY "Enter a number: ".
           ACCEPT N.

           PERFORM PARA1 UNTIL A = N.
           DISPLAY "Result: ".
           DISPLAY F.
           STOP RUN.
       PARA1.
           ADD 1 TO A.
           COMPUTE F = F * A.