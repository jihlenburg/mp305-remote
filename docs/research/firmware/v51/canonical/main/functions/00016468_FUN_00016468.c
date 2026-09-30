/* Address: 00016468; name: FUN_00016468; body bytes: 198 */

undefined4
FUN_00016468(undefined1 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar3 = param_4;
  if (DAT_1fff8f60 == 0) {
    DAT_1fff8f60 = FUN_000666a0(1);
  }
  iVar1 = FUN_00066a10(DAT_1fff8f60,100);
  uVar2 = 0xfffffff8;
  if (iVar1 != 0) {
    if (DAT_1fff8f58 == '\x01') {
      DAT_1fff8f50 = param_5;
      DAT_1fff8f58 = 0;
      DAT_1fff8f54 = 0;
      DAT_1fff8f38 = 0;
      DAT_1fff8f39 = 1;
      DAT_1fff8f3b = param_1;
      DAT_1fff8f3c = param_2;
      DAT_1fff8f40 = param_4;
      DAT_1fff8f44 = param_2;
      DAT_1fff8f48 = param_3;
      DAT_1fff8f4c = param_3;
      FUN_00016370();
      if (DAT_1fff8f5c == 0) {
        DAT_1fff8f5c = FUN_000664d6();
      }
      uVar3 = 100;
      iVar1 = FUN_00066554(DAT_1fff8f5c,2,1,1,100);
      if (iVar1 << 0x1e < 0) {
        DAT_1fff8f3a = 0;
        uVar2 = 0;
      }
      else {
        DAT_1fff8f3a = DAT_1fff8f3a + 1;
        if (3 < DAT_1fff8f3a) {
          DAT_1fff8f3a = 0;
          FUN_000161c0();
          uVar2 = 0xfffffff8;
        }
      }
      FUN_00016988(&DAT_4004e400,0x10d8,0);
      FUN_00016834(&DAT_4004e400,0);
      DAT_1fff8f58 = '\x01';
    }
    else {
      uVar2 = 0xfffffffa;
    }
    FUN_000667a0(DAT_1fff8f60,0,0,0,uVar3);
  }
  return uVar2;
}

