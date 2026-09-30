/* Address: ram:0004e78a; name: FUN_ram_0004e78a; body bytes: 92 */

int FUN_ram_0004e78a(undefined4 param_1,undefined4 param_2,undefined4 param_3,code *param_4)

{
  int iVar1;
  undefined2 uStack_18;
  undefined2 uStack_16;
  int iStack_14;
  
  gp = 0x20004000;
  uStack_16 = (undefined2)param_2;
  uStack_18 = 6;
  iStack_14 = FUN_ram_0004c868(param_2,3);
  iVar1 = 0x13;
  if ((iStack_14 != 0) &&
     ((iVar1 = (*param_4)(param_3,iStack_14,param_3,param_4), iVar1 != 0 ||
      (iVar1 = FUN_ram_0004d9da(param_1,&uStack_18), iVar1 != 0)))) {
    FUN_ram_20000104(iStack_14);
  }
  FUN_ram_0004e44a(param_1);
  return iVar1;
}

