/* Address: ram:00046d6e; name: FUN_ram_00046d6e; body bytes: 48 */

void FUN_ram_00046d6e(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  gp = 0x20004000;
  uVar1 = GAP_GetParamValue(0x37);
  uVar2 = GAP_GetParamValue(0x38);
  uVar3 = GAP_GetParamValue(0x39);
  thunk_FUN_ram_000658b0(1,uVar1,uVar2,uVar3);
  return;
}

