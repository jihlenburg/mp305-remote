/* Address: 0004dedc; name: FUN_0004dedc; body bytes: 222 */

void FUN_0004dedc(undefined4 param_1,uint param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  if (DAT_2003a444 == '\0') {
    return;
  }
  FUN_0004d3d8(param_1);
  param_2 = param_2 & 0xff0000;
  uVar1 = FUN_00050c04(param_3,4);
  uVar2 = FUN_00050c04(param_3,2);
  uVar3 = FUN_00050c04(param_3,1);
  iVar4 = FUN_00050c04(param_3,0x10);
  if (uVar1 != 0) {
    if ((((param_2 != 0xf0000) && (param_2 != 0)) &&
        (iVar5 = FUN_0004c924(param_1,0,2), iVar5 != 0x3fffffff)) &&
       (iVar5 = FUN_0004c924(param_1,0,1), iVar5 != 0x3fffffff)) goto LAB_0004df88;
    FUN_0004e5a6(param_1,0x2f,0);
    FUN_0004d500(param_1);
  }
  if ((param_2 == 0xf0000) || (param_2 == 0)) {
    if (((param_3 == 0xff) || (uVar1 != 0)) && (iVar5 = FUN_0004bc8c(param_1), iVar5 != 0)) {
      FUN_0004d500();
    }
    if (((param_2 == 0xf0000) || (param_2 == 0)) && (iVar4 != 0)) {
      FUN_0004ef6a(param_1);
    }
  }
LAB_0004df88:
  if ((param_3 == 0xff) || (uVar2 != 0)) {
    FUN_0004de6c(param_1);
  }
  FUN_0004d3d8(param_1);
  if (((param_3 == 0xff) || (((uVar2 | uVar1) & uVar3) != 0)) && (param_2 != 0x10000)) {
    FUN_0005adc8(param_1);
    return;
  }
  return;
}

