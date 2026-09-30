/* Address: 00015f5c; name: FUN_00015f5c; body bytes: 20 */

int FUN_00015f5c(void)

{
  int iVar1;
  byte *pbVar2;
  int iVar3;
  bool bVar4;
  
  iVar3 = 0x7c;
  iVar1 = 0;
  pbVar2 = &DAT_1fffa0b8;
  while (bVar4 = iVar3 != 0, iVar3 = iVar3 + -1, bVar4) {
    iVar1 = iVar1 + (uint)*pbVar2;
    pbVar2 = pbVar2 + 1;
  }
  return iVar1;
}

