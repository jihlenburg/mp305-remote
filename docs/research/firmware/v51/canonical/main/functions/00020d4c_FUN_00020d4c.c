/* Address: 00020d4c; name: FUN_00020d4c; body bytes: 128 */

void FUN_00020d4c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 int param_5,int param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,
                 undefined4 param_10,undefined4 param_11,undefined4 param_12,uint param_13)

{
  byte extraout_r2;
  char cVar1;
  uint uVar2;
  longlong lVar3;
  char local_54 [32];
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  
  uVar2 = 0;
  if (param_5 == 0 && param_6 == 0) {
    param_13 = param_13 & 0xffffffef;
  }
  local_34 = param_1;
  uStack_30 = param_2;
  uStack_2c = param_3;
  uStack_28 = param_4;
  lVar3 = CONCAT44(param_6,param_5);
  if ((-1 < (int)(param_13 << 0x15)) ||
     (lVar3 = CONCAT44(param_6,param_5), param_5 != 0 || param_6 != 0)) {
    do {
      lVar3 = FUN_00010388((int)lVar3,(int)((ulonglong)lVar3 >> 0x20),param_9,param_10);
      if (extraout_r2 < 10) {
        cVar1 = extraout_r2 + 0x30;
      }
      else {
        if ((int)(param_13 << 0x1a) < 0) {
          cVar1 = 'A';
        }
        else {
          cVar1 = 'a';
        }
        cVar1 = extraout_r2 + cVar1 + -10;
      }
      local_54[uVar2] = cVar1;
      uVar2 = uVar2 + 1;
    } while ((lVar3 != 0) && (uVar2 < 0x20));
  }
  FUN_00020be8(local_34,uStack_30,uStack_2c,uStack_28,local_54,uVar2,param_7,param_9,param_11,
               param_12,param_13);
  return;
}

