/* Address: 0003f9a4; name: FUN_0003f9a4; body bytes: 46 */

void FUN_0003f9a4(undefined4 param_1,int param_2,undefined4 param_3)

{
  if (param_2 != 0) {
    if ((-1 < (int)((uint)*(byte *)(param_2 + 0x10) << 0x1d)) && (*(int *)(param_2 + 4) != 0)) {
      FUN_00046bec();
    }
    *(undefined4 *)(param_2 + 4) = param_3;
    *(uint *)(param_2 + 0x10) = *(uint *)(param_2 + 0x10) | 4;
    FUN_0004d3d8(param_1);
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

