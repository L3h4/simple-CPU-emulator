#include "InstructionSet.h"

// NOP
void NOP()
{
}


// =========================================== MOV


// MOV R, d8
void MOVRV()
{
}

// MOV R, R
void MOVRR()
{
}

// MOV R, a8
void MOVRA()
{
}

// MOV a8, R
void MOVAR()
{
}

// MOV a8, d8
void MOVAV()
{
}

// MOV R, [R]
void MOVRaR()
{
} 

// MOV [R], R
void MOVaRR()
{
}

// MOV [R], [R]
void MOVaRaR()
{
}

// MOV [R], d8
void MOVaRV()
{
}

// MOV [R], a8
void MOVaRA()
{
}

// MOV a8, [R]
void MOVAaR()
{
}

// MOV a8, a8
void MOVAA()
{
}


// =========================================== ADD


// ADD R, d8
void ADDRV(){}

// ADD R, R
void ADDRR(){}

// ADD R, a8
void ADDRA(){}

// ADD a8, R
void ADDAR(){}

// ADD a8, d8
void ADDAV(){}

// ADD R, [R]
void ADDRaR(){}

// ADD [R], R
void ADDaRR(){}

// ADD [R], [R]
void ADDaRaR(){}

// ADD [R], d8
void ADDaRV(){}

// ADD  [R], a8
void ADDaRA(){}

// ADD a8, [R]
void ADDAaR(){}

// ADD a8, a8
void ADDAA(){}


// =========================================== SUB


// SUB R, d8  
void SUBRV(){}

// SUB R, R
void SUBRR(){}

// SUB R, a8
void SUBRA(){}

// SUB a8, R
void SUBAR(){}

// SUB a8, d8
void SUBAV(){}

// SUB R, [R]
void SUBRaR(){}

// SUB [R], R
void SUBaRR(){}

// SUB [R], [R]
void SUBaRaR(){}

// SUB [R], d8
void SUBaRV(){}

// SUB  [R], a8
void SUBaRA(){}

// SUB a8, [R]
void SUBAaR(){}

// SUB a8, a8
void SUBAA(){}


// =========================================== CMP


// CMP R, d8   
void CMPRV(){}

// CMP R, R
void CMPRR(){}

// CMP R, a8
void CMPRA(){}

// CMP a8, R
void CMPAR(){}

// CMP a8, d8
void CMPAV(){}

// CMP R, [R]
void CMPRaR(){}

// CMP [R], R
void CMPaRR(){}

// CMP [R], [R]
void CMPaRaR(){}

// CMP [R], d8
void CMPaRV(){}

// CMP  [R], a8
void CMPaRA(){}

// CMP a8, [R]
void CMPAaR(){}

// CMP a8, a8
void CMPAA(){}


// =========================================== INC


// INC R    
void INCR(){}

// INC a8
void INCA(){}

// INC [R]
void INCaR(){}


// =========================================== DEC


// DEC R     
void DECR(){}

// DEC a8
void DECA(){}

// DEC [R]
void DECaR(){}


// =========================================== JMP


// JMP R
void JMPR(){}

// JMP a8
void JMPA(){}


// =========================================== JE


// JE R
void JER(){}

//  JE a8
void JEA(){}


// =========================================== JNE


// JNE R
void JNER(){}

// JNE a8
void JNEA(){}


// =========================================== JL


// JL R
void JLR(){}

// JL a8
void JLA(){}


// =========================================== JG


// JG R
void JGR(){}

// JG a8
void JGA(){}


// =========================================== JLE


// JLE R
void JLER(){}

// JLE a8
void JLEA(){}


// =========================================== JGE


// JGE R
void JGER(){}

// JGE a8
void JGEA(){}


// ===========================================


// HLT
void HLT(){}

// SYSCALL
void SYSCALL(){}