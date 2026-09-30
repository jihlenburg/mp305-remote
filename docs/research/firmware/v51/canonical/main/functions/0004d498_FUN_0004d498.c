/* Address: 0004d498; name: FUN_0004d498; body bytes: 44 */

undefined4 FUN_0004d498(undefined4 param_1)

{
  short sVar1;
  int iVar2;
  
  iVar2 = FUN_0004cd92(param_1,0x60001);
  if (((iVar2 == 0) && (iVar2 = FUN_0004bc8c(param_1), iVar2 != 0)) &&
     (sVar1 = FUN_0004c924(iVar2,0,0x16), sVar1 != 0)) {
    return 1;
  }
  return 0;
}

