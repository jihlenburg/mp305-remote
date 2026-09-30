/* Address: 000159cc; name: FUN_000159cc; body bytes: 20 */

int FUN_000159cc(void)

{
  int iVar1;
  byte *pbVar2;
  int iVar3;
  bool bVar4;
  
  iVar3 = 0xbc;
  iVar1 = 0;
  pbVar2 = &DAT_1fffa354;
  while (bVar4 = iVar3 != 0, iVar3 = iVar3 + -1, bVar4) {
    iVar1 = iVar1 + (uint)*pbVar2;
    pbVar2 = pbVar2 + 1;
  }
  return iVar1;
}

