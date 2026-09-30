/* Address: 00052d00; name: FUN_00052d00; body bytes: 8 */

uint FUN_00052d00(short param_1)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  
  for (param_1 = param_1 + 0x5a; iVar2 = (int)param_1, iVar2 < 0; param_1 = param_1 + 0x168) {
  }
  while (sVar1 = (short)iVar2, 0x167 < iVar2) {
    iVar2 = (int)(short)(sVar1 + -0x168);
  }
  if (0x59 < iVar2) {
    if (0x59 < iVar2 - 0x5aU) {
      if (iVar2 - 0xb4U < 0x5a) {
        sVar1 = (short)(iVar2 - 0xb4U);
      }
      else {
        sVar1 = 0x168 - sVar1;
      }
      uVar3 = -(uint)*(ushort *)(&DAT_0007a050 + sVar1 * 2);
      goto LAB_00052d5a;
    }
    iVar2 = (int)(short)(0xb4 - sVar1);
  }
  uVar3 = (uint)*(ushort *)(&DAT_0007a050 + iVar2 * 2);
LAB_00052d5a:
  if (uVar3 == 0x7fff) {
    return 0x8000;
  }
  if (uVar3 == 0xffff8001) {
    uVar3 = 0xffff8000;
  }
  return uVar3;
}

