/* Address: CODE:27b2; name: FUN_CODE_27b2; body bytes: 78 */

byte FUN_CODE_27b2(undefined1 param_1)

{
  byte bVar1;
  undefined1 uVar2;
  
  FUN_CODE_a377();
  FUN_CODE_33b9();
  FUN_CODE_a9ae(0,0x58);
  FUN_CODE_a9ae(0,0x59);
  FUN_CODE_a9ae(0,0x5a);
  FUN_CODE_a9ae(0,0x5c);
  uVar2 = 0;
  FUN_CODE_a623(0);
  FUN_CODE_33d6();
  FUN_CODE_ab68(param_1,0x50,uVar2);
  uVar2 = 0;
  FUN_CODE_a61c(0);
  FUN_CODE_33d6();
  FUN_CODE_ab68(param_1,0x52,uVar2);
  bVar1 = DAT_SFR_c2;
  DAT_SFR_c2 = bVar1 | (&DAT_CODE_b8f6)[DAT_INTMEM_b3];
  return (&DAT_CODE_b8f6)[DAT_INTMEM_b3];
}

