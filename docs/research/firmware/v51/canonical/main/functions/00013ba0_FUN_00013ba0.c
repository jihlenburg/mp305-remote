/* Address: 00013ba0; name: FUN_00013ba0; body bytes: 94 */

int FUN_00013ba0(char *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_1 == (char *)0x0) {
    return -3;
  }
  DAT_40054104 = *(undefined4 *)(param_1 + 4);
  iVar1 = 0;
  if (*param_1 == '\0') {
    if (DAT_40054100 << 0x18 < 0) {
      uVar2 = 1;
    }
    else {
      uVar2 = 8;
    }
    iVar1 = FUN_00013c12(uVar2,0x1000);
    if (iVar1 == 0) {
      DAT_4005402e = 0;
      iVar1 = FUN_00013c12(0x40,0x1000);
      return iVar1;
    }
  }
  else {
    DAT_4005402e = 1;
  }
  return iVar1;
}

