/* Address: CODE:aeac; name: FUN_CODE_aeac; body bytes: 36 */

void FUN_CODE_aeac(undefined2 param_1)

{
  char cVar1;
  char cVar2;
  char cVar3;
  
  cVar2 = BANK1_R1 + (byte)param_1;
  cVar3 = BANK1_R0 + ((char)((ushort)param_1 >> 8) - ((CARRY1(BANK1_R1,(byte)param_1) << 7) >> 7));
  if (cVar3 == BANK1_R0) {
    BANK1_R1 = cVar2;
    return;
  }
  cVar1 = EA;
  if (cVar1 != '\0') {
    EA = 0;
    BANK1_R1 = cVar2;
    BANK1_R0 = cVar3;
    EA = 1;
    return;
  }
  BANK1_R1 = cVar2;
  BANK1_R0 = cVar3;
  return;
}

