/* Address: ram:0004c80e; name: FUN_ram_0004c80e; body bytes: 48 */

undefined4 FUN_ram_0004c80e(undefined1 param_1,int param_2)

{
  int iVar1;
  
  gp = 0x20004000;
  if ((param_2 - 4U & 0xffff) < 4) {
    iVar1 = (param_2 - 4U) * 0xc;
    (&DAT_ram_20001cce)[iVar1] = param_1;
    *(short *)(&DAT_ram_20001ccc + iVar1) = (short)param_2;
    return 0;
  }
  return 2;
}

