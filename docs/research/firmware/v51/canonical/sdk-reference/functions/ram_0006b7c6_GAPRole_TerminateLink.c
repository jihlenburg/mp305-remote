/* Address: ram:0006b7c6; name: GAPRole_TerminateLink; body bytes: 36 */

undefined4 GAPRole_TerminateLink(undefined4 param_1)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  puVar1 = (undefined1 *)FUN_ram_0004df14();
  if (puVar1 != (undefined1 *)0x0) {
    uVar2 = FUN_ram_00045118(*puVar1,param_1,0x13);
    return uVar2;
  }
  return 0x12;
}

