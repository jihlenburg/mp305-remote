/* Address: 00052a74; name: FUN_00052a74; body bytes: 14 */

void FUN_00052a74(int param_1)

{
  if (param_1 != 0) {
    *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) | 1;
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

