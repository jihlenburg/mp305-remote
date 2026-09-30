/* Address: 0005285c; name: FUN_0005285c; body bytes: 76 */

undefined4 * FUN_0005285c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  puVar1 = (undefined4 *)FUN_0004a162(&DAT_2003a494);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[2] = param_1;
    *puVar1 = param_2;
    puVar1[4] = 0xffffffff;
    puVar1[5] = puVar1[5] & 0xfffffffe;
    uVar2 = FUN_00052708();
    puVar1[3] = param_3;
    puVar1[1] = uVar2;
    puVar1[5] = puVar1[5] | 2;
    DAT_2003a4a3 = 1;
    FUN_00052a58();
    return puVar1;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

