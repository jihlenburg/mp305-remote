/* Address: 000528e4; name: FUN_000528e4; body bytes: 86 */

undefined4 FUN_000528e4(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((*(byte *)(param_1 + 0x14) & 1) != 0) {
    return 0;
  }
  uVar2 = 0;
  iVar1 = FUN_00052ace(param_1);
  if (iVar1 == 0) {
    iVar1 = *(int *)(param_1 + 0x10);
    if (0 < iVar1) {
      *(int *)(param_1 + 0x10) = iVar1 + -1;
    }
    uVar2 = FUN_00052708();
    *(undefined4 *)(param_1 + 4) = uVar2;
    if ((*(code **)(param_1 + 8) != (code *)0x0) && (iVar1 != 0)) {
      (**(code **)(param_1 + 8))(param_1);
    }
    uVar2 = 1;
  }
  if ((DAT_2003a4a2 == '\0') && (*(int *)(param_1 + 0x10) == 0)) {
    if ((int)((uint)*(byte *)(param_1 + 0x14) << 0x1e) < 0) {
      FUN_000528ac();
    }
    else {
      FUN_00052a74(param_1);
    }
  }
  return uVar2;
}

