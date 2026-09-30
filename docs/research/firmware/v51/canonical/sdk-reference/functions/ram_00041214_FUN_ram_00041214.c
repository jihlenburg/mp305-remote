/* Address: ram:00041214; name: FUN_ram_00041214; body bytes: 254 */

void FUN_ram_00041214(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  gp = 0x20004000;
  if ((*(uint *)(DAT_ram_20001e88 + 0x38) >> 6 & 1) != 0) {
    *(uint *)(DAT_ram_20001e88 + 0x38) = *(uint *)(DAT_ram_20001e88 + 0x38) & 0xffffff9f;
    if (DAT_ram_20001e9a == 0x80) {
      DAT_ram_20001e9a = (byte)*DAT_ram_20001e84 & 0x40;
    }
    if ((DAT_ram_20001e94 & 0x40) != 0) {
      DAT_ram_20001ea4 = (*DAT_ram_20001c00)();
      DAT_ram_20001e94 = DAT_ram_20001e94 & 0xbf;
    }
    iVar2 = DAT_ram_20001eb0;
    if ((DAT_ram_20001e98 & 0x40) == 0) {
      DAT_ram_20001e99 = 1;
      *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x2000;
      DAT_ram_20001e98 = 0xc0;
      *(undefined4 *)(iVar2 + 100) = DAT_ram_20001ea0;
    }
  }
  iVar2 = DAT_ram_20001e88;
  if ((*(uint *)(DAT_ram_20001e88 + 0x38) >> 4 & 1) != 0) {
    *(uint *)(DAT_ram_20001e88 + 0x38) = *(uint *)(DAT_ram_20001e88 + 0x38) & 0xffffffef;
    DAT_ram_20001e98 = 1;
  }
  if ((*(uint *)(iVar2 + 0x38) >> 7 & 1) != 0) {
    *(uint *)(iVar2 + 0x38) = *(uint *)(iVar2 + 0x38) & 0xffffff7f;
    DAT_ram_20001e98 = 1;
  }
  puVar1 = DAT_ram_20001e84;
  if (((uint)DAT_ram_20001e84[1] >> 1 & 1) != 0) {
    DAT_ram_20001e84[1] = DAT_ram_20001e84[1] & 0xfffffffd;
    puVar1[1] = puVar1[1] & 0xfffffffe;
  }
  return;
}

