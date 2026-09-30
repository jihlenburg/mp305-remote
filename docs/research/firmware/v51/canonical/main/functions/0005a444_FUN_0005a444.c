/* Address: 0005a444; name: FUN_0005a444; body bytes: 264 */

void FUN_0005a444(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  
  iVar1 = DAT_2003a430;
  uVar2 = param_1[7];
  uVar3 = param_1[8];
  uVar4 = param_1[9];
  *(undefined4 *)(DAT_2003a430 + 0x300) = param_1[6];
  *(undefined4 *)(iVar1 + 0x304) = uVar2;
  *(undefined4 *)(iVar1 + 0x308) = uVar3;
  *(undefined4 *)(iVar1 + 0x30c) = uVar4;
  local_28 = param_1;
  uStack_24 = param_2;
  uStack_20 = param_3;
  uStack_1c = param_4;
  iVar1 = FUN_00040988();
  if (iVar1 == 0) {
    FUN_000661e0(DAT_2003a430);
  }
  iVar1 = FUN_0004035a(*(undefined1 *)(DAT_2003a430 + 0x3b));
  if (iVar1 != 0) {
    local_28 = *(undefined4 **)(DAT_2003a430 + 0x300);
    uStack_24 = *(undefined4 *)(DAT_2003a430 + 0x304);
    uStack_20 = *(undefined4 *)(DAT_2003a430 + 0x308);
    uStack_1c = *(undefined4 *)(DAT_2003a430 + 0x30c);
    if (*(char *)(DAT_2003a430 + 0x39) == '\0') {
      FUN_0003ddd6(&local_28,-*(int *)(DAT_2003a430 + 0x300),-*(int *)(DAT_2003a430 + 0x304));
    }
    FUN_000411ca(*param_1,&local_28);
  }
  iVar5 = 0;
  uVar2 = FUN_00040928(DAT_2003a430);
  iVar1 = FUN_0004f610(param_1 + 6,uVar2);
  if (*(int *)(DAT_2003a430 + 0x2c8) != 0) {
    iVar5 = FUN_0004f610(param_1 + 6);
  }
  if (iVar1 == 0 && iVar5 == 0) {
    uVar2 = FUN_000408d8(DAT_2003a430);
    FUN_0005aa24(param_1,uVar2);
  }
  if ((*(byte *)(DAT_2003a430 + 0x2d4) & 1) == 0) {
    if (*(int *)(DAT_2003a430 + 0x2c8) != 0) {
      if (iVar5 == 0) {
        iVar5 = *(int *)(DAT_2003a430 + 0x2c8);
      }
      FUN_0005aa24(param_1,iVar5);
    }
    if (iVar1 == 0) {
      iVar1 = *(int *)(DAT_2003a430 + 0x2c0);
    }
  }
  else {
    if (iVar1 == 0) {
      iVar1 = *(int *)(DAT_2003a430 + 0x2c0);
    }
    FUN_0005aa24(param_1,iVar1);
    if (*(int *)(DAT_2003a430 + 0x2c8) == 0) goto LAB_0005a524;
    iVar1 = iVar5;
    if (iVar5 == 0) {
      iVar1 = *(int *)(DAT_2003a430 + 0x2c8);
    }
  }
  FUN_0005aa24(param_1,iVar1);
LAB_0005a524:
  uVar2 = FUN_00040900(DAT_2003a430);
  FUN_0005aa24(param_1,uVar2);
  uVar2 = FUN_000408ec(DAT_2003a430);
  FUN_0005aa24(param_1,uVar2);
  FUN_000296e4(DAT_2003a430);
  return;
}

