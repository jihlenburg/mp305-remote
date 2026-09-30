/* Address: 000408b0; name: FUN_000408b0; body bytes: 34 */

undefined4 FUN_000408b0(undefined4 *param_1)

{
  undefined4 uVar1;
  
  if ((param_1 != (undefined4 *)0x0) ||
     (uVar1 = 0, param_1 = DAT_2003a434, DAT_2003a434 != (undefined4 *)0x0)) {
    if (((*(byte *)(param_1 + 0xbc) & 7) == 1) || ((*(byte *)(param_1 + 0xbc) & 7) == 3)) {
      return param_1[1];
    }
    uVar1 = *param_1;
  }
  return uVar1;
}

