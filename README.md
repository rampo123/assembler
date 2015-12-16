# assembler

#Intro

• This is a 16 bit isa with 16 registers and some basic instructions. 
• It contains 76 instructions and opcodes are assigned to instructions using expanding opcodes technique.
• An assembler in C to convert any program written in my isa to machine code.
• a.txt -:contains all the 76 instructions ,b.txt-: contains the binary equivalent of the instructions in a.txt,assembler.c-:contains the c code for converting the code written in this isa to machine code,ins_set.txt-:write a program (corresponding to the specified isa) in this file,machine.txt-:contains the machine code of the instructions written in ins_set.txt file
• Has the option of help if there is error in writting the instruction.

#How to run

• First write a program corresponding to this isa in ins_set.txt file
• Now run the c code (in any c compiler) in assembler.c to convert the instructions written in ins_set.txt file to machine code.
• A machine.txt file is generated which contains the machine code of the instructions in ins_set.txt file. 

#Demo
A sample program correponding to this isa is written in ins_set.txt and machine.txt contains the machine code of this program.
