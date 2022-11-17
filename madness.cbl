       IDENTIFICATION DIVISION.
       PROGRAM-ID. madness.
       AUTHOR. Avid Fayaz

       DATA DIVISION.
       WORKING-STORAGE SECTION.
       *> factorial in COBOL

         77 factorial pic 9(15) comp.
         77 n pic 99.
         77 i pic 99.
         77 ist pic XX.
         77 factorialSet pic X(18).

       PROCEDURE DIVISION.
         move 16 to n
         move 0 to i
         move 1 to factorial
         perform until i greater than n
           move i to ist
           move factorial to factorialSet
           display ist "! = " factorialSet
           add 1 to i
           multiply i by factorial
             on size error display "input exceeds limit!"
           end-multiply
         end-perform.
         stop run.