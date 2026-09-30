/* Address: CODE:7568; name: FUN_CODE_7568; body bytes: 88 */

void FUN_CODE_7568(undefined1 param_1)

{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)0xffff;
  FUN_CODE_aeac();
  *puVar1 = param_1;
  FUN_CODE_a62a();
  FUN_CODE_ae2a(0x727);
  FUN_CODE_a631();
  FUN_CODE_ae2a(0x724);
  FUN_CODE_a769(*(undefined1 *)CONCAT11(BANK1_R0,BANK1_R1));
  DAT_INTMEM_cf = 0;
  DAT_INTMEM_d0 = 0;
  DAT_SFR_c6 = 6;
  DAT_SFR_ce = 0xee;
  DAT_SFR_d6 = 3;
  RXCNTL = (&DAT_CODE_b9ce)[*(byte *)CONCAT11(BANK1_R0,BANK1_R1)];
  HPCON = (&DAT_CODE_b9d1)[*(byte *)CONCAT11(BANK1_R0,BANK1_R1)];
  FUN_CODE_a20b((&DAT_CODE_b9d1)[*(byte *)CONCAT11(BANK1_R0,BANK1_R1)]);
  HPSTAT = 4;
  FUN_CODE_a449();
  FUN_CODE_aeac(1);
  return;
}

