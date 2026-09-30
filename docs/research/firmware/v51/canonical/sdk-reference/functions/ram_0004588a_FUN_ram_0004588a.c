/* Address: ram:0004588a; name: FUN_ram_0004588a; body bytes: 58 */

void FUN_ram_0004588a(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  gp = 0x20004000;
  iVar1 = GAP_GetParamValue(0x15);
  uVar2 = GAP_GetParamValue(0x24);
  uVar3 = GAP_GetParamValue(0x25);
  thunk_FUN_ram_00065948(param_1,iVar1 != 0,uVar2,uVar3);
  return;
}

