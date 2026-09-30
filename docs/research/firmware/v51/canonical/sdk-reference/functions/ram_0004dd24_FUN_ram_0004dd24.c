/* Address: ram:0004dd24; name: FUN_ram_0004dd24; body bytes: 168 */

int FUN_ram_0004dd24(undefined4 param_1,undefined1 param_2,int param_3,undefined1 *param_4)

{
  int iVar1;
  undefined2 uStack_2c;
  undefined2 uStack_2a;
  undefined2 uStack_28;
  undefined2 uStack_26;
  undefined2 uStack_24;
  
  gp = 0x20004000;
  tmos_memset(&uStack_2c,0,10);
  uStack_24 = (undefined2)param_3;
  if (param_3 == 0) {
    uStack_2c = *(undefined2 *)(param_4 + 2);
    uStack_28 = DAT_ram_20001a5e;
    iVar1 = *(int *)(param_4 + 0xc);
    if (iVar1 != 0) {
      uStack_26 = *(undefined2 *)(iVar1 + 8);
      uStack_2a = *(undefined2 *)(DAT_ram_20001cc4 + (uint)*(byte *)(iVar1 + 0x1c) * 0x10 + 2);
    }
  }
  iVar1 = FUN_ram_0004da64(param_1,0x15,param_2,&uStack_2c,&LAB_ram_0004dc3c);
  if ((iVar1 == 0) || (param_3 == 0)) {
    *param_4 = 1;
    param_4[4] = 0;
    FUN_ram_0004d312(param_4,0,0);
  }
  else {
    FUN_ram_0004c420(param_4);
  }
  return iVar1;
}

