/* Address: 000149c8; name: FUN_000149c8; body bytes: 74 */

/* WARNING: Removing unreachable block (ram,0x000658a2) */
/* Recovered from stored Thumb pointer at 00017878; callback identification is inferred until
   reviewed. */

void FUN_000149c8(void)

{
  int iVar1;
  
  iVar1 = FUN_000149b4(1);
  if (iVar1 != 1) {
    return;
  }
  FUN_000149a8();
  if (DAT_1ffe0224 != 0) {
    FUN_000670cc(0x656b3,DAT_1ffe0224,1,&stack0xfffffff8);
  }
  return;
}

