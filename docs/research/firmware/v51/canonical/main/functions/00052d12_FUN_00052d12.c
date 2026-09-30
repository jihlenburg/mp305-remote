/* Address: 00052d12; name: FUN_00052d12; body bytes: 104 */

uint FUN_00052d12(int param_1)

{
  short sVar1;
  uint uVar2;
  
  for (; param_1 < 0; param_1 = (int)(short)((short)param_1 + 0x168)) {
  }
  while (sVar1 = (short)param_1, 0x167 < param_1) {
    param_1 = (int)(short)(sVar1 + -0x168);
  }
  if (0x59 < param_1) {
    if (0x59 < param_1 - 0x5aU) {
      if (param_1 - 0xb4U < 0x5a) {
        sVar1 = (short)(param_1 - 0xb4U);
      }
      else {
        sVar1 = 0x168 - sVar1;
      }
      uVar2 = -(uint)*(ushort *)(&DAT_0007a050 + sVar1 * 2);
      goto LAB_00052d5a;
    }
    param_1 = (int)(short)(0xb4 - sVar1);
  }
  uVar2 = (uint)*(ushort *)(&DAT_0007a050 + param_1 * 2);
LAB_00052d5a:
  if (uVar2 == 0x7fff) {
    return 0x8000;
  }
  if (uVar2 == 0xffff8001) {
    uVar2 = 0xffff8000;
  }
  return uVar2;
}

