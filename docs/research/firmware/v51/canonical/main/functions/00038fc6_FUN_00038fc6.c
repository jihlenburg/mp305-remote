/* Address: 00038fc6; name: FUN_00038fc6; body bytes: 40 */

void FUN_00038fc6(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_1 + 0xc);
  iVar1 = FUN_00041546(uVar2,0x10);
  if (iVar1 != 0) {
    FUN_000413fe(uVar2);
  }
  if (*(char *)(param_1 + 8) == '\x01') {
    FUN_00046bec(*(undefined4 *)(param_1 + 4));
    return;
  }
  return;
}

