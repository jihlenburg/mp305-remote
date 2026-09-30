/* Address: 0005e210; name: FUN_0005e210; body bytes: 86 */

void FUN_0005e210(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar1 = FUN_0004bb48();
  if (iVar1 != 0) {
    iVar2 = *(int *)(iVar1 + 0x2c0);
    if (iVar2 != 0) {
      FUN_0004e5a6(iVar2,0x2a,0);
    }
    FUN_0004e5a6(param_1,0x2b,0);
    *(int *)(iVar1 + 0x2c0) = param_1;
    *(undefined4 *)(iVar1 + 0x2cc) = 0;
    FUN_0004e5a6(param_1,0x2c,0);
    if (iVar2 != 0) {
      FUN_0004e5a6(iVar2,0x2d,0);
    }
    FUN_0004d3d8(param_1);
    return;
  }
  return;
}

