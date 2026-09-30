/* Address: ram:0005a7de; name: FUN_ram_0005a7de; body bytes: 38 */

void FUN_ram_0005a7de(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  if (iVar1 != 0) {
    uVar2 = LL_GetNumberOfUnAckPacket(param_1);
    *(undefined4 *)(iVar1 + 0x188) = uVar2;
  }
  return;
}

