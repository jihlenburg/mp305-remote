/* Address: 000263a0; name: FUN_000263a0; body bytes: 122 */

undefined4 FUN_000263a0(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = FUN_0004c924(param_1,0,0x6e);
  if ((((iVar2 != 0) || (iVar2 = FUN_0004c924(param_1,0,0x6c), iVar2 != 0x100)) ||
      (iVar2 = FUN_0004c924(param_1,0,0x6d), iVar2 != 0x100)) ||
     ((iVar2 = FUN_0004c924(param_1,0,0x71), iVar2 != 0 ||
      (iVar2 = FUN_0004c924(param_1,0,0x72), iVar2 != 0)))) {
    return 2;
  }
  cVar1 = FUN_0004c924(param_1,0,0x60);
  if ((cVar1 == -1) &&
     ((iVar2 = FUN_0004c924(param_1,0,0x73), iVar2 == 0 &&
      (cVar1 = FUN_0004c924(param_1,0,0x67), cVar1 == '\0')))) {
    return 0;
  }
  return 1;
}

