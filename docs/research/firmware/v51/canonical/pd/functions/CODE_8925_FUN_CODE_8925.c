/* Address: CODE:8925; name: FUN_CODE_8925; body bytes: 47 */

void FUN_CODE_8925(undefined1 param_1,undefined1 param_2)

{
  undefined1 uVar1;
  undefined2 uStack_1;
  
  uStack_1 = (undefined1 *)
             CONCAT11('\x06' - (((0xfaU < (byte)(DAT_INTMEM_b3 * '\f')) << 7) >> 7),
                      DAT_INTMEM_b3 * '\f' + 5);
  uVar1 = BANK0_R5;
  DAT_EXTMEM_04ad = param_2;
  FUN_CODE_ade7(param_2,2);
  *uStack_1 = param_1;
  uStack_1[1] = uVar1;
  return;
}

