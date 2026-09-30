/* Address: 00065c5c; name: FUN_00065c5c; body bytes: 64 */

/* Recovered from stored Thumb pointer at 000538e0; callback identification is inferred until
   reviewed. */

void FUN_00065c5c(void)

{
  undefined4 uVar1;
  undefined2 *puVar2;
  
  uVar1 = FUN_00046698();
  FUN_0004bc8c();
  puVar2 = (undefined2 *)FUN_0003f334();
  if (0xb < (int)*(char *)(puVar2 + 1) - 1U) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar1 = FUN_0004b9de(uVar1,1);
  FUN_000499de(uVar1,"%d %s",*puVar2,(&PTR_DAT_1ffe0094)[*(char *)(puVar2 + 1)]);
  return;
}

