/* Address: 00051258; name: FUN_00051258; body bytes: 92 */

/* Recovered from stored Thumb pointer at 0007aef8; callback identification is inferred until
   reviewed. */

void FUN_00051258(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  while( true ) {
    uVar2 = *(int *)(param_2 + 0x30) * *(int *)(param_2 + 0x2c);
    if (uVar2 < uVar3 || uVar2 - uVar3 == 0) break;
    iVar1 = *(int *)(*(int *)(param_2 + 0x34) + uVar3 * 4);
    if (iVar1 != 0) {
      if (*(int *)(iVar1 + 4) != 0) {
        FUN_00046bec();
        *(undefined4 *)(*(int *)(*(int *)(param_2 + 0x34) + uVar3 * 4) + 4) = 0;
      }
      FUN_00046bec(*(undefined4 *)(*(int *)(param_2 + 0x34) + uVar3 * 4));
      *(undefined4 *)(*(int *)(param_2 + 0x34) + uVar3 * 4) = 0;
    }
    uVar3 = uVar3 + 1;
  }
  if (*(int *)(param_2 + 0x34) != 0) {
    FUN_00046bec();
  }
  if (*(int *)(param_2 + 0x38) != 0) {
    FUN_00046bec();
  }
  if (*(int *)(param_2 + 0x3c) != 0) {
    FUN_00046bec();
    return;
  }
  return;
}

