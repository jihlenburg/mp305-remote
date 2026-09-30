/* Address: 000472e0; name: FUN_000472e0; body bytes: 14 */

undefined4 FUN_000472e0(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((param_1 != 0) && (uVar1 = 0, *(undefined4 **)(param_1 + 0xc) != (undefined4 *)0x0)) {
    uVar1 = **(undefined4 **)(param_1 + 0xc);
  }
  return uVar1;
}

