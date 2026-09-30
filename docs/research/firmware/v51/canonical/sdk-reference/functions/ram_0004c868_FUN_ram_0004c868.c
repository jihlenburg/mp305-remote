/* Address: ram:0004c868; name: FUN_ram_0004c868; body bytes: 42 */

void FUN_ram_0004c868(short param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_20000040(param_1 + 6,0x4c03);
  if (iVar1 != 0) {
    FUN_ram_00041bf2(iVar1,0xfffffffa);
    return;
  }
  return;
}

