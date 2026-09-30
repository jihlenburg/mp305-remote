/* Address: 00024b34; name: FUN_00024b34; body bytes: 34 */

int FUN_00024b34(int param_1,int param_2)

{
  if (*(uint *)(param_1 + 4) >> 2 != 0) {
    *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) + (*(uint *)(param_2 + 4) & 0xfffffffc) + 4;
    FUN_00024bd4(param_1);
    return param_1;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

