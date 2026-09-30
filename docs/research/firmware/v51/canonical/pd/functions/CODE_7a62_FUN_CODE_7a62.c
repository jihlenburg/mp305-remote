/* Address: CODE:7a62; name: FUN_CODE_7a62; body bytes: 72 */

byte FUN_CODE_7a62(undefined1 param_1)

{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  undefined1 *puVar4;
  
  pbVar3 = (byte *)CONCAT11('\x04' - (((0x62 < DAT_INTMEM_b3) << 7) >> 7),DAT_INTMEM_b3 + 0x9d);
  bVar1 = *pbVar3;
  bVar2 = bVar1 + 1;
  *pbVar3 = bVar2;
  if (9 < bVar2) {
    *(undefined1 *)CONCAT11('\x04' - (((0x62 < DAT_INTMEM_b3) << 7) >> 7),DAT_INTMEM_b3 + 0x9d) = 0;
    bVar1 = DAT_INTMEM_b3;
    FUN_CODE_959b();
    FUN_CODE_1e41();
    FUN_CODE_10ae();
    puVar4 = (undefined1 *)
             CONCAT11('\x04' - (((0xbc < DAT_INTMEM_b3 * '\x02') << 7) >> 7),
                      DAT_INTMEM_b3 * '\x02' + 0x43);
    *puVar4 = param_1;
    puVar4[1] = bVar1;
    return bVar1;
  }
  return bVar1 - 9;
}

