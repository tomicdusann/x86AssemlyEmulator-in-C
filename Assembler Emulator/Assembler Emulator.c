#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MEM_SIZE 256
#define STACK_SIZE 50
#define STACK_START (MEM_SIZE - 1)      // stack starts from the last address(index) in RAM, 
                                        // on x86 platform stack starts on higher addresses & as you add elemente on it, it grows "down" to lower addresses

typedef struct {
    int AX, BX, CX, DX; // CPU registers
    int IP;             // instruction pointer ~ program counter (PC)
    int FLAGS;          // Flags can be 0 or 1
    int ESP;            // ESP register also refered as "Stack pointer"
} CPU;

CPU cpu = {0, 0, 0, 0, 0, 0, STACK_START};
char RAM[MEM_SIZE][20]; // Random access mem. for instructions and data store/load

void execute_instruction(char* instr, char* op1, char* op2)
{
    if (strcmp(instr, "MOV") == 0)
    {
        if (op1[0] == '[')  // MOV [mem addr], reg   ->   STORE data from CPU mem(reg) to RAM
        {
            int addr = atoi(op1 + 1);   // from the begging of char array(string) move to second character and everything that is num transform to int

            if (strcmp(op2, "AX") == 0)
                sprintf(RAM[addr], "%d", cpu.AX);
            if (strcmp(op2, "BX") == 0)
                sprintf(RAM[addr], "%d", cpu.BX);
            if (strcmp(op2, "CX") == 0)
                sprintf(RAM[addr], "%d", cpu.CX);
            if (strcmp(op2, "DX") == 0)
                sprintf(RAM[addr], "%d", cpu.DX);
        }
        else if (op2[0] == '[')   // MOV reg, [mem addr]  ->  LOAD data from RAM to CPU mem(reg)
        {
            int addr = atoi(op2 + 1);       // finding right address where data is stored
            int value = atoi(RAM[addr]);    // in this case everything in RAM is char, so we need to convert to int value

            if (strcmp(op1, "AX") == 0)
                cpu.AX = value;
            if (strcmp(op1, "BX") == 0)
                cpu.BX = value;
            if (strcmp(op1, "CX") == 0)
                cpu.CX = value;
            if (strcmp(op1, "DX") == 0)
                cpu.DX = value;
        }
        else
        {
            int value = atoi(op2);

            if (strcmp(op1, "AX") == 0)
                cpu.AX = value;
            if (strcmp(op1, "BX") == 0)
                cpu.BX = value;
            if (strcmp(op1, "CX") == 0)
                cpu.CX = value;
            if (strcmp(op1, "DX") == 0)
                cpu.DX = value;
        }
    }
    else if (strcmp(instr, "ADD") == 0)     // ADD reg, reg
    {
        if (strcmp(op1, "AX") == 0 && strcmp(op2, "AX") == 0)
            cpu.AX += cpu.AX;
        if (strcmp(op1, "AX") == 0 && strcmp(op2, "BX") == 0)
            cpu.AX += cpu.BX;
        if (strcmp(op1, "AX") == 0 && strcmp(op2, "CX") == 0)
            cpu.AX += cpu.CX;
        if (strcmp(op1, "AX") == 0 && strcmp(op2, "DX") == 0)
            cpu.AX += cpu.DX;

        if (strcmp(op1, "BX") == 0 && strcmp(op2, "AX") == 0)
            cpu.BX += cpu.AX;
        if (strcmp(op1, "BX") == 0 && strcmp(op2, "BX") == 0)
            cpu.BX += cpu.BX;
        if (strcmp(op1, "BX") == 0 && strcmp(op2, "CX") == 0)
            cpu.BX += cpu.CX;
        if (strcmp(op1, "BX") == 0 && strcmp(op2, "DX") == 0)
            cpu.BX += cpu.DX;

        if (strcmp(op1, "CX") == 0 && strcmp(op2, "AX") == 0)
            cpu.CX += cpu.AX;
        if (strcmp(op1, "CX") == 0 && strcmp(op2, "BX") == 0)
            cpu.CX += cpu.BX;
        if (strcmp(op1, "CX") == 0 && strcmp(op2, "CX") == 0)
            cpu.CX += cpu.CX;
        if (strcmp(op1, "CX") == 0 && strcmp(op2, "DX") == 0)
            cpu.CX += cpu.DX;

        if (strcmp(op1, "DX") == 0 && strcmp(op2, "AX") == 0)
            cpu.DX += cpu.AX;
        if (strcmp(op1, "DX") == 0 && strcmp(op2, "BX") == 0)
            cpu.DX += cpu.BX;
        if (strcmp(op1, "DX") == 0 && strcmp(op2, "CX") == 0)
            cpu.DX += cpu.CX;
        if (strcmp(op1, "DX") == 0 && strcmp(op2, "DX") == 0)
            cpu.DX += cpu.DX;
    }
    else if (strcmp(instr, "SUB") == 0)     // SUB reg, reg
    {
        if (strcmp(op1, "AX") == 0 && strcmp(op2, "AX") == 0)
            cpu.AX -= cpu.AX;
        if (strcmp(op1, "AX") == 0 && strcmp(op2, "BX") == 0)
            cpu.AX -= cpu.BX;
        if (strcmp(op1, "AX") == 0 && strcmp(op2, "CX") == 0)
            cpu.AX -= cpu.CX;
        if (strcmp(op1, "AX") == 0 && strcmp(op2, "DX") == 0)
            cpu.AX -= cpu.DX;

        if (strcmp(op1, "BX") == 0 && strcmp(op2, "AX") == 0)
            cpu.BX -= cpu.AX;
        if (strcmp(op1, "BX") == 0 && strcmp(op2, "BX") == 0)
            cpu.BX -= cpu.BX;
        if (strcmp(op1, "BX") == 0 && strcmp(op2, "CX") == 0)
            cpu.BX -= cpu.CX;
        if (strcmp(op1, "BX") == 0 && strcmp(op2, "DX") == 0)
            cpu.BX -= cpu.DX;

        if (strcmp(op1, "CX") == 0 && strcmp(op2, "AX") == 0)
            cpu.CX -= cpu.AX;
        if (strcmp(op1, "CX") == 0 && strcmp(op2, "BX") == 0)
            cpu.CX -= cpu.BX;
        if (strcmp(op1, "CX") == 0 && strcmp(op2, "CX") == 0)
            cpu.CX -= cpu.CX;
        if (strcmp(op1, "CX") == 0 && strcmp(op2, "DX") == 0)
            cpu.CX -= cpu.DX;

        if (strcmp(op1, "DX") == 0 && strcmp(op2, "AX") == 0)
            cpu.DX -= cpu.AX;
        if (strcmp(op1, "DX") == 0 && strcmp(op2, "BX") == 0)
            cpu.DX -= cpu.BX;
        if (strcmp(op1, "DX") == 0 && strcmp(op2, "CX") == 0)
            cpu.DX -= cpu.CX;
        if (strcmp(op1, "DX") == 0 && strcmp(op2, "DX") == 0)
            cpu.DX -= cpu.DX;
    }
    else if (strcmp(instr, "MUL") == 0)     // MUL reg  ->  (result: AX = AX * reg), AX is hardcoded for result destination
    {                                       // Actually it means DX:AX = AX * CX - the high half of the full 32-bit product 
                                            // is always written to DX - DX will be zero for small products where the result "fits" in AX     
        if (strcmp(op1, "BX") == 0) 
            cpu.AX *= cpu.BX;
        if (strcmp(op1, "CX") == 0) 
            cpu.AX *= cpu.CX;
    }
    else if (strcmp(instr, "DIV") == 0)     // DIV reg (AX/reg is result, stored in AX, AX is implicit, similar to MUL)
    {
        if (strcmp(op1, "BX") == 0 && cpu.BX != 0) 
            cpu.AX /= cpu.BX;
        if (strcmp(op1, "CX") == 0 && cpu.CX != 0) 
            cpu.AX /= cpu.CX;
    }
    else if (strcmp(instr, "PUSH") == 0)
    {
        if (cpu.ESP < STACK_SIZE - 1)
        {
            printf("Stack overflow!\n");
            return;
        }

        cpu.ESP--;      //Stack grows (addresses are getting lower

        if (strcmp(op1, "AX") == 0)
            sprintf(RAM[cpu.ESP], "%d", cpu.AX);
        else if (strcmp(op1, "BX") == 0)
            sprintf(RAM[cpu.ESP], "%d", cpu.BX);
        else if (strcmp(op1, "CX") == 0)
            sprintf(RAM[cpu.ESP], "%d", cpu.CX);
        else if (strcmp(op1, "DX") == 0)
            sprintf(RAM[cpu.ESP], "%d", cpu.DX);
        else
        {
            printf("Invalid register for PUSH\n");
        }
    }
    else if (strcmp(instr, "POP") == 0)
    {
        if (cpu.ESP >= STACK_START)
        {
            printf("Stack underflow!\n");
            return;
        }

        int value = atoi(RAM[cpu.ESP]);
        cpu.ESP++;

        if (strcmp(op1, "AX") == 0)
            cpu.AX = value;
        if (strcmp(op1, "BX") == 0)
            cpu.BX = value;
        if (strcmp(op1, "CX") == 0)
            cpu.CX = value;
        if (strcmp(op1, "DX") == 0)
            cpu.DX = value;
        else
        {
            print("Invalid register for POP\n");
        }
    }
    else if (strcmp(instr, "HLT") == 0)
    {
        //exit(0);
        return;
    }
}

void run_program() {
    while (cpu.IP < MEM_SIZE) {
        char instruction_symbol[10], operand1[10], operand2[10];
        int num_read = sscanf(RAM[cpu.IP], "%s %s %s", instruction_symbol, operand1, operand2); // number of elements which match format spec "%s %s %s"

        if (num_read >= 1)
        {
            execute_instruction(instruction_symbol, operand1, operand2);
            cpu.IP++;
        }
    }
}

int main()
{
    cpu.IP = 0;  

    //Loading program in RAM
    strcpy(RAM[0],  "MOV AX,    5");
    strcpy(RAM[1],  "MOV BX,    5");
    strcpy(RAM[2],  "ADD AX,    BX");
    strcpy(RAM[3],  "MOV [10],  AX");    // STORE data from cpu mem(reg) to RAM
    strcpy(RAM[4],  "MOV AX,    0");
    strcpy(RAM[5],  "MOV AX,    [10]");
    strcpy(RAM[6],  "CMP AX,    BX");
    strcpy(RAM[7],  "JZ         9");
    strcpy(RAM[8],  "HLT");
    strcpy(RAM[9],  "MOV AX,    100");
    strcpy(RAM[10], "MOV BX,    31");
    strcpy(RAM[11], "PUSH BX");
    strcpy(RAM[12], "MOV BX,    32");
    strcpy(RAM[13], "POP CX");
    strcpy(RAM[14], "HLT");

    run_program(); // emulation start

    return 0;
}

