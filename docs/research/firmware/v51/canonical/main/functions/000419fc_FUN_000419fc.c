/* Address: 000419fc; name: FUN_000419fc; body bytes: 194 */

undefined4 * FUN_000419fc(int param_1,undefined4 *param_2,uint param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iStack_28;
  undefined4 *puStack_24;
  uint uStack_20;
  undefined4 uStack_1c;
  
  puVar1 = *(undefined4 **)(param_1 + 0x38);
  if (DAT_2003a548 < 2) {
    while( true ) {
      if (puVar1 == (undefined4 *)0x0) {
        return (undefined4 *)0x0;
      }
      if (((puVar1[0x12] != 1) || (*(byte *)(puVar1 + 0x14) == 0)) ||
         (*(byte *)(puVar1 + 0x14) == param_3)) break;
      puVar1[0x12] = 3;
      puVar1 = (undefined4 *)*puVar1;
    }
    if (puVar1[0x12] == 1) {
      return puVar1;
    }
  }
  else {
    iStack_28 = param_1;
    puStack_24 = param_2;
    uStack_20 = param_3;
    uStack_1c = param_4;
    if (puVar1 != (undefined4 *)0x0) {
      FUN_0004f604();
      iVar2 = FUN_000408b0();
      FUN_0004f604();
      iVar3 = FUN_00040960();
      iVar4 = *(int *)(param_1 + 0x38);
      if (((*(int *)(iVar4 + 0x48) != 1) && (*(int *)(iVar4 + 8) < 1)) &&
         ((iVar2 + -1 <= *(int *)(iVar4 + 0x10) &&
          ((*(int *)(iVar4 + 0xc) < 1 && (iVar3 + -1 <= *(int *)(iVar4 + 0x14))))))) {
        return (undefined4 *)0x0;
      }
    }
    if (param_2 == (undefined4 *)0x0) {
      param_2 = *(undefined4 **)(param_1 + 0x38);
      goto LAB_00041a80;
    }
    while( true ) {
      param_2 = (undefined4 *)*param_2;
LAB_00041a80:
      if (param_2 == (undefined4 *)0x0) break;
      if ((param_2[0x12] == 1) &&
         ((*(byte *)(param_2 + 0x14) == 0 || (*(byte *)(param_2 + 0x14) == param_3)))) {
        puVar1 = *(undefined4 **)(param_1 + 0x38);
        while( true ) {
          if (puVar1 == (undefined4 *)0x0) {
            return param_2;
          }
          if (puVar1 == param_2) {
            return param_2;
          }
          if ((puVar1[0x12] != 3) &&
             (iVar2 = FUN_0003db4c(&iStack_28,puVar1 + 6,param_2 + 6), iVar2 != 0)) break;
          puVar1 = (undefined4 *)*puVar1;
        }
      }
    }
  }
  return (undefined4 *)0x0;
}

