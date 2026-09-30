/* Address: 0005231c; name: FUN_0005231c; body bytes: 42 */

undefined * FUN_0005231c(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined *puVar3;
  undefined1 auStack_20 [28];
  
  puVar3 = *(undefined **)(param_1 + 0x38);
  if (puVar3 == (undefined *)0x0) {
    uVar1 = FUN_0004cb4c(param_1,0);
    iVar2 = FUN_00046a36(uVar1,auStack_20,0x2022,0);
    if (iVar2 == 0) {
      puVar3 = &DAT_0005234c;
    }
    else {
      puVar3 = &DAT_00052348;
    }
  }
  return puVar3;
}

