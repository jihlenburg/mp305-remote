/* Address: ram:20002856; name: FUN_ram_20002856; body bytes: 72 */

void FUN_ram_20002856(uint param_1,uint param_2)

{
  int iVar1;
  
  gp = &DAT_ram_20002000;
  iVar1 = 5;
  if ((param_1 & 0xbf) != 0xb) {
    FUN_ram_2000281a(6);
    FUN_ram_2000282c();
    iVar1 = 3;
  }
  FUN_ram_2000281a(param_1);
  while (iVar1 = iVar1 + -1, iVar1 != -1) {
    FUN_ram_20002848(param_2 >> 0x10 & 0xff);
    param_2 = param_2 << 8;
  }
  return;
}

