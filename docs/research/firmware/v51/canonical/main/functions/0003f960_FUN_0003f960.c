/* Address: 0003f960; name: FUN_0003f960; body bytes: 46 */

void FUN_0003f960(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  if (param_2 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  *(undefined4 *)(param_2 + 8) = param_4;
  *(uint *)(param_2 + 0x14) = *(uint *)(param_2 + 0x14) & 0xfffffeff;
  if (param_3 == 0) {
    param_3 = FUN_0003f90e(param_1,0);
  }
  *(int *)(param_2 + 0x10) = param_3;
  FUN_0004d3d8(param_1);
  return;
}

