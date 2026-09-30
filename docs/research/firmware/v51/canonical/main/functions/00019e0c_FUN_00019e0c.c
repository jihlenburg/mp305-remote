/* Address: 00019e0c; name: FUN_00019e0c; body bytes: 210 */

/* WARNING: Removing unreachable block (ram,0x0001f460) */
/* WARNING: Removing unreachable block (ram,0x0001f458) */
/* WARNING: Removing unreachable block (ram,0x0001f4b2) */
/* WARNING: Removing unreachable block (ram,0x0001f49e) */
/* WARNING: Removing unreachable block (ram,0x0001f4b6) */

void FUN_00019e0c(void)

{
  undefined2 extraout_var;
  undefined4 unaff_r4;
  undefined8 uVar1;
  
  DAT_1fffaa2f = 0;
  DAT_1fffa94c = 0;
  DAT_1fffa948 = 0;
  DAT_1fffa93c = 0x5dc;
  FUN_00019116(1);
  FUN_00018c52(1);
  FUN_00019cec();
  FUN_0001f548(0);
  uVar1 = FUN_000103ea(0xa9cda560,0x325,0xce4,0,unaff_r4);
  FUN_000103ea((int)uVar1,(int)((ulonglong)uVar1 >> 0x20),1000,0);
  DAT_1ffe01dc = 0;
  FUN_0001416c(&DAT_40041000,1,0);
  FUN_0001ce68(extraout_var);
  FUN_0001ce98(0x3ff);
  DAT_1fffa95c = 0;
  return;
}

