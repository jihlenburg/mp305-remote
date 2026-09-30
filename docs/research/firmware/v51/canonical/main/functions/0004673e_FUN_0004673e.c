/* Address: 0004673e; name: FUN_0004673e; body bytes: 24 */

undefined4 FUN_0004673e(int param_1)

{
  undefined4 *puVar1;
  
  if ((*(short *)(param_1 + 8) == 0xf) &&
     (puVar1 = (undefined4 *)FUN_0004673a(), puVar1 != (undefined4 *)0x0)) {
    return *puVar1;
  }
  return 0;
}

