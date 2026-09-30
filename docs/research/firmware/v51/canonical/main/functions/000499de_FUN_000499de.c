/* Address: 000499de; name: FUN_000499de; body bytes: 80 */

void FUN_000499de(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  if (param_2 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uStack_8 = param_3;
  uStack_4 = param_4;
  FUN_0004d3d8(param_1);
  if (param_2 != 0) {
    if ((*(int *)(param_1 + 0x2c) != 0) && (-1 < (int)((uint)*(byte *)(param_1 + 0x5c) << 0x1c))) {
      FUN_00046bec();
      *(undefined4 *)(param_1 + 0x2c) = 0;
    }
    uVar1 = FUN_00051b74(param_2,&uStack_8);
    *(undefined4 *)(param_1 + 0x2c) = uVar1;
    *(byte *)(param_1 + 0x5c) = *(byte *)(param_1 + 0x5c) & 0xf7;
  }
  FUN_000493d0(param_1);
  return;
}

