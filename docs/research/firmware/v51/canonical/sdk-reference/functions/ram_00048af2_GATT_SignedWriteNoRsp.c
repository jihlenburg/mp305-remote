/* Address: ram:00048af2; name: GATT_SignedWriteNoRsp; body bytes: 50 */

void GATT_SignedWriteNoRsp(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined1 auStack_14 [8];
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004957c(param_1,auStack_14);
  if (iVar1 != 0x17) {
    *(undefined **)(param_2 + 8) = &sedeleg;
    FUN_ram_00043800(param_1,param_2);
  }
  return;
}

