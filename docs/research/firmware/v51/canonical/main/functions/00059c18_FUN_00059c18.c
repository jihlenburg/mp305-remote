/* Address: 00059c18; name: FUN_00059c18; body bytes: 52 */

undefined4 FUN_00059c18(int param_1,uint param_2,uint param_3,uint param_4)

{
  undefined4 uVar1;
  
  *(uint *)(param_1 + 4) = param_2;
  *(int *)(param_1 + 0x10) = param_1;
  if (param_3 < param_2) {
    uVar1 = DAT_1ffe004c;
    if ((param_3 < param_4) && (param_4 <= param_2)) {
      return 1;
    }
  }
  else {
    uVar1 = DAT_1ffe0050;
    if (*(uint *)(param_1 + 0x18) <= param_3 - param_4) {
      return 1;
    }
  }
  FUN_000656d2(uVar1,param_1 + 4);
  return 0;
}

