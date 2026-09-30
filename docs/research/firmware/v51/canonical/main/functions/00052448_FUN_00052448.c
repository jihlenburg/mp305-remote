/* Address: 00052448; name: FUN_00052448; body bytes: 116 */

void FUN_00052448(int param_1,uint param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if ((*(byte *)(param_1 + 0x70) & 0xf) >> 3 != param_2) {
    *(byte *)(param_1 + 0x70) = *(byte *)(param_1 + 0x70) & 0xf7 | (byte)((param_2 & 1) << 3);
    uVar2 = 0x3fffffff;
    if (param_2 == 0) {
      uVar2 = FUN_0004f078(100);
      uVar1 = 0;
    }
    else {
      uVar1 = FUN_0004f078(100);
    }
    FUN_0004eae2(*(undefined4 *)(param_1 + 0x2c),uVar2);
    FUN_0004e9c8(*(undefined4 *)(param_1 + 0x2c),uVar1,0);
    if (param_2 == 0) {
      FUN_0004e088(param_1,2,0);
    }
    else {
      FUN_0004e654(param_1,0x3fffffff);
    }
    FUN_0004e496(param_1,0,0);
    return;
  }
  return;
}

