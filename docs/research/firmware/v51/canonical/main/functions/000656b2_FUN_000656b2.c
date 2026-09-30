/* Address: 000656b2; name: FUN_000656b2; body bytes: 4 */

/* Recovered from stored Thumb pointer at 000161b8; callback identification is inferred until
   reviewed. */

uint FUN_000656b2(uint *param_1,uint param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  uint uVar5;
  
  uVar5 = 0;
  FUN_00065c04();
  *param_1 = *param_1 | param_2;
  puVar4 = (uint *)param_1[4];
LAB_00066540:
  do {
    puVar1 = puVar4;
    if (puVar1 == param_1 + 3) {
      *param_1 = *param_1 & ~uVar5;
      FUN_00066f6c();
      return *param_1;
    }
    puVar4 = (uint *)puVar1[1];
    uVar3 = *puVar1 & 0xff000000;
    uVar2 = *puVar1 & 0xffffff;
    if ((int)(uVar3 << 5) < 0) goto LAB_00066528;
  } while ((*param_1 & uVar2) == 0);
  goto LAB_0006652e;
LAB_00066528:
  if ((uVar2 & ~*param_1) == 0) {
LAB_0006652e:
    if ((int)(uVar3 << 7) < 0) {
      uVar5 = uVar5 | uVar2;
    }
    FUN_00065b08(puVar1,*param_1 | 0x2000000);
  }
  goto LAB_00066540;
}

