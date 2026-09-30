/* Address: ram:00063fc6; name: FUN_ram_00063fc6; body bytes: 54 */

void FUN_ram_00063fc6(void)

{
  int iVar1;
  
  gp = 0x20004000;
  *(undefined4 *)(DAT_ram_20001efc + 0xc) = 0x1101;
  iVar1 = 0x14;
  do {
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  *(undefined4 *)(DAT_ram_20001efc + 0xc) = 0;
  iVar1 = 0x14;
  do {
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  *(undefined4 *)(DAT_ram_20001efc + 0xc) = 0x1101;
  return;
}

