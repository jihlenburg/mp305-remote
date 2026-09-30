/* Address: 000454e8; name: FUN_000454e8; body bytes: 302 */

void FUN_000454e8(undefined4 *param_1,undefined4 param_2,int param_3,undefined1 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  int iVar5;
  
  iVar1 = FUN_0003db28(param_2);
  iVar2 = FUN_0003db0a(param_2);
  if (iVar1 < iVar2) {
    iVar2 = iVar1;
  }
  if (iVar2 >> 1 < param_3) {
    param_3 = iVar2 >> 1;
  }
  if (param_3 < 0) {
    param_3 = 0;
  }
  FUN_0003da22(param_1 + 2,param_2);
  param_1[6] = param_3;
  *(undefined1 *)(param_1 + 7) = param_4;
  *param_1 = 0x4278b;
  *(undefined1 *)(param_1 + 1) = 2;
  if (param_3 == 0) {
    param_1[8] = 0;
    return;
  }
  FUN_0004aa44();
  uVar3 = 0;
  iVar2 = 1000;
  do {
    iVar1 = param_3 >> 4;
    if ((&DAT_2003a574)[uVar3 * 7] == param_3) {
      (&DAT_2003a570)[uVar3 * 7] = (&DAT_2003a570)[uVar3 * 7] + 1;
      iVar5 = iVar1;
      if (param_3 < 0x10) {
        iVar5 = 1;
      }
      if (iVar5 + (&DAT_2003a56c)[uVar3 * 7] < 1000) {
        if (param_3 < 0x10) {
          iVar1 = 1;
        }
        iVar2 = (&DAT_2003a56c)[uVar3 * 7] + iVar1;
      }
      (&DAT_2003a56c)[uVar3 * 7] = iVar2;
      param_1[8] = &DAT_2003a55c + uVar3 * 7;
      goto LAB_0004560c;
    }
    uVar3 = uVar3 + 1;
  } while (uVar3 < 4);
  puVar4 = (undefined4 *)0x0;
  uVar3 = 0;
  do {
    if (((&DAT_2003a570)[uVar3 * 7] == 0) &&
       ((puVar4 == (undefined4 *)0x0 || ((int)(&DAT_2003a56c)[uVar3 * 7] < (int)puVar4[4])))) {
      puVar4 = &DAT_2003a55c + uVar3 * 7;
    }
    uVar3 = uVar3 + 1;
  } while (uVar3 < 4);
  if (puVar4 == (undefined4 *)0x0) {
    puVar4 = (undefined4 *)FUN_0004a360(0x1c);
    if (puVar4 == (undefined4 *)0x0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    puVar4[4] = 0xffffffff;
  }
  else {
    puVar4[4] = 0;
    puVar4[5] = puVar4[5] + 1;
    iVar5 = iVar1;
    if (param_3 < 0x10) {
      iVar5 = 1;
    }
    if ((iVar5 < 1000) && (iVar2 = iVar1, param_3 < 0x10)) {
      iVar2 = 1;
    }
    puVar4[4] = iVar2;
  }
  param_1[8] = puVar4;
  FUN_000270ec(puVar4,param_3);
LAB_0004560c:
  FUN_0004aa48(&DAT_2003a554);
  return;
}

