/* Address: ram:00049554; name: FUN_ram_00049554; body bytes: 40 */

void FUN_ram_00049554(undefined4 param_1,int param_2)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00049522();
  if ((iVar1 != 0) && (param_2 == *(byte *)(iVar1 + 10) + 1)) {
    *(byte *)(iVar1 + 10) = *(byte *)(iVar1 + 10) & 0x80;
  }
  return;
}

