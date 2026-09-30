/* Address: 00052a98; name: FUN_00052a98; body bytes: 22 */

void FUN_00052a98(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 != 0) {
    uVar1 = FUN_00052708();
    *(undefined4 *)(param_1 + 4) = uVar1;
    FUN_00052a58();
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

