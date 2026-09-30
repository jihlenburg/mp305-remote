/* Address: 0005adc8; name: FUN_0005adc8; body bytes: 62 */

void FUN_0005adc8(int param_1)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar1 = FUN_0004ba5c();
  for (uVar2 = 0; uVar2 < uVar1; uVar2 = uVar2 + 1) {
    uVar3 = *(undefined4 *)(**(int **)(param_1 + 8) + uVar2 * 4);
    FUN_0004d3d8(uVar3);
    FUN_0004e5a6(uVar3,0x2f,0);
    FUN_0004d3d8(uVar3);
    FUN_0005adc8(uVar3);
  }
  return;
}

