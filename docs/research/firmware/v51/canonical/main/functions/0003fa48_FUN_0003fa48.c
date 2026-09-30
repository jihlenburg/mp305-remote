/* Address: 0003fa48; name: FUN_0003fa48; body bytes: 48 */

void FUN_0003fa48(int param_1,int param_2,int param_3,int param_4)

{
  if (param_4 == param_3) {
    param_4 = param_4 + 1;
  }
  if (param_2 == 0) {
    *(int *)(param_1 + 0x4c) = param_4;
    *(int *)(param_1 + 0x44) = param_3;
  }
  else if (param_2 == 1) {
    *(int *)(param_1 + 0x50) = param_4;
    *(int *)(param_1 + 0x48) = param_3;
  }
  else if (param_2 == 2) {
    *(int *)(param_1 + 0x5c) = param_4;
    *(int *)(param_1 + 0x54) = param_3;
  }
  else {
    if (param_2 != 4) {
      return;
    }
    *(int *)(param_1 + 0x60) = param_4;
    *(int *)(param_1 + 0x58) = param_3;
  }
  FUN_0004d3d8();
  return;
}

