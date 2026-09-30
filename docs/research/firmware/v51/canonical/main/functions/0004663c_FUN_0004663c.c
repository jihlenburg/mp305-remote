/* Address: 0004663c; name: FUN_0004663c; body bytes: 60 */

undefined4 *
FUN_0004663c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 *local_18;
  
  local_18 = param_4;
  local_18 = (undefined4 *)FUN_0004a318(0xc);
  if (local_18 == (undefined4 *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  *local_18 = param_2;
  local_18[1] = param_4;
  local_18[2] = param_3;
  iVar1 = FUN_0003df08(param_1);
  if (iVar1 == 0) {
    FUN_0003de42(param_1,1,4);
  }
  FUN_0003de60(param_1,&local_18);
  return local_18;
}

