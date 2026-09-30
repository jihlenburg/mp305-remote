/* Address: ram:000489c2; name: GATT_ExchangeMTU; body bytes: 76 */

int GATT_ExchangeMTU(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 auStack_24 [4];
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004957c(param_1,auStack_24);
  if ((iVar1 == 0) && (iVar1 = FUN_ram_000435c2(param_1,param_2), iVar1 == 0)) {
    FUN_ram_0004972e(auStack_24[0],param_2,3,&LAB_ram_000435a4,param_3);
  }
  return iVar1;
}

