/* Address: 000106d4; name: FUN_000106d4; body bytes: 26 */

void FUN_000106d4(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  puVar1 = (undefined4 *)FUN_00020158();
  uVar2 = *puVar1;
  FUN_00010d1c(param_1,0,10);
  *puVar1 = uVar2;
  return;
}

