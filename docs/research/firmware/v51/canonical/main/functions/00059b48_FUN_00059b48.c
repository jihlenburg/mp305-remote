/* Address: 00059b48; name: FUN_00059b48; body bytes: 132 */

void FUN_00059b48(undefined4 param_1,int param_2,int param_3,undefined4 param_4,uint param_5,
                 undefined4 *param_6,undefined4 *param_7)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  FUN_0001048e(param_7[0xc],param_3 << 2,0xa5);
  iVar1 = param_7[0xc];
  if (param_2 != 0) {
    uVar2 = 0;
    do {
      *(undefined1 *)((int)param_7 + uVar2 + 0x34) = *(undefined1 *)(param_2 + uVar2);
      if (*(char *)(param_2 + uVar2) == '\0') break;
      uVar2 = uVar2 + 1;
    } while (uVar2 < 10);
    *(undefined1 *)((int)param_7 + 0x3d) = 0;
  }
  if (4 < param_5) {
    param_5 = 4;
  }
  param_7[0xb] = param_5;
  param_7[0x10] = param_5;
  FUN_000656cc(param_7 + 1);
  FUN_000656cc(param_7 + 6);
  param_7[4] = param_7;
  param_7[9] = param_7;
  param_7[6] = 5 - param_5;
  uVar3 = FUN_0005a078(iVar1 + param_3 * 4 + -4 & 0xfffffff8,param_1,param_4);
  *param_7 = uVar3;
  if (param_6 != (undefined4 *)0x0) {
    *param_6 = param_7;
  }
  return;
}

