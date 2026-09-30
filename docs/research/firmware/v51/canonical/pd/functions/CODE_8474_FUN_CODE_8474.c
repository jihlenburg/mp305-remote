/* Address: CODE:8474; name: FUN_CODE_8474; body bytes: 26 */

void FUN_CODE_8474(undefined1 param_1,undefined1 *param_2,char param_3,undefined1 param_4,
                  undefined1 param_5)

{
  *param_2 = param_1;
  FUN_CODE_ad3d(param_3 + '\x01');
  FUN_CODE_ad6d(CONCAT11(param_4,param_5) + 3);
  DAT_INTMEM_a6 = DAT_INTMEM_a6 + 1 & 0x1f;
  DAT_INTMEM_a4 = DAT_INTMEM_a4 + '\x01';
  return;
}

