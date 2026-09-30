/* Address: ram:0004a65c; name: FUN_ram_0004a65c; body bytes: 40 */

void FUN_ram_0004a65c(undefined4 param_1,int param_2)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004a3c6();
  if ((iVar1 != 0) && (param_2 == *(byte *)(iVar1 + 4) + 1)) {
    *(byte *)(iVar1 + 4) = *(byte *)(iVar1 + 4) & 0x80;
  }
  return;
}

