/* Address: ram:00041eae; name: tmos_rand; body bytes: 78 */

void tmos_rand(void)

{
  int iVar1;
  code *pcVar2;
  
  gp = 0x20004000;
  pcVar2 = DAT_ram_20001bdc;
  if ((DAT_ram_20001bdc != (code *)0x0) ||
     (pcVar2 = DAT_ram_20001c00, DAT_ram_20001c00 != (code *)0x0)) {
    iVar1 = (*pcVar2)();
    DAT_ram_200019a0 = iVar1 + DAT_ram_200019a0;
  }
  DAT_ram_200019a0 = DAT_ram_200019a0 * 0x343fd + 0x269ec3;
  return;
}

