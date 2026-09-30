/* Address: ram:000432b0; name: ATT_GetMTU; body bytes: 30 */

int ATT_GetMTU(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  if (param_1 == 0xfffe) {
    iVar1 = FUN_ram_0004c74c();
    return iVar1;
  }
  iVar1 = FUN_ram_0004e066();
  if (iVar1 == 0) {
    iVar1 = 0x17;
  }
  return iVar1;
}

