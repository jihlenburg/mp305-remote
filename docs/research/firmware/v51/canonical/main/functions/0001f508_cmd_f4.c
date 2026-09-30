/* Address: 0001f508; name: cmd_f4; body bytes: 64 */

undefined4 cmd_f4(int param_1,undefined1 *param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 uVar3;
  
  uVar3 = 0;
  iVar1 = FUN_0001fc94();
  if (iVar1 == 0) {
    uVar3 = 0xff;
  }
  *param_2 = 0xf5;
  param_2[1] = 0;
  param_2[2] = *(undefined1 *)(param_1 + 2);
  param_2[3] = *(undefined1 *)(param_1 + 3);
  param_2[4] = *(undefined1 *)(param_1 + 4);
  param_2[5] = *(undefined1 *)(param_1 + 5);
  param_2[6] = uVar3;
  if (param_3 == 6) {
    param_2[7] = 0x31;
    uVar2 = 8;
  }
  else {
    uVar2 = 7;
  }
  return uVar2;
}

