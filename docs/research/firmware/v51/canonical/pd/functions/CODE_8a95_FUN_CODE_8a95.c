/* Address: CODE:8a95; name: FUN_CODE_8a95; body bytes: 45 */

void FUN_CODE_8a95(void)

{
  byte bVar1;
  
  FUN_CODE_6c1b(0x4ae);
  bVar1 = FUN_CODE_a934(DAT_EXTMEM_04b0 + 0x10,
                        DAT_EXTMEM_04af - (((0xef < DAT_EXTMEM_04b0) << 7) >> 7),DAT_EXTMEM_04ae);
  bVar1 = FUN_CODE_a99c(bVar1 | 1);
  bVar1 = FUN_CODE_a99c(bVar1 | 2);
  bVar1 = FUN_CODE_a99c(bVar1 & 0xf7);
  FUN_CODE_a99c(bVar1 | 4);
  return;
}

