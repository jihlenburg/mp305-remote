/* Address: 0001f250; name: cmd_f6; body bytes: 50 */

undefined4 cmd_f6(undefined4 param_1,undefined1 *param_2,int param_3)

{
  int iVar1;
  undefined1 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_0001fe0c();
  if (iVar1 == 0) {
    uVar2 = 0xff;
    FUN_0001bdc6(0xf0000);
  }
  *param_2 = 0xf7;
  param_2[1] = 0;
  param_2[2] = uVar2;
  if (param_3 != 6) {
    return 3;
  }
  param_2[3] = 0x31;
  return 4;
}

