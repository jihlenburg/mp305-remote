/* Address: 00041554; name: FUN_00041554; body bytes: 98 */

bool FUN_00041554(undefined1 *param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5,
                 undefined4 param_6,uint param_7)

{
  bool bVar1;
  
  if (param_1 == (undefined1 *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_0004a5e2(param_1,0x1c);
  if (param_5 == 0) {
    param_5 = FUN_00041788(param_2,param_4);
  }
  bVar1 = (uint)(param_5 * param_3) < param_7 || param_5 * param_3 - param_7 == 0;
  if (bVar1) {
    *(short *)(param_1 + 4) = (short)param_2;
    *(short *)(param_1 + 6) = (short)param_3;
    param_1[1] = (char)param_4;
    *(short *)(param_1 + 8) = (short)param_5;
    *(undefined2 *)(param_1 + 2) = 0;
    *param_1 = 0x19;
    *(uint *)(param_1 + 0xc) = param_7;
    *(undefined4 *)(param_1 + 0x10) = param_6;
    *(undefined4 *)(param_1 + 0x14) = param_6;
    *(undefined **)(param_1 + 0x18) = &DAT_2003a4e8;
    FUN_000411a4(param_6,param_4);
  }
  return bVar1;
}

