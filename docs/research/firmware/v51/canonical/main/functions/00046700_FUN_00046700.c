/* Address: 00046700; name: FUN_00046700; body bytes: 24 */

undefined4 FUN_00046700(int param_1)

{
  undefined4 *puVar1;
  
  if ((*(short *)(param_1 + 8) == 0xe) &&
     (puVar1 = (undefined4 *)FUN_0004673a(), puVar1 != (undefined4 *)0x0)) {
    return *puVar1;
  }
  return 0;
}

