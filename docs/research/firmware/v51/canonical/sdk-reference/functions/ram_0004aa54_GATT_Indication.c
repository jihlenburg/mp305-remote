/* Address: ram:0004aa54; name: GATT_Indication; body bytes: 164 */

int GATT_Indication(undefined4 param_1,undefined2 *param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined2 auStack_22 [5];
  
  gp = 0x20004000;
  iVar2 = FUN_ram_0004a3c6();
  iVar1 = 2;
  if (iVar2 != 0) {
    iVar1 = 0x17;
    if ((*(char *)(iVar2 + 2) != -2) && (iVar1 = 0x16, *(char *)(iVar2 + 2) == -1)) {
      if (param_3 != 0) {
        auStack_22[0] = 0;
        GATT_FindHandle(*param_2,auStack_22);
        uVar3 = FUN_ram_0004a2ae(auStack_22[0]);
        iVar1 = FUN_ram_0004df46(param_1,uVar3,1);
        if (iVar1 != 0) {
          gp = 0x20004000;
          return iVar1;
        }
      }
      iVar1 = FUN_ram_00043e66(param_1,param_2);
      if ((iVar1 == 0) && (param_4 != 0xff)) {
        FUN_ram_0004887a(&LAB_ram_00049de6,iVar2,0x1e,iVar2 + 2);
        *(char *)(iVar2 + 3) = (char)param_4;
      }
    }
  }
  return iVar1;
}

