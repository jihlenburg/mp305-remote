/* Address: 00020ccc; name: FUN_00020ccc; body bytes: 128 */

void FUN_00020ccc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 uint param_5,undefined4 param_6,uint param_7,undefined4 param_8,undefined4 param_9,
                 uint param_10)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char cVar4;
  char local_44 [32];
  
  uVar3 = 0;
  if (param_5 == 0) {
    param_10 = param_10 & 0xffffffef;
  }
  if ((-1 < (int)(param_10 << 0x15)) || (param_5 != 0)) {
    do {
      uVar2 = param_5 - param_7 * (param_5 / param_7);
      cVar1 = (char)uVar2;
      if ((uVar2 & 0xff) < 10) {
        cVar1 = cVar1 + '0';
      }
      else {
        if ((int)(param_10 << 0x1a) < 0) {
          cVar4 = 'A';
        }
        else {
          cVar4 = 'a';
        }
        cVar1 = cVar1 + cVar4 + -10;
      }
      param_5 = param_5 / param_7;
      local_44[uVar3] = cVar1;
      uVar3 = uVar3 + 1;
    } while ((param_5 != 0) && (uVar3 < 0x20));
  }
  FUN_00020be8(param_1,param_2,param_3,param_4,local_44,uVar3,param_6,param_7,param_8,param_9,
               param_10);
  return;
}

