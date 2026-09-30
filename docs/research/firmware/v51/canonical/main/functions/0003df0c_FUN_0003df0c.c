/* Address: 0003df0c; name: FUN_0003df0c; body bytes: 52 */

undefined4 FUN_0003df0c(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  
  puVar1 = (undefined4 *)FUN_0004a318(8);
  uVar3 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    iVar2 = FUN_0005285c(0x3df99,0,puVar1);
    if (iVar2 == 0) {
      FUN_00046bec(puVar1);
      return 0;
    }
    *puVar1 = param_1;
    puVar1[1] = param_2;
    FUN_00052ac6(iVar2,1);
    uVar3 = 1;
  }
  return uVar3;
}

