/* Address: CODE:666b; name: FUN_CODE_666b; body bytes: 120 */

void FUN_CODE_666b(char param_1,undefined1 param_2,char param_3)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  char cVar6;
  char *pcVar4;
  undefined1 *puVar5;
  
  DAT_EXTMEM_04c6 = param_3;
  FUN_CODE_ae2a(0x4c7);
  FUN_CODE_a97a(1);
  DAT_EXTMEM_04ca = 0;
  while( true ) {
    cVar6 = -0x36;
    if (0xb < DAT_EXTMEM_04ca) {
      return;
    }
    bVar1 = DAT_EXTMEM_04ca;
    uVar2 = FUN_CODE_8b2b(DAT_EXTMEM_04ca - 0xc);
    if (*(char *)CONCAT11(uVar2,cVar6) == '\0') break;
    pcVar4 = (char *)CONCAT11(uVar2,cVar6 + '\x05');
    FUN_CODE_8b1b();
    if (*pcVar4 != param_1) break;
    DAT_EXTMEM_04ca = DAT_EXTMEM_04ca + 1;
  }
  cVar6 = DAT_EXTMEM_04c6;
  if (*(char *)CONCAT11(param_2,bVar1) == '\0') {
    BANK1_R2 = BANK1_R2 + '\x01';
  }
  *(char *)CONCAT11(param_2,bVar1) = DAT_EXTMEM_04c6;
  ((char *)CONCAT11(param_2,bVar1))[1] = DAT_INTMEM_b3;
  puVar5 = (undefined1 *)
           CONCAT11(-0x49 - (((0xeaU < (byte)(cVar6 * '\x02')) << 7) >> 7),cVar6 * '\x02' + 0x15);
  uVar2 = *puVar5;
  uVar3 = FUN_CODE_8b24(puVar5[1]);
  puVar5[1] = uVar2;
  puVar5[2] = uVar3;
                    /* WARNING: Subroutine does not return */
  FUN_CODE_adf3(0x4c7);
}

