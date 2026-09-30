/* Address: 0005fa74; name: FUN_0005fa74; body bytes: 104 */

void FUN_0005fa74(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  
  if (DAT_1fffaad7 == '\0') {
    FUN_00046756(param_1);
    uVar3 = FUN_0005230c();
    if (uVar3 < 2) {
      FUN_00046756(param_1);
      cVar1 = FUN_0005230c();
      DAT_1fffaae2 = '\x03' - cVar1;
    }
    else {
      FUN_00046756(param_1);
      cVar1 = FUN_0005230c();
      DAT_1fffaae2 = '\x04' - cVar1;
    }
  }
  else {
    FUN_00046756(param_1);
    iVar2 = FUN_0005230c();
    if (iVar2 == 0) {
      DAT_1fffaae3 = '\x03';
    }
    else {
      FUN_00046756(param_1);
      cVar1 = FUN_0005230c();
      DAT_1fffaae3 = '\x04' - cVar1;
    }
  }
  DAT_1ffe02b4 = 0;
  FUN_0001cb8c(0xf);
  return;
}

