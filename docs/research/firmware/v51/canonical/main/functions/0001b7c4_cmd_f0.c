/* Address: 0001b7c4; name: cmd_f0; body bytes: 44 */

undefined4 cmd_f0(int param_1,undefined1 *param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (*(char *)(param_1 + 1) == -0x54) {
    DAT_1fffa00c = 1;
    *param_2 = 0xf1;
    param_2[1] = 0;
    uVar1 = 2;
    if (param_3 == 6) {
      param_2[2] = *(undefined1 *)(param_1 + param_4 + -1);
      uVar1 = 3;
    }
  }
  return uVar1;
}

