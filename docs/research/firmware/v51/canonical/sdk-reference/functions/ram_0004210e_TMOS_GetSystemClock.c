/* Address: ram:0004210e; name: TMOS_GetSystemClock; body bytes: 42 */

int TMOS_GetSystemClock(void)

{
  int iVar1;
  
  gp = 0x20004000;
  if (DAT_ram_20001bfc != (code *)0x0) {
    iVar1 = (*DAT_ram_20001bfc)();
    DAT_ram_20001b78 = iVar1 + DAT_ram_20001b78;
  }
  return DAT_ram_20001b78;
}

