/* Address: CODE:91be; name: FUN_CODE_91be; body bytes: 33 */

void FUN_CODE_91be(void)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  byte bVar5;
  char cVar6;
  
  cVar6 = '\0';
  bVar2 = 0;
  bVar1 = 0;
  cVar4 = '\0';
  cVar3 = '\x04';
  do {
    _1_5 = 1;
    bVar5 = BANK0_R5;
    FUN_CODE_94ae(cVar6);
    bVar5 = cVar4 - (((bVar2 < bVar5) << 7) >> 7);
    cVar6 = bVar1 - bVar5;
    if (bVar1 < bVar5) {
      bVar1 = BANK0_R6;
      bVar2 = BANK0_R7;
    }
    cVar3 = cVar3 + -1;
  } while (cVar3 != '\0');
  return;
}

