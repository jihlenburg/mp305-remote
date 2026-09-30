/* Address: 00052aae; name: FUN_00052aae; body bytes: 16 */

void FUN_00052aae(int param_1)

{
  if (param_1 != 0) {
    *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) & 0xfffffffe;
    FUN_00052a58();
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

