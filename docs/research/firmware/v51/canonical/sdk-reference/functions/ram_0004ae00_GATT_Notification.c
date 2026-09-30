/* Address: ram:0004ae00; name: GATT_Notification; body bytes: 116 */

int GATT_Notification(undefined4 param_1,undefined2 *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined2 uStack_12;
  
  gp = 0x20004000;
  if (DAT_ram_20001a62 < 2) {
    return 0x16;
  }
  iVar1 = FUN_ram_0004a3c6();
  if ((iVar1 == 0) || (iVar2 = 0x17, *(char *)(iVar1 + 2) != -2)) {
    if (param_3 != 0) {
      uStack_12 = 0;
      GATT_FindHandle(*param_2,&uStack_12);
      uVar3 = FUN_ram_0004a2ae(uStack_12);
      iVar1 = FUN_ram_0004df46(param_1,uVar3,1);
      if (iVar1 != 0) {
        gp = 0x20004000;
        return iVar1;
      }
    }
    iVar2 = FUN_ram_00043e34(param_1,param_2);
  }
  return iVar2;
}

