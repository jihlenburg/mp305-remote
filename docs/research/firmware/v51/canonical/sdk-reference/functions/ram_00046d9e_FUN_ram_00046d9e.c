/* Address: ram:00046d9e; name: FUN_ram_00046d9e; body bytes: 84 */

void FUN_ram_00046d9e(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 auStack_50 [64];
  
  gp = 0x20004000;
  uVar1 = GAP_GetParamValue(0x3d);
  uVar2 = GAP_GetParamValue(0x3c);
  uVar3 = GAP_GetParamValue(0x3e);
  uVar4 = GAP_GetParamValue(0x3f);
  thunk_FUN_ram_000659a8(1,uVar1,uVar2,uVar3,uVar4,auStack_50);
  return;
}

