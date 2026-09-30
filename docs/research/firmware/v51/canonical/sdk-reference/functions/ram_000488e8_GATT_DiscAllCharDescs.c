/* Address: ram:000488e8; name: GATT_DiscAllCharDescs; body bytes: 78 */

int GATT_DiscAllCharDescs
              (undefined4 param_1,undefined2 param_2,undefined2 param_3,undefined4 param_4)

{
  int iVar1;
  undefined2 uStack_18;
  undefined2 uStack_16;
  undefined4 uStack_14;
  
  gp = 0x20004000;
  uStack_18 = param_2;
  uStack_16 = param_3;
  iVar1 = FUN_ram_0004957c(param_1,&uStack_14);
  if ((iVar1 == 0) && (iVar1 = FUN_ram_00043650(param_1,&uStack_18), iVar1 == 0)) {
    FUN_ram_0004972e(uStack_14,&uStack_18,5,&LAB_ram_00043608,param_4);
  }
  return iVar1;
}

