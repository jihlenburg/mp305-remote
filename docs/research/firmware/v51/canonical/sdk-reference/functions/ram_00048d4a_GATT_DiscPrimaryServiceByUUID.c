/* Address: ram:00048d4a; name: GATT_DiscPrimaryServiceByUUID; body bytes: 122 */

int GATT_DiscPrimaryServiceByUUID(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined1 uStack_34;
  undefined1 auStack_33 [31];
  
  gp = 0x20004000;
  if ((param_3 != 2) && (param_3 != 0x10)) {
    gp = 0x20004000;
    return 2;
  }
  iVar1 = 0;
  if ((param_2 != 0) && (iVar1 = FUN_ram_0004957c(param_1,&uStack_3c), iVar1 == 0)) {
    uStack_38 = 0xffff0001;
    uStack_34 = (undefined1)param_3;
    tmos_memcpy(auStack_33,param_2);
    iVar1 = FUN_ram_00048cce(param_1,&uStack_38);
    if (iVar1 == 0) {
      FUN_ram_0004972e(uStack_3c,&uStack_38,7,&LAB_ram_00043660,param_4);
    }
  }
  return iVar1;
}

