/* Address: 0001dffc; name: cmd_00; body bytes: 36 */

undefined4 cmd_00(int param_1,undefined1 *param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  
  *param_2 = 1;
  param_2[1] = 0x91;
  param_2[2] = 0x67;
  param_2[3] = 1;
  uVar1 = 4;
  if (param_3 == 6) {
    param_2[4] = *(undefined1 *)(param_1 + param_4 + -1);
    uVar1 = 5;
  }
  return uVar1;
}

