/* Address: ram:20002644; name: FUN_ram_20002644; body bytes: 184 */

void FUN_ram_20002644(void)

{
  undefined4 *puVar1;
  char cVar2;
  
  gp = &DAT_ram_20002000;
  if ((DAT_ram_40002006 & 1) != 0) {
    DAT_ram_20002fa0 = 1;
    DAT_ram_40002006 = 1;
    DAT_ram_40002002 = DAT_ram_40002002 & 0xfe;
  }
  cVar2 = DAT_ram_40002007;
  if ((DAT_ram_40002006 & 2) != 0) {
    while ((char)(cVar2 + -1) != -1) {
      if ((0x67 < DAT_ram_20002fa4) || (DAT_ram_20002fa0 != 0)) {
        DAT_ram_20002fa4 = 0;
        DAT_ram_20002fa0 = 0;
      }
      puVar1 = &DAT_ram_200043c0 + DAT_ram_20002fa4;
      DAT_ram_20002fa4 = DAT_ram_20002fa4 + 1;
      *puVar1 = DAT_ram_40002010;
      cVar2 = cVar2 + -1;
    }
    DAT_ram_40002006 = 2;
    DAT_ram_40002002 = DAT_ram_40002002 | 1;
  }
  return;
}

