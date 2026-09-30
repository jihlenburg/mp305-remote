/* Address: 000666a0; name: FUN_000666a0; body bytes: 36 */

undefined4 * FUN_000666a0(undefined4 param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_000666c4(1,0,param_1);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[2] = 0;
    *puVar1 = 0;
    puVar1[3] = 0;
    FUN_000667a0(puVar1,0,0,0);
  }
  return puVar1;
}

