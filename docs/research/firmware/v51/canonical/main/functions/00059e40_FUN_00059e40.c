/* Address: 00059e40; name: FUN_00059e40; body bytes: 66 */

uint FUN_00059e40(undefined4 *param_1)

{
  int *piVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar2 = FUN_00066c1c();
  if (uVar2 < DAT_1ffe0048) {
    while (piVar1 = DAT_1ffe004c, *DAT_1ffe004c != 0) {
      FUN_00059c6c(*(undefined4 *)DAT_1ffe004c[3],0xffffffff);
    }
    DAT_1ffe004c = DAT_1ffe0050;
    DAT_1ffe0050 = piVar1;
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  *param_1 = uVar3;
  DAT_1ffe0048 = uVar2;
  return uVar2;
}

