/* Address: ram:000625d4; name: BLE_RegInit; body bytes: 216 */

void BLE_RegInit(void)

{
  uint *puVar1;
  
  gp = 0x20004000;
  if (((DAT_ram_20001e9b != '\t') && (DAT_ram_20001e9b != '\x04')) &&
     (DAT_ram_20001e84 == &DAT_ram_4000c300)) {
    FUN_ram_00062730();
    FUN_ram_00063ffc();
    FUN_ram_00061c92();
    puVar1 = DAT_ram_20001e88;
    *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xffffcfff;
    *puVar1 = *puVar1 & 0xfffffe7f;
    *puVar1 = *puVar1 & 0xfffffe7f | 0x100;
    *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
    *(undefined4 *)(DAT_ram_20001eb0 + 0x50) = 0xdd;
    FUN_ram_00064394();
    FUN_ram_000650d8();
    FUN_ram_00064208();
    FUN_ram_0006428a();
    *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f | 0x80;
    *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) & 0xffcdffff;
    *(undefined4 *)(DAT_ram_20001eb0 + 0x50) = 0x80;
    FUN_ram_0006219c();
    DAT_ram_20001e9b = '\0';
  }
  return;
}

