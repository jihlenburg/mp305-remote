/* Address: ram:00048b38; name: GATT_WriteNoRsp; body bytes: 64 */

int GATT_WriteNoRsp(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined1 auStack_14 [8];
  
  gp = 0x20004000;
  if (1 < DAT_ram_20001a62) {
    iVar1 = FUN_ram_0004957c(param_1,auStack_14);
    if (iVar1 == 0) {
      *(undefined2 *)(param_2 + 8) = 0x100;
      iVar1 = FUN_ram_00043800(param_1,param_2);
    }
    return iVar1;
  }
  return 0x16;
}

