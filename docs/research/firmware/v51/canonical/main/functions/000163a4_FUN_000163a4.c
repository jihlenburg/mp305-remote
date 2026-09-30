/* Address: 000163a4; name: FUN_000163a4; body bytes: 188 */

undefined4 FUN_000163a4(undefined1 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  if (DAT_1fff8f60 == 0) {
    DAT_1fff8f60 = FUN_000666a0(1);
  }
  iVar1 = FUN_00066a10(DAT_1fff8f60,100);
  uVar3 = 0xfffffff8;
  if (iVar1 != 0) {
    if (DAT_1fff8f58 == '\x01') {
      DAT_1fff8f58 = 0;
      DAT_1fff8f54 = 0;
      DAT_1fff8f38 = 0;
      DAT_1fff8f39 = 2;
      DAT_1fff8f3b = param_1;
      DAT_1fff8f3c = param_2;
      DAT_1fff8f44 = param_2;
      DAT_1fff8f48 = param_3;
      DAT_1fff8f4c = param_3;
      FUN_00016370();
      if (DAT_1fff8f5c == 0) {
        DAT_1fff8f5c = FUN_000664d6();
      }
      param_4 = 100;
      uVar2 = FUN_00066554(DAT_1fff8f5c,1,1,1,100);
      if ((uVar2 & 1) == 0) {
        DAT_1fff8f3a = DAT_1fff8f3a + 1;
        if (3 < DAT_1fff8f3a) {
          DAT_1fff8f3a = 0;
          FUN_000161c0();
          uVar3 = 0xfffffff8;
        }
      }
      else {
        DAT_1fff8f3a = 0;
        uVar3 = 0;
      }
      FUN_00016988(&DAT_4004e400,0x10d8,0);
      FUN_00016834(&DAT_4004e400,0);
      DAT_1fff8f58 = '\x01';
    }
    else {
      uVar3 = 0xfffffffa;
    }
    FUN_000667a0(DAT_1fff8f60,0,0,0,param_4);
  }
  return uVar3;
}

