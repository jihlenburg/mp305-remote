/* Address: 00045204; name: FUN_00045204; body bytes: 172 */

void FUN_00045204(undefined4 *param_1,undefined4 param_2,undefined4 param_3,uint param_4,
                 uint param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((int)param_4 < 0) {
    param_4 = 0;
  }
  else if (0x167 < (int)param_4) {
    param_4 = 0x167;
  }
  if ((int)param_5 < 0) {
    param_5 = 0;
  }
  else if (0x167 < (int)param_5) {
    param_5 = 0x167;
  }
  if ((int)param_5 < (int)param_4) {
    iVar1 = (0x168 - param_4) + param_5;
  }
  else {
    iVar1 = param_5 - param_4;
    if (iVar1 < 1) {
      iVar1 = param_4 - param_5;
    }
  }
  *(short *)(param_1 + 0x22) = (short)iVar1;
  param_1[4] = param_4;
  param_1[5] = param_5;
  FUN_0004f266(param_1 + 2);
  *param_1 = 0x42493;
  *(undefined1 *)(param_1 + 1) = 1;
  if (0x168 < param_4) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if ((-1 < (int)param_5) && ((int)param_4 < 0x169)) {
    if ((param_5 < 0xb4) || (0xb3 < param_5 - 0xb4)) {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
    FUN_0004537c(param_1 + 6,param_2,param_3,(int)(short)param_4,0xb3 < param_4);
    FUN_0004537c(param_1 + 0x14,param_2,param_3,(int)(short)param_5,uVar2);
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

