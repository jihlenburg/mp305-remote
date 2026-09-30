/* Address: 00013ae8; name: FUN_00013ae8; body bytes: 136 */

int FUN_00013ae8(char *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 == (char *)0x0) {
    return -3;
  }
  DAT_40054100 = *(int *)(param_1 + 4);
  if (*param_1 == '\0') {
    if (DAT_40054100 << 0x18 < 0) {
      uVar1 = 1;
    }
    else {
      uVar1 = 8;
    }
    iVar2 = FUN_00013c12(uVar1,0x1000);
    if (iVar2 == 0) {
      DAT_4005402a = 0;
      iVar2 = FUN_00013c12(0x20,0x1000);
      return iVar2;
    }
  }
  else {
    if ((DAT_40054026 & 7) != 5) {
      DAT_4005402a = 1;
      return 0;
    }
    iVar2 = -6;
  }
  return iVar2;
}

