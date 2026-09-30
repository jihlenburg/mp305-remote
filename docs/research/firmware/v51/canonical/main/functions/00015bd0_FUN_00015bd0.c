/* Address: 00015bd0; name: FUN_00015bd0; body bytes: 22 */

int FUN_00015bd0(void)

{
  int iVar1;
  byte *pbVar2;
  int iVar3;
  bool bVar4;
  
  iVar3 = 0x218;
  iVar1 = 0;
  pbVar2 = &DAT_1fffa138;
  while (bVar4 = iVar3 != 0, iVar3 = iVar3 + -1, bVar4) {
    iVar1 = iVar1 + (uint)*pbVar2;
    pbVar2 = pbVar2 + 1;
  }
  return iVar1;
}

