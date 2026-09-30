/* Address: 00015118; name: cmd_f2; body bytes: 64 */

undefined4 cmd_f2(undefined4 param_1,undefined1 *param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 uVar3;
  
  uVar3 = 0;
  FUN_0001049c(&DAT_1fffa00c,0x98);
  DAT_1fffa00c = 1;
  iVar1 = FUN_0001fc24(param_1);
  if (iVar1 == 0) {
    uVar3 = 0xff;
  }
  *param_2 = 0xf3;
  param_2[1] = 0;
  param_2[2] = uVar3;
  if (param_3 == 6) {
    param_2[3] = 0x31;
    uVar2 = 4;
  }
  else {
    uVar2 = 3;
  }
  return uVar2;
}

