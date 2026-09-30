/* Address: 00039138; name: FUN_00039138; body bytes: 68 */

undefined4 FUN_00039138(uint *param_1,uint *param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = *param_2;
  bVar1 = (byte)param_1[1];
  uVar2 = *param_1;
  if (bVar1 != (byte)param_2[1]) {
    if ((byte)param_2[1] < bVar1) {
      return 1;
    }
    return 0xffffffff;
  }
  if (bVar1 == 1) {
    iVar3 = thunk_FUN_00050a1a(uVar2,uVar4);
    if (iVar3 != 0) {
      if (0 < iVar3) {
        return 1;
      }
      return 0xffffffff;
    }
  }
  else if ((bVar1 == 0) && (uVar2 != uVar4)) {
    if (uVar4 < uVar2) {
      return 1;
    }
    return 0xffffffff;
  }
  return 0;
}

