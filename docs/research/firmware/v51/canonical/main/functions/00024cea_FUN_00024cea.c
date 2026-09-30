/* Address: 00024cea; name: FUN_00024cea; body bytes: 22 */

int FUN_00024cea(int param_1)

{
  if (*(uint *)(param_1 + 4) >> 2 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return (*(uint *)(param_1 + 4) & 0xfffffffc) + param_1 + 4;
}

