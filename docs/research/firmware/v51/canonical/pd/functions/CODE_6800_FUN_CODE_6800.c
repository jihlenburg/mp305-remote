/* Address: CODE:6800; name: FUN_CODE_6800; body bytes: 120 */

void FUN_CODE_6800(byte param_1,byte param_2,byte param_3)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  
  FUN_CODE_ae2a(0x4af);
  DAT_EXTMEM_04b4 = 2;
  cVar4 = (param_2 < 2) << 7;
  bVar2 = param_2 - 2;
  DAT_EXTMEM_04b2 = param_2;
  DAT_EXTMEM_04b3 = param_3;
  if (param_2 >= 2) {
    bVar2 = FUN_CODE_a139(DAT_INTMEM_b3);
    if (cVar4 < '\0') {
      DAT_EXTMEM_04b4 = 1;
      FUN_CODE_9d73();
      cVar3 = FUN_CODE_aa99();
      bVar2 = 0;
      if (cVar3 != '\0' || param_1 != 0) {
        bVar2 = FUN_CODE_aac4(6);
        bVar2 = bVar2 | param_1;
        if (bVar2 == 0) {
          cVar3 = FUN_CODE_aac4(4);
          bVar2 = FUN_CODE_4503(0x4b2);
          bVar1 = param_1 - (((bVar2 < (byte)(cVar3 - (cVar4 >> 7))) << 7) >> 7);
          bVar2 = param_2 - bVar1;
          if (bVar1 <= param_2) {
            cVar4 = FUN_CODE_aac4(bVar2,2);
            param_1 = param_1 - (((param_3 < cVar4 + 1U) << 7) >> 7);
            bVar2 = param_2 - param_1;
            if (param_2 < param_1) {
              FUN_CODE_ab68(DAT_EXTMEM_04b2,6,DAT_EXTMEM_04b3);
              bVar2 = FUN_CODE_a63f(0x13);
            }
          }
        }
      }
    }
  }
                    /* WARNING: Subroutine does not return */
  FUN_CODE_adf3(bVar2,0x4af);
}

